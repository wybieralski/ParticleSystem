//
// Created by lw on 25.11.18.
//

#include "Screen.h"

namespace caveofprogramming {

Screen::Screen()
    : m_window(nullptr), m_renderer(nullptr), m_texture(nullptr),
      m_buffer1(nullptr), m_buffer2(nullptr) {}

bool Screen::init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  } // Initialize SDL2

  // Create an application window with the following settings:
  m_window = SDL_CreateWindow("An SDL2 window",        // window title
                              SDL_WINDOWPOS_UNDEFINED, // initial x position
                              SDL_WINDOWPOS_UNDEFINED, // initial y position
                              SCREEN_WIDTH,            // width, in pixels
                              SCREEN_HEIGHT,           // height, in pixels
                              SDL_WINDOW_SHOWN         // flags - see below
  );

  // Check that the window was successfully created
  if (m_window == nullptr) {
    SDL_Quit();
    // In the case that the window could not be made...
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
  m_texture =
      SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (m_renderer == nullptr) {
    std::cout << "Could not create renderer" << std::endl;
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }
  if (m_texture == nullptr) {
    std::cout << "Could not create texture" << std::endl;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

  memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}
void Screen::update() {
  // Update

  SDL_UpdateTexture(m_texture, nullptr, m_buffer1,
                    SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
  SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }

  Uint32 color = 0;

  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xFF;

  m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::boxBlur() {
  // swap buffers, pixel info is in mbuf2 and we are drawin to mbuf1
  Uint32 *temp = m_buffer1;

  m_buffer1 = m_buffer2;
  m_buffer2 = temp;

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {

      int redTotal = 0;
      int greenTotal = 0;
      int blueTotal = 0;

      for (int row = -1; row <=1; row++) {
        for (int col = -1; col <= 1; col++) {
          int currentX = x + col;
          int currentY = y + col;

          if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
            Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

            Uint8 red = color >> 24;
            Uint8 green = color >> 16;
            Uint8 blue = color >> 8;

            redTotal += red;
            greenTotal += green;
            blueTotal += blue;
          }
        }
      }
      Uint8 red = redTotal / 9;
      Uint8 green = greenTotal / 9;
      Uint8 blue = blueTotal / 9;

      setPixel(x, y, red, green, blue);
    }
  }
}

bool Screen::processEvents() {

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }
  }
  return true;
}

void Screen::close() {
  // Close and destroy the window
  delete[] m_buffer1;
  delete[] m_buffer2;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);

  // Clean up
  SDL_Quit();
}

} // namespace caveofprogramming