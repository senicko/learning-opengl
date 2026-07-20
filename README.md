Playing with graphics programming in OpenGL. To build run

```
cmake -B build -S . && cmake --build build
```

Note that this setup was tested on MacOS, so it might require CMake fixes on other OS.

---

The goal of this "project" is to explore how GPU programming works with something easier (OpenGL) and then look at Metal.
Source code is full of hand-written comments explaining what is going on (e.g. based on docs.gl for gl* functions)
