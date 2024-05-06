#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../Basics.h"


#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Shader.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text
{
public:

    void RenderText(std::string text, float x, float y, glm::mat4 viewMat = glm::mat4(1.0f), float scale = 1, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

    bool Init(int fontSize);


    std::map<GLchar, Character> Characters;

private:
    FT_Library ft;
    FT_Face face;
    
    unsigned int VAO;
    unsigned int VBO;

};







