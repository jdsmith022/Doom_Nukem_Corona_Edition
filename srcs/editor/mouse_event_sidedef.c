#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void	add_player(t_doom *doom, int x, int y)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	if (check_sector_in_sector(doom, pos) == TRUE)
	{
		doom->game_design.pl_x = x;
		doom->game_design.pl_y = y;
		doom->game_design.player_placed = TRUE;
	}
	doom->game_design.pl_pos = 0;
}

void		mouse_press_sidedef_txt(t_doom *doom, int x, int y)
{
	if (x > AR_LEFT_TS2_X && x < AR_LEFT_TS2_X + FRAME_WIDTH && \
	y > AR_LEFT_TS2_Y && y < AR_LEFT_TS2_Y + FRAME_HEIGHT && \
	doom->game_design.tex_index - 1 >= 0)
		doom->game_design.tex_index--;
	else if (x > AR_RIGHT_TS2_X && x < AR_RIGHT_TS2_X + FRAME_WIDTH && \
	y > AR_RIGHT_TS2_Y && y < AR_RIGHT_TS2_Y + FRAME_HEIGHT &&\
	doom->game_design.tex_index + 1 < 12)
		doom->game_design.tex_index++;
}

static void	create_portal(t_doom *doom)
{
	t_ed_sidedef 	*sidedef;
	t_ed_sector		*sector;

	sidedef = doom->game_design.ed_sidedef;
	sidedef->opp_sector = doom->game_design.sc_len;
	set_sidedef_values(doom, sidedef->line);
	doom->game_design.ed_sidedef->opp_sector = sidedef->sector;
	doom->game_design.edit_sector = FALSE;
	doom->game_design.open_connection = TRUE;
}

static void	set_sidedef_to_prev(t_doom *doom)
{
	t_ed_sidedef *sidedef;

	sidedef = doom->game_design.ed_sidedef;
	if (sidedef->id - 1 >= 0)
	{
		sidedef = sidedef->previous;
		doom->game_design.cur_sd = sidedef->id;
		doom->game_design.ed_sidedef = sidedef;
	}
}

static void	set_sidedef_to_next(t_doom *doom)
{
	t_ed_sidedef *sidedef;

	sidedef = doom->game_design.ed_sidedef;
	if (sidedef->id + 1 < doom->game_design.sd_len)
	{
		sidedef = sidedef->next;
		doom->game_design.cur_sd = sidedef->id;
		doom->game_design.ed_sidedef = sidedef;
	}
}

void		mouse_press_sidedef(t_doom *doom, int x, int y)
{
	t_gamedesign editor;

	editor = doom->game_design;
	if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && \
	y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_next(doom);
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && \
	y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
		set_sidedef_to_prev(doom);
	else if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && \
		y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
		create_portal(doom);
	// else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	// editor.pl_pos == 0 && editor.object_bar == 1)
		// add_object(doom, x, y);
	if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && \
	editor.pl_pos == TRUE && editor.edit_sector == TRUE)
		add_player(doom, x, y);
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SD_Y && y < RM_SD_Y + FRAME_HEIGHT)
		delete_sidedef(doom);
	else if (x > RM_SD_X && x < RM_SD_X + FRAME_WIDTH && \
	y > RM_SC_Y && y < RM_SC_Y + FRAME_HEIGHT)
		delete_sector(doom);
}
