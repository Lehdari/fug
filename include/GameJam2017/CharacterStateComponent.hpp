#ifndef FUG_CHARACTER_COMPONENT_HPP
#define FUG_CHARACTER_COMPONENT_HPP


#include <Eigen/Dense>
#include "Core/Component.hpp"


namespace fug {

    class CharacterStateComponent : public Component {
    public:
        bool alive;
        bool moveUp;
        bool moveDown;
        bool moveLeft;
        bool moveRight;
    };

}


#endif // FUG_CHARACTER_COMPONENT_HPP
