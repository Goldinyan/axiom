
#include "../../core/src/geometry/Generator.hpp"
#include "SettingsManager.hpp"
#include "UI/UIManager.hpp"
#include "fmt/core.h"
#include "Camera.hpp"
#include "raylib.h"
#include "rlgl.h"

namespace Axiom
{
class Application
{
public:
        Application();
        ~Application();
        void run(); 

private:
        void update(); 
        void render(); 
        void RefreshMesh();

private:
        UIManager m_ui_manager;
        CameraManager m_camera;
        Generator m_generator;
        Model m_surfaceModel;
        std::vector<Expression> m_expressions;
        bool m_clampZ = true;
};
} // namespace Axiom
