/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:51:02 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "doom.h"
# include "struct.h"

typedef struct s_doom	t_doom;

void				action_handler(t_doom *doom);
void				light_switch(t_doom *doom, t_sidedef poster);
void				light_timer(t_doom *doom, int *flag);
void				change_sector_light(t_doom *doom);
void				scissor_lift_up(t_doom *doom);
void				scissor_lift_down(t_doom *doom);
void				player_fall(t_doom *doom);
void				jump_player(t_doom *doom, double dt);
void				get_up(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);
void				sanitizer_refill(t_doom *doom);
void				sanitizer_pause(t_doom *doom);
void				check_select(t_doom *doom);

#endif
