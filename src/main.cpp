#include "Application.h"
#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Initializing Engine Architecture ..." << std::endl;

    Application app("OpenGL", 1280, 720);
    app.Run();

    std::cout << "Engine Shutdown Sequence Complete." << std::endl;
    return 0;
}
