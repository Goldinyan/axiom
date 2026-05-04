#pragma once
#include "raylib.h"

namespace Axiom
{

class CameraManager
{
  public:
    CameraManager();

    void update();
    
    void setRotatingSpeed(float speed) { m_rotating_speed = speed; }

    Camera3D &getRawCamera() { return m_camera; }

  private:
    Camera3D m_camera;
    float m_rotating_speed;
};

} // namespace Axiom
