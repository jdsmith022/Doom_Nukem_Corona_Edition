/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:50:56 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "doom.h"
# include "struct.h"

void				key_press(t_doom *doom, t_event *event,\
						SDL_KeyboardEvent *key);
void				key_select_and_shoot(t_doom *doom, t_event *event,
						SDL_KeyboardEvent *key);
void				key_release(t_event *event, SDL_KeyboardEvent *key);
void				key_handler(t_doom *doom, t_event *event, double dt);
void				mouse_press(t_doom *doom,\
						SDL_MouseButtonEvent *button, t_event event);
void				mouse_release(t_doom *doom,\
						SDL_MouseButtonEvent *button);
void				camera_movement(t_doom *doom,\
						SDL_MouseMotionEvent *motion, double dt);
void				move_cam_direction(t_doom *doom,\
						SDL_MouseMotionEvent *motion,\
						double dt, t_event *event);
void				set_new_position(t_doom *doom, t_event *event, double dt);
int					check_floor_diff(t_doom *doom, int sector, int next_sector);
int					check_sector_height_diff(t_doom *doom,\
						int sector, int next_sector);

#endif
