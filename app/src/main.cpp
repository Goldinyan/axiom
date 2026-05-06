
#include "../../core/src/tokenizer/Lexer.hpp"
#include "fmt/core.h"
#include <iostream>

// Nur inkludieren, wenn wir NICHT im CLI-Modus sind
#ifndef NO_UI
#include "app/camera.hpp"
#include "raylib.h"
#endif

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

#else
        // --- NORMALER UI MODUS (RAYLIB) ---
        InitWindow(960, 1280, "Axiom");

        Axiom::CameraManager cameraManager;

        // Auch im UI Modus können wir kurz die Tokens in die Konsole werfen
        Axiom::Lexer lexer("f(x) = x*2");
        lexer.tokenize();
        auto tokens = lexer.get_tokens();

        for (const auto &token : tokens)
        {
                fmt::print("Token: Lexeme='{}', Type={}\n", token.lexeme, (int)token.type);
        }

        SetTargetFPS(120);

        while (!WindowShouldClose())
        {
                cameraManager.update();

                BeginDrawing();
                ClearBackground(RAYWHITE);

                BeginMode3D(cameraManager.getRawCamera());
                DrawGrid(10, 1.0f);
                EndMode3D();

                DrawFPS(10, 10);
                EndDrawing();
        }

        CloseWindow();
#endif

        return 0;
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

