#include <iostream>

#include <GLFW/glfw3.h>

#include <Vulkan.h>

namespace {
    uint32_t getAPIVersion() {
        const uint32_t api_version = vk::enumerateInstanceVersion();

        std::println(std::cout, "Instance API Version: {}.{}.{}", vk::apiVersionMajor(api_version),
                     vk::apiVersionMinor(api_version), vk::apiVersionPatch(api_version));

        return api_version;
    }

    std::vector<const char *> getExtensions(const bool enable_debug_extensions) {
        uint32_t glfw_extension_count{};
        const char **glfw_extensions{glfwGetRequiredInstanceExtensions(&glfw_extension_count)};

        std::span<const char *const> const span(glfw_extensions, glfw_extension_count);
        std::vector<const char *> extensions(span.begin(), span.end());

        extensions.emplace_back(vk::KHRPortabilityEnumerationExtensionName);
        if (enable_debug_extensions)
            extensions.emplace_back(vk::EXTDebugUtilsExtensionName);


        std::vector<vk::ExtensionProperties> available_extensions =
                vk::enumerateInstanceExtensionProperties();

        std::vector<const char *> extensions_check(extensions.begin(), extensions.end());
        for (const auto &[extensionName, specVersion]: available_extensions)
            std::erase_if(extensions_check, [&](const char *ext)
                          { return strcmp(ext, extensionName) == 0; }); // NOLINT

        if (!extensions_check.empty())
            throw std::runtime_error("Missing required extensions.");

        std::println(std::cout, "Instance Extensions:");
        for (const auto *const extension: extensions)
            std::println(std::cout, "  {}", extension);

        return extensions;
    }

    std::vector<const char *> getLayers(const bool enable_debug_extensions) {
        std::vector<const char *> layers;
        if (enable_debug_extensions)
            layers.emplace_back("VK_LAYER_KHRONOS_validation");

        const std::vector<vk::LayerProperties> available_layers =
                vk::enumerateInstanceLayerProperties();

        std::vector<const char *> layer_check(layers.begin(), layers.end());
        for (const auto available_layer: available_layers)
            std::erase_if(layer_check, [&](const char *ext)
                          { return strcmp(ext, available_layer.layerName) == 0; }); // NOLINT

        if (!layer_check.empty())
            throw std::runtime_error("Missing required layers.");

        std::println(std::cout, "Instance Layers:");
        for (const auto *const layer: layers)
            std::println(std::cout, "  {}", layer);

        return layers;
    }
} // namespace

namespace FrogEngine::Vulkan {
    void Vulkan::createInstance() {
        vk::ApplicationInfo app_info;
        app_info.pApplicationName = "FrogEngine";
        app_info.applicationVersion = vk::makeApiVersion(0, 1, 0, 0);
        app_info.pEngineName = "FrogEngine";
        app_info.engineVersion = vk::makeApiVersion(0, 1, 0, 0);
        app_info.apiVersion = getAPIVersion();

        const std::vector<const char *> extensions = getExtensions(enableDebugExtensions);
        const std::vector<const char *> layers = getLayers(enableDebugExtensions);

        vk::InstanceCreateInfo instance_info;
        instance_info.flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
        instance_info.pApplicationInfo = &app_info;
        instance_info.enabledLayerCount = static_cast<uint32_t>(layers.size());
        instance_info.ppEnabledLayerNames = layers.data();
        instance_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instance_info.ppEnabledExtensionNames = extensions.data();

        vkInstance = vk::createInstance(instance_info);
        std::println(std::cout, "---------Instance-Created---------");
    }

    void Vulkan::destroyInstance() const {
        vkInstance.destroy();
        std::println(std::cout, "--------Instance Destroyed--------");
    }
}