/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_info_to_lib.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:43:41 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/25 10:43:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static void		create_object(t_doom *doom, int fd, int i,
					int total_sprites)
{
	t_lib		*col_lib;
	static int	l;
	static int	obj_int;
	int			j;

	col_lib = &doom->lib;
	if (!l)
	{
		l = 0;
		obj_int = 0;
	}
	col_lib->sector[i].i_objects = obj_int;
	j = 0;
	while (j < col_lib->sector[i].n_objects)
	{
		col_lib->sprites[l] = object_inf(doom, fd, i, col_lib->len_obj_lib);
		l++;
		j++;
	}
	obj_int = obj_int + j;
	if (obj_int > total_sprites)
		doom_exit_failure(doom, \
			"error: number of objects in file is incorrect\n");
}

void			add_inf_to_lib(t_doom *doom, int len, int fd)
{
	int		i;
	int		j;
	char	*line;
	t_lib	*col_lib;

	col_lib = &doom->lib;
	i = 0;
	while (i < len)
	{
		create_sidedef(doom, fd, len, i);
		create_object(doom, fd, i, doom->total_sprites);
		i++;
	}
}
