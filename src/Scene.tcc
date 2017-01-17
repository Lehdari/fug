template <typename T_Implementation>
SceneBase<T_Implementation>& SceneBase<T_Implementation>::instance(void)
{
    static SceneBase<T_Implementation> scene;
    return scene;
}

template <typename T_Implementation>
template <typename... T_Components>
EId SceneBase<T_Implementation>::addEntity(T_Components&&... components) {
    return static_cast<T_Implementation*>(this)->
           addEntity(std::forward<T_Components>(components)...);
}

template <typename T_Implementation>
void SceneBase<T_Implementation>::removeEntity(const EId& entity) {
    return static_cast<T_Implementation*>(this)->removeEntity(entity);
}

template <typename T_Implementation>
template<typename T_Visitor, typename... T_Components>
void SceneBase<T_Implementation>::accept(Visitor<T_Visitor, T_Components...>& visitor) {
    return static_cast<T_Implementation*>(this)->accept(visitor);
}

#ifdef FUG_DEBUG
template <typename T_Implementation>
void SceneBase<T_Implementation>::print(void) {
    return static_cast<T_Implementation*>(this)->print();
}
#endif
