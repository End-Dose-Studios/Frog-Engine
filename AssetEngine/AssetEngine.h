#pragma once

#include <filesystem>
#include <iostream>
#include <source_location>
#include <unordered_map>

namespace EngineCore {
    class EngineCore;
}

namespace Assets {
    enum AssetType : uint8_t {
        Texture,
        Model,
        Shader,
    };

    struct Asset {
        AssetType type;
        std::string name;
        uint32_t size;
        std::vector<uint8_t> data;
    };

    struct AssetHash {
        std::size_t operator()(const std::pair<AssetType, std::string> &asset) const noexcept {
            return std::hash<uint8_t>{}(asset.first) ^
                   (std::hash<std::string>{}(asset.second) << 1);
        }
    };

    struct Package {
        std::string name;
        std::vector<Asset> assets;

        std::unordered_map<std::pair<AssetType, std::string>, Asset *, AssetHash> assetMap;

        Asset *QueryAssets(AssetType type, const std::string &name);
    };

    struct PackageReference {
        std::string name;
        std::filesystem::path path;
    };

    class AssetEngine {
    public:
        explicit AssetEngine(EngineCore::EngineCore *engine_core_ptr);
        ~AssetEngine();

        void InitLoader();

        Package *LoadPackage(const char *package_name);
        void UnloadPackage(Package *&package);

    private:
        EngineCore::EngineCore *engineCorePtr;

        std::list<Package> loadedPackages;
        std::vector<PackageReference> packageReferences;

        using CreateShader = void (*)(Asset &asset);
    };
} // namespace Assets
