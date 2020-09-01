/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/01 22:34:43 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"

int	main(void)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	sdl_init(&doom);
	save_libraries(&doom);
	save_font_libraries(&doom);
	doom_init(&doom);
	doom_start(&doom);
	game_loop(&doom);
	return (0);
}
