#ifndef FUG_SFML_INPUT_CONFIG_HPP
#define FUG_SFML_INPUT_CONFIG_HPP


#include <cstdint>
#include <utility>
#include <unordered_map>
#include <SFML/Window.hpp>
#include "Core/Resource.hpp"
#include "GameJam2017/constants.hpp"


namespace fug {
    struct SfKeyboardKeyHash {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    class FUG_RESOURCE(SfmlInputConfig) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        
        // <key, <player_id, action>>
        using InputMap = std::unordered_map<sf::Keyboard::Key, std::pair<uint8_t, Input::Action>,
                                            SfKeyboardKeyHash>;

        InputMap inputMap;
    };

}


#endif // FUG_SFML_INPUT_CONFIG_HPP
