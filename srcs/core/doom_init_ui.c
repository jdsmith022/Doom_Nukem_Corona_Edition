/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init_ui.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 16:02:29 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 23:43:31 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void	init_menu(t_doom *doom)
{
	doom->menu = (t_menu*)ft_memalloc(sizeof(t_menu));
	if (doom->menu == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->menu->state = menu;
	doom->menu->settings = FALSE;
	doom->menu->start_timer = FALSE;
	doom->game.editor = FALSE;
}

void	init_hud(t_doom *doom)
{
	doom->hud = (t_hud*)ft_memalloc(sizeof(t_hud));
	if (doom->hud == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->hud->update = -1;
	doom->hud->sanitizer_level = 100;
	doom->hud->corona_level = 0;
	doom->hud->hold_time = 600;
	doom->hud->curr_time = 600;
}

void	init_player_sprite(t_doom *doom)
{
	doom->player.handed = left;
	doom->player.character = player_1;
}
