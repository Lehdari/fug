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

    for (auto& event : FUG_EVENT_MANAGER.template getMailbox<sf::Event>(sf::Event::MouseMoved+123)) {

        float dx = -event.data.mouseMove.x / 500.f;
        float dy = event.data.mouseMove.y / 500.f;

        Vector3Glf v = trans.orientation.vec();
        Vector3Glf k = { -v[2], 0, v[0] };
        k = k / k.norm();

        Matrix3Glf rot;
        rot << cos(dx), 0, sin(dx),
               0,       1, 0,
               -sin(dx),0,  cos(dx);

        v = rot * v * cos(dy) + k.cross(v) * sin(dy) + k * (k.dot(v)) * (1 - cos(dy));
        trans.orientation = {1.f, v[0], v[1], v[2]};

    }
}
