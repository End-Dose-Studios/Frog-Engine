#pragma once

#include "VulkanGraphics/VulkanGraphics.h"

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
        GLFWwindow *windowPtr;

        Vulkan::Graphics vulkanGraphics;
    };
} // namespace Graphics