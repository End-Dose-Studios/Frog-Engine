#pragma once

class GLFWwindow;
namespace EngineCore {
    class EngineCore;
    class VulkanEngine;
} // namespace EngineCore

namespace Graphics {
    class GraphicsEngine {
    public:
        explicit GraphicsEngine(EngineCore::EngineCore *engine_core_ptr);
        ~GraphicsEngine();

        void StartGraphicsEngine();

    private:
        EngineCore::EngineCore *engineCorePtr;
        EngineCore::VulkanEngine *vulkanEnginePtr;
        GLFWwindow *windowPtr;
    };
} // namespace Graphics