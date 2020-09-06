#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static uint8_t	get_groc_type(SDL_Surface *surface)
{
	uint8_t		type;

	type = *(uint8_t *)surface->userdata;
	if (type >= 1 && type <= GROC_TYPES)
		return (type);
	else
		return (0);
}

static void		set_sidedef_values(t_doom *doom, t_sidedef *sidedef,
				t_ed_sidedef *ed_sidedef, t_item *groceries)
{
	sidedef->id = ed_sidedef->id;
	sidedef->line = ed_sidedef->line;
	sidedef->txt_1 = 14;
	sidedef->txt_2 = ed_sidedef->texture;
	sidedef->txt_3 = 17;
	sidedef->sector = ed_sidedef->sector;
	sidedef->opp_sector = ed_sidedef->opp_sector;
	sidedef->action = 0;
	sidedef->poster = -1;
	groceries->type = get_groc_type(doom->lib.tex_lib[ed_sidedef->texture]);
}

static bool			is_valid_type(uint8_t type, t_item *tex_types, int len)
{
	int i;

	if (type == 0)
		return (false);
	i = 0;
	while ((i + 1) < len)
	{
		if (tex_types[i].type == type)
			return (false);
		i++;
	}
	return (true);
}

static void			set_groceries_in_level(t_doom *doom, t_item *t_types)
{
	int				i;
	int				j;
	int				len;
	t_item			groceries[GROC_TYPES];

	i = 0;
	j = 0;
	len = doom->game_design.sd_len;
	doom->groceries = (t_groceries*)ft_memalloc(sizeof(t_groceries));
	if (!doom->groceries)
		doom_exit_failure(doom, "error: saving groceries in editor");
	doom->groceries->num_of_groceries = 0;
	while (i < len)
	{
		if (is_valid_type(t_types[i].type, &t_types[i], len - i))
		{
			doom->groceries->num_of_groceries++;
			groceries[j] = t_types[i];
			j++;
		}
		i++;
	}
	doom->groceries->groceries_in_level =
		(t_item*)ft_memalloc(sizeof(t_item) * doom->groceries->num_of_groceries);
	if (!doom->groceries->groceries_in_level)
		doom_exit_failure(doom, "error: saving groceries in editor");
	ft_memcpy(
		doom->groceries->groceries_in_level,
		groceries, sizeof(t_item) * doom->groceries->num_of_groceries);
}

void		set_sidedef_lib(t_doom *doom)
{
	t_ed_sidedef	*ed_sidedef;
	t_lib			lib;
	int				index;
	t_item			tex_types[doom->game_design.sd_len];

	ed_sidedef = doom->game_design.sd_head->next;
	lib.sidedef = \
		(t_sidedef*)ft_memalloc(sizeof(t_sidedef) * doom->game_design.sd_len);
	if (lib.sidedef == NULL)
		doom_exit_failure(doom, "error: saving game editor info");
	index = 0;
	while (ed_sidedef)
	{
		set_sidedef_values(doom, &lib.sidedef[index],\
			ed_sidedef, &tex_types[index]);
		ft_bzero(ed_sidedef->previous, sizeof(t_ed_sidedef));
		free(ed_sidedef->previous);
		if (ed_sidedef->next == NULL)
			free(ed_sidedef);
		ed_sidedef = ed_sidedef->next;
		index++;
	}
	free(doom->game_design.sd_head->next);
	set_groceries_in_level(doom, tex_types);
	doom->lib.sidedef = lib.sidedef;
}
