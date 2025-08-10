#include <iostream>

#include <GLFW/glfw3.h>

#include "../../../Include/Window.h"

namespace FrogEngine {
    Window::Window() = default;
    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    };

    void Window::InitWindow() {
        if (window) {
            glfwDestroyWindow(window);
            std::println(std::cout, "Destroyed Previous Window");
        }

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
    }

    void Window::SetFullscreen(const bool new_fullscreen) {
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

    bool Window::GetFullscreen() const { return fullscreen; }

} // namespace FrogEngine
