#include "avr-boy-core/cartridge.hpp"
#include "avr-boy-core/graphx.hpp"

#include "avr-boy-emulator/transceiver_pipe.hpp"

#include "spdlog/spdlog.h"
#include "util/delay.hpp"
#include "fly.hpp"
#include "frog.hpp"

static constexpr uint8_t sprite_blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

struct game_s {

private:
	static constexpr uint8_t x_min = 0;
	static constexpr uint8_t x_max = graphx_c::max_x;
	static constexpr uint8_t y_min = 9;
	static constexpr uint8_t y_max = graphx_c::max_y;


	boundaries_s m_bounds{x_min, x_max, y_min, y_max};

	uint16_t m_score = 1;
	uint8_t m_delay_ms = 10;
	cartridge_c& m_cartridge;
	frog_c m_frog{m_bounds, 64, 32};

	fly_c m_fly{fly_c::direction_e::DIR_UPRIGHT, x_min, x_max, y_min,
		     y_max};

public:
	game_s(cartridge_c& cartridge) : m_cartridge(cartridge) {
		m_fly.set_coordinates(10, 10);


		for( uint8_t x=0; x < graphx_c::width; ++x)
		{
			m_cartridge.set_pixel(x, 8, avrboy_payload::COLOR_BLACK);
		}

		draw_score();

		m_cartridge.draw_buffer();
	}

	void redraw_ball()
	{
		m_cartridge.set_pixel(m_fly.get_x(), m_fly.get_y(),
		                    avrboy_payload::color_e::COLOR_WHITE);
		m_fly.bounce();
		m_cartridge.set_pixel(m_fly.get_x(), m_fly.get_y(),
		                    avrboy_payload::color_e::COLOR_BLACK);
	}

	void move_spider()
	{
		m_cartridge.set_tile_8x8(m_frog.get_x(), m_frog.get_y(), sprite_blank);

		avrboy_payload::buttons_s buttons;
		m_cartridge.get_buttons(buttons);

		if ( buttons.states & (1<< avrboy_payload::button_e::BUTTON_UP))
			m_frog.move_up();

		if ( buttons.states & (1<< avrboy_payload::button_e::BUTTON_DOWN))
			m_frog.move_down();

		if ( buttons.states & (1<< avrboy_payload::button_e::BUTTON_LEFT))
			m_frog.move_left();

		if ( buttons.states & (1<< avrboy_payload::button_e::BUTTON_RIGHT))
			m_frog.move_right();

		m_frog.draw(m_cartridge);
	}

	void draw_score() {
		char tmp[6];
		snprintf(tmp, 6, "%05d", m_score);
		tmp[5] = '\0';

		m_cartridge.set_text(98, 0, tmp);
	}

	void iterate() {
		move_spider();
		redraw_ball();

		// TODO: Bird which hunts frog

		if( m_frog.does_colide_with(m_fly.get_x(), m_fly.get_y()))
		{
			++m_score;
			m_fly.set_coordinates(rand()&m_bounds.max_x, rand()&m_bounds.max_y);
		}

		draw_score();

		m_cartridge.draw_buffer();
		ab_util::wait_ms(m_delay_ms);
	}



};



int main()
{
	spdlog::set_level(spdlog::level::info);
	spdlog::info("Hello World!");

	struct cartridge_emulator_s : public cartridge_c {
		transceiver_pipe_cartridge m_transceiver;

		void send_byte(uint8_t byte) override
		{
			m_transceiver.send_byte(byte);
		}

		uint8_t receive_byte() override
		{
			return m_transceiver.receive_byte();
		}
	};

	cartridge_emulator_s cartridge;

	cartridge.sync_with_handheld();

	cartridge.clear_buffer();
	ab_util::draw_sequencial(cartridge, 20, 20, "FROG VS. FLY", 80);
	ab_util::wait_ms(2000);

	cartridge.clear_buffer();


	game_s game(cartridge);

	while(1)
	{
		game.iterate();
	}

}
