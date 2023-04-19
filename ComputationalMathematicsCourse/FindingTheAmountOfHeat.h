#pragma once
#include <iostream>
#include <optional>
#include "Menu.h"
#include "InputData.h"

namespace KHAS {
    class FindingTheAmountOfHeatSingleton final
    {
    private:
        struct DB { double a, b, c, d; };
        struct LinierInterpolation { double left, right, step; };

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
        double mathFunc2(double x, double y) const noexcept;
        void printFindingTheRootOfANonlinearEquation(double x, size_t count_iterations) const noexcept;

        std::vector<DB> rungeKuttaMethodInArray() const noexcept;
        void printRungeKuttaMethod() const noexcept;
        double mathRungeKutta(double x, double y, double h) const noexcept;
        double calculateHalfHeight(double x, double y, double h, size_t step) const noexcept;

        double mathLinearInterpolation(const DB& db, double x) const noexcept;
        std::vector<std::pair<double, double>> linearInterpolation(const LinierInterpolation& lip) const noexcept;
        DB searchInRungeKuttaArray(double x, const std::vector<FindingTheAmountOfHeatSingleton::DB>& base) const noexcept;
        void printLinearInterpolation() const noexcept;

        void printIntegralTrapezoidMethod() const noexcept;
        double calculateIntegralTrapezoidMethod() const noexcept;
        double integralMethod(double y) const noexcept;

    private:
        size_t width_screen_;
        InputData data_;
        Menu menu_;

        std::vector<FindingTheAmountOfHeatSingleton::DB> array_runge_kutta_;
        std::vector<std::pair<double, double>> array_linear_interpolation_;
    };
}

#include "FindingTheAmountOfHeat.hpp"