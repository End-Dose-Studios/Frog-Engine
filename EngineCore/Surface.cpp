#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "EngineCore.h"

namespace EngineCore {
    void EngineCore::CreateSurface() {
        VkSurfaceKHR surface;
        glfwCreateWindowSurface(vkInstance, window.window, nullptr, &surface);
        vkSurface = surface;
        println(std::cout, "----------Surface-Created---------");
    }

    void EngineCore::DestroySurface() const {
        vkInstance.destroySurfaceKHR(vkSurface);
        println(std::cout, "---------Surface-Destroyed--------");
    }
} // namespace EngineCore