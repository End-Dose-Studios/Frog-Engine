#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

class GLFWwindow;
namespace EngineCore {
    class VulkanEngine;
}

namespace Graphics {
    struct SwapchainDetails {
        vk::SurfaceCapabilitiesKHR capabilities{};
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class VulkanGraphics {
    public:
        VulkanGraphics();
        ~VulkanGraphics();

        void InitVulkanGraphics(EngineCore::VulkanEngine *vulkan_engine_ptr);

    private:
        EngineCore::VulkanEngine *vulkanEnginePtr;
        GLFWwindow *windowPtr;

        void CreateSwapchain();
        void DestroySwapChain() const;
        vk::SwapchainKHR vkSwapchain;
        vk::SurfaceFormatKHR swapchainSurfaceFormat;
        vk::PresentModeKHR swapchainPresentMode;
        vk::Extent2D swapchainExtent;
        SwapchainDetails swapchainDetails{};

        void CreateSwapchainImages();
        void DestroySwapchainImages() const;
        std::vector<vk::Image> swapchainImages;
        std::vector<vk::ImageView> swapchainImageViews;
    };
} // namespace Graphics
