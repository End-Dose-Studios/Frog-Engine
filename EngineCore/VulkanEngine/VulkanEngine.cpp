#include "VulkanEngine.h"

namespace EngineCore {
    VulkanEngine::VulkanEngine() = default;
    VulkanEngine::~VulkanEngine() {
        DestroyDebugMessenger();
        DestroyInstance();
    };

    void VulkanEngine::InitVulkanEngine() {
        CreateInstance();
        CreateDebugMessenger();
        GetPhysicalDevices();
    }


} // namespace EngineCore