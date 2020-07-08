/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 12:44:57 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/07 11:41:12 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void			set_sprites(t_sprite *sprite)
{
	sprite[0].index = 0;
	sprite[0].amount = 1;
	sprite[0].pos.x = 250;
	sprite[0].pos.y = 50;
	sprite[0].sector = 1;
	sprite[0].action = 0;
	sprite[0].size = 4; //it's 8
	sprite[0].visible = 0;
	sprite[0].position = 2; //0 is ground floor, 25%, 2 is above the middle, 3 is top
	//size door de helft
	sprite[0].line.start.x = sprite[0].pos.x - sprite[0].size;
	sprite[0].line.start.y = sprite[0].pos.y - sprite[0].size;
	sprite[0].line.end.x = sprite[0].pos.x + sprite[0].size;
	sprite[0].line.end.y = sprite[0].pos.y + sprite[0].size;

	sprite[1].index = 1;
	sprite[1].amount = 1;
	sprite[1].pos.x = 450;
	sprite[1].pos.y = 50;
	sprite[1].sector = 2;
	sprite[1].action = 0;
	sprite[1].size = 8;
	sprite[1].visible = 0;
	sprite[0].position = 2; //0 is ground floor, 25%, 2 is above the middle, 3 is top
	sprite[1].line.start.x = sprite[1].pos.x - sprite[1].size;
	sprite[1].line.start.y = sprite[1].pos.y - sprite[1].size;
	sprite[1].line.end.x = sprite[1].pos.x + sprite[1].size;
	sprite[1].line.end.y = sprite[1].pos.y + sprite[1].size;

	sprite[2].index = 1;
	sprite[2].amount = 1;
	sprite[2].pos.x = 250;
	sprite[2].pos.y = 225;
	sprite[2].sector = 1;
	sprite[2].action = 0;
	sprite[2].size = 8;
	sprite[2].visible = 0;
	sprite[0].position = 2; //0 is ground floor, 25%, 2 is above the middle, 3 is top
	sprite[2].line.start.x = sprite[2].pos.x - sprite[2].size;
	sprite[2].line.start.y = sprite[2].pos.y - sprite[2].size;
	sprite[2].line.end.x = sprite[2].pos.x + sprite[2].size;
	sprite[2].line.end.y = sprite[2].pos.y + sprite[2].size;

	sprite[3].index = 0;
	sprite[3].amount = 1;
	sprite[3].pos.x = 100;
	sprite[3].pos.y = 400;
	sprite[3].sector = 0;
	sprite[3].action = 0;
	sprite[3].size = 8;
	sprite[3].visible = 0;
	sprite[0].position = 2; //0 is ground floor, 25%, 2 is above the middle, 3 is top
	sprite[3].line.start.x = sprite[3].pos.x - sprite[3].size;
	sprite[3].line.start.y = sprite[3].pos.y - sprite[3].size;
	sprite[3].line.end.x = sprite[3].pos.x + sprite[3].size;
	sprite[3].line.end.y = sprite[3].pos.y + sprite[3].size;
}

void			load_sprites_in_array(t_doom *doom)
{
	doom->sprite_image[0] = SDL_LoadBMP("./sprites/apple.BMP");
	if (doom->sprite_image[0] == NULL)
		printf("img is not loaded\n");
	doom->sprite_image[1] = SDL_LoadBMP("./sprites/banana.BMP");
	if (!doom->sprite_image[1])
		printf("img is not loaded\n");
}

void		sprite_init(t_doom *doom)
{
	load_sprites_in_array(doom);
	set_sprites(doom->sprite);
}
