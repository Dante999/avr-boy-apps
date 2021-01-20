#ifndef FROG_HPP
#define FROG_HPP

#include "boundaries.hpp"
#include "avr-boy-core/cartridge.hpp"

class frog_c
{
private:
    static constexpr uint8_t m_sprite[8] = {0x81, 0x42, 0x24, 0x7e, 0x7e, 0x24, 0x42, 0x81};

    const boundaries_s& m_bounds;

    uint8_t m_x = 0;
    uint8_t m_y = 0;

public:
        frog_c(boundaries_s& bounds, uint8_t x_start, uint8_t y_start)
	    : m_bounds(bounds), m_x(x_start), m_y(y_start) {}

	inline uint8_t get_x()
	{
	    return m_x;
	}

	inline uint8_t get_y()
	{
	    return m_y;
	}

	void move_up()
	{
	    if( m_y > m_bounds.min_y )
		--m_y;
	}

	void move_down()
	{
	    if( m_y < m_bounds.max_y-7)
		++m_y;
	}

	void move_left()
	{
	    if( m_x > m_bounds.min_x)
		--m_x;
	}

	void move_right()
	{
	    if( m_x < m_bounds.max_x-7)
		++m_x;
	}

	bool does_colide_with(uint8_t x, uint8_t y)
	{
	        return  ( m_x <= x && x < m_x+8) && ( m_y <= y && y < m_y+8);
	}

	void draw(cartridge_c& cartridge)
	{
	        cartridge.set_tile_8x8(m_x, m_y, m_sprite);
	}
};

#endif // FROG_HPP

