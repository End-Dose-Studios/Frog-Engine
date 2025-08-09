#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

class GLFWwindow;
namespace EngineCore::Vulkan {
    class Engine;
}

namespace Graphics::Vulkan {
    struct SwapchainDetails {
        vk::SurfaceCapabilitiesKHR capabilities{};
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class Graphics {
    public:
        Graphics();
        ~Graphics();

        void InitGraphics(EngineCore::Vulkan::Engine *vulkan_engine_ptr);

    private:
        EngineCore::Vulkan::Engine *vulkanEnginePtr;
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
} // namespace Graphics::Vulkan
