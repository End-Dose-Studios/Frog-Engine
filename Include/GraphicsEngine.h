#pragma once

#include <list>

#include <vulkan/vulkan.hpp>

struct GLFWwindow;
using FrogAsset = const void *;
namespace FrogEngine {
    class FrogEngine;
}

namespace FrogEngine::Graphics {
    struct SwapchainDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    struct GraphicsPipeline {
        vk::Pipeline pipeline;
        vk::PipelineLayout pipelineLayout;

        vk::CommandBuffer commandBuffer;
    };

    class GraphicsEngine {
    public:
        explicit GraphicsEngine(FrogEngine *frog_engine_ptr);
        ~GraphicsEngine();

        void startGraphicsEngine();

        vk::RenderPass *createRenderPass();
        void destroyRenderPass(const vk::RenderPass *render_pass) const;

        GraphicsPipeline *createGraphicsPipeline(FrogAsset vert, FrogAsset frag,
                                                 const vk::RenderPass *render_pass);
        void destroyGraphicsPipeline(const GraphicsPipeline *graphics_pipeline) const;

    private:
        FrogEngine *frogEnginePtr{nullptr};
        GLFWwindow *windowPtr{nullptr};

        std::vector<vk::CommandPool> commandPools;
        vk::CommandPool secondaryPool;
        std::vector<vk::CommandBuffer> commandBuffers;

        std::list<vk::RenderPass> renderPasses;
        std::list<GraphicsPipeline> graphicPipelines;

        void createSwapchain();
        void destroySwapchain() const;
        vk::SwapchainKHR vkSwapchain;
        vk::SurfaceFormatKHR swapchainSurfaceFormat;
        vk::PresentModeKHR swapchainPresentMode{};
        vk::Extent2D swapchainExtent;
        SwapchainDetails swapchainDetails;

        void createSwapchainImages();
        void destroySwapchainImages() const;
        std::vector<vk::Image> swapchainImages;
        std::vector<vk::ImageView> swapchainImageViews;
    };
}