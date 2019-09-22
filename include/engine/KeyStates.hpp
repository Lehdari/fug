#ifndef FUG_ENGINE_KEYSTATE_HPP
#define FUG_ENGINE_KEYSTATE_HPP

#include <array>

namespace fug {
    template <typename KeyType, size_t keyMax>
    class KeyStates {
    public:
        KeyStates() = default;

        void handleKeyPress(KeyType key)
        {
            uint64_t& pressed = _getPressed(key);
            if (pressed) /* Skip repeats */
                return;
            _getReleased(key) = 0;
            pressed = ++_count;
        }

        void handleKeyRelease(KeyType key)
        {
            uint64_t& released = _getReleased(key);
            if (released) /* Skip repeats */
                return;
            _getPressed(key) = 0;
            released = ++_count;
        }

        uint64_t isPressed(KeyType key)
        {
            return _getPressed(key);
        }

        uint64_t isReleased(KeyType key)
        {
            return _getReleased(key);
        }

    private:
        uint64_t& _getPressed(KeyType key)
        {
            return _pressed[static_cast<size_t>(key)];
        }

        uint64_t& _getReleased(KeyType key)
        {
            return _released[static_cast<size_t>(key)];
        }

        std::array<uint64_t, keyMax> _pressed = { 0 };
        std::array<uint64_t, keyMax> _released = { 0 };
        uint64_t _count = 0;
    };
}

#endif
