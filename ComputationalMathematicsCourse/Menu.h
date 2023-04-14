#pragma once
#include <vector>
#include <string>
#include "MenuItem.h"

namespace KHAS {
    class Menu final
    {
    public:
        explicit Menu(size_t width_screen, size_t reserve_buffer = 2);

        void show(std::ostream& out = std::cout) const noexcept;
        bool runCommand(size_t cmd) const noexcept;

        template <typename Name, typename Func>
            requires std::is_convertible_v<Name, std::string>
        void insert(Name&& name, Func&& func) noexcept;
    private:
        size_t width_screen_;
        std::vector<MenuItem> buffer_;
    };

}

#include "Menu.hpp"