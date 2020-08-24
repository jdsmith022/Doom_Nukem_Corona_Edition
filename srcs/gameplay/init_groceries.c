# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

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
	return (num_of_groceries);
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
	doom->groceries->tp = FALSE;
	set_grocery_font(&doom->groceries->font);
}
