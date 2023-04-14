
namespace KHAS {

    template <typename Name, typename Func>
        requires std::is_convertible_v<Name, std::string>
    void Menu::insert(Name&& name, Func&& func) noexcept {
        buffer_.emplace_back(MenuItem{ std::forward<Name>(name), std::forward<Func>(func) });
    }

}