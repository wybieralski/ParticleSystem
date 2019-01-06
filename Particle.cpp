//
// Created by lw on 27.11.18.banes
//

#include "Particle.h"
#include <math.h>

namespace particlesystem {

Particle::Particle() : m_x(0), m_y(0) { init(); }
Particle::~Particle() {}


// inicjalizujemy particles
void Particle::init() {
  m_y = 0;
  m_x = 0;
  vetlet_r=1;
  vetlet_r=1;
  //    explosion:
  //    m_direction = (2 * M_PI * rand()) / RAND_MAX;
  // tunnel m_direction =1;

  m_force=1;
  m_mass= ( std::rand() % 5 ) +1;
  m_acceleration= m_force*m_mass;

  m_direction = (2 * M_PI * rand()) / RAND_MAX;
  m_speed = (0.04 * rand()) / RAND_MAX;
  m_speed *= m_speed;
}


// interval odpowiada za dt
void Particle::update(int interval) {

// explosion
//
//bum bum
//    m_direction = (int)((1 + sin(interval * 0.001)) * 128)*cos(interval)*rand();
//

  // Euler method
  m_acceleration=m_force*m_mass;
  m_velocity=m_velocity+m_acceleration*interval;


  m_direction += interval * 0.0003;

  double xspeed = m_speed * cos(m_direction);
  double yspeed = m_speed * sin(m_direction);

  m_x += xspeed * interval;
  m_y += yspeed * interval;


  // tworzymy nowe particles z "ogniska"
  if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
    init();
  }
  if (rand() < RAND_MAX / 100) {
    init();
  }
}
void Particle::compute_euler(){

}

} // namespace particlesystem