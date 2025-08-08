#include <array>
#include <filesystem>
#include <fstream>
#include <windows.h>

#include "Loader.h"

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

namespace Resources {
    Loader::Loader() = default;
    Loader::~Loader() = default;

    void Loader::InitLoader() {
        std::array<char, MAX_PATH> path{};
        const DWORD length =
                GetModuleFileNameA(nullptr, path.data(), static_cast<DWORD>(path.size()));
        LoaderCheck(length > 0 && length < path.size(), "Finding Executable Path...");

        const std::filesystem::path app_path = std::string(path.data(), length);
        const std::filesystem::path package_directory = app_path.parent_path().append("Packages");

        LoaderCheck(is_directory(package_directory), "Finding Package Directory...");

        for (const auto &package: std::filesystem::directory_iterator(package_directory)) {
            if (!is_regular_file(package))
                continue;

            PackageReference package_reference;
            package_reference.name = package.path().stem().string();
            package_reference.path = package.path();

            packageReferences.emplace_back(package_reference);
        }
    }

    Package *Loader::LoadPackage(const char *package_name) {
        std::println(std::cout, "Loading Package: {}", package_name);

        for (const auto &[pack_name, pack_path]: packageReferences) {
            if (pack_name != package_name)
                continue;

            loadedPackages.emplace_back();
            auto &[name, assets, assetMap] = loadedPackages.back();

            name = pack_name;

            std::ifstream file(pack_path, std::ios::binary);
            LoaderCheck(file.is_open(), "Opening Package File...");

            uint32_t magic_string{};
            readUInt(file, magic_string);
            uint32_t version{};
            readUInt(file, version);
            uint32_t asset_count{};
            readUInt(file, asset_count);
            assets.reserve(asset_count);

            for (uint32_t i = 0; i < asset_count; i++) {
                Asset asset;
                readUInt(file, asset.type);
                readString(file, asset.name);
                readUInt(file, asset.size);
                readBytes(file, asset.data, asset.size);

                assets.emplace_back(asset);

                assetMap[{asset.type, asset.name}] = &assets.back();
            }
            break;
        }

        return &loadedPackages.back();
    }

    void Loader::UnloadPackage(Package *&package) {
        if (!package)
            return;

        const auto target_package = std::ranges::find_if(
                loadedPackages, [&](const Package &pack) { return &pack == package; });

        if (target_package != loadedPackages.end()) {
            loadedPackages.erase(target_package);
        }

        package = nullptr;
    }

    Asset *Package::QueryAssets(AssetType type, const std::string &name) {
        if (const auto asset = assetMap.find({type, std::string{name}}); asset != assetMap.end()) {
            return asset->second;
        }
        return nullptr;
    }

} // namespace Resources