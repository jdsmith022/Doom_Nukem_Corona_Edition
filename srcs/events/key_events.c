
#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"

void			key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->fall == FALSE && (event->move_pos_f == TRUE || \
		event->move_pos_b == TRUE || event->move_pos_r == TRUE ||\
		event->move_pos_l == TRUE))
		set_new_position(doom, event, dt);
	if (event->jump == TRUE && event->scissor_lift == FALSE \
		&& event->fall == FALSE)
		jump_player(doom, dt);
	if (event->fall == TRUE && event->jump == TRUE)
		get_up(doom, dt);
	if (event->step_down == TRUE && event->fall == FALSE)
		step_down(doom, dt);
	if ((event->bend == TRUE && event->scissor_lift == FALSE) || \
	(doom->player_height < doom->player_std_height +\
	doom->lib.sector[doom->i_sector].height_floor \
	&& event->fall == FALSE))
		bend_down(doom);
	if (event->bend == TRUE && event->scissor_lift == TRUE && \
		doom->player_height == 50)
		exit_scissor_lift(doom);
	else if (event->scissor_lift_up == TRUE)
		scissor_lift_up(doom);
	else if (event->scissor_lift_down == TRUE)
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
	else if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

static void		key_select_and_shoot(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_e)
	{
		event->select = event->select == TRUE ? FALSE : TRUE;
		if (event->select == TRUE)
		{
			event->shoot = FALSE;
			event->mouse_pointer = FALSE;
		}
	}
	else if (key->keysym.sym == SDLK_r)
	{
		event->shoot = event->shoot == TRUE ? FALSE : TRUE;
		if (event->shoot == TRUE)
		{
			event->select = FALSE;
			event->mouse_pointer = FALSE;
		}
	}
	else if (key->keysym.sym == SDLK_t)
	{
		
		event->mouse_pointer = event->mouse_pointer == TRUE ? FALSE : TRUE;
		if (event->mouse_pointer == TRUE)
		{
			event->select = FALSE;
			event->shoot = FALSE;
		}
	}
}

static void		key_press2(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_b)
		add_to_game(doom);
	else if (key->keysym.sym == SDLK_y)
		doom->menu->pause = TRUE;
	else if (key->keysym.sym == SDLK_r || key->keysym.sym == SDLK_e || key->keysym.sym == SDLK_t)
		key_select_and_shoot(doom, event, key);
	else if (key->keysym.sym == SDLK_v && doom->game_editor == TRUE)
		printing_map(&(EDIT));
	else if (key->keysym.sym == SDLK_SPACE)
		event->jump = TRUE;
	else if (key->keysym.sym == SDLK_x)
		event->bend = TRUE;
	else if (key->keysym.sym == SDLK_n)
	{
		doom->game_editor = FALSE;
		doom->hud_display = TRUE;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		if (doom->lib.font_lib.bools.walking_info == TRUE)
			clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
	}
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
	key_press2(doom, event, key);
}
