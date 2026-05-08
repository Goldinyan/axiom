// core/include/axiom/Constants.hpp
#pragma once

#include "raylib.h"

namespace Axiom
{

inline constexpr Color BACKGROUND_COLOR_PLOTTER = {77, 77, 77, 255};
inline constexpr Color POINTS_COLOR_PLOTTER = {16, 23, 148, 255};

inline constexpr int DEFAULT_RESOLUTION = 100;
inline constexpr float DEFAULT_STEP = 0.1f;

inline constexpr float CAMERA_SENSITIVITY = 0.01f;
inline constexpr float MOUSE_WHEEL_SPEED = 2.0f;

} // namespace Axiom
