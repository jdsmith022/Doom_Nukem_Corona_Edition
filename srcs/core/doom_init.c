#include "../../includes/doom.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void		doom_init_events(t_event *event)
{
	event->jump = FALSE;
	event->velocity = VELOCITY;
	event->floor_diff = 0;
	event->step_down = FALSE;
	event->jump = FALSE;
	event->y_pitch = 0;
	event->select = TRUE;
	event->shoot = FALSE;
}

static void		init_infection(t_doom *doom)
{
	doom->lib.infection = (t_sidedef*)malloc(sizeof(t_sidedef) * 100);
	doom->lib.tot_len_infection = 100;
	doom->lib.cur_len_infection = 0;
}

static void		init_player(t_doom *doom)
{
	doom->pos.x = 32;
	doom->pos.y = 130;
	// doom->pos.x = 32; //skybox start
	// doom->pos.y = 220;
	doom->player_height = 48;
	doom->player_width = 48;
	doom->player_std_height = 48;
	// doom->difficulty = 1;
}

static void		init_settings(t_doom *doom)
{
	doom->own_event.mouse_state_switched = TRUE;
	doom->is_running = TRUE;
	doom->light = TRUE;
	doom->huds = TRUE;
	doom->audio->engine = OFF;
	doom->game_editor = FALSE;
}

void			doom_init(t_doom *doom)
{
	srand(time(0));
	init_groceries(doom);
	init_audio(doom);
	init_player(doom);
	init_settings(doom);
	init_menu(doom);
	init_infection(doom);
	doom_init_events(&doom->own_event);
	if (doom->audio->engine)
		load_audio(doom->audio);
	// set_lines(doom->sidedef);
	doom->ray_adjacent = FOV / WIDTH;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
	// doom->pos.x = 400;
	// doom->pos.y = 20;
	doom->max_ray = 10000;
	doom->dir_angle = 90;
	doom->i_sector = 0;
	doom->visible_sprites = 0;
	doom->player_std_height = 48;
}
