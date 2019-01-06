//
// Created by lw on 27.11.18.
//

#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H
#include "stdlib.h"
namespace particlesystem {

struct Particle {

  double m_x;
  double m_y;

  double m_mass;
  double m_acceleration;
  double m_force;
  double m_velocity;

  const double g=9.81;

  double vetlet_h;
  double vetlet_r;
  double vetlet_f;

  double m_speed;
  double m_direction;

  void compute_euler();
private:
    void init();
public:
  Particle();
  virtual ~Particle();
  void update(int interval);
  void verlet(int interval);
};
} // namespace particlesystem
#endif // PARTICLES_PARTICLE_H
