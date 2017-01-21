#ifndef FUG_CHARACTER_COMPONENT_HPP
#define FUG_CHARACTER_COMPONENT_HPP


#include "Core/Component.hpp"
#include "Core/MathTypes.hpp"


namespace fug {

    class CharacterStateComponent : public Component {
    public:
        bool alive;
        Vector3f movementDir;
    };

}


#endif // FUG_CHARACTER_COMPONENT_HPP
