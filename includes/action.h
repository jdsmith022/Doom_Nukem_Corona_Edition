#ifndef ACTION_H
# define ACTION_H

# include "doom.h"
# include "struct.h"

typedef struct s_doom	t_doom;

/*action functions */
void				action_handler(t_doom *doom);
void				sliding_door(t_doom *doom, int sd_index);
void				create_mv_sidedef(t_sidedef **sidedef, int k, int len);
void				relocate_moving_wall(t_point *intersect,\
						t_sidedef *near_sidedef, t_doom *doom, int x);
void				relocate_poster(t_doom *doom, t_sidedef *poster);
int					init_poster(int x, double distance, t_point intersect,\
						t_sidedef *poster);
void				light_switch(t_doom *doom);
void				add_infection(t_doom *doom);
void				find_infection(t_doom *doom, t_ray ray,\
						double min_distance);
void				scissor_lift_up(t_doom *doom);
void				scissor_lift_down(t_doom *doom);
void				player_fall(t_doom *doom, t_sprite *sprite);
void				jump_player(t_doom *doom, double dt);
void				step_down(t_doom *doom, double dt);
void				bend_down(t_doom *doom);

#endif
