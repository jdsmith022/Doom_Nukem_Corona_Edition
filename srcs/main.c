/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:34:53 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/06 15:36:38 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int     main(void)
{
	t_doom 	doom;
	
	//load_maps();
	//init_struct();
	//init_message_bus();
	doom_init(&doom);
	//init_HUD/UI
	game_loop(&doom);
	return (0);
}
