#include <application.h>

template <class T>
std::mutex APPLICATION<T>::synthDataMutex;

template <class T>
APPLICATION<T> *APPLICATION<T>::app = nullptr;

template <class T>
APPLICATION<T> &APPLICATION<T>::instance(const int width, const int height)
{
    if (app == nullptr)
        app = new APPLICATION(width, height);
    return *app;
}

template <class T>
APPLICATION<T>::APPLICATION(const int width, const int height)
{
    initialise();

    window = SDL_CreateWindow("sound-synth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    synthData.ticks = 0;
    synthData.secondsPerTick = static_cast<T>(1.0 / frequency);

    SDL_AudioSpec desired = {};
    SDL_AudioSpec obtained = {};

    SDL_zero(desired);
    desired.freq = frequency;
    desired.channels = channels;
    desired.samples = samples;
    desired.userdata = &synthData;
    desired.callback = audioCallback;
    desired.format = AUDIO_S32SYS;

    audioDevice = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);

    // Default state is paused, this unpauses it
    SDL_PauseAudioDevice(audioDevice, 0);
}
template <class T>
APPLICATION<T>::~APPLICATION()
{
    SDL_GL_DeleteContext(context);
    SDL_CloseAudioDevice(audioDevice);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
template <class T>
void APPLICATION<T>::initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    initialised = true;
}
template <class T>
void APPLICATION<T>::run()
{
    running = true;
    while (running)
    {
        handleEvents();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}
template <class T>
void APPLICATION<T>::handleEvents()
{

    std::lock_guard<std::mutex> guard(synthDataMutex);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Detect if the user tries to close the window and if so stop running, which will call the destructor
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || event.key.keysym.sym == SDLK_ESCAPE)
        {
            running = false;
        }
        // If user presses any of 1 - 9 change instrument
        else if (SDLK_0 <= event.key.keysym.sym && event.key.keysym.sym <= SDLK_9)
        {
            if (event.type == SDL_KEYDOWN)
                changeInstrument(event.key.keysym.sym);
        }
        else
        {
            for (auto it : keys)
            {
                if (event.key.keysym.sym == it)
                {
                    int keyID = keyCodeToKeyID(it);
                    // Add pressed key
                    if (event.type == SDL_KEYDOWN)
                    {
                        std::cout << "Note " << keyID << " was played\n";
                        addNote(keyID);
                    }

                    // Removed released key
                    else if (event.type == SDL_KEYUP)
                        removeNote(keyID);
                }
            }
        }
    }
}

template <class T>
int APPLICATION<T>::keyCodeToKeyID(SDL_KeyCode key)
{
    int id = 0;
    switch (key)
    {
    case SDLK_z:
        id = 0;
        break;
    case SDLK_s:
        id = 1;
        break;
    case SDLK_x:
        id = 2;
        break;
    case SDLK_c:
        id = 3;
        break;
    case SDLK_f:
        id = 4;
        break;
    case SDLK_v:
        id = 5;
        break;
    case SDLK_g:
        id = 6;
        break;
    case SDLK_b:
        id = 7;
        break;
    case SDLK_n:
        id = 8;
        break;
    case SDLK_j:
        id = 9;
        break;
    case SDLK_m:
        id = 10;
        break;
    case SDLK_k:
        id = 12;
        break;
    case SDLK_COMMA:
        id = 13;
        break;
    case SDLK_l:
        id = 14;
        break;
    case SDLK_PERIOD:
        id = 15;
        break;
    case SDLK_SLASH:
        id = 16;
        break;
    }

    return 64 + id;
}

template <class T>
void APPLICATION<T>::addNote(int keyID)
{
    auto noteFound = std::find_if(synthData.notes.begin(), synthData.notes.end(), [&keyID](const note<T> &item)
                                  { return item.id == keyID; });
    if (noteFound == synthData.notes.end())
    {
        try
        {
            synthData.notes.emplace_back(note<T>(keyID, synthData.ticks, 0, true));
        }
        catch (std::runtime_error &error)
        {
            std::cout << "In addNote: " << error.what() << "\n";
        }
    }
    else
    {
        noteFound->on = synthData.ticks;
        noteFound->active = true;
    }
}

template <class T>
void APPLICATION<T>::removeNote(int keyID)
{
    auto noteFound = std::find_if(synthData.notes.begin(), synthData.notes.end(), [&keyID](const note<T> &item)
                                  { return item.id == keyID; });
    noteFound->off = synthData.ticks;
}

template <class T>
void APPLICATION<T>::changeInstrument(SDL_Keycode instCode)
{

    switch (instCode)
    {
    case SDLK_1:
    {
        synthData.currentInstrument = &harm;
        std::cout << "Switched instrument to " << harm;
    }
    break;
    case SDLK_2:
    {
        synthData.currentInstrument = &bell;
        std::cout << "Switched instrument to " << bell;
    }
    break;
    case SDLK_3:
    {
        synthData.currentInstrument = &hihat;
        std::cout << "Switched instrument to " << hihat;
    }
    break;
    case SDLK_4:
    {
        synthData.currentInstrument = &kick;
        std::cout << "Switched instrument to " << kick;
    }
    break;
    case SDLK_5:
    {
        synthData.currentInstrument = &snare;
        std::cout << "Switched instrument to " << snare;
    }
    break;
    default:
        break;
    }
}

template <class T>
void APPLICATION<T>::audioCallback(void *userdata, Uint8 *stream, int len)
{

    std::lock_guard<std::mutex> guard(synthDataMutex);
    synthDataStruct *curSynthData = reinterpret_cast<synthDataStruct *>(userdata);
    int sizePerSample = static_cast<int>(sizeof(T));
    int numToWrite = len / (sizePerSample * 2);

    SDL_memset(stream, 0, len);
    T *buffer = reinterpret_cast<T *>(stream);

    for (int sample = 0; sample < numToWrite; sample++)
    {
        curSynthData->ticks += curSynthData->secondsPerTick;

        T mixedOutput = 0;
        for (auto &n : curSynthData->notes)
        {
            bool noteFinished = false;
            mixedOutput += curSynthData->currentInstrument->sound(curSynthData->ticks, n, noteFinished);
            if (noteFinished)
                n.active = false;
        }

        // std::cout << mixedOutput << "\n";
        *buffer++ = mixedOutput;
        *buffer++ = mixedOutput;
        std::erase_if(curSynthData->notes, [](const note<T> &item)
                      { return item.active == false; });
    }
}

template class APPLICATION<float>;
template class APPLICATION<double>;