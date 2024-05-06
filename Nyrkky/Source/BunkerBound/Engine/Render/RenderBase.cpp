#include "RenderBase.h"


void RenderBase::Clean()
{
    delete _va;
    delete _vb;
    delete _ib;
    delete _layout;

    _va = nullptr;
    _vb = nullptr;
    _ib = nullptr;
    _layout = nullptr;

    for (auto &t : _textures)
    {
        if (t != nullptr)
        {
            delete t;
            t = nullptr;
        }
    }
}




