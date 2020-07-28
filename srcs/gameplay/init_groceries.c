# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

SDL_Rect		get_position(uint16_t index, int start_x)
{
	SDL_Rect	position;

	position.x = start_x + (index * 50);
	position.y = 50;
	position.w = 30;
	position.h = 30;
	return position;
}

void			set_positions(t_list **basket)
{
	t_list		*temp;
	t_item		*item;
	uint16_t	i;

	i = 0;
	temp = *basket;
	if (!temp)
		return;
	while (temp)
	{
		item = (t_item *)temp->content;
		item->position = get_position(i, 50);
		temp = temp->next;
		i++;
	}
}

static uint8_t	*get_groceries()
{
	uint8_t		*groceries;
	uint8_t		i;

	i = 0;
	groceries = ft_memalloc(sizeof(uint8_t) * GROCERY_LENGTH);
	while (i < GROCERY_LENGTH)
	{
		groceries[i] = (i + i);
		i++;
	}
	return groceries;
}

void			set_grocery_font(TTF_Font **font)
{
	*font = TTF_OpenFont("srcs/font/font_style/Cicle_Semi.ttf", 16);
}

uint8_t			get_num_of_groceries(t_doom *doom)
{
	uint16_t	i;
	uint8_t		num_of_groceries;

	i = 0;
	num_of_groceries = 0;
	while (i < doom->lib.len_tex_lib)
	{
		if (*(uint8_t *)TEXTURES[i]->userdata)
			num_of_groceries++;
		i++;
	}
	return num_of_groceries;
}

void			init_groceries(t_doom *doom)
{
	uint8_t		num_of_groceries;

	doom->groceries = (t_groceries *)ft_memalloc(sizeof(t_groceries)); // NOTE: FREE
	doom->groceries->num_of_groceries = get_num_of_groceries(doom);
	if (doom->groceries->num_of_groceries < MAX_SHOPPING_LIST_LENGTH)
		doom->groceries->shopping_list_len = num_of_groceries;
	else
		doom->groceries->shopping_list_len = MAX_SHOPPING_LIST_LENGTH;
	generate_shopping_list(doom);
	doom->groceries->basket = NULL;
	set_grocery_font(&doom->groceries->font);
	print_shopping_list(doom->groceries);
}
