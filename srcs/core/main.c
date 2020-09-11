/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:15 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 13:43:31 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/read.h"
#include "../../includes/audio.h"
#include "../../includes/font.h"

static void		argument_check(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putendl("Please run program in this fashion: ./duke_nukem");
		exit(0);
	}
}

int				main(int argc, char **argv)
{
	t_doom	doom;

	argument_check(argc, argv);
	ft_bzero(&doom, sizeof(t_doom));
	sdl_init(&doom);
	save_font_libraries(&doom);
	save_player_sprites(&doom);
	doom_start(&doom);
	save_libraries(&doom);
	doom_init(&doom);
	Mix_HaltMusic();
	game_loop(&doom);
	return (0);
}
