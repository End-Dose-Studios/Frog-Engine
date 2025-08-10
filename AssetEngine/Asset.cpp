#include "Asset.h"
#include "AssetEngine.h"

namespace Assets {
    void *GetHandlePtr(APIHandle handle) {
        return std::visit(
                []<typename t0>(const t0 &arg) -> void *
                {
                    using T = std::decay_t<t0>;
                    if constexpr (std::is_same_v<T, std::monostate>)
                        return nullptr;
                    else
                        return static_cast<void *>(const_cast<std::remove_const_t<T> *>(&arg));
                },
                handle);
    }

    void Asset::CreateHandle() {
        switch (type) {
            case AssetType::Shader:
                assetEnginePtr->createShader(*this);
                break;
            default:
                break;
        }
    }

    void Asset::DestroyHandle() const {
        switch (type) {
            case AssetType::Shader:
                assetEnginePtr->destroyShader(*this);
                break;
            default:
                break;
        }
    }
} // namespace Assets