/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_position.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:29:08 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/08 17:07:39 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		find_x(t_doom *doom, int index)
{
	//player position should be (0,0)
	//adjust cords of the sprite
	//use atan2 to find angle of sprite position
	int 	middle;
	int		dist;
	int		screen_x;

	middle = WIDTH / 2;
	dist = sqrt(doom->lib.sprite[index].distance * doom->lib.sprite[index].distance\
	+ doom->dist_to_plane * doom->dist_to_plane);
	screen_x = 0;
	printf("dist pixels from middle (%d): %d\n", middle, dist);
	if (doom->lib.sprite[index].x <= middle)
		screen_x = middle - dist;
	else
		screen_x = middle + dist;
	// return (screen_x);
	return (middle); //for now
}

int		find_y(t_doom *doom)
{
	int	middle;

	//check height in sprite index
	middle = (HEIGHT + doom->player_height) / 2;
	return (middle);
}

/*
**	find position x on screen
**	- what are the cords of the most left cord and the most right cord on map,
**		drawn on the screen
**	find position y on screen
**	- this is based on position from sprite struct
*/
void	find_position(t_doom *doom, t_point *sprite_cord, int index)
{
	sprite_cord->x = find_x(doom, index);
	sprite_cord->y = find_y(doom); //temp, I need to consider size of the wall
	printf("sprite_cord->x: %f\n", sprite_cord->x);
	printf("sprite_cord->y: %f\n", sprite_cord->y);
}
