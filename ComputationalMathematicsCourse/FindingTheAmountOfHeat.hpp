#include "Functions.h"
namespace KHAS {

    template <typename TData>
        requires std::is_convertible_v<TData, InputData>
    FindingTheAmountOfHeatSingleton::FindingTheAmountOfHeatSingleton(TData&& data, size_t width_screen)
        : width_screen_{ width_screen }
        , data_{ data }
        , menu_{ width_screen }
    {
        init();
    }


    template <typename TData>
        requires std::is_convertible_v<TData, InputData>
    FindingTheAmountOfHeatSingleton& FindingTheAmountOfHeatSingleton::getInstance(TData&& data, size_t width_screen)
    {
        static FindingTheAmountOfHeatSingleton instance{ std::forward<TData>(data), width_screen };
        return instance;
    }

    template <typename T, typename TString>
        requires std::is_convertible_v<TString, std::string>
    std::optional<T> FindingTheAmountOfHeatSingleton::showReadCommand(TString&& str, std::istream& in) const noexcept
    {
        using value_type = T;
        using opt_type = std::optional<value_type>;

        opt_type result;
        value_type cmd{};
        std::string cmd_name{ std::forward<TString>(str) };
        std::cout << "| " << cmd_name << "  " << delimiter('_', width_screen_ - cmd_name.size() - 6) << " |"
            << delimiter('\b', width_screen_ - cmd_name.size()-4);

        result = (in >> cmd) ? opt_type{ std::move(cmd) } : std::nullopt;
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return result;
    }

}