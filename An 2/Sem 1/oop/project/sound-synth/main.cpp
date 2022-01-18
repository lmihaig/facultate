#define SDL_MAIN_HANDLED 1
#include <application.h>

// Need argc and argv for windows compatibility
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{

    constexpr int WIDTH = 1920 * 0.5;
    constexpr int HEIGHT = 1080 * 0.5;

    // Type determines the quality of the audio float < double
    auto &app = APPLICATION<float>::instance(WIDTH, HEIGHT);
    app.run();
    return 0;
}