namespace KHAS {

    template <typename Name, typename Func>
        requires std::is_convertible_v<Name, std::string>
    MenuItem::MenuItem(Name&& name, Func&& func)
        : name_{ std::forward<Name>(name) }
        , func_{ std::forward<Func>(func) }
        , id_{ createId() } {}

}