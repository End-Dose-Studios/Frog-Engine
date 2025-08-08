#pragma once

namespace EngineCore {
    class EngineCore;
    class VulkanEngine;
}

namespace Graphics {
    class GraphicsEngine {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void StartGraphicsEngine();

    private:
        EngineCore::EngineCore* engineCorePtr;
        EngineCore::VulkanEngine* engineVulkanPtr;
    };
}