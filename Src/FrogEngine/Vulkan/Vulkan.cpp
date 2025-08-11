#include <iostream>

#include <FrogEngine.h>
#include <Vulkan.h>

namespace FrogEngine::Vulkan {
    Vulkan::Vulkan(FrogEngine *frog_engine_ptr) { frogEnginePtr = frog_engine_ptr; }

    Vulkan::~Vulkan() {
        destroyLogicalDevice();
        destroySurface();
        destroyDebugMessenger();
        destroyInstance();
    }

    void Vulkan::initVulkan() {
        std::println(std::cout, "-------------Starting-Vulkan-Engine-------------");
        createInstance();
        createDebugMessenger();
        getPhysicalDevices();
        createSurface();
        getQueueFamilyIndices();
        createLogicalDevice();
        std::println(std::cout, "-------------Finished-Vulkan-Engine-------------\n");
    }

}
