#ifndef FGJ_GAME_HPP
#define FGJ_GAME_HPP

#include <string>
#include <memory>

#include <Box2D/Box2D.h>

namespace fgj {

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
