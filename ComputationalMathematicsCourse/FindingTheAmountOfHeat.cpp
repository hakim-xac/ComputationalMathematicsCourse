#include "FindingTheAmountOfHeat.h"
#include "Functions.h"
#include <iomanip>
#include <cassert>
#include <vector>


namespace KHAS {

    void FindingTheAmountOfHeatSingleton::showHeader(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        std::string subject_header{ "����������:" };
        std::string subject_name{ "�������������� ����������" };
        std::string student_header{ "�������:" };
        std::string student_name{ "������� �.�." };
        std::string group_header{ "������:" };
        std::string group_name{ "��-11" };
        std::string variant_header{ "�������:" };
        std::string variant_name{ "�1" };
        std::string theme_header{ "����:" };
        std::string theme_name{ "��������� �����������������" };

        std::string left_range_header{ "��������:" };
        std::string left_range_name{ typeToString(data_.accuracy, 4).first };
        std::string right_range_header{ "�������� ��� �����-�����:" };
        std::string right_range_name{ typeToString(data_.accuracy_for_kutt, 4).first };
        std::string step_header{ "���:" };
        std::string step_name{ typeToString(data_.step, 4ull).first };
        std::string error_header{ "�����������:" };
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
        assert(step_header.size() <= width && step_name.size() <= width);
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
        out << "| " << std::setw(width) << std::left << step_header << " | " << std::setw(width + offset) << std::right << step_name << " |\n";
        out << "| " << std::setw(width) << std::left << error_header << " | " << std::setw(width + offset) << std::right << error_name << " |\n";

        out << delim << "\n";
    }

    void FindingTheAmountOfHeatSingleton::init() noexcept
    {
        menu_.insert("���������� ����� ����������� ��������� ������� ����.", [&]() { findingTheRootOfANonlinearEquation(); });
        menu_.insert("������� ����������������� ��������� ������� �����-����� ���������� �������.", [&] {  });
        menu_.insert("���������� � ������� �������� ������������ ������������ �������� �������.", [] {});
        menu_.insert("����������� ���������� ������� ������� ��������.", [] {});
        menu_.insert("�����", [] {});
    }

    void FindingTheAmountOfHeatSingleton::showUnknownCommand(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        out << delim << "\n";
        out << generateString("����������� �������", width_screen_) << "\n";
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

            cmd = showReadCommand<size_t>("������� �������:").value_or(0);
        }
    }

    double FindingTheAmountOfHeatSingleton::mathFunc(double x) const noexcept {
        return 3 * pow(x, 4) + 8 * pow(x, 3) + 6 * pow(x, 2) - 10;
    }

    void FindingTheAmountOfHeatSingleton::findingTheRootOfANonlinearEquation() const noexcept {
        auto left_range{ showReadCommand<double>("������� ������ ������� ��������� �������� ����� ����������� ���������:").value_or(0) };
        auto right_range{ showReadCommand<double>("������� ������� ������� ��������� �������� ����� ����������� ���������:").value_or(0) };
        
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






}