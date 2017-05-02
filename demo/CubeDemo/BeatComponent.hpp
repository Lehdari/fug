#ifndef FUG_BEAT_COMPONENT_HPP
#define FUG_BEAT_COMPONENT_HPP

#include <unordered_map>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace fug {

    class BeatComponent {
       
    public:
        enum ReactType {
            Pulse,
            FlashBg
        };
        
        BeatComponent(ReactType, float = 1.0f, float = 0.1f);

        ReactType behavior;
        float strength;
        float release;

    private:
        float _delta;

        friend class BeatVisitor;
    };
} 


#endif // FUG_BEAT_COMPONENT_HPP
