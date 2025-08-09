#pragma once

#include "VulkanEngine/VulkanEngine.h"
#include "Window/Window.h"

enum class GraphicsAPI : uint8_t {
    Vulkan = 0,
    OpenGL = 1,
};

namespace EngineCore {
    class EngineCore {
    public:
        EngineCore();
        ~EngineCore();

        void StartEngineCore();

        Vulkan::Engine *GetVulkanEnginePtr();

        GraphicsAPI selectedAPI = GraphicsAPI::Vulkan;
        GLFWwindow *windowPtr{nullptr};

    private:
        Window window;

        Vulkan::Engine vulkanEngine;
    };
} // namespace EngineCore