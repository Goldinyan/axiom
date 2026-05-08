#pragma once

#include "raylib.h"
#include "Camera.hpp"

namespace Axiom
{

class Renderer
{
public:
        static void DrawPlotter(const Model& surfaceModel, CameraManager &cameraManager);

};

} // namespace Axiom
