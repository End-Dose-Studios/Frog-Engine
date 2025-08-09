#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "VulkanEngine.h"

namespace EngineCore {
    void VulkanEngine::CreateSurface() {
        VkSurfaceKHR surface;
        glfwCreateWindowSurface(vkInstance, windowPtr, nullptr, &surface);
        vkSurface = surface;
        println(std::cout, "----------Surface-Created---------");
    }

    void VulkanEngine::DestroySurface() const {
        vkInstance.destroySurfaceKHR(vkSurface);
        println(std::cout, "---------Surface-Destroyed--------");
    }

    const vk::SurfaceKHR *VulkanEngine::GetSurfacePtr() const { return &vkSurface; }


} // namespace EngineCore