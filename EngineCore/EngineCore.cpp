#include <iostream>

#include <vulkan/vulkan.hpp>

#include "EngineCore.h"

#include <GLFW/glfw3.h>

namespace {
    GraphicsAPI detectAPI() {
        try {
            const vk::InstanceCreateInfo instance_info{}; // NOLINT

            if (vk::UniqueInstance instance = vk::createInstanceUnique(instance_info);
                instance->enumeratePhysicalDevices().empty()) {
                std::println(std::cerr,
                             "No Vulkan-compatible GPUs detected.\nFalling back to OpenGL");
                return GraphicsAPI::OpenGL;
            }

            std::println(std::cout, "Vulkan instance and compatible device found.");
            return GraphicsAPI::Vulkan;
        }
        catch (const vk::SystemError &err) {
            std::println(std::cerr, "Vulkan system error: {}", err.what());
            return GraphicsAPI::OpenGL;
        }
        catch (const std::exception &err) {
            std::println(std::cerr, "General System exception: {}", err.what());
            return GraphicsAPI::OpenGL;
        }
        catch (...) {
            std::println(std::cerr, "Unknown error while testing Vulkan support.");
            return GraphicsAPI::OpenGL;
        }
    }
} // namespace

namespace EngineCore {
    EngineCore::EngineCore() = default;
    EngineCore::~EngineCore() = default;

    GLFWwindow *EngineCore::GetWindowPtr() const { return window.GetWindowPtr(); }
    VulkanEngine *EngineCore::GetVulkanEnginePtr() { return &VulkanEngine; }

    void EngineCore::StartEngineCore() {
        selectedAPI = detectAPI();

        if (selectedAPI == GraphicsAPI::Vulkan) {
            try {
                println(std::cout, "------------Starting-Window-Creation------------");
                if (!glfwInit())
                    throw std::runtime_error("Failed to initialize GLFW");
                println(std::cout, "Initialized GLFW");
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                window.InitWindow();
                println(std::cout, "------------Finished-Window-Creation------------");
                println(std::cout, "--------------Starting-Vulkan-Base--------------");
                VulkanEngine.InitVulkanEngine();
                println(std::cout, "--------------Finished-Vulkan-Base--------------");
            }
            catch (const vk::SystemError &err) {
                std::println(std::cerr, "Vulkan system error: {}", err.what());
                selectedAPI = GraphicsAPI::OpenGL;
            }
            catch (const std::exception &err) {
                std::println(std::cerr, "General System exception: {}", err.what());
                selectedAPI = GraphicsAPI::OpenGL;
            }
            catch (...) {
                std::println(std::cerr, "Unknown error while starting Vulkan.");
                selectedAPI = GraphicsAPI::OpenGL;
            }
        }
        if (selectedAPI == GraphicsAPI::OpenGL) {
            println(std::cout, "------------Starting-Window-Creation------------");
            if (!glfwInit())
                throw std::runtime_error("Failed to initialize GLFW");
            println(std::cout, "Initialized GLFW");
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            window.InitWindow();
            println(std::cout, "------------Finished-Window-Creation------------");
            println(std::cout, "------------Starting-OpenGL-Creation------------");
            // TODO: Create OpenGL Stuff
            println(std::cout, "------------Finished-OpenGL-Creation------------");
        }
    }
} // namespace EngineCore