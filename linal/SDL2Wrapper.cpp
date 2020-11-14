#include "SDL2Wrapper.h"

unique_ptr<SDL_Window, void(*)(SDL_Window*)> SDL2Wrapper::InitWindow(int width, int height) {
    return unique_ptr<SDL_Window, void(*)(SDL_Window*)>(
        SDL_CreateWindow("LINAL2D",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
        SDL_DestroyWindow);
}

unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> SDL2Wrapper::InitRenderer() {
    return unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(
        SDL_CreateRenderer(
            SDLWindow.get(),
            -1,
            SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
}

SDL2Wrapper::SDL2Wrapper(int width, int height, const RGB& backgroundColor) :
    Width(width), Height(height), BackgroundColor(backgroundColor),
    SDLWindow(InitWindow(width, height)), SDLRenderer(InitRenderer()) {
    //SDL_RenderSetScale(SDLRenderer.get(), 2.0f, 2.0f);
    SetBackground();
    SDL_RenderPresent(SDLRenderer.get());
}

SDL2Wrapper::~SDL2Wrapper() {
    SDL_Quit();
}

void SDL2Wrapper::OnEvent(Renderer& renderer) {
    while (Running) {
        renderer.BeforeEach();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: Running = false; break;
                case SDL_WINDOWEVENT:
                    if (event.window.event != SDL_WINDOWEVENT_SIZE_CHANGED) break;
                    Width = event.window.data1;
                    Height = event.window.data2;
                    renderer.OnResize(Width, Height);
                    break;

                case SDL_KEYUP: renderer.OnKey(SDL_KEYUP, event.key.keysym.scancode); break;
                case SDL_KEYDOWN: renderer.OnKey(SDL_KEYDOWN, event.key.keysym.scancode); break;

                case SDL_MOUSEMOTION: renderer.OnMouse(SDL_MOUSEMOTION); break;
                case SDL_MOUSEBUTTONDOWN: renderer.OnMouse(SDL_MOUSEBUTTONDOWN); break;
                case SDL_MOUSEBUTTONUP: renderer.OnMouse(SDL_MOUSEBUTTONUP); break;
                case SDL_MOUSEWHEEL: renderer.OnMouse(SDL_MOUSEWHEEL+(event.wheel.y > 0 ? 100 : 200)); break;
            }
        }
        SDL_RenderPresent(SDLRenderer.get());
    }
}

void SDL2Wrapper::SetBackground() {
    SDL_SetRenderDrawColor(SDLRenderer.get(), 
        BackgroundColor.R, BackgroundColor.G, BackgroundColor.B, BackgroundColor.A);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = Width;
    rect.h = Height;
    SDL_RenderFillRect(SDLRenderer.get(), &rect);
}

void SDL2Wrapper::DrawLine(int ax, int ay, int bx, int by, const RGB& rgb) {
    const int sdl_ax = ax;
    const int sdl_ay = Height - ay;
    const int sdl_bx = bx;
    const int sdl_by = Height - by;

    SDL_SetRenderDrawColor(SDLRenderer.get(), rgb.R, rgb.G, rgb.B, rgb.A);
    SDL_RenderDrawLine(SDLRenderer.get(), sdl_ax, sdl_ay, sdl_bx, sdl_by);
}

void SDL2Wrapper::DrawPoint(int centreX, int centreY, int radius, const RGB& rgb) {
    const int sdl_x = centreX;
    const int sdl_y = Height - centreY;

    SDL_SetRenderDrawColor(SDLRenderer.get(), rgb.R, rgb.G, rgb.B, rgb.A);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x + x, sdl_y - y);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x + x, sdl_y + y);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x - x, sdl_y - y);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x - x, sdl_y + y);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x + y, sdl_y - x);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x + y, sdl_y + x);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x - y, sdl_y - x);
        SDL_RenderDrawPoint(SDLRenderer.get(), sdl_x - y, sdl_y + x);

        DrawLine(sdl_x + x, sdl_y - y, sdl_x - x, sdl_y - y, rgb);
        DrawLine(sdl_x + x, sdl_y + y, sdl_x - x, sdl_y + y, rgb);
        DrawLine(sdl_x + y, sdl_y - x, sdl_x - y, sdl_y - x, rgb);
        DrawLine(sdl_x + y, sdl_y + x, sdl_x - y, sdl_y + x, rgb);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
