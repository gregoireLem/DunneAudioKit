// Copyright AudioKit. All Rights Reserved.

#pragma once

#include <vector>
#include <cassert>

namespace DunneCore
{

    // WaveStack represents a series of progressively lower-resolution sampled versions of a
    // waveform. Client code supplies the initial waveform, at a resolution of 1024 samples,
    // equivalent to 43.6 Hz at 44.1K samples/sec (about 23.44 cents below F1, midi note 29),
    // and then calls initStack() to create the filtered higher-octave versions.
    // This provides a basis for anti-aliased oscillators; see class WaveStackOscillator.
    
    struct WaveStack
    {
        // Highest-resolution rep uses 2^maxBits samples
        static constexpr int maxBits = 10;  // 1024

        // maxBits also defines the number of octave levels; highest level has just 2 samples
        float *pData[maxBits];

        WaveStack();
        ~WaveStack();

        // Fill pWaveData with 1024 samples, then call this
        void initStack(const std::vector<float>& waveData, int maxHarmonic=512);

        float interp(int octave, float phase);
    };

}
