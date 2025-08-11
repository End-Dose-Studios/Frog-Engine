#include <iostream>

#include <FrogEngine.h>
#include <GraphicsEngine.h>

namespace FrogEngine::Graphics {
    GraphicsEngine::GraphicsEngine(FrogEngine *frog_engine_ptr) {
        frogEnginePtr = frog_engine_ptr;
        windowPtr = frog_engine_ptr->window.window;
    };

    GraphicsEngine::~GraphicsEngine() {
        destroySwapchainImages();
        destroySwapchain();
    }

    void GraphicsEngine::startGraphicsEngine() {
        std::println(std::cout, "------------Starting-Vulkan-Graphics------------");
        createSwapchain();
        createSwapchainImages();
        std::println(std::cout, "------------Finished-Vulkan-Graphics------------\n");
    }
}