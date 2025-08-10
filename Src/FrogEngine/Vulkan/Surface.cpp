#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <FrogEngine.h>

namespace FrogEngine {
    void Vulkan::CreateSurface() {
        VkSurfaceKHR surface;
        glfwCreateWindowSurface(vkInstance, frogEnginePtr->window.window, nullptr, &surface);
        vkSurface = surface;
        std::println(std::cout, "----------Surface-Created---------");
    }

    void Vulkan::DestroySurface() const {
        vkInstance.destroySurfaceKHR(vkSurface);
        std::println(std::cout, "---------Surface-Destroyed--------");
    }
} // namespace FrogEngine