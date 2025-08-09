#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "VulkanEngine.h"

namespace EngineCore::Vulkan {
    void Engine::CreateSurface() {
        VkSurfaceKHR surface;
        glfwCreateWindowSurface(vkInstance, windowPtr, nullptr, &surface);
        vkSurface = surface;
        println(std::cout, "----------Surface-Created---------");
    }

    void Engine::DestroySurface() const {
        vkInstance.destroySurfaceKHR(vkSurface);
        println(std::cout, "---------Surface-Destroyed--------");
    }

    const vk::SurfaceKHR *Engine::GetSurfacePtr() const { return &vkSurface; }


} // namespace EngineCore::Vulkan