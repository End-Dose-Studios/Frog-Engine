#pragma once

#include <filesystem>
#include <iostream>
#include <source_location>
#include <unordered_map>

inline void LoaderCheck(const bool result, const char *message,
                        const std::source_location &location = std::source_location::current()) {
    std::println(std::cout, "{}  | Result = {}", message, result);
    if (!result) {
        std::println(std::cerr,
                     "Uh Oh!!! Looks like the package loader had an error.\n{}, Line: "
                     "{}\n`\\_('_')_/`\tGood Luck!!\nAnd in case I don't see ya, good afternoon, "
                     "good evening, and good night.",
                     location.file_name(), location.line());
        throw std::runtime_error("Failed Load Packages");
    }
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
            return std::hash<uint8_t>{}(static_cast<uint8_t>(asset.first)) ^
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
        AssetEngine();
        ~AssetEngine();

        void InitLoader();

        Package *LoadPackage(const char *package_name);
        void UnloadPackage(Package *&package);

    private:
        std::list<Package> loadedPackages;
        std::vector<PackageReference> packageReferences;
    };
} // namespace Assets
