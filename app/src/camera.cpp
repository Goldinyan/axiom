#include "app/camera.hpp"
#include "math.h"

// Nur kompilieren, wenn NO_UI NICHT definiert ist
#ifndef NO_UI
#include "raylib.h"
#include "../../core/src/constants/UIConstants.hpp"

static float angleAzi = -45.0f * DEG2RAD;
static float angleElev = 20.0f * DEG2RAD;
static float radius = 70.0f;

namespace Axiom
{

CameraManager::CameraManager()
{
        m_camera = {0};
        m_camera.position = (Vector3){10.0f, 10.0f, 10.0f};
        m_camera.target = (Vector3){0.0f, 0.0f, 0.0f}; // Der Punkt, um den wir kreisen
        // bei {0, 1, 0} wäre die y achse oben, aber so ist die z wie gewollt
        m_camera.up = (Vector3){0.0f, 0.0f, 1.0f};
        m_camera.fovy = 45.0f;
        m_camera.projection = CAMERA_PERSPECTIVE;

        m_rotating_speed = 0.0f;
}

void CameraManager::update()
{
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
                Vector2 delta = GetMouseDelta();
                angleAzi -= delta.x * 0.01f;  // Horizontal drehen
                angleElev += delta.y * 0.01f; // Vertikal drehen

                // Begrenzung, damit die Kamera nicht über den Nordpol "umkippt"
                if (angleElev > 89.0f * DEG2RAD)
                        angleElev = 89.0f * DEG2RAD;
                if (angleElev < -89.0f * DEG2RAD)
                        angleElev = -89.0f * DEG2RAD;
        }

        float mouseWheel = GetMouseWheelMove();
        radius -= mouseWheel * 1.0f;
        if (radius < 1.0f)
                radius = 1.0f;
        if (radius > 200.0f)
                radius = 200.0f;

        // 4. Position auf der Kugel berechnen (Sphärische zu Kartesische Koordinaten)

        m_camera.position.x = m_camera.target.x + radius * cosf(angleElev) * cosf(angleAzi);
        m_camera.position.y = m_camera.target.y + radius * cosf(angleElev) * sinf(angleAzi);
        m_camera.position.z = m_camera.target.z + radius * sinf(angleElev);
}

} // namespace Axiom

#else

// --- CLI FALLBACK ---
namespace Axiom
{
// Im CLI Modus machen diese Funktionen einfach nichts
CameraManager::CameraManager() : m_rotating_speed(0.0f) {}
void CameraManager::update() {}
} // namespace Axiom

#endif
