file(GLOB_RECURSE EXAMPLE_SOURCES "src/*.cpp")

add_executable(
    example_${BUILD_EXAMPLE}
    ${EXAMPLE_SOURCES}
    "${VENDOR_DIR}/glad/src/glad.c"
)

target_include_directories(example_${BUILD_EXAMPLE} PRIVATE "${VENDOR_DIR}/glad/include")

target_link_libraries(
    example_${BUILD_EXAMPLE} PRIVATE
    glfw
    glm
    Threads::Threads
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)

set_target_properties(example_${BUILD_EXAMPLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${BUILD_EXAMPLE}/bin"
)
