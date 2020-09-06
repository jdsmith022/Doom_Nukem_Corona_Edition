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

static uint8_t	get_next_grocery(t_doom *doom, uint32_t curr_texture)
{
	uint8_t		type;

	while (!is_existing_grocery(doom, doom->lib.tex_lib[curr_texture]))
	{
		if (curr_texture < doom->groceries->num_of_groceries - 1)
			curr_texture += 1;
		else
			curr_texture = 0;
	}
	type = *(int *)doom->lib.tex_lib[curr_texture]->userdata;
	curr_texture += 1;
	return (type);
}

static t_item	create_item(uint8_t type, int i)
{
	t_item item;

	item.type = type;
	item.amount = (rand() % 5) + 1;
	item.position = get_position(i, WIDTH - 35, 60);
	return (item);
}

void			default_shopping_list(t_doom *doom, t_item *s_list)
{
	uint32_t	curr_texture;
	uint8_t		shopping_list_len;
	uint8_t		i;

	s_list = ft_memalloc(sizeof(t_item) * shopping_list_len);
	doom->groceries->shopping_list = s_list;
	srand(time(0));
	i = 1;
	s_list[0] = create_item(TOILET, 0);
	set_sprite(doom, s_list[0].type, &s_list[0]);
	while (i < shopping_list_len)
	{
		curr_texture = rand() % (doom->groceries->num_of_groceries);
		s_list[i] = create_item(get_next_grocery(doom, curr_texture), i);
		set_sprite(doom, s_list[i].type, &s_list[i]);
		i++;
	}
}

void			custom_shopping_list(t_doom *doom, t_item *s_list)
{
	uint32_t	curr_texture;
	uint8_t		shopping_list_len;
	t_item		*groc_in_lvl;
	uint8_t		i;

	s_list = ft_memalloc(sizeof(t_item) * shopping_list_len);
	doom->groceries->shopping_list = s_list;
	groc_in_lvl = doom->groceries->groceries_in_level;
	srand(time(0));
	i = 0;
	while (i < shopping_list_len)
	{
		curr_texture = rand() % (doom->groceries->num_of_groceries);
		s_list[i] = create_item(groc_in_lvl[curr_texture].type, i);
		set_sprite(doom, s_list[i].type, &s_list[i]);
		i++;
	}
}

void			generate_shopping_list(t_doom *doom, t_item *s_list)
{
	uint32_t	curr_texture;
	uint8_t		shopping_list_len;
	uint8_t		i;

	printf("groceries in level: %d\n", doom->groceries->num_of_groceries);
	printf("shoppinglist length: %d\n", doom->groceries->shopping_list_len);
	shopping_list_len = doom->groceries->shopping_list_len;
	if (!shopping_list_len)
		return ;
	if (doom->game_design.custom_level)
		custom_shopping_list(doom, s_list);
	else
		default_shopping_list(doom, s_list);
}
