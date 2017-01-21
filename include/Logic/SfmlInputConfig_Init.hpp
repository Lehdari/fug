#ifndef FUG_SFML_INPUT_CONFIG_INIT_HPP
#define FUG_SFML_INPUT_CONFIG_INIT_HPP


#include "Logic/SfmlInputConfig.hpp"


namespace fug {

    struct SfmlInputConfig_Init_Default {
        SfmlInputConfig::InputMap map;
    };


    #include "SfmlInputConfig_Init.tcc"

}


#endif // FUG_SFML_INPUT_CONFIG_INIT_HPP
