#include "ControlVisitor.hpp"
#include "Core/EventManager.hpp"

using namespace fug;

void ControlVisitor::operator() (TransformComponent& pos, ControlMapComponent& control_map)
{
    for (auto& event : FUG_EVENT_MANAGER.template getMailbox<sf::Event>(sf::Event::KeyPressed)) {
        if (control_map.map.find(event.data.key.code) != control_map.map.end()) {
            switch (control_map.map[event.data.key.code]) {
                case ControlMapComponent::MoveUp:
                    pos.transform(1,3) += _move_amount;
                    break;
                case ControlMapComponent::MoveDown:
                    pos.transform(1,3) -= _move_amount;
                    break;
                case ControlMapComponent::MoveLeft:
                    pos.transform(0,3) -= _move_amount;
                    break;
                case ControlMapComponent::MoveRight:
                    pos.transform(0,3) += _move_amount;
                    break;
                default:
                    break;
            }
        }
    }
}
