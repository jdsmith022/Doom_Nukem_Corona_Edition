/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:44 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/05 10:44:10 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void		init_sprites(t_doom *doom)
{
	int i;
	t_sector *sector;

	i = 0;
	doom->visible_sprites = 0;
	doom->save_scissor_lift = -1;
	doom->lib.sprite_order = NULL;
	sector = doom->lib.sector;
	doom->lib.move = 0;
	while (i < 20)
	{
		doom->lib.sprite_height[i] = i;
		i++;
	}
	doom->clip = (t_clip_lists*)malloc(sizeof(t_clip_lists) * 1);
	//protect
	doom->clip->head_bottom = (t_clip*)malloc(sizeof(t_clip) * 1);
	// if (!doom->clip->head_bottom)
	// 	printf("exit\n");
	//exit?
	//set content to NULL
	//and content size to ZERO
	//else malloc for content (not necessary)
	doom->clip->head_bottom->next = NULL;
	doom->clip->head_top = (t_clip*)malloc(sizeof(t_clip) * 1);
	//if (!doom->clip)
	//exit?
	//set content to NULL
	//and content size to ZERO
	//else malloc for content (not necessary)
	doom->clip->head_top->next = NULL;
	doom->clip->head_mid_bottom = (t_clip*)malloc(sizeof(t_clip) * 1);
	//if (!doom->clip)
	//exit?
	//set content to NULL
	//and content size to ZERO
	//else malloc for content (not necessary)
	doom->clip->head_mid_bottom->next = NULL;
	doom->clip->head_mid_top = (t_clip*)malloc(sizeof(t_clip) * 1);
	//if (!doom->clip)
	//exit?
	//set content to NULL
	//and content size to ZERO
	//else malloc for content (not necessary)
	doom->clip->head_mid_top->next = NULL;
}

static void		init_render(t_doom *doom)
{
	doom->cast.ray_adjacent = (60 * (PI / 180)) / WIDTH;
	doom->cast.dist_to_plane = (WIDTH / 2) / tan((60 * (PI / 180)) / 2);
	doom->cast.max_ray = 10000;
	doom->cast.dir_angle = 90;
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
	doom->game.is_running = TRUE;
	doom->game.light = TRUE;
	doom->game.hud_display = TRUE;
	doom->game.editor = FALSE;
	doom->game.start_timer = FALSE;
	doom->cast.poster = FALSE;
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
