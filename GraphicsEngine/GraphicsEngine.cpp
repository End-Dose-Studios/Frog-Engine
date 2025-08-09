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
            println(std::cout, "------------Starting-Vulkan-Graphics------------");
            vulkanGraphics.InitGraphics(engineCorePtr->GetVulkanEnginePtr());
            println(std::cout, "------------Finished-Vulkan-Graphics------------\n");
        }
        else if (engineCorePtr->selectedAPI == GraphicsAPI::OpenGL) {
            // TODO
        }
    }

} // namespace Graphics