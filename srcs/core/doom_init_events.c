
#include "../../includes/doom.h"

static void	init_events_2(t_event *event)
{
	event->died = FALSE;
	event->sprite_collision = FALSE;
	event->virus_red_i = -1;
	event->virus_red = FALSE;
	event->mist = FALSE;
	event->spray_mist = FALSE;
	event->light_switch = FALSE;
	event->click_light = -1;
	event->sanitizer_refills = 0;
	event->refill = FALSE;
	event->spray_shopper = FALSE;
	event->sprite_index = -1;
	event->toilet_paper = FALSE;
	event->trolly = FALSE;
	event->sliding_door = -1;
}

void		init_events(t_event *event)
{
	event->jump = FALSE;
	event->velocity = VELOCITY;
	event->floor_diff = 0;
	event->step_down = FALSE;
	event->y_pitch = 0;
	event->select = TRUE;
	event->shoot = FALSE;
	event->mouse_pointer = FALSE;
	event->scissor_lift = FALSE;
	event->scissor_lift_down = FALSE;
	event->scissor_lift_up = FALSE;
	event->virus_hit_index = -1;
	event->parked_too_close = FALSE;
	event->fall = FALSE;
	event->fall_count = -1;
	event->mouse_state_switched = TRUE;
	event->groc_pickup = FALSE;
	init_events_2(event);
}
