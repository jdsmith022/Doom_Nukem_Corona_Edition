#ifndef ACTION_H
# define ACTION_H

# include "doom.h"
# include "struct.h"

typedef struct s_doom	t_doom;

/*action functions */
void				action_handler(t_doom *doom);
void				relocate_moving_wall(t_point *intersect,\
						t_sidedef *near_sidedef, t_doom *doom, int x);
void				light_switch(t_doom *doom);
void				add_infection(t_doom *doom);
void				scissor_lift_up(t_doom *doom);
void				scissor_lift_down(t_doom *doom);
void				player_fall(t_doom *doom);
void				jump_player(t_doom *doom, double dt);
void				get_up(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);
void				sanitizer_refill(t_doom *doom);
void				check_select(t_doom *doom);

#endif
