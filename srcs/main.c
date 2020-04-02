/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:34:53 by Malou          #+#    #+#                */
/*   Updated: 2020/04/01 16:39:09 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int     main(void)
{
	t_doom 	doom;
	
	doom_init(&doom);
	game_loop(&doom);
	return (0);
}
