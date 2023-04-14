#pragma once
#include <string>

namespace KHAS {

    std::string delimiter(char c, size_t width_screen) noexcept;

    template <typename Str>
        requires std::is_convertible_v<Str, std::string>
    std::string generateString(Str&& str, size_t width_screen) noexcept;

    double precision(double num, size_t degree) noexcept;
}

#include "Functions.hpp"