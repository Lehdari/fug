#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include <cstdint>
#include <vector>
#include <functional>


class Container {
public:
    Container();
    ~Container();

    /// Add new entity
    uint64_t addEntity();

    /// Add component for the current entity
    template <typename T>
    void addComponent(const T& component);

private:
    /// Wrapper type for components
    template <typename T>
    struct ComponentWrapper {
        uint64_t    entityId;
        T           component;

        ComponentWrapper(uint64_t& eId, const T& c) :
            entityId(eId), component(c) {}
    };

    /// TypeId system
    static uint64_t typeIdCounter;
    template <typename T>
    static uint64_t typeId();

    /// Component vector handling functions
    template <typename T>
    std::vector<ComponentWrapper<T>>& accessComponents();

    template <typename T>
    static void deleteComponents(void* components);

    /// Component vector handling datatypes
    std::vector<void*>                  _components;
    std::vector<std::function<void()>>  _componentDeleters;

    /// ID of the last entity
    uint64_t                            _entityId;
};


template <typename T>
void Container::addComponent(const T& component)
{
    printf("added component, entity: %llu, typeId: %llu\n", _entityId, typeId<T>());

    auto& v = accessComponents<T>();
    v.emplace_back(_entityId, component);
}

template <typename T>
uint64_t Container::typeId()
{
    static uint64_t tId = typeIdCounter++;
    return tId;
}

template<typename T>
std::vector<Container::ComponentWrapper<T>>& Container::accessComponents()
{
    auto tId = typeId<T>();
    if (tId == _components.size()) {
        _components.push_back(new std::vector<T>);
        _componentDeleters.push_back(std::bind(&deleteComponents<T>, _components.back()));
    }
    return *static_cast<std::vector<ComponentWrapper<T>>*>(_components[tId]);
}

template<typename T>
void Container::deleteComponents(void *components) {
    auto* v = static_cast<std::vector<ComponentWrapper<T>>*>(components);
    printf("deleted vector of type %llu, size %llu\n", typeId<T>(), v->size());

    delete static_cast<std::vector<ComponentWrapper<T>>*>(components);
}


#endif // CONTAINER_HPP
