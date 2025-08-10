#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../EngineCore/EngineCore.h"
#include "AssetEngine.h"
#include "VulkanAssets/VulkanAssets.h"

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

namespace Assets {
    AssetEngine::AssetEngine(EngineCore::EngineCore *engine_core_ptr) {
        engineCorePtr = engine_core_ptr;
        if (engineCorePtr->selectedAPI == GraphicsAPI::Vulkan) {
            createShader = &Vulkan::CreateShader;
            destroyShader = &Vulkan::DestroyShader;
        }
        if (engineCorePtr->selectedAPI == GraphicsAPI::OpenGL) {
            // TODO
        }
    };
    AssetEngine::~AssetEngine() = default;

    void AssetEngine::InitLoader() {
        std::println(std::cout, "-------------Starting-Asset-Engine-------------");

        std::array<char, MAX_PATH> path{};
        const DWORD length =
                GetModuleFileNameA(nullptr, path.data(), static_cast<DWORD>(path.size()));

        const std::filesystem::path app_path = std::string(path.data(), length);
        if (!exists(app_path)) {
            throw std::runtime_error("Failed to get the path of the executable.");
        }

        const std::filesystem::path package_directory = app_path.parent_path().append("Packages");
        if (!exists(package_directory)) {
            throw std::runtime_error("Could not find packages directory");
        }
        println(std::cout, "Found: {}", package_directory.string());

        for (const auto &package: std::filesystem::directory_iterator(package_directory)) {
            if (!is_regular_file(package))
                continue;

            println(std::cout, "  {}", package.path().string());

            PackageReference package_reference;
            package_reference.name = package.path().stem().string();
            package_reference.path = package.path();

            packageReferences.emplace_back(package_reference);
        }
        println(std::cout, "----------Packages-Found----------");
        std::println(std::cout, "-------------Finished-Asset-Engine--------------\n");
    }

    Package *AssetEngine::LoadPackage(const char *package_name) {
        for (const auto &[pack_name, pack_path]: packageReferences) {
            if (pack_name != package_name)
                continue;

            Package *package = &loadedPackages.emplace_back();

            package->name = pack_name;

            std::ifstream file(pack_path, std::ios::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open package file.");
            }

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

                asset.engineCorePtr = engineCorePtr;
                asset.assetEnginePtr = this;
                package->assets.emplace_back(asset);

                Asset *test = &package->assets.back();

                package->assetMap[{asset.type, asset.name}] = &package->assets.back();
            }
            break;
        }

        println(std::cout, "-------Loaded {}-------", package_name);

        return &loadedPackages.back();
    }

    void AssetEngine::UnloadPackage(Package *&package) {
        if (!package)
            return;

        const auto target_package = std::ranges::find_if(
                loadedPackages, [&](const Package &pack) { return &pack == package; });

        for (const auto &asset: package->assets) {
            if (GetHandlePtr(asset.handle) != nullptr)
                asset.DestroyHandle();
        }

        std::string pack_name = package->name;

        if (target_package != loadedPackages.end())
            loadedPackages.erase(target_package);

        println(std::cout, "------Unloaded {}------\n", pack_name);

        package = nullptr;
    }
} // namespace Assets