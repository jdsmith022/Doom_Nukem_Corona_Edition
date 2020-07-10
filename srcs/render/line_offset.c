/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   offset.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 10:07:26 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/10 10:11:44 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

Uint8			find_slope_line_offset(t_point start, t_point end)
{
	Uint8 max_x;
	Uint8 max_y;
	Uint8 diff;

	if (start.x > end.x)
		max_x = start.x - end.x;
	else
		max_x = end.x - start.x;
	if (start.y > end.y)
		max_y = start.y - end.y;
	else
		max_y = end.y - start.y;
	if (max_x < max_y)
		diff = 1;
	else
		diff = 2;
	return (diff);
}
