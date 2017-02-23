#ifndef FUG_CONTROL_MAP_COMPONENT_HPP
#define FUG_CONTROL_MAP_COMPONENT_HPP

#include <unordered_map>
#include <SFML/Window.hpp>

namespace fug {

    class ControlMapComponent {

    public:

        enum Action {
            MoveUp,
            MoveDown,
            MoveLeft,
            MoveRight
        };
        
        std::unordered_map<std::size_t, Action> map;
    };
} 


#endif // FUG_CONTROL_MAP_COMPONENT_HPP
