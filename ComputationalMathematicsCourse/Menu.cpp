#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Menu.h"
#include "Functions.h"

namespace KHAS {

    Menu::Menu(size_t width_screen, size_t reserve_buffer)
        : width_screen_{ width_screen }
        , buffer_{}
    {
        buffer_.reserve(reserve_buffer);
    }

    void Menu::show(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        out << delim << "\n";
        out << generateString("Μενώ", width_screen_) << "\n";
        out << delim << "\n";
        for (auto&& elem : buffer_) {
            auto name{ elem.getName() };
            assert(name.size() + 10 <= width_screen_);
            out << std::setw(5) << std::right << elem.getId() << " | " << std::setw(width_screen_ - 10) << std::right << name << " |\n";
        }
        out << delim << "\n";
    }

    bool Menu::runCommand(size_t cmd) const noexcept
    {
        if (cmd < 0 || cmd > buffer_.size()) return false;
        if (cmd == 0) return true;
        buffer_[cmd - 1].call();
        return true;
    }

}