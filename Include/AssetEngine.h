#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <variant>

#include <vulkan/vulkan.hpp>

enum AssetType : uint8_t {
    TEXTURE,
    MODEL,
    SHADER,
};

namespace FrogEngine {
    class FrogEngine;
}

namespace FrogEngine::Assets {
    inline const vk::Device *device_ptr;

    using APIHandle = std::variant<std::monostate, vk::ShaderModule>;

    struct Asset {
        AssetType type;
        std::string name;
        uint32_t size;
        std::vector<uint8_t> data;

        APIHandle handle;

        [[nodiscard]] const void *getHandlePtr() const;

        void createHandle();
        void destroyHandle();

        void createShader();
        void destroyShader();
    };

    struct AssetHash {
        std::size_t operator()(const std::pair<AssetType, std::string> &asset) const noexcept {
            return std::hash<uint8_t>{}(asset.first) ^
                   (std::hash<std::string>{}(asset.second) << 1);
        }
    };

    struct PackageReference {
        std::string name;
        std::filesystem::path path;
    };

    struct Package {
        std::string name;
        std::vector<Asset> assets;

        std::unordered_map<std::pair<AssetType, std::string>, Asset *, AssetHash> assetMap;

        const void *queryAssets(AssetType asset_type, const std::string &asset_name);
    };

    class AssetEngine {
    public:
        explicit AssetEngine(const FrogEngine *frog_engine_ptr);
        ~AssetEngine();

        void startAssetLoader();

        std::list<Package>::iterator loadPackage(const char *package_name);
        void unloadPackage(std::list<Package>::iterator &package);

    private:
        std::list<Package> loadedPackages;
        std::vector<PackageReference> packageReferences;
    };
}