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

        std::string getFunctionInput() const { return m_functionBuffer; }
        float getStepSize() const { return m_stepSize; }

private:
        Sizes m_currentSize;
        Rectangle m_area;
        float m_baseHeight;

private:
        char m_functionBuffer[256];
        bool m_editMode;
        float m_stepSize;
};
} // namespace Axiom
