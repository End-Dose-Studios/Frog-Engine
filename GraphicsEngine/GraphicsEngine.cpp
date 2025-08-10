#include <iostream>

#include "../EngineCore/EngineCore.h"
#include "GraphicsEngine.h"

namespace Graphics {
    GraphicsEngine::GraphicsEngine(EngineCore::EngineCore *engine_core_ptr) {
        engineCorePtr = engine_core_ptr;
        windowPtr = engine_core_ptr->windowPtr;
    };

    GraphicsEngine::~GraphicsEngine() = default;

    void GraphicsEngine::StartGraphicsEngine() {
        if (engineCorePtr->selectedAPI == GraphicsAPI::Vulkan) {
            std::println(std::cout, "------------Starting-Vulkan-Graphics------------");
            vulkanGraphics.InitGraphics(&engineCorePtr->vulkanEngine);
            std::println(std::cout, "------------Finished-Vulkan-Graphics------------\n");
        }
        else if (engineCorePtr->selectedAPI == GraphicsAPI::OpenGL) {
            // TODO
        }
    }

} // namespace Graphics