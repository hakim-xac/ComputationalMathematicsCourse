#include <cassert>
#include <string>
#include <sstream>
#include <type_traits>
#include <iomanip>

namespace KHAS {

    template <typename Str>
        requires std::is_convertible_v<Str, std::string>
    std::string generateString(Str&& str, size_t width_screen) noexcept {

        std::string s{ std::forward<Str>(str) };

        size_t size{ s.size() };

        assert(size + 4 <= width_screen);
        size_t part_size{ (width_screen - size - 4) >> 1 };
        size_t offset{ width_screen - ((part_size << 1) + 4 + size) };

        return "| " + std::string(part_size, ' ') + s + std::string(part_size + offset, ' ') + " |";
    }

    template <typename T>
    [[nodiscard]] std::optional<std::string> typeToString(T&& value) {

        using opt_type = std::optional<std::string>;

        std::stringstream ss{ "" };
        ss << std::forward<T>(value);
        return ss.good() ? opt_type{ ss.str() } : std::nullopt;
    }

    template <typename T>
        requires std::is_floating_point_v<T>
    [[nodiscard]] std::optional<std::string> typeToString(const T& value, size_t prec) {
        using opt_type = std::optional<std::string>;
        std::stringstream ss{ "" };
        ss << std::fixed << std::setprecision(prec) << precision(value, prec);
        return ss.good() ? opt_type{ ss.str() } : std::nullopt;
    }
}