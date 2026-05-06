#include "generator.hpp"
#include "Vector3.hpp"
#include <vector>

namespace Axiom
{

Generator::Generator() {};

std::vector<Vector3> Generator::generate(Expression expr, std::pair<Vector3, Vector3> limits, float step)
{
        int resolution = 100; // 100 Punkte pro achse
        std::vector<Vector3> points;
        points.reserve((resolution + 1) * (resolution + 1));

        float x_start = limits.first.x;
        float x_end = limits.second.x;
        float y_start = limits.first.y;
        float y_end = limits.second.y;
        float x_range = x_end - x_start;
        float y_range = y_end - y_start;

        for (int i = 0; i <= resolution; ++i)
        {
                float x = x_start + (static_cast<float>(i) / resolution) * x_range;

                for (int j = 0; j <= resolution; ++j)
                {
                        float y = y_start + (static_cast<float>(j) / resolution) * y_range;
                        float z = expr.eval(x, y);
                        points.emplace_back(x, y, z);
                }
        }

        return points;
}
} // namespace Axiom
