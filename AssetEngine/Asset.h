#pragma once

#include <variant>

#include <vulkan/vulkan.hpp>

namespace EngineCore {
    class EngineCore;
}
namespace Assets {
    class AssetEngine;

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

        EngineCore::EngineCore *engineCorePtr;
        AssetEngine *assetEnginePtr;

        APIHandle handle;
        void CreateHandle();
        void DestroyHandle() const;
    };

    struct AssetHash {
        std::size_t operator()(const std::pair<AssetType, std::string> &asset) const noexcept {
            return std::hash<uint8_t>{}(asset.first) ^
                   (std::hash<std::string>{}(asset.second) << 1);
        }
    };

} // namespace Assets
