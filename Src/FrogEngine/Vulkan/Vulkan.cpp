#include <iostream>

#include <FrogEngine.h>
#include <Vulkan.h>

namespace FrogEngine {
    Vulkan::Vulkan(FrogEngine *frog_engine_ptr) { frogEnginePtr = frog_engine_ptr; }

    Vulkan::~Vulkan() {
        DestroyLogicalDevice();
        DestroySurface();
        DestroyDebugMessenger();
        DestroyInstance();
    }

    void Vulkan::StartVulkan() {
        std::println(std::cout, "-------------Starting-Vulkan-Engine-------------");
        CreateInstance();
        CreateDebugMessenger();
        GetPhysicalDevices();
        CreateSurface();
        GetQueueFamilyIndices();
        CreateLogicalDevice();
        std::println(std::cout, "-------------Finished-Vulkan-Engine-------------\n");
    }

} // namespace FrogEngine
