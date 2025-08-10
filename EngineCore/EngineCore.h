#pragma once

#include "VulkanEngine/VulkanEngine.h"
#include "Window/Window.h"

enum class GraphicsAPI : uint8_t {
    Vulkan = 0,
    OpenGL = 1,
    None = 2,
};

namespace EngineCore {
    class EngineCore {
    public:
        EngineCore();
        ~EngineCore();

        void StartEngineCore();
        
        Vulkan::Engine vulkanEngine;

        GraphicsAPI selectedAPI = GraphicsAPI::None;
        GLFWwindow *windowPtr{nullptr};

    private:
        Window window;
    };
} // namespace EngineCore