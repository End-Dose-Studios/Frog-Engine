#include "GraphicsEngine.h"
#include "../EngineCore/EngineCore.h"

namespace Graphics {
    GraphicsEngine::GraphicsEngine(EngineCore::EngineCore *engine_core_ptr) {
        engineCorePtr = engine_core_ptr;
        vulkanEnginePtr = engine_core_ptr->GetVulkanEnginePtr();
        windowPtr = engine_core_ptr->windowPtr;
    };

    GraphicsEngine::~GraphicsEngine() = default;

    void GraphicsEngine::StartGraphicsEngine() {}


} // namespace Graphics