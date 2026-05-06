#include "app/camera.hpp"

// Nur kompilieren, wenn NO_UI NICHT definiert ist
#ifndef NO_UI
#include "raylib.h"

namespace Axiom
{

CameraManager::CameraManager()
{
        m_camera = {0};
        m_camera.position = (Vector3){10.0f, 10.0f, 10.0f};
        m_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        m_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        m_camera.fovy = 45.0f;
        m_camera.projection = CAMERA_PERSPECTIVE;

        m_rotating_speed = 0.0f;
}

void CameraManager::update()
{
        Vector3 movement = {0, 0, 0};
        Vector3 rotation = {0, 0, 0};
        float zoom = 0.0f;

        if (m_rotating_speed != 0.0f)
        {
                rotation.x = m_rotating_speed;
        }

        zoom = -GetMouseWheelMove() * 1.0f;

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
                Vector2 delta = GetMouseDelta();
                rotation.x += delta.x * 0.1f;
        }

        UpdateCameraPro(&m_camera, movement, rotation, zoom);
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
