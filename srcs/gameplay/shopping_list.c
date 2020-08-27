#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static uint8_t	is_existing_grocery(t_doom *doom, SDL_Surface *curr)
{
	if (!curr->userdata)
		return (FALSE);
	if (*(uint8_t *)curr->userdata)
		return (TRUE);
	return (FALSE);
}

static uint8_t	get_next_grocery(t_doom *doom, uint8_t *curr_texture)
{
	uint8_t		type;

	while (!is_existing_grocery(doom, TEXTURES[*curr_texture]))
		*curr_texture += 1;
	type = *(int *)TEXTURES[*curr_texture]->userdata;
	*curr_texture += 1;
	return (type);
}

void			generate_shopping_list(t_doom *doom)
{
	uint8_t		curr_texture;
	uint8_t		shopping_list_len;
	uint8_t		i;
	t_item		*s_list;

	i = 0;
	shopping_list_len = doom->groceries->shopping_list_len;
	s_list = ft_memalloc(sizeof(t_item) * shopping_list_len);
	while (i < shopping_list_len)
	{
		curr_texture = rand() % doom->groceries->num_of_groceries;
		s_list[i].type = get_next_grocery(doom, &curr_texture);
		s_list[i].amount = (rand() % 5) + 1;
		set_sprite(doom, s_list[i].type, &s_list[i]);
		s_list[i].position = get_position(i, WIDTH - 35, 60);
		i++;
	}
	doom->groceries->shopping_list = s_list;
}
