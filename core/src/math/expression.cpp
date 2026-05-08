

#include "Expression.hpp"
namespace Axiom
{

float Expression::eval(std::optional<float> x, std::optional<float> y)
{
        return static_cast<float>(x.value_or(0.0f) * x.value_or(0.0f));
}

} // namespace Axiom
