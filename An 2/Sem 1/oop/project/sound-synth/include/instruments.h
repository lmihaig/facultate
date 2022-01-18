#pragma once
#include <iostream>
#include <string>
#include <envelopeADSR.h>

template <class T>
class note;

template <class T>
class instrument_base;

template <class T>
std::ostream &operator<<(std::ostream &os, const instrument_base<T> &n);

template <class T>
class instrument_base
{
protected:
    static constexpr double pi = 3.1415926535;
    T maxLifeTime;
    envelopeADSR<T> env;
    std::string name;

public:
    friend std::ostream &operator<<<>(std::ostream &os, const instrument_base<T> &inst);
    instrument_base(const T maxLifeTime, envelopeADSR<T> env, const std::string name);
    instrument_base(const instrument_base<T> &copy);
    bool operator==(const instrument_base<T> &rhs) const;
    bool operator!=(const instrument_base<T> &rhs) const;
    instrument_base<T> &operator=(const instrument_base<T> &copy);

    virtual T sound(const T time, note<T> &n, bool &noteFinished) = 0;
    T hz_to_rad(const T hertz);
    T oscSine(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSquare(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscTriangle(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSaw(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0, const T steps = 50);
    T oscRand();

    T scale(const int noteID);
};

template <class T>
class instrument_bell : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (amp <= 0.0)
            noteFinished = true;
        T sound = 1.00 * this->oscSine(time - n.on, this->scale(n.id + 12), 5.0, 0.001) + 0.50 * this->oscSine(time - n.on, this->scale(n.id + 24)) + 0.25 * this->oscSine(time - n.on, this->scale(n.id + 36));

        return sound * amp;
    };

    instrument_bell() : instrument_base<T>(3, envelopeADSR<T>(1.0, 0.01, 1.0, 0.0, 1.0), "Bell"){};
};

template <class T>
class instrument_harmonica : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (amp <= 0.0)
            noteFinished = true;
        T sound = 1.0 * this->oscSaw(time - n.on, this->scale(n.id - 12), 5.0, 0.001, 100) + 1.0 * this->oscSquare(time - n.off, this->scale(n.id), 5.0, 0.001) + 0.5 * this->oscSquare(time - n.on, this->scale(n.id + 12)) + 0.05 * this->oscRand();

        return sound * amp;
    };

    instrument_harmonica() : instrument_base<T>(-1, envelopeADSR<T>(1.0, 0, 1.0, 0.95, 0.1), "Harmonica"){};
};

template <class T>
class instrument_drum_kick : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (this->maxLifeTime > 0.0 && time - n.on >= this->maxLifeTime)
            noteFinished = true;
        T sound = 1.0 * this->oscSine(time - n.on, this->scale(n.id - 36), 1, 1) + 0.01 * this->oscRand();
        return sound * amp;
    };

    instrument_drum_kick() : instrument_base<T>(1.5, envelopeADSR<T>(1.0, 0.01, 0.15, 0, 0), "Drumkick"){};
};

template <class T>
class instrument_drum_snare : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (this->maxLifeTime > 0.0 && time - n.on >= this->maxLifeTime)
            noteFinished = true;
        T sound = 0.5 * this->oscSine(time - n.on, this->scale(n.id - 24), 0.5, 1) + 0.5 * this->oscRand();

        return sound * amp;
    };

    instrument_drum_snare() : instrument_base<T>(1, envelopeADSR<T>(1.0, 0, 0.2, 0, 0), "Snare"){};
};

template <class T>
class instrument_drum_hihat : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (this->maxLifeTime > 0.0 && time - n.on >= this->maxLifeTime)
            noteFinished = true;
        T sound = 0.1 * this->oscSquare(time - n.on, this->scale(n.id - 12), 1.5, 1) + 0.9 * this->oscRand();

        return sound * amp;
    };

    instrument_drum_hihat() : instrument_base<T>(1, envelopeADSR<T>(1.0, 0.01, 0.05, 0, 0), "Hihat"){};
};

// template <class T>
// class instrument_piano : public instrument_base<T>
// {
//     T sound(const T time, note<T> &n, bool &noteFinished);
// };

// template <class T>
// class instrument_guitar : public instrument_base<T>
// {
//     T sound(const T time, note<T> &n, bool &noteFinished);
// };

// template <class T>
// class instrument_harp : public instrument_base<T>
// {
//     T sound(const T time, note<T> &n, bool &noteFinished);
// };

// template <class T>
// class instrument_flute : public instrument_base<T>
// {
//     T sound(const T time, note<T> &n, bool &noteFinished);
// };
