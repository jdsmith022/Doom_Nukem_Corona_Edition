/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position_vertical.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 18:18:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/26 18:45:15 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	position_jump(t_doom *doom)
{
	int		height;
	int		i;

	height = doom->player_height;
	i = 0;
	while (i < 180)
	{
		doom->player_height = height + sin(i - PI /180);
		i++;
	}
	doom->player_height = height;
}
