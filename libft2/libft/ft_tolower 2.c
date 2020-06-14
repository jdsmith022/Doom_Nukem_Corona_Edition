/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tolower.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nde-wild <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 15:30:07 by nde-wild      #+#    #+#                 */
/*   Updated: 2019/01/16 10:33:16 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
