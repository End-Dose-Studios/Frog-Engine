#include <iostream>

#include "EngineCore.h"

namespace {
    int checkExtensionSupport(const vk::PhysicalDevice *device) {
        int score{0};

        const auto available_extensions = device->enumerateDeviceExtensionProperties();

        std::vector<const char *> extension_check{vk::KHRSwapchainExtensionName};
        for (const auto [extensionName, specVersion]: available_extensions) {
            std::erase_if(extension_check, [&](const char *ext)
                          { return strcmp(ext, extensionName) == 0; }); // NOLINT
        }
        if (!extension_check.empty())
            score = -INT16_MAX;

        return score;
    }

    int getProperties(const vk::PhysicalDevice *device) {
        int score{0};

        const auto device_properties = device->getProperties();

        std::println(std::cout, "  Name: {}", device_properties.deviceName.data());
        std::println(std::cout, "  Type: {}",
                     device_properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu
                             ? "Discrete"
                             : "Integrated");
        std::println(std::cout, "  API Version: {}.{}.{}",
                     vk::apiVersionMajor(device_properties.apiVersion),
                     vk::apiVersionMinor(device_properties.apiVersion),
                     vk::apiVersionPatch(device_properties.apiVersion));

        constexpr int DEVICE_TYPE_WEIGHT{1000};
        score += device_properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu
                         ? DEVICE_TYPE_WEIGHT
                         : -DEVICE_TYPE_WEIGHT;

        constexpr int VULKAN_VERSION_MINOR_WEIGHT{50};
        score += VULKAN_VERSION_MINOR_WEIGHT * vk::apiVersionMinor(device_properties.apiVersion);

        return score;
    }

    int getFeatures(const vk::PhysicalDevice *device) {
        int score{0};

        const auto device_features = device->getFeatures();

        println(std::cout, "  Geometry Shader: {}",
                static_cast<bool>(device_features.geometryShader));
        println(std::cout, "  Tessellation Shader: {}",
                static_cast<bool>(device_features.tessellationShader));

        constexpr uint32_t SHADER_SUPPORT_WEIGHT{500};
        score += SHADER_SUPPORT_WEIGHT *
                 (device_features.geometryShader + device_features.tessellationShader);

        return score;
    }

    int getMemoryProperties(const vk::PhysicalDevice *device) {
        int score{0};

        const auto memory_properties = device->getMemoryProperties();

        uint64_t v_ram = 0;
        for (const auto &[size, flags]: memory_properties.memoryHeaps) {
            if (flags & vk::MemoryHeapFlagBits::eDeviceLocal)
                v_ram += size;
        }

        constexpr uint64_t BYTES_TO_GIGABYTES{1048576};
        const float v_ram_gb = static_cast<float>(v_ram) / static_cast<float>(BYTES_TO_GIGABYTES);
        println(std::cout, "  VRAM: {} Mb", static_cast<int>(v_ram_gb + 0.5)); // NOLINT

        constexpr uint64_t VRAM_WEIGHT{20};
        score += static_cast<uint32_t>(
                static_cast<float>(v_ram) /
                (static_cast<float>(BYTES_TO_GIGABYTES) * static_cast<float>(VRAM_WEIGHT)));

        return score;
    }

    int getPhysicalDevice(const vk::PhysicalDevice *device) {
        int score{0};

        score += checkExtensionSupport(device);
        score += getProperties(device);
        score += getFeatures(device);
        score += getMemoryProperties(device);

        println(std::cout, "  Score: {}", score);
        return score;
    }
} // namespace

namespace EngineCore {
    void EngineCore::GetPhysicalDevices() {
        println(std::cout, "----Finding-All-Engine-Devices----");

        const std::vector<vk::PhysicalDevice> devices = vkInstance.enumeratePhysicalDevices();

        uint32_t highest_score{};
        uint32_t highest_score_index{};
        for (size_t i = 0; i < devices.size(); i++) {
            std::println(std::cout, "Device: {}", i);

            if (const int score = getPhysicalDevice(&devices[i]); score > highest_score) {
                highest_score = score;
                highest_score_index = i;
            }

            physicalDevices.emplace_back(devices[i]);
        }
        selectedDevice = &physicalDevices[highest_score_index];
        std::println(std::cout, "Selected Device: {}",
                     selectedDevice->getProperties().deviceName.data());
    }

} // namespace EngineCore