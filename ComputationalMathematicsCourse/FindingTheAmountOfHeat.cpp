#include "FindingTheAmountOfHeat.h"
#include "Functions.h"
#include <iomanip>
#include <cassert>
#include <vector>
#include <numeric>


namespace KHAS {

    void FindingTheAmountOfHeatSingleton::showHeader(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        std::string subject_header{ "Дисциплина:" };
        std::string subject_name{ "Вычислительная математика" };
        std::string student_header{ "Студент:" };
        std::string student_name{ "Хакимов А.С." };
        std::string group_header{ "Группа:" };
        std::string group_name{ "ПБ-11" };
        std::string variant_header{ "Вариант:" };
        std::string variant_name{ "№1" };
        std::string theme_header{ "Тема:" };
        std::string theme_name{ "Численное дифференцирование" };

        std::string left_range_header{ "Точность:" };
        std::string left_range_name{ typeToString(data_.accuracy, 4).first };
        std::string right_range_header{ "Точность для Рунге-Кутта:" };
        std::string right_range_name{ typeToString(data_.accuracy_for_kutt, 4).first };
        std::string error_header{ "Погрешность:" };
        std::string error_name{ typeToString(data_.error, 4ull).first };

        size_t width{ (width_screen_ - 3) / 2 - 2 };
        size_t offset{ width_screen_ % 2 == 0 };
        assert(width >= 0 && "you need to increase the width of the output on the screen");
        assert(subject_header.size() <= width && subject_name.size() <= width);
        assert(student_header.size() <= width && student_name.size() <= width);
        assert(group_header.size() <= width && group_name.size() <= width);
        assert(variant_header.size() <= width && variant_name.size() <= width);
        assert(theme_header.size() <= width && theme_name.size() <= width);

        assert(left_range_header.size() <= width && left_range_name.size() <= width);
        assert(right_range_header.size() <= width && right_range_name.size() <= width);
        assert(error_header.size() <= width && error_name.size() <= width);


        out << delim << "\n";
        out << "| " << std::setw(width) << std::left << subject_header << " | " << std::setw(width + offset) << std::right << subject_name << " |\n";
        out << "| " << std::setw(width) << std::left << student_header << " | " << std::setw(width + offset) << std::right << student_name << " |\n";
        out << "| " << std::setw(width) << std::left << group_header << " | " << std::setw(width + offset) << std::right << group_name << " |\n";
        out << "| " << std::setw(width) << std::left << variant_header << " | " << std::setw(width + offset) << std::right << variant_name << " |\n";
        out << "| " << std::setw(width) << std::left << theme_header << " | " << std::setw(width + offset) << std::right << theme_name << " |\n";
        out << delim << "\n";
        out << "| " << std::setw(width) << std::left << left_range_header << " | " << std::setw(width + offset) << std::right << left_range_name << " |\n";
        out << "| " << std::setw(width) << std::left << right_range_header << " | " << std::setw(width + offset) << std::right << right_range_name << " |\n";
        out << "| " << std::setw(width) << std::left << error_header << " | " << std::setw(width + offset) << std::right << error_name << " |\n";

        out << delim << "\n";
    }

    void FindingTheAmountOfHeatSingleton::init() noexcept
    {

        array_runge_kutta_ = rungeKuttaMethodInArray();
        array_linear_interpolation_ = linearInterpolation(LinierInterpolation{ 0, 2, 0.1 });

        menu_.insert("Нахождение корня нелинейного уравнения методом хорд.", [&]() { findingTheRootOfANonlinearEquation(); });
        menu_.insert("Решение дифференциального уравнения методом Рунге-Кутта четвертого порядка.", [&] { printRungeKuttaMethod(); });
        menu_.insert("Нахождение с помощью линейной интерполяции приближенных значения функции.", [&] { printLinearInterpolation(); });
        menu_.insert("Определение количества теплоты методом трапеций.", [&] { printIntegralTrapezoidMethod(); });
        menu_.insert("Выход", [] {});
    }

    void FindingTheAmountOfHeatSingleton::showUnknownCommand(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        out << delim << "\n";
        out << generateString("Неизвестная команда", width_screen_) << "\n";
        out << delim << "\n";
    }

    void FindingTheAmountOfHeatSingleton::loop() const noexcept
    {
        size_t cmd{};
        size_t exit_code{ menu_.exitCode() };
        while (cmd != exit_code) {
            system("cls");
            showHeader();

            if (!menu_.runCommand(cmd)) showUnknownCommand();

            menu_.show();

            cmd = showReadCommand<size_t>("Введите команду:").value_or(0);
        }
    }

    double FindingTheAmountOfHeatSingleton::mathFunc(double x) const noexcept {
        return 3 * pow(x, 4) + 8 * pow(x, 3) + 6 * pow(x, 2) - 10;
    }

    double FindingTheAmountOfHeatSingleton::mathFunc2(double x, double y) const noexcept {
        return 1 - sin(3 * x + y) + (y / (2 + x));
    }

    void FindingTheAmountOfHeatSingleton::findingTheRootOfANonlinearEquation() const noexcept {
        auto left_range{ showReadCommand<double>("Введите нижнюю границу интервала изоляции корня нелинейного уравнения:").value_or(0) };
        auto right_range{ showReadCommand<double>("Введите верхнюю границу интервала изоляции корня нелинейного уравнения:").value_or(0) };
        
        auto&& [result, count] { calculationFindingTheRootOfANonlinearEquation(left_range, right_range) };
        printFindingTheRootOfANonlinearEquation(result, count);
    }

    std::pair<double, size_t> FindingTheAmountOfHeatSingleton::calculationFindingTheRootOfANonlinearEquation(double left_range, double right_range) const noexcept {
        
        assert(left_range - data_.accuracy > 0 || right_range - data_.accuracy > 0);
        assert(data_.accuracy > 0.000001);

        size_t count{};
        double left_range_tmp{ left_range };
        double right_range_tmp{ right_range };

        while(fabs(right_range_tmp - left_range_tmp) > data_.accuracy) {
            ++count;
            auto math_left_range{ mathFunc(left_range) };
            auto math_right_range{ mathFunc(right_range) };
            auto tmp{ left_range - (math_left_range /(math_right_range - math_left_range) ) * (right_range- left_range) };
            
            left_range_tmp = std::exchange(right_range_tmp, tmp);

            if (math_left_range * mathFunc(tmp) < 0) right_range = right_range_tmp;
            else left_range = right_range_tmp;
        }
        return { right_range_tmp , count };
    }


    void FindingTheAmountOfHeatSingleton::printFindingTheRootOfANonlinearEquation(double x, size_t count_iterations) const noexcept {
        std::cout << "x: " << x << "\n" << "count: " << count_iterations << "\n";
    }


    std::vector<FindingTheAmountOfHeatSingleton::DB> FindingTheAmountOfHeatSingleton::rungeKuttaMethodInArray() const noexcept {

        double h{ 0.25 };
        double x{};
        double x2{ 2 };
        auto&& [y, _] { calculationFindingTheRootOfANonlinearEquation(x, x2) };

        double yy{ y };
        double xx{ x };

        auto num{ static_cast<size_t>(round(1 + (x2 - x) / h)) };
        std::vector<DB> arr;
        arr.emplace_back(DB{ x, y, y, 0 });

        for (size_t i{ 1 }, ie{ num }; i != ie; ++i) {
            DB db{};
            db.a = xx + h;
            db.b = mathRungeKutta(xx, yy, h);
            db.c = calculateHalfHeight(x, y, h, i);
            db.d = fabs(db.b - db.c);

            xx += h;
            yy = db.b;
            arr.emplace_back(std::move(db));
        }

        return arr;
    }


    double FindingTheAmountOfHeatSingleton::calculateHalfHeight(double x, double y, double height, size_t step) const noexcept {
        
        double xx{ x };
        double yy{y};
        double h{ height / 2 };
        for (size_t i{}, ie{2*step}; i != ie; ++i) {
            yy = mathRungeKutta(xx, yy, h);
            xx += h;
        }
        return yy;
    }


    double FindingTheAmountOfHeatSingleton::mathRungeKutta(double x, double y, double h) const noexcept {
        double k{ mathFunc2(x, y) };
        double k2{ mathFunc2(x+h/2, y+(h*k)/2) };
        double k3{ mathFunc2(x+h/2, y+(h*k2)/2) };
        double k4{ mathFunc2(x+h, y+h*k3) };
        return y + (h * (k + 2 * k2 + 2 * k3 + k4)) / 6.0;
    }


    void FindingTheAmountOfHeatSingleton::printRungeKuttaMethod() const noexcept {
        for (auto&& elem: array_runge_kutta_) {
            std::cout << precision(elem.a, 4) << " | "
                << precision(elem.b, 4) << " | "
                << precision(elem.c, 4) << " | "
                << precision(elem.d, 4) << "\n";
        }
    }


    std::vector<std::pair<double, double>> FindingTheAmountOfHeatSingleton::linearInterpolation(const LinierInterpolation& lip) const noexcept {
        std::vector<std::pair<double, double>> arr;
        arr.reserve(static_cast<size_t>(round(1 + ((lip.right-lip.left) / lip.step))));

        auto base{ rungeKuttaMethodInArray() };

        for (double i{ lip.left }, ie{ lip.right }; i < ie; i += lip.step) {
            auto fn{ searchInRungeKuttaArray(i, base) };
            arr.emplace_back(i, mathLinearInterpolation(std::move(fn), i));
        }
        arr.emplace_back(lip.right, base.back().c);
        return arr;
    }


    FindingTheAmountOfHeatSingleton::DB FindingTheAmountOfHeatSingleton::searchInRungeKuttaArray(double x, const std::vector<FindingTheAmountOfHeatSingleton::DB>& base) const noexcept {
        
        assert(base.size() > 0);

        for (size_t i{}, ie{ base.size()-1 }; i != ie; ++i) {
            if (x >= base[i].a && x <= base[i+1].a) {
                return { base[i].a, base[i+1].a, base[i].c, base[i+1].c };
            }
        }
        return DB{};
    }


    double FindingTheAmountOfHeatSingleton::mathLinearInterpolation(const DB& db, double x) const noexcept {
        return db.c+(x-db.a)*((db.d-db.c)/(db.b-db.a));
    }


    void FindingTheAmountOfHeatSingleton::printLinearInterpolation() const noexcept {

        for (auto&& elem : array_linear_interpolation_) {
            std::cout << precision(elem.first, 4) << " | "
                << precision(elem.second, 4) << "\n";
        }
    }


    double FindingTheAmountOfHeatSingleton::calculateIntegralTrapezoidMethod() const noexcept {
        double arithmetic_mean{ (integralMethod(array_linear_interpolation_.front().second)
            + integralMethod(array_linear_interpolation_.back().second)) };

        double sum{ std::accumulate(array_linear_interpolation_.begin(), array_linear_interpolation_.end(), 0.0, [&](double lhs, auto&& elem) {
            return lhs + integralMethod(elem.second);
            }) - arithmetic_mean };

        return 0.1 * (arithmetic_mean / 2 + sum);
    }


    double FindingTheAmountOfHeatSingleton::integralMethod(double y) const noexcept {
        return y * y;
    }


    void FindingTheAmountOfHeatSingleton::printIntegralTrapezoidMethod() const noexcept {

        std::cout << "q:  " << calculateIntegralTrapezoidMethod() << "\n";
    }

}