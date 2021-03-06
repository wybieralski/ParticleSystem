#include "Particle.h"
#include "SDL.h"
#include "SDL_video.h"
#include "Screen.h"
#include "Swarm.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace particlesystem;
int main(int argc, char *argv[]) {

  srand(time(NULL));
    particlesystem::Screen screen;

  if (screen.init() == false) {
    std::cout << "Error initialasing SDL";
  }
  Swarm swarm;
  Swarm swarm2;

  int max = 0;
    int count =4;
  while (true) {
    int elapsed = SDL_GetTicks();

    // Update particles
    // Draw particles
    swarm.update(elapsed);

    unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001)) * 128);
    unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
    unsigned char blue = (unsigned char)((1 + cos(elapsed * 0.0003)) * 128);


    const Particle *const pParticles = swarm.getParticles();

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y =
                    particle.m_y * Screen::SCREEN_WIDTH / 2  + Screen::SCREEN_HEIGHT / 2 + Screen::SCREEN_HEIGHT / 5 ;
            screen.setPixel(x, y, red, green, blue);
        }

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y =
                    particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
            screen.setPixel(x, y, blue, red, green);
        }


      for (int i = 0; i < Swarm::NPARTICLES; i++) {
          Particle particle = pParticles[i];

          int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
          int y =
                  particle.m_y * Screen::SCREEN_WIDTH / 3 + Screen::SCREEN_HEIGHT / 3;
          screen.setPixel(x, y, red, blue, green);
      }


      for (int i = 0; i < Swarm::NPARTICLES; i++) {
          Particle particle = pParticles[i];

          int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2 -Screen::SCREEN_WIDTH / 4;;
          int y =
                  particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
          screen.setPixel(x, y, green, red, blue);
      }

      for (int i = 0; i < Swarm::NPARTICLES; i++) {
          Particle particle = pParticles[i];

          int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_WIDTH / 4;
          int y =
                  particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
          screen.setPixel(x, y, blue, green, red);
      }


    screen.boxBlur();

    // Draw the screen
    screen.update();

    if (screen.processEvents() == false) {
      break;
    }
  }

  SDL_Delay(3000); // Pause execution for 3000 milliseconds, for example
  screen.close();

  return 0;
}