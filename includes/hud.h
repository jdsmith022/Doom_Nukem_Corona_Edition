#ifndef HUD_H
# define HUD_H

# define SCISSOR 28
# define SPRAY_HAND 29
# define SPRAYING_HAND 30
# define TROLLEY 33
# define LEFT_SELECT 74
# define RIGHT_SELECT 75
# define CROSS_HAIR 76

typedef	struct s_doom	t_doom;

typedef enum		e_event_state
{
	sanitizer_shooting,
	sanitizer,
	facemask,
	health_pack,
	shopper_collision,
	health_pack_plus,
	boxes,
	corona_hit
}					t_event_state;

typedef struct	s_hud
{
	bool		start;
	int			update;
	int			hold_time;
	int 		curr_time;
	Uint32		corona_level;
	Uint32		sanitizer_level;
}				t_hud;

void			update_hud(t_doom *doom);
void			update_hud_levels(t_doom *doom, t_font *lib);
void			calculate_hud_levels(t_doom *doom);
void			update_timer(t_doom *doom, t_font *lib);
void			update_list_and_basket(t_doom *doom);

#endif