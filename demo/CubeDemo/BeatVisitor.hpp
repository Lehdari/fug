#ifndef FUG_BEAT_VISITOR_HPP
#define FUG_BEAT_VISITOR_HPP

#include "Core/Visitor.hpp"

#include "BeatComponent.hpp"
#include "Logic/TransformComponent.hpp"

#include "unsupported/Eigen/FFT"

#define NTYPE double
#define FFT_SIZE 1024

namespace fug {

    // Beat reactor visitor - makes affected entities pulse with music
    class BeatVisitor : public Visitor<BeatVisitor, BeatComponent, TransformComponent> {
    
    public:
        BeatVisitor(sf::Sound const&);
        void operator()(BeatComponent&, TransformComponent&);

    private:
        void induce(BeatComponent&, TransformComponent&);

        sf::Sound const& _source;
        Eigen::FFT<NTYPE> _fft;
    };
}

#endif // FUG_BEAT_VISITOR_HPP
