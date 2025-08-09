#ifdef NDEBUG
#include <fstream>
#include <iostream>
#endif

#include <GLFW/glfw3.h>

#include "AssetEngine/AssetEngine.h"
#include "EngineCore/EngineCore.h"
#include "GraphicsEngine/GraphicsEngine.h"

int main() {
#ifdef NDEBUG
    const std::ofstream log("log.txt");
    std::cout.rdbuf(log.rdbuf());
    std::cerr.rdbuf(log.rdbuf());
#endif

    EngineCore::EngineCore engine_core;
    engine_core.StartEngineCore();
    GLFWwindow *window = engine_core.windowPtr;

    Graphics::GraphicsEngine graphics_engine(&engine_core);
    graphics_engine.StartGraphicsEngine();

    // TODO Create Asset Manager
    Assets::AssetEngine asset_engine;
    asset_engine.InitLoader();
    Assets::Package *global_pack = asset_engine.LoadPackage("Global");
    asset_engine.UnloadPackage(global_pack);

    // TODO Relocate To Engine Core
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    println(std::cout, "\n-------------------Cleaning-Up------------------");
    return EXIT_SUCCESS;
}
