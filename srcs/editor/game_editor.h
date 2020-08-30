#ifndef GAME_EDITOR_H
# define GAME_EDITOR_H

# include <stdint.h>

# define FRAME_COUNT 8
# define FRAME_WIDTH 32
# define FRAME_HEIGHT 32
# define SIDEBAR_SECTOR 160
# define SIDEBAR_SIDEDEF 640
# define MINUS_X 160
# define MINUS_Y 0
# define PLUS_X 672
# define PLUS_Y 0
# define AR_LEFT_M_X 160
# define AR_LEFT_M_Y 300
# define AR_RIGHT_M_X 608
# define AR_RIGHT_M_Y 300
# define AR_UP_M_X 400
# define AR_UP_M_Y 568
# define AR_DOWN_M_X 400
# define AR_DOWN_M_Y 0

# define DEL_SECTOR_X 104
# define DEL_SECTOR_Y 75
# define ADD_SECTOR_X 24
# define ADD_SECTOR_Y 75

# define AR_LEFT_X 24
# define AR_LEFT_Y 0
# define AR_RIGHT_X 104
# define AR_RIGHT_Y 0

# define AR_LEFT_S_X 664
# define AR_LEFT_S_Y 0
# define AR_RIGHT_S_X 744
# define AR_RIGHT_S_Y 0

# define CROSS_P_X 714
# define CROSS_P_Y 150

# define PORTAL_X 744
# define PORTAL_Y 225
# define RM_SD_X 669
# define RM_SD_Y 225

# define DEL_OBJ_X 714
# define DEL_OBJ_Y 225

# define AR_LEFT_SC_X 664
# define AR_LEFT_SC_Y 300
# define AR_RIGHT_SC_X 744
# define AR_RIGHT_SC_Y 300

# define AR_LEFT_TF_X 0
# define AR_LEFT_TF_Y 375
# define TEX_FL_X 56
# define TEX_FL_Y 375
# define AR_RIGHT_TF_X 128
# define AR_RIGHT_TF_Y 375

# define AR_LEFT_TC_X 0
# define AR_LEFT_TC_Y 450
# define TEX_CE_X 56
# define TEX_CE_Y 450
# define AR_RIGHT_TC_X 128
# define AR_RIGHT_TC_Y 450

# define AR_LEFT_TS1_X 640
# define AR_LEFT_TS1_Y 375
# define TEX_S1_X 696
# define TEX_S1_Y 375
# define AR_RIGHT_TS1_X 768
# define AR_RIGHT_TS1_Y 375

# define AR_LEFT_TS2_X 640
# define AR_LEFT_TS2_Y 450
# define TEX_S2_X 696
# define TEX_S2_Y 450
# define AR_RIGHT_TS2_X 768
# define AR_RIGHT_TS2_Y 450

# define AR_LEFT_TS3_X 640
# define AR_LEFT_TS3_Y 525
# define TEX_S3_X  696
# define TEX_S3_Y 525
# define AR_RIGHT_TS3_X 768
# define AR_RIGHT_TS3_Y 525

# define SIDEDEF_BUTTON_X 640
# define SIDEDEF_BUTTON_Y 568

# define SECTOR_BUTTON_X 768
# define SECTOR_BUTTON_Y 568

# define HF_MAX 30
# define HF_MIN -30
# define HF_DIFF 60
# define HF_X 0
# define HF_Y 150
# define HF_HEIGHT 5
# define HF_LEN 160.0

# define HC_MAX 30
# define HC_MIN -30
# define HC_DIFF 60
# define HC_X 0
# define HC_Y 225
# define HC_HEIGHT 5
# define HC_LEN 160.0

# define LL_MAX 20
# define LL_MIN 0
# define LL_DIFF 20
# define LL_X 0
# define LL_Y 300
# define LL_HEIGHT 5
# define LL_LEN 160.0

enum			game_editor_im{
				plus,
				arrow_left,
				arrow_right,
				arrow_up,
				arrow_down,
				garbage,
				player
};

typedef struct	s_bar
{
    int			min;
    int			max;
    int			diff;
    int			x;
    int			y;
    int			height;
    int			len;
    int			cur_height;
}				t_bar;

typedef struct	s_poin {
	double		x;
	double		y;
}				t_poin;

typedef struct	s_point_int {
	int			x;
	int			y;
}				t_point_int;

typedef struct	s_angle_line
{
	t_point_int	diff;
	t_poin		steps;
	t_poin		start;
}				t_angle_line;
#endif
