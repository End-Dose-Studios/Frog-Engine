#pragma once

#include <vulkan/vulkan.hpp>

struct GLFWwindow;
namespace FrogEngine {
    class FrogEngine;
} // namespace FrogEngine

namespace Graphics {
    struct SwapchainDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    class GraphicsEngine {
    public:
        explicit GraphicsEngine(FrogEngine::FrogEngine *frog_engine_ptr);
        ~GraphicsEngine();

        void StartGraphicsEngine();

    private:
        FrogEngine::FrogEngine *frogEnginePtr{nullptr};
        GLFWwindow *windowPtr{nullptr};

        void CreateSwapchain();
        void DestroySwapchain() const;
        vk::SwapchainKHR vkSwapchain;
        vk::SurfaceFormatKHR swapchainSurfaceFormat;
        vk::PresentModeKHR swapchainPresentMode{};
        vk::Extent2D swapchainExtent;
        SwapchainDetails swapchainDetails;

        void CreateSwapchainImages();
        void DestroySwapchainImages() const;
        std::vector<vk::Image> swapchainImages;
        std::vector<vk::ImageView> swapchainImageViews;
    };
} // namespace Graphics