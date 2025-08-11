#pragma once

#include <AssetEngine.h>
#include <GraphicsEngine.h>
#include <Vulkan.h>
#include <Window.h>

namespace FrogEngine {
    using FrogAsset = const void *;
    using Package = std::list<Assets::Package>::iterator;
    using GraphicsPipeline = Graphics::GraphicsPipeline;

    class FrogEngine {
    public:
        FrogEngine();
        ~FrogEngine();

        void startFrogEngine();

        Window::Window window;
        Vulkan::Vulkan vulkan;
        Graphics::GraphicsEngine graphicsEngine;
        Assets::AssetEngine assetEngine;
    };
}