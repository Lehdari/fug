#include "BeatVisitor.hpp"

#include <iostream>


float hanning_filter(float val) {
	float a = 0.54, b = 0.46;
	if (val == 1.0) {
		return a;
	}
	return a - b * cos((2*PI)/(val-1));
}


using namespace fug;

BeatVisitor::BeatVisitor(sf::Sound const& source) :
    _source(source)
{
    if (!source.getBuffer()) {
        // Invalid SoundBuffer
        throw;
    }
}

void BeatVisitor::operator()(BeatComponent& beat_comp, TransformComponent& tran_comp)
{
    if (_source.getStatus() != sf::SoundSource::Status::Playing) {
        // No need to continue if the sound source isn't used
        return;
    }
    auto& buffer = *_source.getBuffer();

    static std::vector<NTYPE> timevec(FFT_SIZE, 0);
    static std::vector<std::complex<NTYPE>> freqvec = {};

    static float offset_prev = 0.f, peak = 0.f;
	float offset = _source.getPlayingOffset().asSeconds();
    if (offset_prev != offset) {
        // New samples

        uint32_t cur_sample = offset * buffer.getSampleRate();
        const int16_t* samples = buffer.getSamples() + cur_sample;

        // if there are enough samples, assign them to timevec and apply Hanning filter
        if ((cur_sample + FFT_SIZE) < buffer.getSampleCount()) {
            timevec.assign(samples, samples + FFT_SIZE);
            std::transform(timevec.begin(), timevec.end(), back_inserter(timevec), hanning_filter);
        }

        // calculate FFT
        _fft.fwd(freqvec, timevec);
        
        auto reg_start = 0, reg_size = 100;
        auto it = freqvec.begin() + reg_start;
        auto it_stop = it + reg_size;
        float mag = 0.f, thresh = 160.f;

        // Find maximum magnitude over the threshold
        peak = 0.f;
        while (it++ != freqvec.end() && it < it_stop) {
		    mag = log(sqrt(pow(it->real(), 2) + pow(it->imag(), 2))) * 10;
            if (mag > thresh && mag > peak) {
                peak = mag;
            }
        }
    }
    offset_prev = offset;

    if (peak) {
        beat_comp._delta = beat_comp.strength;
    }
    if (beat_comp._delta > 0.f) {
        beat_comp._delta -= beat_comp.release;
        induce(beat_comp, tran_comp);
    }
    else {
        beat_comp._delta = 0.f;
    }
}

void BeatVisitor::induce(BeatComponent& beat_comp, TransformComponent& tran_comp)
{
    switch (beat_comp.behavior) {
        case BeatComponent::Pulse:
            tran_comp.scale << beat_comp._delta + 1, beat_comp._delta + 1, beat_comp._delta + 1;
            break;
        case BeatComponent::FlashBg:
            std::cout << beat_comp._delta << std::endl;
            glClearColor(0.0f, beat_comp._delta * 2, beat_comp._delta * 2, 1.0f);
            break;
        default:
            // unhandled
            break;
    }
}




