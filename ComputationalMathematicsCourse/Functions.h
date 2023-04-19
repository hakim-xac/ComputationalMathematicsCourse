#pragma once
#include <string>
#include <optional>

namespace KHAS {

    std::string delimiter(char c, size_t width_screen) noexcept;
    double precision(double num, size_t degree) noexcept;

    template <typename Str>
        requires std::is_convertible_v<Str, std::string>
    std::string generateString(Str&& str, size_t width_screen) noexcept;

    template <typename T>
    [[nodiscard]] std::optional<std::string> typeToString(T&& value);

    template <typename T>
        requires std::is_floating_point_v<T>
    [[nodiscard]] std::optional<std::string> typeToString(const T& value, size_t prec);

}

#include "Functions.hpp"