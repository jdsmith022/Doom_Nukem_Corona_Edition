/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:34:53 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/05 16:33:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int	main(void)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	//load_maps();
	//init_struct();
	//init_message_bus();
	main2(&doom);
	printf("sector: %d\n", doom.lib.sector[0].outside);
	doom_init(&doom);
	//load_default(); //loads default settings ie menu, player settings
	//init_HUD/UI
	game_loop(&doom);
	return (0);
}
