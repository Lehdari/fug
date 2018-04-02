#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include <cstdint>
#include <vector>
#include <functional>


class Container {
public:
    ~Container();

    template <typename T>
    void addComponent(const T& component);

private:
    std::vector<void*>                  _components;
    std::vector<std::function<void()>>  _componentDeleters;

    static uint64_t typeIdCounter;
    template <typename T>
    static uint64_t typeId(void);

    template <typename T>
    std::vector<T>& accessComponents(void);

    template <typename T>
    static void deleteComponents(void* components);
};


template <typename T>
void Container::addComponent(const T& component)
{
    printf("typeId: %llu\n", typeId<T>());

    auto& v = accessComponents<T>();
    v.push_back(component);
}

template <typename T>
uint64_t Container::typeId(void)
{
    static uint64_t tId = typeIdCounter++;
    return tId;
}

template<typename T>
std::vector<T>& Container::accessComponents(void)
{
    auto tId = typeId<T>();
    if (tId == _components.size()) {
        _components.push_back(new std::vector<T>);
        _componentDeleters.push_back(std::bind(&deleteComponents<T>, _components.back()));
    }
    return *static_cast<std::vector<T>*>(_components[tId]);
}

template<typename T>
void Container::deleteComponents(void *components) {
    auto* v = static_cast<std::vector<T>*>(components);
    printf("deleted vector of type %llu, size %llu\n", typeId<T>(), v->size());

    delete static_cast<std::vector<T>*>(components);
}


#endif // CONTAINER_HPP
