#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "Asset.h"

namespace Assets {
    class AssetEngine;

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
}; // namespace Assets
