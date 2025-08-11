#include <iostream>

#include <GLFW/glfw3.h>

#include "../../../Include/Window.h"

namespace FrogEngine::Window {
    Window::Window() = default;
    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    };

    void Window::initWindow() {
        std::println(std::cout, "------------Starting-Window-Creation------------");
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
        std::println(std::cout, "Initialized GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(width, height, "Frog Engine", nullptr, nullptr);
        if (window == nullptr || monitor == nullptr || mode == nullptr) {
            std::println(std::cout, "Failed to create GLFW window.\n");
            std::exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwGetWindowPos(window, &posX, &posY);
        std::println(std::cout, "Created Window\n  Size: (640 x 480)\n  TItle: Frog Engine");
        std::println(std::cout, "------------Finished-Window-Creation------------\n");
    }

    void Window::setFullscreen(const bool new_fullscreen) {
        if (fullscreen == new_fullscreen)
            return;

        fullscreen = new_fullscreen;
        if (fullscreen) {
            glfwGetWindowPos(window, &posX, &posY);
            glfwGetWindowSize(window, &width, &height);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
            return;
        }
        glfwSetWindowMonitor(window, nullptr, posX, posY, width, height, GLFW_DONT_CARE);
    }

    bool Window::getFullscreen() const { return fullscreen; }

}
