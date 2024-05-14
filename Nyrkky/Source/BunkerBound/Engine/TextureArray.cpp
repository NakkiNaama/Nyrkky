#include "TextureArray.h"
#include "stb_image/stb_image.h"
#include <iostream>

namespace std {
    template<> struct hash<std::vector<std::string>> {
        size_t operator()(const std::vector<std::string>& v) const {
            std::hash<std::string> hasher;
            size_t seed = 0;
            for (const std::string& str : v) {
                seed ^= hasher(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

std::unordered_map<std::vector<std::string>, std::shared_ptr<TextureArray>> TextureManager::_textureMap;

TextureArray::TextureArray(std::vector<std::string>& paths)
    : _rendererID(0), _width(0), _height(0), _BPP(0)
{
    glGenTextures(1, &_rendererID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _rendererID);

    _textureNum = static_cast<int>(paths.size());

    unsigned char* localBuffer = nullptr;

    // Find maximum width and height of textures
    int maxWidth = 0, maxHeight = 0;
    for (const std::string& path : paths) {
        localBuffer = stbi_load(path.c_str(), &_width, &_height, &_BPP, 4);
        if (localBuffer) {
            maxWidth = std::max(maxWidth, _width);
            maxHeight = std::max(maxHeight, _height);
            stbi_image_free(localBuffer);
        }
        else {
            std::cout << "Failed to load texture: " << path << std::endl;
        }
    }

    _width = maxWidth;
    _height = maxHeight;

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, _width, _height, _textureNum, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (int i = 0; i < _textureNum; ++i) {
        localBuffer = stbi_load(paths[i].c_str(), &_width, &_height, &_BPP, 4);
        if (localBuffer) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, _width, _height, 1, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
            stbi_image_free(localBuffer);
        }
        else {
            std::cout << "Failed to load texture: " << paths[i] << std::endl;
        }
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
    glDeleteTextures(1, &_rendererID);
}

void TextureArray::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _rendererID);
}

void TextureArray::Unbind()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

std::shared_ptr<TextureArray> TextureManager::GetTextureArray(std::vector<std::string>& paths)
{
    auto it = _textureMap.find(paths);
    if (it != _textureMap.end()) {
        return it->second;
    }
    else {
        std::shared_ptr<TextureArray> textureArray = std::make_shared<TextureArray>(paths);
        _textureMap.emplace(paths, textureArray);
        return textureArray;
    }
}
