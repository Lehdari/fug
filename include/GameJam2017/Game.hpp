#ifndef FGJ_GAME_HPP
#define FGJ_GAME_HPP

#include <string>
#include <memory>

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
    };

}


#endif // FGJ_GAME_HPP
