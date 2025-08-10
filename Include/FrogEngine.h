#pragma once

#include <AssetEngine.h>
#include <GraphicsEngine.h>
#include <Vulkan.h>
#include <Window.h>

namespace FrogEngine {
    class FrogEngine {
    public:
        FrogEngine();
        ~FrogEngine();

        void StartFrogEngine();

        Vulkan vulkan;
        Graphics::GraphicsEngine graphicsEngine;
        Assets::AssetEngine assetEngine;
        Window window;
    };
} // namespace FrogEngine