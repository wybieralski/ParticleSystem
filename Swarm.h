//
// Created by lw on 27.11.18.
//

#ifndef PARTICLES_SWARM_H
#define PARTICLES_SWARM_H

#include "Particle.h"

namespace caveofprogramming {
class Swarm {
public:
  const static int NPARTICLES = 5000;
  Swarm();
  ~Swarm();
  void update(int elapsed);
  const Particle *const getParticles() { return m_pParticles; }

private:
  Particle *m_pParticles;
  int lastTime;
};
} // namespace caveofprogramming

#endif // PARTICLES_SWARM_H
