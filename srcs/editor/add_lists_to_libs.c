#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

void		set_sector_lib(t_doom *doom)
{
	t_ed_sector *ed_sector;
	t_lib		lib;
	int			index;

	ed_sector = doom->game_design.sc_head->next;
	lib.sector = \
		(t_sector*)ft_memalloc(sizeof(t_sector) * doom->game_design.sc_len);
	if (lib.sector == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	index = 0;
	while (ed_sector)
	{
		lib.sector[index].id = ed_sector->id;
		lib.sector[index].n_sidedefs = ed_sector->n_sidedefs;
		lib.sector[index].i_sidedefs = ed_sector->i_sidedefs;
		lib.sector[index].height_floor = ed_sector->height_floor;
		lib.sector[index].height_ceiling = ed_sector->height_ceiling;
		lib.sector[index].n_objects = doom->game_design.n_sprites;
		lib.sector[index].i_objects = doom->game_design.i_sprites;
		lib.sector[index].light_level = doom->game_design.light_level;
		lib.sector[index].action = 0;
		lib.sector[index].hold_light = 0;
		lib.sector[index].slope_floor_id = -1;
		lib.sector[index].slope_floor = 0;
		lib.sector[index].slope_ceiling_id = -1;
		lib.sector[index].slope_ceiling = 0;
		lib.sector[index].txt_ceiling = 14;
		lib.sector[index].txt_floor = 17;
		ft_bzero(ed_sector->previous, sizeof(t_ed_sector));
		free(ed_sector->previous);
		if (ed_sector->next == NULL)
		{
			ft_bzero(ed_sector, sizeof(t_ed_sector));
			free(ed_sector);
		}
		ed_sector = ed_sector->next;
		index++;
	}
	doom->lib.sector = lib.sector;
}

static void		set_gameplay_settings(t_doom *doom)
{
	doom->i_sector = doom->i_sector;
	doom->pos = doom->pos;
	doom->lib.sector = light_correction(\
		doom->lib.sector, doom->game_design.sc_len);
	doom->player.height = PLAYER_HEIGHT \
		+ doom->lib.sector[doom->i_sector].height_floor;
	doom->game.light = TRUE;
	doom->menu->state = start_game;
	doom->menu->start_timer = FALSE;
	doom->lib.sector[doom->i_sector].action = START_TIMER;
	doom->game.hud_display = TRUE;
	doom->lib.font_lib.bools.walking_info = TRUE;
	doom->lib.font_lib.bools.walking_text = TRUE;
	doom->lib.font_lib.bools.start_sector = TRUE;
	doom->lib.font_lib.bools.trolly = FALSE;
	doom->lib.font_lib.bools.checkout = TRUE;
	doom->lib.font_lib.bools.scissor_lift = FALSE;
	doom->lib.font_lib.bools.text = FALSE;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->own_event.mouse_pointer = FALSE;
	clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	SDL_UpdateWindowSurface(doom->window);
}

static void		flush_sector_list_info(t_doom *doom)
{
	doom->game_design.ed_sector->light_level = doom->game_design.light_level;
	doom->game_design.ed_sector->height_floor = doom->game_design.floor_height;
	doom->game_design.ed_sector->height_ceiling = \
		doom->game_design.ceiling_height;
}

void			add_lists_to_libs(t_doom *doom)
{
	flush_sector_list_info(doom);
	set_sector_lib(doom);
	set_sprite_lib(doom);
	set_sidedef_lib(doom);
	set_gameplay_settings(doom);
	del_groceries(doom->groceries);
	init_groceries(doom);
	printf("%f - %f, %d\n", doom->pos.x, doom->pos.y, doom->i_sector);
}
