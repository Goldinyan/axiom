#pragma once

namespace Axiom
{
class SettingsManager
{
public:
        // Zugriff über SettingsManager::getInstance()
        static SettingsManager &getInstance()
        {
                static SettingsManager instance;
                return instance;
        }

        float &getResolutionRef() { return m_resolution; } 
        float getResolution() const { return m_resolution; }

        bool &getClampZRef() { return m_clamp_z; } 
        bool getClampZ() const { return m_clamp_z; }

        bool changed = false;

private:
        SettingsManager() = default; // Privat, damit niemand ein zweites Objekt erstellt
        float m_resolution = 100.0f;
        bool m_clamp_z = true;
};
} // namespace Axiom
