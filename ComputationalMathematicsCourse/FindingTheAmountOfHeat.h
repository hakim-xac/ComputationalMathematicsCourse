#pragma once
#include <iostream>
#include <optional>
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

        void init() noexcept;
        void showHeader(std::ostream& out = std::cout) const noexcept;
        void showUnknownCommand(std::ostream& out = std::cout) const noexcept;

        template <typename T, typename TString>
            requires std::is_convertible_v<TString, std::string>
        std::optional<T> showReadCommand(TString&& str,  std::istream& in = std::cin) const noexcept;

    private:
        void findingTheRootOfANonlinearEquation() const noexcept;
        std::pair<double, size_t> calculationFindingTheRootOfANonlinearEquation(double left_range, double right_range) const noexcept;
        double mathFunc(double x) const noexcept;
        void printFindingTheRootOfANonlinearEquation(double x, size_t count_iterations) const noexcept;

        

    private:
        size_t width_screen_;
        InputData data_;
        Menu menu_;
    };
}

#include "FindingTheAmountOfHeat.hpp"