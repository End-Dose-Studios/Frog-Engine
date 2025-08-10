#include <iostream>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "EngineCore.h"

namespace EngineCore {
    EngineCore::EngineCore() = default;
    EngineCore::~EngineCore() {
        println(std::cout, "---------------Cleaning-Up-Vulkan---------------");
        DestroyLogicalDevice();
        DestroySurface();
        DestroyDebugMessenger();
        DestroyInstance();
    }

    void EngineCore::StartEngineCore() {
        println(std::cout, "------------Starting-Window-Creation------------");
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
        println(std::cout, "Initialized GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window.InitWindow();
        println(std::cout, "------------Finished-Window-Creation------------\n");

        println(std::cout, "-------------Starting-Vulkan-Engine-------------");
        CreateInstance();
        CreateDebugMessenger();
        GetPhysicalDevices();
        CreateSurface();
        GetQueueFamilyIndices();
        CreateLogicalDevice();
        println(std::cout, "-------------Finished-Vulkan-Engine-------------\n");
    }
} // namespace EngineCore