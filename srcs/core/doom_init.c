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
	event->y_pitch = 0;
	event->select = TRUE;
	event->shoot = FALSE;
	event->scissor_lift = FALSE;
	event->scissor_lift_down = FALSE;
	event->scissor_lift_up = FALSE;
	event->virus_hit_index = -1;
	event->parked_too_close = FALSE;
	event->fall = FALSE;
	event->fall_count = -1;
	event->mouse_state_switched = TRUE;
	event->groc_pickup = FALSE;
	event->died = FALSE;
	event->sprite_collision = FALSE;
	event->virus_red_i = -1;
	event->virus_red = FALSE;
	event->mist = FALSE;
	event->spray_mist = FALSE;
	event->light_switch = FALSE;
	event->click_light = -1;
	event->sanitizer_refills = 0;
	event->refill = FALSE;
	event->spray_shopper = FALSE;
	event->sprite_index = -1;
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
	// 	doom->pos.x =360; //start in cross
	// doom->pos.y = 10;
	doom->player_height = 48;
	doom->player_width = 48;
	doom->player_std_height = 48;
}

static void		init_settings(t_doom *doom)
{
	doom->is_running = TRUE;
	doom->light = TRUE;
	doom->hud_display = TRUE;
	doom->audio = (t_audio *)ft_memalloc(sizeof(t_audio)); // NOTE: FREE
	doom->audio->engine = OFF;
	doom->game_editor = FALSE;
	doom->start_timer = FALSE;
}

void			doom_init(t_doom *doom)
{
	srand(time(0));
	init_groceries(doom);
	init_player(doom);
	init_settings(doom);
	init_audio(doom);
	init_menu(doom);
	init_infection(doom);
	doom_init_events(&doom->own_event);
	doom->ray_adjacent = FOV / WIDTH;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
	doom->max_ray = 10000;
	doom->dir_angle = 90;
	doom->i_sector = 0;
	doom->visible_sprites = 0;
	doom->player_std_height = 48;
	doom->save_scissor_lift = -1;
}
