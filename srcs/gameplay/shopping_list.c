# include "../../includes/doom.h"
# include "../../includes/gameplay.h"
# include "../../includes/textures.h"

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

	i = 0;
	curr_texture = 0;
	shopping_list_len = doom->groceries->shopping_list_len;
	SHOPPING_LIST = ft_memalloc(sizeof(t_item) * shopping_list_len);
	while (i < shopping_list_len)
	{
		SHOPPING_LIST[i].type = get_next_grocery(doom, &curr_texture);
		SHOPPING_LIST[i].amount = (rand() % 5) + 1;
		set_sprite(doom, SHOPPING_LIST[i].type, &SHOPPING_LIST[i]);
		SHOPPING_LIST[i].position = get_position(i, WIDTH - 35, 60);
		i++;
	}
}
