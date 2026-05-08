#pragma once
#include "raylib.h"
#include <string>
#include <vector>

namespace Axiom
{

enum Sizes
{
        SMALL,
        MEDIUM,
        LARGE
};

class UIManager
{
public:
        UIManager();

        void draw();

        void init();
        void CleanUp();

        std::string getFunctionInput() const { return m_functionBuffer; }

private:
        Sizes m_currentSize;
        Rectangle m_area;
        float m_baseHeight;

private:
        char m_functionBuffer[256];
        bool m_editMode;
};
} // namespace Axiom
