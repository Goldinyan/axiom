#include "Renderer.hpp"

namespace Axiom
{

void Renderer::DrawPlotter(const Model &surfaceModel, CameraManager &cameraManager)
{
        BeginMode3D(cameraManager.getRawCamera());

        if (surfaceModel.meshes != nullptr && surfaceModel.meshCount > 0)
        {
                DrawModel(surfaceModel, {0, 0, 0}, 1.0f, WHITE);
                DrawModelWires(surfaceModel, {0, 0, 0}, 1.0f, DARKGRAY);
        }

        DrawLine3D({-20, 0, 0}, {20, 0, 0}, RAYWHITE);
        DrawTriangle3D({21, 0, 0}, {20, 1, 0}, {20, -1, 0}, RAYWHITE);
        DrawLine3D({0, -20, 0}, {0, 20, 0}, RAYWHITE);
        DrawLine3D({0, 0, -20}, {0, 0, 20}, RAYWHITE);

        EndMode3D();
}

} // namespace Axiom
