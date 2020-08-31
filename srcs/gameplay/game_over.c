#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

static bool			basket_is_empty(t_doom *doom, t_game_over *info)
{
	if (!doom->groceries->basket_len)
	{
		info->groceries_to_display = doom->groceries->shopping_list;
		info->groceries_len = doom->groceries->shopping_list_len;
		return (TRUE);
	}
	return (FALSE);
}

static void			check_item_from_basket(t_item *item, t_item *list,
						int i, t_item g)
{
	if (!item)
	{
		ft_memcpy(&g, &list[i], sizeof(t_item));
	}
	else if (item->amount != list->amount)
	{
		if (item->amount > list[i].amount)
			item->amount -= list[i].amount;
		else
			item->amount = list[i].amount - item->amount;
		ft_memcpy(&g, item, sizeof(t_item));
	}
}

static void			assign_missing(t_doom *doom, t_game_over *info, t_item *g)
{
	uint8_t			i;
	uint8_t			j;
	t_item			*item;
	t_item			*list;

	i = 0;
	j = 0;
	list = &doom->groceries->shopping_list[i];
	while (i < doom->groceries->shopping_list_len)
	{
		item = get_item_from_basket(list[i].type, &doom->groceries->basket);
		check_item_from_basket(item, list, i, g[j]);
		j++;
		i++;
	}
	info->groceries_to_display = g;
	info->groceries_len = j;
}

static void			set_missing_groceries(t_doom *doom, t_game_over *info)
{
	t_item			*missing_groc;

	missing_groc = (t_item *)ft_memalloc(sizeof(t_item) *
	doom->groceries->shopping_list_len);
	if (!missing_groc)
		doom_exit_failure(doom, "failed to allocate missing groceries\n");
	if (basket_is_empty(doom, info))
		return ;
	assign_missing(doom, info, missing_groc);
}

void				get_game_over_info(t_doom *doom)
{
	t_game_over		info;
	uint8_t			i;

	i = 0;
	doom->groceries->basket_len = get_basket_len(&doom->groceries->basket);
	info.won = checkout(doom->groceries) ? TRUE : FALSE;
	if (info.won)
	{
		info.groceries_to_display = doom->groceries->shopping_list;
		info.groceries_len = doom->groceries->shopping_list_len;
	}
	else
		set_missing_groceries(doom, &info);
	doom->groceries->info = info;
}
