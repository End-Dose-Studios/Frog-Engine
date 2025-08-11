#ifdef NDEBUG
#include <fstream>
#endif

#include <FrogEngine.h>

namespace FrogEngine {
    FrogEngine::FrogEngine() : vulkan(this), graphicsEngine(this), assetEngine(this){};
    FrogEngine::~FrogEngine() = default;

    void FrogEngine::startFrogEngine() {

#ifdef NDEBUG
        const std::ofstream log("log.txt");
        std::cout.rdbuf(log.rdbuf());
        std::cerr.rdbuf(log.rdbuf());
#endif

        window.initWindow();
        vulkan.initVulkan();
        graphicsEngine.startGraphicsEngine();
        assetEngine.startAssetLoader();
    }
}