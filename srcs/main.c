/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 15:23:14 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/04 15:23:25 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int	main(void)
{
	t_doom	doom;

	//load_maps();
	//init_struct();
	//init_message_bus();
	load_textures(&doom);
	sprite_init(&doom); //this will also be part of load_textures
	doom_init(&doom);
	//load_default(); //loads default settings ie menu, player settings
	//init_HUD/UI
	game_loop(&doom);
	return (0);
}
