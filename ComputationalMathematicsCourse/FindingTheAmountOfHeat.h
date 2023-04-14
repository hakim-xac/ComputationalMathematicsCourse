#pragma once
#include <iostream>
#include "Menu.h"
#include "InputData.h"

namespace KHAS {
    class FindingTheAmountOfHeatSingleton final
    {
    public:
        FindingTheAmountOfHeatSingleton(const FindingTheAmountOfHeatSingleton&) = delete;
        void operator =(const FindingTheAmountOfHeatSingleton&) = delete;

        template <typename TData>
            requires std::is_convertible_v<TData, InputData>
        static FindingTheAmountOfHeatSingleton& getInstance(TData&& data, size_t width_screen);

    public:
        void loop() const noexcept;

    private:
        template <typename TData>
            requires std::is_convertible_v<TData, InputData>
        FindingTheAmountOfHeatSingleton(TData&& data, size_t width_screen);

        void showHeader(std::ostream& out = std::cout) const noexcept;
        void showUnknownCommand(std::ostream& out = std::cout) const noexcept;
        size_t showReadCommand(std::istream& in = std::cin) const noexcept;
    private:
        size_t width_screen_;
        InputData data_;
        Menu menu_;
    };


    template <typename TData>
        requires std::is_convertible_v<TData, InputData>
    FindingTheAmountOfHeatSingleton::FindingTheAmountOfHeatSingleton(TData&& data, size_t width_screen)
        : width_screen_{width_screen}
        , data_{data}
        , menu_{width_screen} {}




    template <typename TData>
        requires std::is_convertible_v<TData, InputData>
    FindingTheAmountOfHeatSingleton& FindingTheAmountOfHeatSingleton::getInstance(TData&& data, size_t width_screen)
    {
        static FindingTheAmountOfHeatSingleton instance{ std::forward<TData>(data), width_screen };
        return instance;
    }

}