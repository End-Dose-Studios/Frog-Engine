#pragma once

#include <vulkan/vulkan.hpp>

struct GLFWwindow;
namespace EngineCore {
    class EngineCore;
} // namespace EngineCore

namespace Graphics {
    struct SwapchainDetails {
        vk::SurfaceCapabilitiesKHR capabilities{};
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class GraphicsEngine {
    public:
        explicit GraphicsEngine(EngineCore::EngineCore *engine_core_ptr);
        ~GraphicsEngine();

        void StartGraphicsEngine();

    private:
        EngineCore::EngineCore *engineCorePtr{nullptr};
        GLFWwindow *windowPtr{nullptr};

        void CreateSwapchain();
        void DestroySwapChain() const;
        vk::SwapchainKHR vkSwapchain{};
        vk::SurfaceFormatKHR swapchainSurfaceFormat{};
        vk::PresentModeKHR swapchainPresentMode{};
        vk::Extent2D swapchainExtent{};
        SwapchainDetails swapchainDetails{};

        void CreateSwapchainImages();
        void DestroySwapchainImages() const;
        std::vector<vk::Image> swapchainImages{};
        std::vector<vk::ImageView> swapchainImageViews{};
    };
} // namespace Graphics