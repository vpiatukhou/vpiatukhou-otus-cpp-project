find_package(Threads REQUIRED)
find_package(Boost 1.81.0 REQUIRED EXACT)

add_library(web_server STATIC Application.cpp
                              ApplicationConfig.cpp
                              RequestDispatcher.cpp
                              StaticResouceController.cpp
                              Server.cpp
                              SslServer.cpp
                              SslTcpConnection.cpp
                              TcpConnection.cpp
                              MediaTypeResolver.cpp)
add_executable(web_server_cli Main.cpp)

#rename the executable to "web_server"
set_target_properties(web_server_cli PROPERTIES OUTPUT_NAME web_server)

target_include_directories(web_server PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(web_server crypto ssl ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(web_server_cli PRIVATE web_server)

#BEGIN release
install(TARGETS web_server_cli)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END
