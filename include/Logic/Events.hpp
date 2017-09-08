#ifndef FUG_LOGIC_CORE_EVENTS_HPP
#define FUG_LOGIC_CORE_EVENTS_HPP

namespace fug {

    class CoreEvent {
    public:

        // Enums

        enum class Direction {
            Forward,
            Backward,
            Up,
            Down,
            Left,
            Right,
        };

        enum class Axis {
            Pitch,
            Yaw,
            Roll
        };

        enum class EventType {
            AxialTranslation,
            AxialRotation,
            KeyPress
        };

        // Event types

        struct AxialTranslationEvent {
            Direction direction;
            float amount;
        };

        struct AxialRotationEvent {
            Axis axis;
            float amount;
            bool useDegrees;
        };

        struct KeyPressEvent {
            int key;
        };

        // Member data

        EventType type;

        union {
            AxialTranslationEvent axialTranslation;
            AxialRotationEvent axialRotation;
            KeyPressEvent keyPress;
        };

    };

} // namespace fug

#endif // FUG_LOGIC_CORE_EVENTS_HPP
