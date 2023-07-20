FROM gcc:latest
RUN apt-get update && apt-get install -y \
    libboost-dev \
    libboost-log-dev \
    libboost-program-options-dev \
    libgtest-dev \
    cmake build-essential gdb

#build the application
WORKDIR /usr/src/app/src/
COPY . .
WORKDIR /usr/src/app/build/

RUN rm -rf * && \
    cmake ../src/ -DBUILD_DEMO=ON && \
    cmake --build .

#run the application
CMD ["./demo/demo"]