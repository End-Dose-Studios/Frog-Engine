#include <iostream>

#include <AssetEngine.h>

namespace Assets {
    void Asset::CreateShader() {
        VkShaderModuleCreateInfo shader_info{};
        shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

        assert(data.size() % 4 == 0);
        const auto *const code_ptr = reinterpret_cast<const uint32_t *>(data.data());
        shader_info.pCode = code_ptr;
        shader_info.codeSize = data.size();

        handle = devicePtr->createShaderModule(shader_info);
        std::println(std::cout, "---------{}-Created---------", name);
    }

    void Asset::DestroyShader() {
        devicePtr->destroyShaderModule(*static_cast<vk::ShaderModule *>(GetHandlePtr(handle)));
        std::println(std::cout, "--------{}-Destroyed--------", name);
    }
} // namespace Assets