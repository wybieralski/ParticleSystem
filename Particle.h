//
// Created by lw on 27.11.18.
//

#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H
#include "stdlib.h"
namespace caveofprogramming {

struct Particle {

  double m_x;
  double m_y;

  double vetlet_h;
  double vetlet_r;
  double vetlet_f;

  double m_speed;
  double m_direction;
private:
    void init();
public:
  Particle();
  virtual ~Particle();
  void update(int interval);
  void verlet(int interval);
};
} // namespace caveofprogramming
#endif // PARTICLES_PARTICLE_H
