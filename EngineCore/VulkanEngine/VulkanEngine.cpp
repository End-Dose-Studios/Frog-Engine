#include "VulkanEngine.h"
#include "../EngineCore.h"

namespace EngineCore::Vulkan {
    Engine::Engine() = default;
    Engine::~Engine() {
        DestroyLogicalDevice();
        DestroySurface();
        DestroyDebugMessenger();
        DestroyInstance();
    };

    void Engine::InitEngine(const EngineCore *engine_core) {
        windowPtr = engine_core->windowPtr;

        CreateInstance();
        CreateDebugMessenger();
        GetPhysicalDevices();
        CreateSurface();
        GetQueueFamilyIndices();
        CreateLogicalDevice();
    }


} // namespace EngineCore::Vulkan