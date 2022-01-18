#pragma once
#include <SDL.h>

template <class T>
class envelopeADSR
{
    T attackLevel;
    T attackTime;
    T decayTime;
    T sustainLevel;
    T releaseTime;

public:
    envelopeADSR(T attackLevel = 1.f, T attackTime = .15f, T decayTime = .2f, T sustainLevel = .8f, T releaseTime = .65f);
    T amplitude(const T currentTime, const T noteOnTime, const T noteOffTime);

    bool operator==(const envelopeADSR<T> &rhs) const;
    bool operator!=(const envelopeADSR<T> &rhs) const;
    envelopeADSR<T> &operator=(const envelopeADSR<T> &copy);
};