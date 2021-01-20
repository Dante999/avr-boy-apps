#ifndef DELAY_HPP
#define DELAY_HPP

// ---
#include <unistd.h> // sleep()
#include <chrono>
#include <thread>
// ---

namespace ab_util {

    void wait_ms(uint16_t ms)
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    void draw_sequencial(cartridge_c &cartridge, uint8_t x, uint8_t y,
                                const char *text, uint8_t delay_ms)
    {
	    uint8_t i = 0;

	    while (*text != 0) {
		    cartridge.set_char(x + i, y, *text);
		    cartridge.draw_buffer();
		    ++text;
		    i += 8;
		    //sleep_for_ms(delay_ms);
		    wait_ms(delay_ms);
	    }
    }

}



#endif // DELAY_HPP
