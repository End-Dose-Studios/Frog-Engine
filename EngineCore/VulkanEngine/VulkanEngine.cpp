#include "VulkanEngine.h"

#include "../EngineCore.h"

namespace EngineCore {
    VulkanEngine::VulkanEngine() = default;
    VulkanEngine::~VulkanEngine() {
        DestroyLogicalDevice();
        DestroySurface();
        DestroyDebugMessenger();
        DestroyInstance();
    };

    void VulkanEngine::InitVulkanEngine(const EngineCore *engine_core) {
        windowPtr = engine_core->windowPtr;

        CreateInstance();
        CreateDebugMessenger();
        GetPhysicalDevices();
        CreateSurface();
        GetQueueFamilyIndices();
        CreateLogicalDevice();
    }


} // namespace EngineCore