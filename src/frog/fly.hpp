#ifndef BALL_HPP
#define BALL_HPP

#include <stdint.h>

class fly_c {

public:
    enum direction_e : uint8_t {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UPLEFT,
	DIR_UPRIGHT,
	DIR_DOWNLEFT,
	DIR_DOWNRIGHT
    };


private:
    direction_e m_dir;
    const uint8_t m_min_x;
    const uint8_t m_max_x;
    const uint8_t m_min_y;
    const uint8_t m_max_y;

    uint8_t m_x;
    uint8_t m_y;

    bool poke_up();
    bool poke_down();
    bool poke_left();
    bool poke_right();

    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void move_upleft();
    void move_upright();
    void move_downleft();
    void move_downright();

public:
    fly_c(direction_e initial_direction, uint8_t x_min, uint8_t x_max, uint8_t y_min, uint8_t y_max):
        m_dir(initial_direction), m_min_x(x_min), m_max_x(x_max), m_min_y(y_min), m_max_y(y_max) {}


    void bounce();

    inline uint8_t get_x() {
	return m_x;
    }

    inline uint8_t get_y() {
	return m_y;
    }

    inline void set_coordinates(uint8_t x, uint8_t y)
    {
	m_x = x;
	m_y = y;
    }


};

#endif // BALL_HPP
