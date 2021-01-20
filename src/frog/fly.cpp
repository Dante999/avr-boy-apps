#include "ball.hpp"

void ball_c::bounce()
{

	switch (m_dir) {

	case DIR_UP:
		move_up();
		break;

	case DIR_DOWN:
		move_down();
		break;

	case DIR_LEFT:
		move_left();
		break;

	case DIR_RIGHT:
		move_right();
		break;

	case DIR_UPLEFT:
		move_upleft();
		break;

	case DIR_UPRIGHT:
		move_upright();
		break;

	case DIR_DOWNLEFT:
		move_downleft();
		break;

	case DIR_DOWNRIGHT:
		move_downright();
		break;
	}
}

bool ball_c::poke_up()
{
	if (m_y > m_min_y) {
		--m_y;
		return true;
	}
	else {
		++m_y;
		return false;
	}
}

bool ball_c::poke_down()
{
	if (m_y < m_max_y) {
		++m_y;
		return true;
	}
	else {
		--m_y;
		return false;
	}
}

bool ball_c::poke_left()
{

	if (m_x > m_min_x) {
		--m_x;
		return true;
	}
	else {
		++m_x;
		return false;
	}
}

bool ball_c::poke_right()
{
	if (m_x < m_max_x) {
		++m_x;
		return true;
	}
	else {
		--m_x;
		return false;
	}
}

void ball_c::move_up(void)
{
	if (!poke_up()) {
		m_dir = DIR_DOWN;
	}
}

void ball_c::move_down(void)
{
	if (!poke_down()) {
		m_dir = DIR_UP;
	}
}

void ball_c::move_left(void)
{
	if (!poke_left()) {
		m_dir = DIR_RIGHT;
	}
}
void ball_c::move_right(void)
{
	if (!poke_right()) {
		m_dir = DIR_LEFT;
	}
}

void ball_c::move_upleft()
{
	bool hit_top  = !poke_up();
	bool hit_left = !poke_left();

	if (hit_top && hit_left) {
		m_dir = DIR_DOWNRIGHT;
	}
	else if (hit_top) {
		m_dir = DIR_DOWNLEFT;
	}
	else if (hit_left) {
		m_dir = DIR_UPRIGHT;
	}
}

void ball_c::move_upright()
{
	bool hit_top   = !poke_up();
	bool hit_right = !poke_right();

	if (hit_top && hit_right) {
		m_dir = DIR_DOWNLEFT;
	}
	else if (hit_top) {
		m_dir = DIR_DOWNRIGHT;
	}
	else if (hit_right) {
		m_dir = DIR_UPLEFT;
	}
}

void ball_c::move_downleft()
{
	bool hit_bot  = !poke_down();
	bool hit_left = !poke_left();

	if (hit_bot && hit_left) {
		m_dir = DIR_UPRIGHT;
	}
	else if (hit_bot) {
		m_dir = DIR_UPLEFT;
	}
	else if (hit_left) {
		m_dir = DIR_DOWNRIGHT;
	}
}

void ball_c::move_downright()
{
	bool hit_bot   = !poke_down();
	bool hit_right = !poke_right();

	if (hit_bot && hit_right) {
		m_dir = DIR_UPLEFT;
	}
	else if (hit_bot) {
		m_dir = DIR_UPRIGHT;
	}
	else if (hit_right) {
		m_dir = DIR_DOWNLEFT;
	}
}
