/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameplay.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elkanfrank <elkanfrank@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 20:02:50 by elkanfrank    #+#    #+#                 */
/*   Updated: 2020/09/07 13:24:08 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void				groceries(t_doom *doom)
{
	if (!doom->groceries)
		return ;
	if (doom->own_event.mouse_press)
		handle_groceries(doom);
}
