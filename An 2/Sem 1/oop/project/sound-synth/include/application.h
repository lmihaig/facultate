#pragma once
#include <note.h>
#include <mutex>
#include <vector>
#include <algorithm>

template <class T>
class APPLICATION
{
    const Uint16 frequency = 48000;
    const Uint16 samples = 4096;
    const Uint8 channels = 2;

    struct synthDataStruct
    {
        T ticks;
        T secondsPerTick;
        instrument_base<T> *currentInstrument;
        std::vector<note<T>> notes;
    };

    static std::mutex synthDataMutex;
    inline static synthDataStruct synthData;
    inline static const std::vector<SDL_KeyCode> keys = {SDLK_z, SDLK_s, SDLK_x, SDLK_c, SDLK_f, SDLK_v, SDLK_g, SDLK_b, SDLK_n, SDLK_j, SDLK_m, SDLK_k, SDLK_COMMA, SDLK_l, SDLK_PERIOD, SDLK_SLASH};
    bool initialised = false;
    bool running = true;

    instrument_bell<T> bell;
    instrument_harmonica<T> harm;
    instrument_drum_hihat<T> hihat;
    instrument_drum_kick<T> kick;
    instrument_drum_snare<T> snare;

    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    static APPLICATION *app;

    void initialise();
    void handleEvents();
    void addNote(int keyID);
    void removeNote(int keyID);
    void changeInstrument(SDL_Keycode instCode);
    int keyCodeToKeyID(SDL_KeyCode keyCode);
    APPLICATION(const int width, const int height);

public:
    static APPLICATION &instance(const int width, const int height);
    ~APPLICATION();
    void run();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
};