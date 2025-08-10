#pragma once

#include "Asset.h"
#include "Package.h"

namespace EngineCore {
    class EngineCore;
} // namespace EngineCore

namespace Assets {
    class AssetEngine {
    public:
        explicit AssetEngine(EngineCore::EngineCore *engine_core_ptr);
        ~AssetEngine();

        void InitLoader();

        Package *LoadPackage(const char *package_name);
        void UnloadPackage(Package *&package);

        EngineCore::EngineCore *engineCorePtr;

        void (*createShader)(Asset &asset);
        void (*destroyShader)(const Asset &asset);

    private:
        std::list<Package> loadedPackages;
        std::vector<PackageReference> packageReferences;
    };
} // namespace Assets
