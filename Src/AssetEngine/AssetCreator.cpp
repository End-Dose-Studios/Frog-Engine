#include <iostream>

#include <AssetEngine.h>

namespace FrogEngine::Assets {
    void Asset::createShader() {
        vk::ShaderModuleCreateInfo shader_module_info = {};

        shader_module_info.codeSize = size;
        shader_module_info.pCode = reinterpret_cast<const uint32_t *>(data.data());
        handle = device_ptr->createShaderModule(shader_module_info);

        std::println(std::cout, "---------{}-Created---------", name);
    }

    void Asset::destroyShader() {
        device_ptr->destroyShaderModule(*static_cast<const vk::ShaderModule *>(getHandlePtr()));
        std::println(std::cout, "--------{}-Destroyed--------", name);
    }
}