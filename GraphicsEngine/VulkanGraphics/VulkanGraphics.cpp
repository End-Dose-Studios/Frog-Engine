#include "VulkanGraphics.h"
#include "../../EngineCore/VulkanEngine/VulkanEngine.h"

namespace Graphics {
    VulkanGraphics::VulkanGraphics() = default;
    VulkanGraphics::~VulkanGraphics() {
        DestroySwapchainImages();
        DestroySwapChain();
    };

    void VulkanGraphics::InitVulkanGraphics(EngineCore::VulkanEngine *vulkan_engine_ptr) {
        vulkanEnginePtr = vulkan_engine_ptr;
        windowPtr = vulkan_engine_ptr->windowPtr;

        CreateSwapchain();
        CreateSwapchainImages();
    }


} // namespace Graphics