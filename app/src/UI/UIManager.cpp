#include "UIManager.hpp"
#include "../../../extern/raygui/raygui.h"
#include "../SettingsManager.hpp"
#include "../core/src/utils/logger.hpp"
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
        m_editMode = false;
        m_functionBuffer[0] = '\0'; // Leerer String
}

void UIManager::init()
{

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
        float &res = SettingsManager::getInstance().getResolutionRef();
        float oldRes = res;

        m_area = {0, (float)GetScreenHeight() - 200, (float)GetScreenWidth(), 200};

        // 2. Panel zeichnen (Nutzt automatisch die Farben aus deinem .rgs Style!)
        GuiPanel(m_area, NULL);

        float padding_x = 40.0f;
        float padding_y = 20.0f;
        float start_x = m_area.x + padding_x;
        float start_y = m_area.y + padding_y;

        GuiLabel({start_x, start_y, 150, 25}, "FUNKTION f(x, y)");
        if (GuiTextBox({start_x, start_y + 25, 300, 40}, m_functionBuffer, 256, m_editMode))
        {
                m_editMode = !m_editMode;
        }

        float slider_y = start_y + 80;
        GuiLabel({start_x, slider_y, 150, 25}, "AUFLÖSUNG");

        GuiSlider({start_x, slider_y + 25, 200, 30}, "10", "", &res, 10.0f, 100.0f);

        GuiLabel({start_x + 210, slider_y + 25, 50, 30}, TextFormat("%.0f", res));

        if(oldRes != res)
        {
                SettingsManager::getInstance().changed = true;
        }
}

void UIManager::CleanUp()
{
        GuiLoadStyleDefault(); // entlädt custom
        Logger::info("UIManager cleaned up.");
}

} // namespace Axiom
