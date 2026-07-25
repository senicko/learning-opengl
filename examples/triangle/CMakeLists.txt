file(GLOB_RECURSE EXAMPLE_SOURCES "src/*.cpp")

add_executable(
    example_${BUILD_EXAMPLE}
    ${EXAMPLE_SOURCES}
    "${VENDOR_DIR}/glad/src/glad.c"
)

target_include_directories(example_${BUILD_EXAMPLE} PRIVATE "include")
target_include_directories(example_${BUILD_EXAMPLE} PRIVATE "${VENDOR_DIR}/glad/include")

target_link_libraries(
    example_${BUILD_EXAMPLE} PRIVATE
    glfw
    glm
    Threads::Threads
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)

add_custom_command(TARGET example_${BUILD_EXAMPLE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:example_${BUILD_EXAMPLE}>/assets"
)

set_target_properties(example_${BUILD_EXAMPLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${BUILD_EXAMPLE}/bin"
)
