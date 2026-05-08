#include "Application.hpp"
#include "../../core/src/constants/UIConstants.hpp"
#include "../../core/src/geometry/MeshBuilder.hpp"
#include "../core/src/utils/logger.hpp"
#include "Renderer.hpp"
#include "SettingsManager.hpp"
#include "raylib.h"

namespace Axiom
{

Application::Application()
{
        Logger::info("Application initialized.");
        m_surfaceModel = {0};
}

Application::~Application()
{
        Logger::info("Application shutting down.");
        if (m_surfaceModel.meshCount > 0)
        {
                UnloadModel(m_surfaceModel);
        }
}

void Application::run()
{
        m_expressions.push_back(Axiom::Expression());
        m_expressions[0].params = {true, true};

        InitWindow(960, 1280, "Axiom");
        SetTargetFPS(120);

        m_ui_manager.init();

        while (!WindowShouldClose())
        {
                update();
                render();
        }

        m_ui_manager.CleanUp();
        if (m_surfaceModel.meshCount > 0)
        {
                UnloadModel(m_surfaceModel);
                m_surfaceModel = {0}; // WICHTIG: Markiert das Model als leer/gelöscht
        }
        CloseWindow();

        return;
}

void Application::update()
{
        m_camera.update();

        if(SettingsManager::getInstance().changed)
        {
                RefreshMesh();
                SettingsManager::getInstance().changed = false;
        }

        // Space-Logik jetzt hier
        if (IsKeyPressed(KEY_SPACE))
        {
                m_clampZ = !m_clampZ;
                RefreshMesh(); // Hilfsfunktion zum neu generieren
        }
}

void Application::render()
{
        BeginDrawing();
        ClearBackground(Axiom::BACKGROUND_COLOR_PLOTTER);

        Renderer::DrawPlotter(m_surfaceModel, m_camera);

        m_ui_manager.draw();

        DrawFPS(10, 10);
        EndDrawing();
}

void Application::RefreshMesh()
{
        float res = SettingsManager::getInstance().getResolution();
        bool clamp = SettingsManager::getInstance().getClampZ();

        UnloadModel(m_surfaceModel);
        auto newPoints = m_generator.generate(m_expressions[0], {{-15, -15, -15}, {15, 15, 15}}, res, clamp);
        Mesh newMesh = Axiom::MeshBuilder::CreateMeshFromPoints(newPoints, res);
        m_surfaceModel = LoadModelFromMesh(newMesh);
        m_surfaceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;
}

} // namespace Axiom
