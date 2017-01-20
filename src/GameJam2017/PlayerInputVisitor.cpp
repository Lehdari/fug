#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"
#include "GameJam2017/PlayerInputVisitor.hpp"
#include "GameJam2017/constants.hpp"


using namespace fug;

void PlayerInputVisitor::operator()(CharacterStateComponent& state, CharacterInfoComponent& info)
{
    auto inputConfig = FUG_RESOURCE_MANAGER.getResource<SfmlInputConfig>(1);
    auto& inputMap = inputconfig->inputMap;

    // Käy eventit läpi. Jos input-eventti mätsää hahmon id:hen:
    state.moveDir = WorldDir::up;
    if(inputMap.count(event.x.key.code) > 0) {
        switch inputMap[event.x.key.code] {
            Input::Up:
                state.moveUp = (event.x.type == sf::Event::KeyPressed);
                state.moveDown = false;
                break;

            Input::Down:
                state.moveUp = false;
                state.moveDown = (event.x.type == sf::Event::KeyPressed);
                break;

            Input::Left:
                state.moveLeft = (event.x.type == sf::Event::KeyPressed);
                state.moveRight = false;
                break;

            Input::Right:
                state.moveLeft = false;
                state.moveRight = (event.x.type == sf::Event::KeyPressed);
                break;
        }
    }
}
