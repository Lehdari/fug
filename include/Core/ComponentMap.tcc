template <typename T_Component>
void ComponentMap::addComponentType(const ComponentTypeId& typeId, const T_Component& component)
{
    accessComponentTypes<T_Component>()[typeId] = component;
}

template <typename T_Component>
std::unordered_map<ComponentTypeId, T_Component>& ComponentMap::accessComponentTypes(void)
{
    static std::unordered_map<ComponentTypeId, T_Component> _componentTypes;
    return _componentTypes;
}

template <typename T_Component>
ComponentMapEntry<T_Component>::ComponentMapEntry(const std::string& componentName)
{
    FUG_LOG(LogLevel::Debug)("Registering component add function: %s\n",
                              componentName.c_str());
    FUG_COMPONENT_MAP._addFunctionJsonMap.insert(std::make_pair(componentName, addComponentJson));
    FUG_COMPONENT_MAP._addFunctionMap.insert(std::make_pair(componentName, addComponent));
    FUG_COMPONENT_MAP._addTypeFunctionMap.insert(std::make_pair(componentName, addComponentType));
}

template <typename T_Component>
void ComponentMapEntry<T_Component>::addComponentJson(const json& json)
{
    T_Component component;
    initComponent(json, component);
    FUG_SCENE.addComponent<T_Component>(std::move(component));
}

template <typename T_Component>
void ComponentMapEntry<T_Component>::addComponent(const ComponentTypeId& typeId)
{
    T_Component component = FUG_COMPONENT_MAP.accessComponentTypes<T_Component>()[typeId];
    FUG_SCENE.addComponent<T_Component>(std::move(component));
}

template <typename T_Component>
void ComponentMapEntry<T_Component>::addComponentType(const ComponentTypeId& typeId, const json& json)
{
    initComponent(json, FUG_COMPONENT_MAP.accessComponentTypes<T_Component>()[typeId]);
}
