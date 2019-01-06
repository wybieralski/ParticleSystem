//
// Created by lw on 27.11.18.
//

#ifndef PARTICLES_SWARM_H
#define PARTICLES_SWARM_H

#include "Particle.h"

namespace particlesystem {
class Swarm {
public:
    // ustalamy liczbę particles
  const static int NPARTICLES = 2000;
  Swarm();
  ~Swarm();
  void update(int elapsed);
  const Particle *const getParticles() { return m_pParticles; }

private:
  Particle *m_pParticles;
  int lastTime;
};
} // namespace particlesystem

#endif // PARTICLES_SWARM_H
