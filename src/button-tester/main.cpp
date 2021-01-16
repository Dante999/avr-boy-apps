#include <memory>
#include <stdio.h>
#include <unistd.h> // sleep()
// ---
#include <chrono>
#include <thread>
// --
#include "avr-boy-core/cartridge.hpp"
#include "avr-boy-core/graphx.hpp"

#include "avr-boy-emulator/transceiver_pipe.hpp"

#include "spdlog/spdlog.h"

inline static void sleep_for_ms(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

static void demo_buttons(cartridge_c &cartridge)
{
	using namespace avrboy_payload;

	cartridge.clear_buffer();
	cartridge.draw_buffer();

	constexpr uint16_t max_bounces   = 500;
	constexpr uint8_t  draw_delay_ms = 20;

	cartridge.set_text(5, 5, "Press buttons");

	cartridge.set_text(5, 20, "up    ");
	cartridge.set_text(5, 30, "down  ");
	cartridge.set_text(5, 40, "left  ");
	cartridge.set_text(5, 50, "right ");

	cartridge.set_text(75, 20, "A      ");
	cartridge.set_text(75, 30, "B      ");
	cartridge.set_text(75, 40, "start  ");
	cartridge.set_text(75, 50, "select ");
	cartridge.draw_buffer();

	auto stc = [](buttons_s buttons, button_e id) -> char {
		return (buttons.states & (1 << id)) ? '1' : '0';
	};

	avrboy_payload::buttons_s btns;

	for (uint16_t i = 0; i < max_bounces; ++i) {
		cartridge.get_buttons(btns);

		cartridge.set_char(40, 20, stc(btns, button_e::BUTTON_UP));
		cartridge.set_char(40, 30, stc(btns, button_e::BUTTON_DOWN));
		cartridge.set_char(40, 40, stc(btns, button_e::BUTTON_LEFT));
		cartridge.set_char(40, 50, stc(btns, button_e::BUTTON_RIGHT));

		cartridge.set_char(120, 20, stc(btns, button_e::BUTTON_A));
		cartridge.set_char(120, 30, stc(btns, button_e::BUTTON_B));
		cartridge.set_char(120, 40, stc(btns, button_e::BUTTON_START));
		cartridge.set_char(120, 50, stc(btns, button_e::BUTTON_SELECT));

		cartridge.draw_buffer();
		sleep_for_ms(draw_delay_ms);
	}
}

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

	spdlog::info("Configuration done, starting with main loop");

	cartridge.set_text(0, 0, "AVR BOY DEMO");

	while (1) {
		demo_buttons(cartridge);
		sleep_for_ms(1000);
	}
}
