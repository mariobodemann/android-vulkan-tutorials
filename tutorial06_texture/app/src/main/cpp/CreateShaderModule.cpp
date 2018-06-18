/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "CreateShaderModule.h"

// Create VK shader module from given glsl shader file
// filePath: glsl shader file (including path ) in APK's asset folder
VkResult buildShaderFromFile(android_app *appInfo, const char *filePath,
                             VkShaderStageFlagBits type, VkDevice vkDevice,
                             VkShaderModule *shaderOut) {
    AAsset *file = AAssetManager_open(appInfo->activity->assetManager, filePath, AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char *fileContent = new char[fileLength];
    AAsset_read(file, fileContent, fileLength);

    // build vulkan shader module
    VkShaderModuleCreateInfo shaderModuleCreateInfo{
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .codeSize = fileLength,
            .pCode = (const uint32_t *) fileContent,
            .flags = 0,
    };
    VkResult result = vkCreateShaderModule(vkDevice, &shaderModuleCreateInfo, nullptr, shaderOut);

    return result;
}
