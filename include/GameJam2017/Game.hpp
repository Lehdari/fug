#ifndef FGJ_GAME_HPP
#define FGJ_GAME_HPP

#include <string>
#include <memory>

#include <Box2D/Box2D.h>
#include "Logic/Box2dWorld.hpp"
#include "Core/ResourcePointer.hpp"

namespace fgj {

    using namespace fug;

    class Game {
    public:
        Game();
        ~Game();

        bool loadLevel(std::string name);
        void loop();

    private:
        ResourcePointer<Box2dWorld> worldRes;
    };

}


#endif // FGJ_GAME_HPP
