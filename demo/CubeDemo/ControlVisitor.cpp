#include "ControlVisitor.hpp"
#include "Core/EventManager.hpp"

using namespace fug;

void ControlVisitor::operator() (TransformComponent& trans, ControlMapComponent& control_map)
{
    for (auto& event : FUG_EVENT_MANAGER.template getMailbox<sf::Event>(sf::Event::KeyPressed)) {
        if (control_map.map.find(event.data.key.code) != control_map.map.end()) {
            switch (control_map.map[event.data.key.code]) {
                case ControlMapComponent::MoveUp:
                    trans.transform(1,3) += _move_amount;
                    break;
                case ControlMapComponent::MoveDown:
                    trans.transform(1,3) -= _move_amount;
                    break;
                case ControlMapComponent::MoveLeft:
                    trans.transform(0,3) -= _move_amount;
                    break;
                case ControlMapComponent::MoveRight:
                    trans.transform(0,3) += _move_amount;
                    break;
                default:
                    break;
            }
        }
    }
}
