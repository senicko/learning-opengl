Playing with graphics programming in OpenGL.

## Building

To build run

```
cmake -B build && cmake --build build
```

which creates a binary at `build/bin/learning-opengl`.

> Note that this setup was tested on MacOS only, so it might require CMake fixes on other OS.

## Examples

Build system supports writing smaller example apps (to play with some specific things in isolated env). To build an example run

```
cmake -B build -DBUILD_EXAMPLE=triangle && cmake --build build
```

This creates a binary at `build/examples/<examle_name>/bin/example_<example_name>`.

# Why

The goal of this "project" is to explore fundamentals of GPU programming. As OpenGL is quite mature there are a lot of resources around it which makes it easier to learn and understand how things work before moving to something like Metal.
