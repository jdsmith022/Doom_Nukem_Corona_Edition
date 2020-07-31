#include "../../includes/doom.h"

void			key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->cam_move_f == TRUE)
		cam_move_fb(doom, dt, MOVE_SPEED);
	else if (event->cam_move_b == TRUE)
		cam_move_fb(doom, dt, -MOVE_SPEED);
	else if (event->cam_move_l == TRUE)
		cam_move_rl(doom, dt, -90 * PI / 180);
	else if (event->cam_move_r == TRUE)
		cam_move_rl(doom, dt, 90 * PI / 180);
	if (event->jump == TRUE)
		jump_player(doom, dt);
	if (event->step_down == TRUE)
		step_down(doom, dt);
	if (event->bend == TRUE || \
	doom->player_height < \
	doom->player_std_height + doom->lib.sector[doom->i_sector].height_floor)
		bend_down(doom);
}

void			key_release(t_event *event, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		event->cam_move_f = FALSE;
	else if (key->keysym.sym == SDLK_s)
		event->cam_move_b = FALSE;
	else if (key->keysym.sym == SDLK_a)
		event->cam_move_l = FALSE;
	else if (key->keysym.sym == SDLK_d)
		event->cam_move_r = FALSE;
	if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

static void 	key_select_and_shoot(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_q)
	{
		if (event->select == TRUE)
			event->select = FALSE;
		else
			event->select = TRUE;
	}
	if (key->keysym.sym == SDLK_e)
	{
		if (event->shoot == TRUE)
			event->shoot = FALSE;
		else
			event->shoot = TRUE;
	}
}

static void		key_press2(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_b)
		add_to_game(doom);
	if (key->keysym.sym == SDLK_q || key->keysym.sym == SDLK_e)
		key_select_and_shoot(doom, event, key);
	if (key->keysym.sym == SDLK_p) //needs to become an click on button event
		doom->light = doom->light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_o) //needs to become a click on button event
		doom->lib.sector[doom->i_sector].light =\
			doom->lib.sector[doom->i_sector].light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_v && doom->game_editor == TRUE)
		printing_map(&(doom->game_design));
}

void			key_press(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_ESCAPE)
		doom->is_running = FALSE;
	else if (key->keysym.sym == SDLK_w)
		event->cam_move_f = TRUE;
	else if (key->keysym.sym == SDLK_s)
		event->cam_move_b = TRUE;
	else if (key->keysym.sym == SDLK_a)
		event->cam_move_l = TRUE;
	else if (key->keysym.sym == SDLK_d)
		event->cam_move_r = TRUE;
	if (key->keysym.sym == SDLK_SPACE)
		event->jump = TRUE;
	if (key->keysym.sym == SDLK_x)
		event->bend = TRUE;
	if (key->keysym.sym == SDLK_q)
			event->select = event->select == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_m)
	{
		doom->game_editor = TRUE;
		doom->hud = FALSE;
	}
	if (key->keysym.sym == SDLK_n)
	{
		doom->game_editor = FALSE;
		doom->hud = TRUE;
	}
	key_press2(doom, event, key);
}
