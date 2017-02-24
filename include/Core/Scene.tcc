template <typename T_Implementation>
SceneBase<T_Implementation>& SceneBase<T_Implementation>::instance(void)
{
    static T_Implementation scene;
    return scene;
}

template <typename T_Implementation>
EId SceneBase<T_Implementation>::addEntity(void)
{
    return static_cast<T_Implementation*>(this)->addEntity();
}

template <typename T_Implementation>
template <typename T_Component>
void SceneBase<T_Implementation>::addComponent(T_Component&& component)
{
    static_cast<T_Implementation*>(this)->
        addComponent(std::forward<T_Component>(component));
}

template <typename T_Implementation>
void SceneBase<T_Implementation>::removeEntity(const EId& entity)
{
    static_cast<T_Implementation*>(this)->removeEntity(entity);
}

template <typename T_Implementation>
template <typename T_Visitor, typename... T_Components>
void SceneBase<T_Implementation>::accept(Visitor<T_Visitor, T_Components...>& visitor)
{
    static_cast<T_Implementation*>(this)->accept(visitor);
}

#ifdef FUG_DEBUG
template <typename T_Implementation>
void SceneBase<T_Implementation>::print(void)
{
    return static_cast<T_Implementation*>(this)->print();
}
#endif
