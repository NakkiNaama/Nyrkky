#include "TextEntity.h"

TextEntity::TextEntity(int posx, int posy, int fontSize)
{
    text = std::make_unique<Text>();

    PosX = (posx * 64);
    PosY = -(posy * 64);
    text->Init(fontSize);
}

TextEntity::~TextEntity()
{
}





