#include <string>
#include <cmath>
#include "Functions.h"

namespace KHAS {

    std::string delimiter(char c, size_t width_screen) noexcept
    {
        return std::string(width_screen, c);
    }
    double KHAS::precision(double num, size_t degree) noexcept
    {
        auto tmp{ std::pow(10., degree) };
        return std::round(num * tmp) / tmp;
    }
}