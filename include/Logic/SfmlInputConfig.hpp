#ifndef FUG_SFML_INPUT_COMPONENT_HPP
#define FUG_SFML_INPUT_COMPONENT_HPP


#include <unordered_map>
#include <SFML/Keyboard.hpp>
#include "Core/Resource.hpp"
#include "GameJam0217/constants.hpp"


namespace fug {

    class FUG_RESOURCE(SfmlInputConfig) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        std::unordered_map<sf::Keyboard::Key, Input::Action> inputMap;
    };

}


#endif // FUG_SFML_INPUT_COMPONENT_HPP
