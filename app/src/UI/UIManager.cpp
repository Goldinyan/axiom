#include "UIManager.hpp"
#include "raylib.h"
#include <filesystem>
#include <iostream>

#define RAYGUI_IMPLEMENTATION // Header only tool
#include "raygui/raygui.h"

namespace Axiom
{

UIManager::UIManager()
{
        m_currentSize = MEDIUM;
        m_stepSize = 50.0f;
        m_editMode = false;
        m_functionBuffer[0] = '\0'; // Leerer String
        

        m_area = {0, GetScreenHeight() - m_baseHeight, (float)GetScreenWidth(), m_baseHeight};


        if (std::filesystem::exists("extern/raygui/style_jungle.rgs"))
        {
                std::cout << "Datei gefunden!" << std::endl;
                GuiLoadStyle("extern/raygui/style_jungle.rgs");
        }
        else
        {
                std::cout << "Datei NICHT gefunden in: " << std::filesystem::current_path() << std::endl;
        }
}

void UIManager::draw()
{
        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();
        int panelHeight = 200;


        DrawRectangle(0, m_area.y, m_area.width, m_area.height, BLUE);
        DrawLine(0, screenHeight - panelHeight, screenWidth, screenHeight - panelHeight, GRAY);

        GuiLabel({20, (float)screenHeight - 180, 100, 40}, "Funktion f(x,y):");
        if (GuiTextBox({20, (float)screenHeight - 160, 300, 50}, m_functionBuffer, 256, m_editMode))
        {
                m_editMode = !m_editMode;
        }

        

        GuiLabel({20, (float)screenHeight - 110, 100, 20}, "Auflösung:");
        GuiSlider({20, (float)screenHeight - 90, 200, 40}, "Low", "High", &m_stepSize, 10.0f, 100.0f);

        if (GuiButton({330, (float)screenHeight - 160, 100, 50}, "Plotten"))
        {
        }
}
} // namespace Axiom
