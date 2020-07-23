# include "../../includes/doom.h"
# include "../../includes/gameplay.h"
# include "../../includes/textures.h"

t_item 		*get_shopping_list(t_doom *doom, uint8_t *groceries)
{
	t_item	*shopping_list;
	uint8_t	i;

	i = 0;
	shopping_list = ft_memalloc(sizeof(t_item) * SHOPPING_LIST_LENGTH);
	while (i < SHOPPING_LIST_LENGTH)
	{
		shopping_list[i].type = 8 + i;
		shopping_list[i].amount = (rand() % 5) + 1;
		set_sprite(doom, shopping_list[i].type, &shopping_list[i]);
		shopping_list[i].position = get_position(i, WIDTH - 300);
		i++;
	}
	return shopping_list;
}

void	print_shopping_list(t_item *shopping_list)
{
	uint8_t i;

	i = 0;
	while (i < SHOPPING_LIST_LENGTH){
		printf("type: %d  amount: %d  ", shopping_list[i].type, shopping_list[i].amount);
		i++;
	}
	printf("\n");
}
