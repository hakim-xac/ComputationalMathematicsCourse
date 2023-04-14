#include "FindingTheAmountOfHeat.h"
#include "Functions.h"
#include <iomanip>
#include <cassert>


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

        std::string left_range_header{ "Минимальная граница:" };
        std::string left_range_name{ typeToString(data_.left_range, 4).first };
        std::string right_range_header{ "Максимальная граница:" };
        std::string right_range_name{ typeToString(data_.right_range, 4ull).first };
        std::string step_header{ "Шаг:" };
        std::string step_name{ typeToString(data_.step, 4ull).first };
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

    void FindingTheAmountOfHeatSingleton::showUnknownCommand(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        out << delim << "\n";
        out << generateString("Неизвестная команда", width_screen_) << "\n";
        out << delim << "\n";
    }

    size_t FindingTheAmountOfHeatSingleton::showReadCommand(std::istream& in) const noexcept
    {
        size_t cmd;
        std::string cmd_name{ "Введите команду:" };
        std::cout << cmd_name << delimiter('_', width_screen_ - cmd_name.size())
            << delimiter('\b', width_screen_ - cmd_name.size());

        if (!(in >> cmd)) cmd = -1;
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return cmd;
    }

    void FindingTheAmountOfHeatSingleton::loop() const noexcept
    {
        size_t cmd{};
        while (cmd != 3) {
            system("cls");
            showHeader();

            if (!menu_.runCommand(cmd)) showUnknownCommand();

            menu_.show();

            cmd = showReadCommand();
        }
    }

}