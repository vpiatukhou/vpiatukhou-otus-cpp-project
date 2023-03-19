set(Boost_USE_STATIC_LIBS ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED program_options) #TODO set exact version

add_library(webserver STATIC Application.cpp
                             ApplicationConfig.cpp
                             RequestDispatcher.cpp
                             ProgramOptions.cpp
                             StaticResouceController.cpp
                             HttpServer.cpp
                             HttpsServer.cpp
                             MediaTypeResolver.cpp
                             HttpsConnection.cpp)
add_executable(webserver_cli Main.cpp)

#rename the executable to "webserver"
set_target_properties(webserver_cli PROPERTIES OUTPUT_NAME webserver)

target_include_directories(webserver PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(webserver Boost::program_options crypto ssl ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(webserver_cli PRIVATE webserver)

#BEGIN release
install(TARGETS webserver_cli)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END
