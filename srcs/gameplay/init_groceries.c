/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_groceries.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:28:34 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

uint8_t			get_num_of_groceries(t_doom *doom)
{
	uint16_t	i;
	uint8_t		num_of_groceries;

	i = 0;
	num_of_groceries = 0;
	while (i < doom->lib.len_tex_lib)
	{
		if (*(uint8_t *)doom->lib.tex_lib[i]->userdata)
			num_of_groceries++;
		i++;
	}
	return (num_of_groceries);
}

static void		init_default_groceries(t_doom *doom)
{
	doom->groceries = NULL;
	doom->groceries = (t_groceries *)ft_memalloc(sizeof(t_groceries));
	if (doom->groceries == NULL)
		doom_exit_failure(doom, "error: groceries malloc");
	doom->groceries->num_of_groceries = get_num_of_groceries(doom);
}

void			init_groceries(t_doom *doom)
{
	uint8_t		num_of_groceries;

	if (!doom->game_design.custom_level)
		init_default_groceries(doom);
	num_of_groceries = doom->groceries->num_of_groceries;
	if (doom->groceries->num_of_groceries < MAX_SL_LEN)
		doom->groceries->shopping_list_len = num_of_groceries;
	else
		doom->groceries->shopping_list_len = MAX_SL_LEN;
	doom->groceries->shopping_list =
		ft_memalloc(sizeof(t_item) * doom->groceries->shopping_list_len);
	generate_shopping_list(doom);
	doom->groceries->basket = NULL;
	doom->groceries->font = doom->lib.font_lib.font_16;
}
