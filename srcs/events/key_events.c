#include "../../includes/doom.h"
#include "../../includes/menu.h"

void			key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->cam_move_f == TRUE && event->fall == FALSE)
		cam_move_fb(doom, dt, MOVE_SPEED);
	else if (event->cam_move_b == TRUE && event->fall == FALSE)
		cam_move_fb(doom, dt, -MOVE_SPEED);
	else if (event->cam_move_l == TRUE && event->fall == FALSE)
		cam_move_rl(doom, dt, -90 * PI / 180);
	else if (event->cam_move_r == TRUE && event->fall == FALSE)
		cam_move_rl(doom, dt, 90 * PI / 180);
	if (event->jump == TRUE && event->scissor_lift == FALSE)
		jump_player(doom, dt);
	if (event->step_down == TRUE && event->fall == FALSE)
		step_down(doom, dt);
	if ((event->bend == TRUE || \
	doom->player_height < \
	doom->player_std_height +\
	doom->lib.sector[doom->i_sector].height_floor) \
	&& event->fall == FALSE)
		bend_down(doom);
	if (event->scissor_lift_up == TRUE)
		scissor_lift_up(doom);
	if (event->scissor_lift_down == TRUE)
		scissor_lift_down(doom);
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
	else if (key->keysym.sym == SDLK_UP && event->scissor_lift == TRUE)
		event->scissor_lift_up = FALSE;
	else if (key->keysym.sym == SDLK_DOWN && event->scissor_lift == TRUE)
		event->scissor_lift_down = FALSE;
	if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

static void 	key_select_and_shoot(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_q)
		event->select = event->select == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_e)
		event->shoot = event->shoot == TRUE ? FALSE : TRUE;
}

static void		key_press2(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_b)
		add_to_game(doom);
	if (key->keysym.sym == SDLK_y)
		doom->menu->pause = TRUE;
	if (key->keysym.sym == SDLK_q || key->keysym.sym == SDLK_e)
		key_select_and_shoot(doom, event, key);
	if (key->keysym.sym == SDLK_p) //needs to become an click on button event
		doom->light = doom->light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_o) //needs to become a click on button event
		doom->lib.sector[doom->i_sector].light =\
			doom->lib.sector[doom->i_sector].light == TRUE ? FALSE : TRUE;
	if (key->keysym.sym == SDLK_v && doom->game_editor == TRUE)
		printing_map(&(EDIT));
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
