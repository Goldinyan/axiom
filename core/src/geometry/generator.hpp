#pragma once

#include "Vector3.hpp"
#include <utility>
#include <vector>
#include "../math/Expression.hpp"

namespace Axiom
{

class Generator
{
public:
        Generator();

        std::vector<Vector3> generate(Expression expr, std::pair<Vector3, Vector3> limits, float step, bool clampZ = true);
private:
};
} // namespace Axiom
