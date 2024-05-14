#pragma once

#include "Renderer.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class TextureArray
{
public:
    TextureArray(std::vector<std::string>& paths);
    ~TextureArray();

    void Bind(unsigned int slot = 0) const;
    void Unbind();

    GLuint GetID()
    {
        return _rendererID;
    }

    int GetSize()
    {
        return _textureNum;
    }

private:
    GLuint _rendererID;
    int _width = 64;
    int _height = 64;
    int _BPP;
    int _textureNum;

};

class TextureManager
{
public:
    static std::shared_ptr<TextureArray> GetTextureArray(std::vector<std::string>& paths);

private:
    TextureManager() {}

    static std::unordered_map<std::vector<std::string>, std::shared_ptr<TextureArray>> _textureMap;
};
