#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void		init_sprites(t_doom *doom)
{
	doom->visible_sprites = 0;
	doom->save_scissor_lift = -1;
}

static void		init_render(t_doom *doom)
{
	doom->ray_adjacent = FOV / WIDTH;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
	doom->max_ray = 10000;
	doom->dir_angle = 90;
}

static void		init_player(t_doom *doom)
{
	doom->pos.x = 32;
	doom->pos.y = 130;
	doom->player_height = PLAYER_HEIGHT;
	doom->player_width = 48;
	doom->player_std_height = PLAYER_HEIGHT;
	doom->i_sector = 0;
}

static void		init_settings(t_doom *doom)
{
	doom->is_running = TRUE;
	doom->light = TRUE;
	doom->hud_display = TRUE;
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
	init_render(doom);
	init_sprites(doom);
	init_events(&doom->own_event);
}
