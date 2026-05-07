
#include "../../core/src/geometry/Generator.hpp"
#include "../../core/src/tokenizer/Lexer.hpp"
#include "fmt/core.h"
#include <iostream>

// Nur inkludieren, wenn wir NICHT im CLI-Modus sind
#ifndef NO_UI
#include "app/camera.hpp"
#include "raylib.h"
#include "rlgl.h"
#endif

void draw_grid();

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
        // --- NORMALER UI MODUS (RAYLIB) ---
        InitWindow(960, 1280, "Axiom");

        Axiom::CameraManager cameraManager;

        // Auch im UI Modus können wir kurz die Tokens in die Konsole werfen
        Axiom::Lexer lexer("f(x) = x*2");
        lexer.tokenize();
        auto tokens = lexer.get_tokens();

        Axiom::Generator generator;
        Axiom::Expression expr;
        expr.params = {true, false};
        auto points = generator.generate(expr, {{-15, -15, -15}, {15, 15, 15}}, 300);

        /*for (const auto &token : tokens)
        {
                fmt::print("Token: Lexeme='{}', Type={}\n", token.lexeme, (int)token.type);
        }

        for (const auto &p : points)
        {
                fmt::print("Punkt: ({}, {}, {})\n", p.x, p.y, p.z);
        }*/

        SetTargetFPS(120);

        Axiom::Vector3 point = points[0];
        size_t index = 0;

        while (!WindowShouldClose())
        {
                cameraManager.update();

                BeginDrawing();
                ClearBackground(DARKGRAY);

                BeginMode3D(cameraManager.getRawCamera());
                // draw_grid();
                for (const auto &p : points)
                {
                        //DrawLine3D((Vector3){point.x, point.y, point.z}, (Vector3){p.x, p.y, p.z}, GREEN);
                        DrawPoint3D({p.x, p.y, p.z}, GREEN);
                        point = p;
                        index++;
                        if (index >= points.size())
                        {
                                index = 0;
                                point = points[0];
                        }
                }

                DrawLine3D({-20, 0, 0}, {20, 0, 0}, RAYWHITE);
                DrawTriangle3D({21, 0, 0}, {20, 1, 0}, {20, -1, 0}, RAYWHITE);
                DrawLine3D({0, -20, 0}, {0, 20, 0}, RAYWHITE);
                DrawLine3D({0, 0, -20}, {0, 0, 20}, RAYWHITE);

                EndMode3D();
                DrawFPS(10, 10);
                EndDrawing();
        }

        CloseWindow();
#endif

        return 0;
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

/*
 *Der Kleber. Initialisiert das Fenster, startet den Loop, ruft den
 * input_handler auf und lässt den renderer alles zeichnen.
 */

/*
* Der Datenfluss (The "Happy Path")

    User tippt x*x + y*y in der ui_layer ein.

    Die app gibt den String an core::generator.

    Der generator nutzt math::parser, berechnet alle Punkte und füllt ein
core::mesh.

    Die app::scene nimmt das mesh, lädt die Daten in die Buffer der Grafikkarte
(VBO/VAO).

    Der input_handler bemerkt ein Mausziehen und bewegt die camera.

    Der renderer zeichnet alles mit den shaders neu.
*
*/

/*
#include "fmt/format.h"
#include "app/input_handler.hpp"
#include "app/renderer/scene.hpp"
#include "app/ui_layer.hpp"
#include "core/geometry/generator.hpp"

// Hier kommen später die GLFW/OpenGL Includes hin
// #include <GLFW/glfw3.h>

int main(int argc, char *argv[])
{
    // 1. INITIALISIERUNG
    // Fenster erstellen (GLFW), OpenGL Kontext laden (Glad/Glew)
    fmt::print("Axiom Plotter wird gestartet...\n");

    // 2. OBJEKTE ERSTELLEN
    axiom::Generator generator;
    axiom::Scene scene;
    axiom::InputHandler input;
    axiom::UILayer ui;

    // Initialer Plot
    auto initialMesh = generator.generate("x*x + y*y");
    scene.loadMesh(initialMesh);

    // 3. MAIN LOOP
    while (!windowShouldClose)
    {
        // A. Input verarbeiten (Maus/Keyboard)
        input.update();

        // B. UI Zeichnen (ImGui)
        ui.render();
        if (ui.functionChanged())
        {
            // Happy Path: Neuer String -> Neues Mesh -> GPU Update
            auto newMesh = generator.generate(ui.getFunctionString());
            scene.loadMesh(newMesh);
        }

        // C. Rendering
        scene.draw(); // Nutzt intern die Camera-Matrix vom input_handler

        // D. Buffer Swapping
        // glfwSwapBuffers(window);
    }

    return 0;
}
*/
