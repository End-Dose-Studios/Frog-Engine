#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <FrogEngine.h>

namespace FrogEngine::Vulkan {
    void Vulkan::createSurface() {
        VkSurfaceKHR surface{VK_NULL_HANDLE};
        glfwCreateWindowSurface(vkInstance, frogEnginePtr->window.window, nullptr, &surface);
        vkSurface = surface;
        std::println(std::cout, "----------Surface-Created---------");
    }

    void Vulkan::destroySurface() const {
        vkInstance.destroySurfaceKHR(vkSurface);
        std::println(std::cout, "---------Surface-Destroyed--------");
    }
}