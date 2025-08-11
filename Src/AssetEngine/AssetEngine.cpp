#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <AssetEngine.h>
#include <FrogEngine.h>

namespace {
    template<typename t>
    void readUInt(std::ifstream &in_file, t &value) {
        in_file.read(reinterpret_cast<char *>(&value), sizeof(t));
    }

    void readBytes(std::ifstream &in_file, std::vector<uint8_t> &bytes, const std::size_t size) {
        bytes.resize(size);
        in_file.read(reinterpret_cast<char *>(bytes.data()), static_cast<std::streamsize>(size));
    }

    void readString(std::ifstream &in_file, std::string &str) {
        uint32_t length{};
        readUInt(in_file, length);
        str.resize(length);
        in_file.read(str.data(), length);
    }
} // namespace

namespace FrogEngine::Assets {
    void Asset::createHandle() {
        switch (type) {
            case AssetType::SHADER:
                createShader();
                break;
            default:
                break;
        }
    }

    void Asset::destroyHandle() {
        switch (type) {
            case AssetType::SHADER:
                destroyShader();
                break;
            default:
                break;
        }
    }

    const void *Asset::getHandlePtr() const {
        return std::visit(
                []<typename T0>(const T0 &val) -> const void *
                {
                    if constexpr (std::is_same_v<std::decay_t<T0>, std::monostate>) {
                        return nullptr;
                    } else {
                        return static_cast<const void *>(&val);
                    }
                },
                handle);
    }

    const void *Package::queryAssets(AssetType asset_type, const std::string &asset_name) {
        if (const auto asset = assetMap.find({asset_type, asset_name}); asset != assetMap.end()) {
            if (!asset->second->getHandlePtr())
                asset->second->createHandle();

            return asset->second->getHandlePtr();
        }
        return nullptr;
    }

    AssetEngine::AssetEngine(const FrogEngine *frog_engine_ptr) {
        device_ptr = &frog_engine_ptr->vulkan.vkDevice;
    };
    AssetEngine::~AssetEngine() = default;

    void AssetEngine::startAssetLoader() {
        std::println(std::cout, "-------------Starting-Asset-Engine-------------");

        std::array<char, MAX_PATH> path{};
        const DWORD length =
                GetModuleFileNameA(nullptr, path.data(), static_cast<DWORD>(path.size()));

        const std::filesystem::path app_path = std::string(path.data(), length);
        if (!exists(app_path))
            throw std::runtime_error("Failed to get the path of the executable.");

        const std::filesystem::path package_directory = app_path.parent_path().append("Packages");
        if (!exists(package_directory))
            throw std::runtime_error("Could not find packages directory");
        std::println(std::cout, "Found: {}", package_directory.string());

        for (const auto &package: std::filesystem::directory_iterator(package_directory)) {
            if (!is_regular_file(package))
                continue;

            std::println(std::cout, "  {}", package.path().string());

            PackageReference package_reference;
            package_reference.name = package.path().stem().string();
            package_reference.path = package.path();

            packageReferences.emplace_back(package_reference);
        }
        std::println(std::cout, "----------Packages-Found----------");
        std::println(std::cout, "-------------Finished-Asset-Engine--------------\n");
    }

    std::list<Package>::iterator AssetEngine::loadPackage(const char *package_name) {
        for (const auto &[pack_name, pack_path]: packageReferences) {
            if (pack_name != package_name)
                continue;

            Package *package = &loadedPackages.emplace_back();

            package->name = pack_name;

            std::ifstream file(pack_path, std::ios::binary);
            if (!file.is_open())
                throw std::runtime_error("Could not open package file.");

            uint32_t magic_string{};
            readUInt(file, magic_string);
            uint32_t version{};
            readUInt(file, version);
            uint32_t asset_count{};
            readUInt(file, asset_count);
            package->assets.reserve(asset_count);

            for (uint32_t i = 0; i < asset_count; i++) {
                Asset asset;
                readUInt(file, asset.type);
                readString(file, asset.name);
                readUInt(file, asset.size);
                readBytes(file, asset.data, asset.size);

                package->assets.emplace_back(asset);
                package->assetMap[{asset.type, asset.name}] = &package->assets.back();
            }
            break;
        }

        std::println(std::cout, "-------Loaded {}-------", package_name);

        return std::prev(loadedPackages.end());
    }

    void AssetEngine::unloadPackage(std::list<Package>::iterator &package) {
        if (package == loadedPackages.end())
            return;

        for (auto &asset: package->assets)
            if (asset.getHandlePtr() != nullptr)
                asset.destroyHandle();

        std::string pack_name = package->name;

        package = loadedPackages.erase(package);

        std::println(std::cout, "------Unloaded {}------\n", pack_name);
    }
}