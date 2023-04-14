#pragma once
#include <string>
#include <functional>
#include <iostream>


namespace KHAS {

    class MenuItem final
    {
    public:
        template <typename Name, typename Func>
            requires std::is_convertible_v<Name, std::string>
        explicit inline MenuItem(Name&& name, Func&& func);

        size_t getId() const noexcept;
        const std::string& getName() const& noexcept;
        void call()const noexcept;

    private:
        const size_t createId() const noexcept;
    private:
        std::string name_{ "-" };
        std::function<void()> func_;
        size_t id_{};
    };


}
#include "MenuItem.hpp"
