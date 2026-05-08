
#include "../../core/src/geometry/Generator.hpp"
#include "../../core/src/geometry/MeshBuilder.hpp"
#include "../../core/src/tokenizer/Lexer.hpp"
#include "UI/UIManager.hpp"
#include "fmt/core.h"
#include <iostream>

// Nur inkludieren, wenn wir NICHT im CLI-Modus sind
#ifndef NO_UI
#include "../../core/src/constants/UIConstants.hpp"
#include "app/camera.hpp"
#include "raylib.h"
#include "rlgl.h"
#endif

void draw_grid();
void draw_plotter(Model surfaceModel, Axiom::CameraManager &cameraManager);

int main()
{
#ifdef NO_UI
        // --- CLI DEBUG MODUS ---
        fmt::print("Axiom CLI Debug Mode\n");
        fmt::print("--------------------\n");

        Axiom::Lexer lexer("g(x, y) = x - y");
        auto tokens = lexer.tokenize();

        fmt::print("TOKENS:\n");
        for (const auto &token : tokens)
        {
                fmt::print("  -> Lexeme='{}', Type={}\n", token.lexeme, (int)token.type);
        }

        fmt::print("--------------------\n");
        fmt::print("Lexing beendet.\n");
        fmt::print("Debug Points.\n");
        Axiom::Generator generator;
        auto points = generator.generate(Axiom::Expression(), {{-10, -10, -10}, {10, 10, 10}}, 10);
        fmt::print("Generierte Punkte:\n");
        for (const auto &point : points)
        {
                fmt::print("  -> ({}, {}, {})\n", point.x, point.y, point.z);
        }

#else
        InitWindow(960, 1280, "Axiom");

        Axiom::CameraManager cameraManager;

        Axiom::Lexer lexer("f(x) = x*2");
        lexer.tokenize();
        auto tokens = lexer.get_tokens();

        Axiom::Generator generator;
        Axiom::Expression expr;
        Axiom::UIManager uiManager;
        expr.params = {true, true};
        
        bool clampZ = true;  // Toggle zwischen Clamp und Skip
        
        auto points = generator.generate(expr, {{-15, -15, -15}, {15, 15, 15}}, 200, clampZ);

        Mesh surfaceMesh = Axiom::MeshBuilder::CreateMeshFromPoints(points, 200);
        Model surfaceModel = LoadModelFromMesh(surfaceMesh);
        surfaceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = Axiom::POINTS_COLOR_PLOTTER;

        SetTargetFPS(120);

        while (!WindowShouldClose())
        {
                cameraManager.update();
                
                // Toggle clampZ mit Leertaste
                if (IsKeyPressed(KEY_SPACE)) {
                        clampZ = !clampZ;
                        UnloadModel(surfaceModel);
                        auto newPoints = generator.generate(expr, {{-15, -15, -15}, {15, 15, 30}}, 200, clampZ);
                        Mesh newMesh = Axiom::MeshBuilder::CreateMeshFromPoints(newPoints, 200);
                        surfaceModel = LoadModelFromMesh(newMesh);
                        surfaceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = Axiom::POINTS_COLOR_PLOTTER;
                }

                BeginDrawing();
                ClearBackground(Axiom::BACKGROUND_COLOR_PLOTTER);
        
                draw_plotter(surfaceModel, cameraManager);

                uiManager.draw();
                DrawFPS(10, 10);
                DrawText(clampZ ? "Z: CLAMP (Press SPACE to SKIP)" : "Z: SKIP (Press SPACE to CLAMP)", 10, 30, 20, RAYWHITE);
                EndDrawing();
        }

        UnloadModel(surfaceModel);
        CloseWindow();
#endif

        return 0;
}

void draw_plotter(Model surfaceModel, Axiom::CameraManager &cameraManager)
{
        BeginMode3D(cameraManager.getRawCamera());
        
        DrawModel(surfaceModel, {0, 0, 0}, 1.0f, WHITE);
        
        DrawModelWires(surfaceModel, {0, 0, 0}, 1.0f, Axiom::POINTS_COLOR_PLOTTER);

        DrawLine3D({-20, 0, 0}, {20, 0, 0}, RAYWHITE);
        DrawTriangle3D({21, 0, 0}, {20, 1, 0}, {20, -1, 0}, RAYWHITE);
        DrawLine3D({0, -20, 0}, {0, 20, 0}, RAYWHITE);
        DrawLine3D({0, 0, -20}, {0, 0, 20}, RAYWHITE);

        EndMode3D();
}

void draw_grid()
{

        // 1. Das normale, horizontale Grid (XZ-Ebene)
        DrawGrid(20, 1.0f);

        rlPushMatrix();         // Speichert den aktuellen Zustand der Welt
        rlRotatef(90, 1, 0, 0); // Rotiere um 90 Grad um die X-Achse
        DrawGrid(20, 1.0f);     // Zeichne das Grid (es ist jetzt vertikal)
        rlPopMatrix();          // Stellt den Zustand wieder her

        rlPushMatrix();
        rlRotatef(90, 0, 0, 1); // Rotiere um 90 Grad um die Z-Achse
        DrawGrid(20, 1.0f);
        rlPopMatrix();
}
