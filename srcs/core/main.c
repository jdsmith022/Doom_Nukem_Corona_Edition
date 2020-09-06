/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 12:59:02 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"
#include "../../includes/audio.h"
#include "../../includes/font.h"

int	main(void)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	sdl_init(&doom);
	save_font_libraries(&doom);
	doom_start(&doom);
	save_libraries(&doom);
	doom_init(&doom);
	Mix_HaltMusic();
	game_loop(&doom);
	return (0);
}
