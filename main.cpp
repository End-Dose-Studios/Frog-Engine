#ifdef NDEBUG
#include <fstream>
#include <iostream>
#endif

#include <GLFW/glfw3.h>

#include "EngineCore/EngineCore.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "Loader/Loader.h"

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
    Resources::Loader loader;
    loader.InitLoader();
    Resources::Package *global_pack = loader.LoadPackage("Global");
    loader.UnloadPackage(global_pack);

    // TODO Relocate To Engine Core
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    return EXIT_SUCCESS;
}
