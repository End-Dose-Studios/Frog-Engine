#include <iostream>

#include <FrogEngine.h>
#include <GraphicsEngine.h>

namespace Graphics {
    GraphicsEngine::GraphicsEngine(FrogEngine::FrogEngine *frog_engine_ptr) {
        frogEnginePtr = frog_engine_ptr;
        windowPtr = frog_engine_ptr->window.window;
    };

    GraphicsEngine::~GraphicsEngine() {
        DestroySwapchainImages();
        DestroySwapchain();
    }

    void GraphicsEngine::StartGraphicsEngine() {
        std::println(std::cout, "------------Starting-Vulkan-Graphics------------");
        CreateSwapchain();
        CreateSwapchainImages();
        std::println(std::cout, "------------Finished-Vulkan-Graphics------------\n");
    }
} // namespace Graphics