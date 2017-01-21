#include "GameJam2017/GameJam2017.hpp"
#include "GameJam2017/Game.hpp"


using namespace fgj;


int fgj::gameJam2017(void)
{
    Game game;
    game.loadLevel("penis");
    game.loop();

    return 0;

}
