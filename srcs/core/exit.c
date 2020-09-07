/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 11:16:51 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"

void			doom_exit_lib_failure(t_bmp *bmp,
					const char *exit_meassge)
{
	ft_putendl(exit_meassge);
	ft_bzero(bmp, sizeof(bmp));
	free(bmp);
}

static void		sdl_window_screen_free(t_doom *doom)
{
	if (doom->window)
	{
		ft_bzero(doom->window, sizeof(doom->window));
		free(doom->window);
	}
	if (doom->surface)
	{
		ft_bzero(doom->window, sizeof(doom->surface));
		free(doom->surface);
	}
}

void			doom_exit_read_failure(t_doom *doom, const char *exit_message,
					int line)
{
	SDL_Quit();
	ft_putnbr(line);
	ft_putendl(exit_message);
	free_sdl_lib(doom);
	free_struct_lib(doom);
	ft_bzero(doom, sizeof(doom));
	exit(EXIT_FAILURE);
}

void			doom_exit_failure(t_doom *doom,
					const char *exit_message)
{
	SDL_Quit();
	ft_putendl(exit_message);
	free_lists(doom);
	free_clip_lists(doom);
	free_sdl_lib(doom);
	free_struct_lib(doom);
	ft_bzero(doom, sizeof(doom));
	exit(EXIT_FAILURE);
}

void			doom_exit_success(t_doom *doom)
{
	SDL_Quit();
	free_sdl_lib(doom);
	free_struct_lib(doom);
	ft_bzero(doom, sizeof(doom));
	exit(EXIT_SUCCESS);
}
