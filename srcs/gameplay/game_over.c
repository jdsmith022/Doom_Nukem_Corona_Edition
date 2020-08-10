#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

static uint8_t			rem_amount(uint8_t a, uint8_t b)
{
	return (a > b ? a - b : b - a);
}

static void				set_missing_groceries(t_doom *doom, t_game_over_info *info)
{
	t_item				*missing_groc;
	t_item				*item;
	uint8_t				i;
	uint8_t				j;

	i = 0;
	j = 0;
	missing_groc = (t_item *)ft_memalloc(sizeof(t_item) * SHOPPING_LIST_L); // note: FREE (on program exit)
	if (!doom->groceries->basket_len)
	{
		info->groceries_to_display = SHOPPING_LIST;
		info->groceries_len = SHOPPING_LIST_L;
		return ;
	}
	while (i < SHOPPING_LIST_L)
	{
		item = get_item_from_basket(SHOPPING_LIST[i].type, &BASKET);
		if (!item)
			ft_memcpy(&missing_groc[j], &SHOPPING_LIST[i], sizeof(t_item));
		else if (item->amount != SHOPPING_LIST[i].amount)
		{
			item->amount = rem_amount(item->amount, SHOPPING_LIST[i].amount);
			ft_memcpy(&missing_groc[j], item, sizeof(t_item));
			j++;
		}
		i++;
	}
	info->groceries_to_display = missing_groc;
	info->groceries_len = j;
}

t_game_over_info		get_game_over_info(t_doom *doom)
{
	t_game_over_info	info;
	uint8_t				i;

	i = 0;
	doom->groceries->basket_len = get_basket_len(&doom->groceries->basket);
	info.won = checkout(doom->groceries) ? true : false;
	if (info.won){
		info.groceries_to_display = doom->groceries->shopping_list;
		info.groceries_len = SHOPPING_LIST_L;
	}
	else
		set_missing_groceries(doom, &info);
	printf("%s\n" , info.won ? "Level completed!" : "Game over!");
	printf("to display len: %d\n", info.groceries_len);
	while (i < info.groceries_len)
	{
		printf("%s\n", info.won ? "Collected all groceries!" : "Missed some groceries");
		printf("type: %d\n", info.groceries_to_display[i].type);
		printf("amount: %d\n", info.groceries_to_display[i].amount);
		i++;
	}
	return info;
}