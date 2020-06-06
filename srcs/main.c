/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:34:53 by Malou          #+#    #+#                */
/*   Updated: 2020/06/06 17:16:51 by rsteigen      ########   odam.nl         */
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
