#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

static void	set_sidedef_lib(t_doom *doom)
{
	t_ed_sidedef *ed_sidedef;
	t_lib		lib;
	int			index;

	ed_sidedef = doom->game_design.sd_head->next;
	lib.sidedef = (t_sidedef*)ft_memalloc(sizeof(t_sidedef) * doom->game_design.sd_len);
	if (lib.sidedef == NULL)
		doom_exit_failure(doom, "error: saving game editor info"); // add freeing of lists
	index = 0;
	while (ed_sidedef)
	{
		lib.sidedef[index].id = ed_sidedef->id;
		lib.sidedef[index].line = ed_sidedef->line;
		lib.sidedef[index].txt_1 = 14;
		lib.sidedef[index].txt_2 = ed_sidedef->texture;
		lib.sidedef[index].txt_3 = 17;
		lib.sidedef[index].sector = ed_sidedef->sector;
		lib.sidedef[index].opp_sector = ed_sidedef->opp_sector;
		lib.sidedef[index].action = 0;
		lib.sidedef[index].poster = -1;
		ft_bzero(ed_sidedef->previous, sizeof(t_ed_sidedef));
		free(ed_sidedef->previous);
		if (ed_sidedef->next == NULL)
		{
			ft_bzero(ed_sidedef, sizeof(t_ed_sidedef));
			free(ed_sidedef);
		}
		ed_sidedef = ed_sidedef->next;
		index++;
	}
	doom->lib.sidedef = lib.sidedef;
}

static void	set_sector_lib(t_doom *doom)
{
	t_ed_sector *ed_sector;
	t_lib		lib;
	int			index;

	ed_sector = doom->game_design.sc_head->next;
	lib.sector = (t_sector*)ft_memalloc(sizeof(t_sector) * doom->game_design.sc_len);
	if (lib.sector == NULL)
		doom_exit_failure(doom, "error: saving game editor info"); // add freeing of lists
	index = 0;
	while (ed_sector)
	{
		lib.sector[index].id = ed_sector->id;
		lib.sector[index].n_sidedefs = ed_sector->n_sidedefs;
		lib.sector[index].i_sidedefs = ed_sector->i_sidedefs;
		lib.sector[index].height_floor = ed_sector->height_floor;
		lib.sector[index].height_ceiling = ed_sector->height_ceiling;
		lib.sector[index].n_objects = doom->game_design.n_objects;
		lib.sector[index].i_objects = doom->game_design.i_objects;
		lib.sector[index].light_level = 10;// ed_sector->light_level;
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

void 	add_lists_to_libs(t_doom *doom)
{
	set_sector_lib(doom);
	set_sidedef_lib(doom);
	// set_object_lib(doom);
	// doom->lib.obj_lib = (SDL_Surface **)ft_memalloc(sizeof(SDL_Surface*));
	// if (doom->lib.obj_lib == NULL)
	doom->lib.sprites = (t_sprite*)ft_memalloc(sizeof(t_sprite) * doom->game_design.o_len);
	if (doom->lib.sprites == NULL)
		doom_exit_failure(doom, "error: saving game editor info"); // add freeing of lists
	doom->lib.len_obj_lib = 0; // wont need after objects are being set 
	doom->lib.sector = light_correction(\
		doom->lib.sector, doom->game_design.sc_len);
	doom->pos.x = doom->game_design.pl_x;
	doom->pos.y = doom->game_design.pl_y;
	doom->i_sector = doom->game_design.pl_sec;
	doom->player.height = PLAYER_HEIGHT \
		+ doom->lib.sector[doom->game_design.pl_sec].height_floor;
	doom->game.light = TRUE;
	doom->menu->state = start_game;
	doom->menu->start_timer = FALSE;
	doom->lib.sector[doom->i_sector].action = START_TIMER;
	doom->game.hud_display = TRUE;
	set_menu_game_variables(doom);
	clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->own_event.mouse_pointer = FALSE;
	init_groceries(doom);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	SDL_UpdateWindowSurface(doom->window);
}
