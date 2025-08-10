#include <iostream>

#include "../../EngineCore/EngineCore.h"
#include "VulkanAssets.h"

namespace Assets::Vulkan {
    void CreateShader(Asset &asset) {
        VkShaderModuleCreateInfo shader_info{};
        shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

        assert(asset.data.size() % 4 == 0);
        const auto *const code_ptr = reinterpret_cast<const uint32_t *>(asset.data.data());
        shader_info.pCode = code_ptr;
        shader_info.codeSize = asset.data.size();

        asset.handle =
                asset.engineCorePtr->vulkanEngine.GetDevicePtr()->createShaderModule(shader_info);
        std::println(std::cout, "---------{}-Created---------", asset.name);
    }

    void DestroyShader(const Asset &asset) {
        asset.engineCorePtr->vulkanEngine.GetDevicePtr()->destroyShaderModule(
                *static_cast<vk::ShaderModule *>(GetHandlePtr(asset.handle)));
        std::println(std::cout, "--------{}-Destroyed--------", asset.name);
    }
} // namespace Assets::Vulkan