#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static uint8_t	is_existing_grocery(t_doom *doom, SDL_Surface *curr)
{
	int		i;
	t_item	*shoppinglist;

	i = 0;
	shoppinglist = doom->groceries->shopping_list;
	while (i < doom->groceries->shopping_list_len)
	{
		if (shoppinglist[i].type == *(uint8_t *)curr->userdata)
			return (FALSE);
		i++;
	}
	if (!curr->userdata)
		return (FALSE);
	if (*(uint8_t *)curr->userdata)
		return (TRUE);
	return (FALSE);
}

static uint8_t	get_next_grocery(t_doom *doom)
{
	uint8_t		type;
	uint32_t	random_tex;

	srand(time(0));
	random_tex = rand() % (doom->lib.len_tex_lib);
	while (!is_existing_grocery(doom, doom->lib.tex_lib[random_tex]))
		random_tex = rand() % (doom->lib.len_tex_lib);
	type = *(int *)doom->lib.tex_lib[random_tex]->userdata;
	return (type);
}

static t_item	new_item(uint8_t type, int i)
{
	t_item		item;

	item.type = type;
	item.amount = (rand() % 5) + 1;
	item.position = get_position(i, WIDTH - 35, 60);
	return (item);
}

void			default_shopping_list(t_doom *doom, t_groceries *groceries)
{
	uint8_t		shopping_list_len;
	uint8_t		i;
	t_item		*s_list;

	s_list = groceries->shopping_list;
	shopping_list_len = groceries->shopping_list_len;
	i = 1;
	s_list[0] = new_item(TOILET, 0);
	set_sprite(doom, s_list[0].type, &s_list[0]);
	while (i < shopping_list_len)
	{
		s_list[i] = new_item(get_next_grocery(doom), i);
		set_sprite(doom, s_list[i].type, &s_list[i]);
		i++;
	}
}

void			generate_shopping_list(t_doom *doom)
{
	if (!doom->groceries->shopping_list_len)
		return ;
	if (doom->game_design.custom_level)
		custom_shopping_list(doom, doom->groceries);
	else
		default_shopping_list(doom, doom->groceries);
}
