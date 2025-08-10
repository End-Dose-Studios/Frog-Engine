#include <iostream>

#include "../EngineCore/EngineCore.h"
#include "GraphicsEngine.h"

namespace Graphics {
    GraphicsEngine::GraphicsEngine(EngineCore::EngineCore *engine_core_ptr) {
        engineCorePtr = engine_core_ptr;
        windowPtr = engine_core_ptr->window.window;
    };

    GraphicsEngine::~GraphicsEngine() {
        DestroySwapchainImages();
        DestroySwapChain();
    }

    void GraphicsEngine::StartGraphicsEngine() {
        std::println(std::cout, "------------Starting-Vulkan-Graphics------------");
        CreateSwapchain();
        CreateSwapchainImages();
        std::println(std::cout, "------------Finished-Vulkan-Graphics------------\n");
    }
} // namespace Graphics