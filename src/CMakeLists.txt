set(PROJECT_SOURCES
    Controler.cpp
    Bird.cpp
    City.cpp
    Scenario.cpp
    Scenario1.cpp
    Scenario2.cpp
    Scenario3.cpp
    Scenario4.cpp
    Scenario5.cpp
    Scenario6.cpp
    Scenario7~.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# Specify the directories where the headers and libraries are located

include_directories(${RAYLIB_PATH}/include)

link_directories(${RAYLIB_PATH}/lib)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()