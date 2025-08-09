#include <iostream>

#include "VulkanEngine.h"

namespace {
    const char *getSeverity(const vk::DebugUtilsMessageSeverityFlagBitsEXT severity) {
        switch (severity) {
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
                return "Verbose";
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
                return "Warning";
            case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
                return "Error";
            default:
                return "No Severity";
        }
    }

    const char *getType(const vk::DebugUtilsMessageTypeFlagsEXT type) {
        if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral) {
            return "General";
        }
        if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation) {
            return "Validation";
        }
        if (type & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance) {
            return "Performance";
        }
        return "No Type";
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            const vk::DebugUtilsMessageSeverityFlagBitsEXT message_severity,
            const vk::DebugUtilsMessageTypeFlagsEXT message_type,
            const vk::DebugUtilsMessengerCallbackDataEXT *p_callback_data, void * /*p_user_data*/) {

        const char *severity{getSeverity(message_severity)};
        const char *type{getType(message_type)};

        std::println(std::cerr, "Severity: {}\nType: {}\n{}", severity, type,
                     p_callback_data->pMessage);

        return VK_FALSE;
    }
} // namespace

namespace EngineCore::Vulkan {

    void Engine::CreateDebugMessenger() {
        if (!enableDebugExtensions)
            return;

        vk::DebugUtilsMessengerCreateInfoEXT debug_messenger_info{};
        debug_messenger_info.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                                               vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                               vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
        debug_messenger_info.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                           vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                                           vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
        debug_messenger_info.pfnUserCallback = debugCallback;
        debug_messenger_info.pUserData = nullptr;

        if (const vk::detail::DispatchLoaderDynamic instanceLoader(vkInstance,
                                                                   vkGetInstanceProcAddr);
            vkInstance.createDebugUtilsMessengerEXT(&debug_messenger_info, nullptr,
                                                    &vkDebugMessenger,
                                                    instanceLoader) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create debug messenger");
        };
        println(std::cout, "-----Debug-Messenger-Created------");
    }

    void Engine::DestroyDebugMessenger() const {
        if (!enableDebugExtensions)
            return;

        const vk::detail::DispatchLoaderDynamic instanceLoader(vkInstance, vkGetInstanceProcAddr);
        vkInstance.destroyDebugUtilsMessengerEXT(vkDebugMessenger, nullptr, instanceLoader);
        println(std::cout, "-----Debug-Messenger-Destroyed----");
    }

} // namespace EngineCore::Vulkan