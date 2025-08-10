#include <iostream>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <FrogEngine.h>

namespace FrogEngine {
    FrogEngine::FrogEngine() : vulkan(this), graphicsEngine(this), assetEngine(this){};
    FrogEngine::~FrogEngine() = default;

    void FrogEngine::StartFrogEngine() {
        std::println(std::cout, "------------Starting-Window-Creation------------");
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");
        std::println(std::cout, "Initialized GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window.InitWindow();
        std::println(std::cout, "------------Finished-Window-Creation------------\n");


        vulkan.StartVulkan();
        graphicsEngine.StartGraphicsEngine();
        assetEngine.StartAssetLoader();
    }
} // namespace FrogEngine