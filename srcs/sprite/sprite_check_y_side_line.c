/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_check_y_side_line.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 12:56:50 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int				check_y_side_line(t_line line, int x, int y)
{
	t_point		compare;
	int			diff;
	int			diff_compare;

	compare.x = line.start.x;
	compare.y = line.start.y + 1;
	diff = (x - line.start.x) * (line.end.y - line.start.y) -\
			(y - line.start.y) * (line.end.x - line.start.x);
	diff_compare = (compare.x - line.start.x) * (line.end.y - line.start.y) -\
					(compare.y - line.start.y) * (line.end.x - line.start.x);
	if ((diff < 0 && diff_compare < 0) || (diff > 0 && diff_compare > 0)\
		|| diff == 0)
		return (-1);
	else
		return (1);
}
