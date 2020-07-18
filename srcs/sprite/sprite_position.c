/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_position.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:29:08 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/18 18:28:07 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

// int		find_x(t_doom *doom, int index)
// {
// 	//player position should be (0,0)
// 	//adjust cords of the sprite
// 	//use atan2 to find angle of sprite position
// 	int 	middle;
// 	int		dist;
// 	int		screen_x;

// 	middle = WIDTH / 2;
// 	dist = sqrt(doom->lib.sprites[index].distance * doom->lib.sprites[index].distance\
// 	+ doom->dist_to_plane * doom->dist_to_plane);
// 	screen_x = 0;
// 	printf("dist pixels from middle (%d): %d\n", middle, dist);
// 	screen_x = middle + dist; //this doesn't make sense
// 	// return (screen_x);
// 	return (middle); //for now
// }

void	find_y(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index)
{
	double	middle;
	double	middle_divisor;
	// int d;

	//check height in sprite index
	// middle = (HEIGHT + doom->player_height) / 2;
	middle = (HEIGHT + doom->player_height) / 2;
	middle_divisor = HEIGHT / middle;
	sprite_begin->y = (-doom->lib.sprites[index].height / middle_divisor) + middle;
	if (sprite_begin->y < 0)
		sprite_begin->y = 0;
	sprite_end->y = (doom->lib.sprites[index].height / middle_divisor) + middle;
	if (sprite_end->y >= HEIGHT)
		sprite_end->y = HEIGHT - 1;
}

/*
**	find position x on screen
**	- what are the cords of the most left cord and the most right cord on map,
**		drawn on the screen
**	find position y on screen
**	- this is based on position from sprite struct
*/
void	find_position(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index)
{
	// sprite_cord->x = find_x(doom, index);
	sprite_begin->x = doom->lib.sprites[index].sprite_x;
	sprite_end->x = sprite_begin->x + doom->lib.sprites[index].width;
	if (sprite_begin->x < 0)
		sprite_begin->x = 0;
	if (sprite_end->x > WIDTH)
		sprite_end->x = WIDTH - 1;
	find_y(doom, sprite_begin, sprite_end, index); //temp, I need to consider size of the wall
	printf("sprite_begin cords: (%f ;%f)\n", sprite_begin->x, sprite_begin->y);
	printf("sprite_end cords: (%f ;%f)\n", sprite_end->x, sprite_end->y);
}
