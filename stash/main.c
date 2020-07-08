/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
<<<<<<< HEAD:stash/main.c
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 15:23:14 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/07/04 15:23:25 by rsteigen      ########   odam.nl         */
=======
/*   ft_print_numbers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/07 18:08:46 by efrank        #+#    #+#                 */
/*   Updated: 2019/01/07 18:09:40 by efrank        ########   odam.nl         */
>>>>>>> origin:bmp/libft/src/ft_memmove.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD:stash/main.c
int	main(void)
{
	t_doom	doom;

	//load_maps();
	//init_struct();
	//init_message_bus();
	load_textures(&doom);
	sprite_init(&doom); //this will also be part of load_textures
	doom_init(&doom);
	//load_default(); //loads default settings ie menu, player settings
	//init_HUD/UI
	game_loop(&doom);
	return (0);
=======
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		tmp[len];
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	i = 0;
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		d[i] = tmp[i];
		i++;
	}
	return (dst);
>>>>>>> origin:bmp/libft/src/ft_memmove.c
}
