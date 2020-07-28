# include "../../includes/doom.h"
# include "../../includes/gameplay.h"
# include "../../includes/textures.h"

static uint8_t	is_existing_grocery(t_doom *doom, SDL_Surface *curr)
{
	if (!curr->userdata)
		return false;
	if (*(uint8_t *)curr->userdata)
		return true;
	else return false;
}

static uint8_t	get_next_grocery(t_doom *doom, uint8_t *curr_texture)
{
	uint8_t		type;

	while (!is_existing_grocery(doom, TEXTURES[*curr_texture]))
		*curr_texture += 1;
	type = *(int *)TEXTURES[*curr_texture]->userdata;
	*curr_texture += 1;
	return type;
}

t_item 		*get_shopping_list(t_doom *doom, uint8_t *groceries)
{
	t_item		*shopping_list;
	uint8_t		curr_texture;
	uint8_t 	shopping_list_len;
	uint8_t		i;

	i = 0;
	curr_texture = 0;
	shopping_list_len = doom->groceries->shopping_list_len;
	shopping_list = ft_memalloc(sizeof(t_item) * shopping_list_len);
	while (i < shopping_list_len)
	{
		shopping_list[i].type = get_next_grocery(doom, &curr_texture);
		shopping_list[i].amount = (rand() % 5) + 1;
		set_sprite(doom, shopping_list[i].type, &shopping_list[i]);
		shopping_list[i].position = get_position(i, WIDTH - 300);
		i++;
	}
	return shopping_list;
}

void	print_shopping_list(t_groceries *groceries)
{
	uint8_t i;

	i = 0;
	while (i < groceries->shopping_list_len){
		printf("type: %d  amount: %d  ", groceries->shopping_list[i].type, groceries->shopping_list[i].amount);
		i++;
	}
	printf("\n");
}
