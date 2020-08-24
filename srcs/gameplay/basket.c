#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

void		set_sprite(t_doom *doom, uint8_t type, t_item *item)
{
	uint16_t	i;

	i = 0;
	item->sprite = NULL;
	while (i < doom->lib.len_obj_lib)
	{
		if (!doom->lib.obj_lib[i])
			return ;
		else if (*((uint8_t *)doom->lib.obj_lib[i]->userdata) == type)
		{
			item->sprite = doom->lib.obj_lib[i];
			return ;
		}
		i++;
	}
	return ;
}

static t_item	init_item(t_doom *doom, uint8_t type)
{
	t_item item;

	item.type = type;
	item.amount = 1;
	set_sprite(doom, type, &item);
	if (!item.sprite)
		ft_putstr("Sprite not found\n");
	return (item);
}

static bool		valid_input(uint8_t type, t_list **head)
{
	if (!type || type > NUM_OF_GROCERIES)
		return (false);
	if (get_basket_len(head) >= MAX_BASKET_LEN)
		return (false);
	return (true);
}

void			add_item_to_basket(t_doom *doom, t_list **head, uint8_t type)
{
	t_list	*temp;
	t_item	item;

	temp = *head;
	if (!valid_input(type, head))
		return ;
	item = init_item(doom, type);
	doom->own_event.groc_pickup = TRUE;
	if (!temp)
	{
		temp = ft_lstnew(&item, sizeof(t_item));
		*head = temp;
		return ;
	}
	while (!is_in_basket((t_item *)temp->content, type))
	{
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	if (is_in_basket((t_item *)temp->content, type))
		change_amount((t_item *)temp->content, 1);
	else
		temp->next = ft_lstnew(&item, sizeof(t_item));
}

bool		remove_item_from_basket(t_list **head, uint8_t type)
{
	t_list	*temp;
	t_item	*item;

	temp = *head;
	if (!temp)
		return (false);
	item = (t_item *)temp->content;
	while (item->type != type)
	{
		if (!temp->next)
			return (false);
		temp = temp->next;
		item = (t_item *)temp->content;
	}
	change_amount(item, -1);
	if (item->amount == 0)
		del_node(head, temp);
	return (true);
}
