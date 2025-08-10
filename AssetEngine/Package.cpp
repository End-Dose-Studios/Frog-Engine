#include "Package.h"

namespace Assets {
    void *Package::QueryAssets(AssetType type, const std::string &name) {
        if (const auto asset = assetMap.find({type, name}); asset != assetMap.end()) {
            if (GetHandlePtr(asset->second->handle) == nullptr)
                asset->second->CreateHandle();
            return GetHandlePtr(asset->second->handle);
        }
        return nullptr;
    }
} // namespace Assets