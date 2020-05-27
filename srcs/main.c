/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:34:53 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/27 14:47:13 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int	main(void)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	//load_maps();
	//init_struct();
	//init_message_bus();
	doom_init(&doom);
	//load_default(); //loads default settings ie menu, player settings
	//init_HUD/UI
	game_loop(&doom);
	return (0);
}
