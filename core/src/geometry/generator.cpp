#include "Generator.hpp"
#include "../utils/logger.hpp"
#include "Vector3.hpp"
#include "fmt/core.h"
#include <vector>
#include <cmath>

namespace Axiom
{

Generator::Generator() {};

std::vector<Vector3> Generator::generate(Expression expr, std::pair<Vector3, Vector3> limits, float step, bool clampZ)
{
        bool check_x = true;
        bool check_y = true;

        auto start =
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        Logger::info("Generating points...");
        int resolution = step ? step : 100; // 100 Punkte pro achse
        std::vector<Vector3> points;
        points.reserve((resolution + 1) * (resolution + 1));

        if (expr.params.empty())
        {
                Logger::err("Expression has no parameters. Cannot generate points.");
                return points;
        }

        if (!expr.params.at(0))
                check_x = false;

        if (!expr.params.at(1))
                check_y = false;

        float x_start = limits.first.x;
        float x_end = limits.second.x;
        float y_start = limits.first.y;
        float y_end = limits.second.y;
        float x_range = x_end - x_start;
        float y_range = y_end - y_start;

        int x_steps = check_x ? resolution : 0;
        int y_steps = check_y ? resolution : 0;

        // we have resolution * resoltion points, so with 100 res we have 10K points

        for (int i = 0; i <= x_steps; ++i)
        {
                float x = (x_steps > 0)
                              ? x_start + (static_cast<float>(i) / x_steps) * x_range
                              : 0.0f;

                for (int j = 0; j <= y_steps; ++j)
                {
                        float y = (y_steps > 0)
                                      ? y_start + (static_cast<float>(j) / y_steps) * y_range
                                      : 0.0f;

                        // f(x, y) auswerten
                        //
                        if (!check_y)
                        {
                                float y0 = expr.eval(x, 0);

                                points.emplace_back(x, y0, 0);
                        }
                        else
                        {
                                float z = expr.eval(x, y);

                                if (clampZ) {
                                        // Clamp z auf die Limits
                                        if (z > limits.second.z)
                                                z = limits.second.z;
                                        if (z < limits.first.z)
                                                z = limits.first.z;
                                        points.emplace_back(x, y, z);
                                } else {
                                        // Mark Punkte außerhalb der Limits als NaN
                                        if (z > limits.second.z || z < limits.first.z)
                                                z = NAN;
                                        points.emplace_back(x, y, z);
                                }
                        }
                }
        }

        auto end =
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        Logger::info(fmt::format("Generated {} points in {} seconds.",
                                 points.size(),
                                 std::difftime(end, start)));

        return points;
}
} // namespace Axiom
