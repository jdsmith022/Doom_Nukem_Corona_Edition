#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/action.h"

void			key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->fall == FALSE && (event->move_pos_f == TRUE || \
		event->move_pos_b == TRUE || event->move_pos_r == TRUE ||\
		event->move_pos_l == TRUE))
		set_position(doom, event, dt);
	if (event->jump == TRUE && event->scissor_lift == FALSE)
		jump_player(doom, dt);
	if (event->step_down == TRUE && event->fall == FALSE)
		step_down(doom, dt);
	if ((event->bend == TRUE && event->scissor_lift == FALSE) || \
	(doom->player_height < doom->player_std_height +\
	doom->lib.sector[doom->i_sector].height_floor \
	&& event->fall == FALSE))
		bend_down(doom);
	if (event->bend == TRUE && event->scissor_lift == TRUE)
		exit_scissor_lift(doom);
	if (event->scissor_lift_up == TRUE)
		scissor_lift_up(doom);
	if (event->scissor_lift_down == TRUE)
		scissor_lift_down(doom);
}

void			key_release(t_event *event, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		event->move_pos_f = FALSE;
	else if (key->keysym.sym == SDLK_s)
		event->move_pos_b = FALSE;
	else if (key->keysym.sym == SDLK_a)
		event->move_pos_l = FALSE;
	else if (key->keysym.sym == SDLK_d)
		event->move_pos_r = FALSE;
	else if (key->keysym.sym == SDLK_UP && event->scissor_lift == TRUE)
		event->scissor_lift_up = FALSE;
	else if (key->keysym.sym == SDLK_DOWN && event->scissor_lift == TRUE)
		event->scissor_lift_down = FALSE;
	if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

static void		key_select_and_shoot(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_e)
	{
		event->select = event->select == TRUE ? FALSE : TRUE;
		if (event->select == TRUE)
			event->shoot = FALSE;
	}
	if (key->keysym.sym == SDLK_r)
	{
		event->shoot = event->shoot == TRUE ? FALSE : TRUE;
		if (event->shoot == TRUE)
			event->select = FALSE;
	}
}

static void		key_press2(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_b)
		add_to_game(doom);
	if (key->keysym.sym == SDLK_y)
		doom->menu->pause = TRUE;
	if (key->keysym.sym == SDLK_r || key->keysym.sym == SDLK_e)
		key_select_and_shoot(doom, event, key);
	if (key->keysym.sym == SDLK_p) //needs to become an click on button event
		doom->light = doom->light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_o) //needs to become a click on button event
		doom->lib.sector[doom->i_sector].light =\
			doom->lib.sector[doom->i_sector].light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_v && doom->game_editor == TRUE)
		printing_map(&(EDIT));
	// if (key->keysym.sym == SDLK_y && !doom->game_editor)
	// 	doom->menu->pause = TRUE;
}

void			key_press(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_ESCAPE)
		doom->is_running = FALSE;
	else if (key->keysym.sym == SDLK_w)
		event->move_pos_f = TRUE;
	else if (key->keysym.sym == SDLK_s)
		event->move_pos_b = TRUE;
	else if (key->keysym.sym == SDLK_a)
		event->move_pos_l = TRUE;
	else if (key->keysym.sym == SDLK_d)
		event->move_pos_r = TRUE;
	else if (key->keysym.sym == SDLK_UP && event->scissor_lift == TRUE)
		event->scissor_lift_up = TRUE;
	else if (key->keysym.sym == SDLK_DOWN && event->scissor_lift == TRUE)
		event->scissor_lift_down = TRUE;
	if (key->keysym.sym == SDLK_SPACE)
		event->jump = TRUE;
	if (key->keysym.sym == SDLK_x)
		event->bend = TRUE;
	if (key->keysym.sym == SDLK_m)
	{
		doom->game_editor = TRUE;
		doom->hud_display = FALSE;
	}
	if (key->keysym.sym == SDLK_n)
	{
		doom->game_editor = FALSE;
		doom->hud_display = TRUE;
		if (doom->lib.font_lib.bools.walking_info == TRUE)
			clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
	}
	key_press2(doom, event, key);
}
