/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_player_settings_sprites.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 11:52:36 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/11 14:44:40 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static SDL_Surface		**save_player_settings_sprites(t_doom *doom,
							int fd, int *len)
{
	char		*line;
	SDL_Surface **lib;
	int			ret;

	ret = get_line(doom, &line, fd, 1);
	*len = ft_atoi(line);
	lib = read_from_line(doom, line, fd, *len);
	free(line);
	return (lib);
}

void					save_player_sprites(t_doom *doom)
{
	int fd;

	modified(doom, "srcs/read_file/player_sprites");
	fd = open_file(doom, "srcs/read_file/player_sprites");
	doom->lib.player_lib = save_objects(doom, fd, &doom->lib.len_player_lib);
}
