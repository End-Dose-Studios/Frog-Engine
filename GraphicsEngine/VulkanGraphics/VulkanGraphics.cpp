#include "VulkanGraphics.h"
#include "../../EngineCore/VulkanEngine/VulkanEngine.h"

namespace Graphics::Vulkan {
    Graphics::Graphics() = default;
    Graphics::~Graphics() {
        DestroySwapchainImages();
        DestroySwapChain();
    };

    void Graphics::InitGraphics(EngineCore::Vulkan::Engine *vulkan_engine_ptr) {
        vulkanEnginePtr = vulkan_engine_ptr;
        windowPtr = vulkan_engine_ptr->windowPtr;

        CreateSwapchain();
        CreateSwapchainImages();
    }


} // namespace Graphics::Vulkan