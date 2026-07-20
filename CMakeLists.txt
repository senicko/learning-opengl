cmake_minimum_required(VERSION 4.4)
include(FetchContent)
project(learning-opengl LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable compiler-specific extensions to guarantee cross-platform compatibility
set(CMAKE_CXX_EXTENSIONS OFF)

# Variables pointing to current directory structure
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

# glfw
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.2
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

# Recursively find all C++ source files in src dir
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} ${VENDOR_DIR}/glad/src/glad.c)

# Tell CMake to look into /include for local header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${VENDOR_DIR}/glad/include)

# Copy the assets folder to executable directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Find the GLFW package installed via Homebrew.
# REQUIRED flag stops the build if the package is missing.
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw
  glm
  Threads::Threads
  OpenGL::GL
  ${CMAKE_DL_LIBS}
)
