#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <variant>

#include <vulkan/vulkan.hpp>

namespace EngineCore {
    class EngineCore;
}
namespace Assets {

    inline const vk::Device *devicePtr;

    enum AssetType : uint8_t {
        Texture,
        Model,
        Shader,
    };

    using APIHandle = std::variant<std::monostate, vk::ShaderModule>;
    void *GetHandlePtr(APIHandle handle);

    struct Asset {
        AssetType type;
        std::string name;
        uint32_t size;
        std::vector<uint8_t> data;

        APIHandle handle;
        void CreateHandle();
        void DestroyHandle();

        void CreateShader();
        void DestroyShader();
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

        void *QueryAssets(AssetType type, const std::string &name);
    };

    class AssetEngine {
    public:
        explicit AssetEngine(const EngineCore::EngineCore *engine_core_ptr);
        ~AssetEngine();

        void InitLoader();

        Package *LoadPackage(const char *package_name);
        void UnloadPackage(Package *&package);

    private:
        std::list<Package> loadedPackages;
        std::vector<PackageReference> packageReferences;
    };
} // namespace Assets
