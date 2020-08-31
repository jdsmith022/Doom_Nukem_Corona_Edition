
#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void		init_sprites(t_doom *doom)
{
	int i;

	i = 0;
	doom->visible_sprites = 0;
	doom->save_scissor_lift = -1;
	doom->lib.sprite_order = NULL;
	while (i < 20)
	{
		doom->lib.sprite_height[i] = i;
		i++;
	}
	doom->lib.move = 0;
}

static void		init_render(t_doom *doom)
{
	doom->ray_adjacent = (60 * (PI / 180)) / WIDTH;
	doom->dist_to_plane = (WIDTH / 2) / tan((60 * (PI / 180)) / 2);
	doom->max_ray = 10000;
	doom->dir_angle = 90;
}

static void		init_player(t_doom *doom)
{
	doom->pos.x = 23;
	doom->pos.y = 130;
	doom->player.height = PLAYER_HEIGHT;
	doom->player.std_height = PLAYER_HEIGHT;
	doom->i_sector = 0;
	doom->player.handed = left;
	doom->player.character = player_1;
}

static void		init_settings(t_doom *doom)
{
	doom->is_running = TRUE;
	doom->light = TRUE;
	doom->hud_display = TRUE;
	doom->game_editor = FALSE;
	doom->start_timer = FALSE;
	doom->poster = FALSE;
}

void			init_window(t_doom *doom)
{
	doom->lib.window.x_start = -1;
	doom->lib.window.x_end = WIDTH + 1;
	ft_bzero(doom->lib.window.y_pixel_bottom, WIDTH);
	ft_bzero(doom->lib.window.y_pixel_top, WIDTH);
	ft_bzero(doom->lib.window.height_standard, WIDTH);
	ft_bzero(doom->lib.window.wall_offset, WIDTH);
	doom->own_event.window = FALSE;
}

void			doom_init(t_doom *doom)
{
	init_groceries(doom);
	init_player(doom);
	init_settings(doom);
	init_audio(doom);
	init_menu(doom);
	init_render(doom);
	init_sprites(doom);
	init_events(&doom->own_event);
	init_window(doom);
}
