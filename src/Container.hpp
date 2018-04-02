#ifndef CONTAINER_HPP
#define CONTAINER_HPP


#include <cstdint>
#include <vector>


class Container {
public:
    template <typename T>
    void addComponent(const T& component);

private:
    std::vector<void*> _components;

    static uint64_t typeIdCounter;
    template <typename T>
    uint64_t typeId(void);
};


template <typename T>
void Container::addComponent(const T& component)
{
    printf("typeId: %llu\n", typeId<T>());
}

template <typename T>
uint64_t Container::typeId(void)
{
    static uint64_t tId = typeIdCounter++;
    return tId;
}


#endif // CONTAINER_HPP
