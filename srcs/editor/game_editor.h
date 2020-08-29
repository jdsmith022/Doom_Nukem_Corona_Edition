#ifndef GAME_EDITOR_H
# define GAME_EDITOR_H


# include <stdint.h>
// # include "../../includes/doom.h"

#define FRAME_COUNT 8
#define FRAME_WIDTH 32
#define FRAME_HEIGHT 32
#define SIDEBAR_SECTOR WIDTH / 5
#define SIDEBAR_SIDEDEF WIDTH - WIDTH / 5
#define MINUS_X WIDTH / 5
#define MINUS_Y 0
#define PLUS_X WIDTH - WIDTH / 5 - FRAME_WIDTH
#define PLUS_Y 0
#define AR_LEFT_M_X SIDEBAR_SECTOR
#define AR_LEFT_M_Y HEIGHT / 2
#define AR_RIGHT_M_X SIDEBAR_SIDEDEF - FRAME_WIDTH
#define AR_RIGHT_M_Y HEIGHT / 2
#define AR_UP_M_X WIDTH / 2
#define AR_UP_M_Y HEIGHT - FRAME_HEIGHT
#define AR_DOWN_M_X WIDTH / 2
#define AR_DOWN_M_Y 0

#define DEL_SECTOR_X SIDEBAR_SECTOR - FRAME_WIDTH - AR_LEFT_X
#define DEL_SECTOR_Y HEIGHT / 8
#define ADD_SECTOR_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH) / 2
#define ADD_SECTOR_Y HEIGHT / 8

#define AR_LEFT_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH) / 2
#define AR_LEFT_Y 0
#define AR_RIGHT_X SIDEBAR_SECTOR - FRAME_WIDTH - AR_LEFT_X
#define AR_RIGHT_Y 0

#define AR_LEFT_S_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH) / 2 + SIDEBAR_SIDEDEF
#define AR_LEFT_S_Y 0
#define AR_RIGHT_S_X SIDEBAR_SECTOR - FRAME_WIDTH - AR_LEFT_X + SIDEBAR_SIDEDEF
#define AR_RIGHT_S_Y 0

#define CROSS_P_X SIDEBAR_SECTOR / 2 - FRAME_WIDTH / 2 + SIDEBAR_SIDEDEF
#define CROSS_P_Y HEIGHT / 8 * 2

#define PORTAL_X SIDEBAR_SECTOR - FRAME_WIDTH - AR_LEFT_X + SIDEBAR_SIDEDEF
#define PORTAL_Y HEIGHT / 8 * 3
#define RM_SD_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH) / 2 + SIDEBAR_SIDEDEF
#define RM_SD_Y HEIGHT / 8 * 3

#define DEL_OBJ_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH / 2) + SIDEBAR_SIDEDEF
#define DEL_OBJ_Y HEIGHT / 8 * 3

#define AR_LEFT_SC_X (SIDEBAR_SECTOR / 2 - FRAME_WIDTH) / 2 + SIDEBAR_SIDEDEF
#define AR_LEFT_SC_Y HEIGHT / 8 * 4
#define AR_RIGHT_SC_X SIDEBAR_SECTOR - FRAME_WIDTH - AR_LEFT_X + SIDEBAR_SIDEDEF
#define AR_RIGHT_SC_Y HEIGHT / 8 * 4

#define AR_LEFT_TF_X 0
#define AR_LEFT_TF_Y HEIGHT / 8 * 5
#define TEX_FL_X   SIDEBAR_SECTOR / 2 - 24
#define TEX_FL_Y HEIGHT / 8 * 5
#define AR_RIGHT_TF_X SIDEBAR_SECTOR - FRAME_WIDTH
#define AR_RIGHT_TF_Y HEIGHT / 8 * 5

#define AR_LEFT_TC_X 0
#define AR_LEFT_TC_Y HEIGHT / 8 * 6
#define TEX_CE_X  SIDEBAR_SECTOR / 2 - 24
#define TEX_CE_Y HEIGHT / 8 * 6
#define AR_RIGHT_TC_X SIDEBAR_SECTOR - FRAME_WIDTH
#define AR_RIGHT_TC_Y HEIGHT / 8 * 6

#define AR_LEFT_TS1_X SIDEBAR_SIDEDEF
#define AR_LEFT_TS1_Y HEIGHT / 8 * 5
#define TEX_S1_X  SIDEBAR_SECTOR / 2 - 24 + SIDEBAR_SIDEDEF
#define TEX_S1_Y HEIGHT / 8 * 5
#define AR_RIGHT_TS1_X WIDTH - FRAME_WIDTH
#define AR_RIGHT_TS1_Y HEIGHT / 8 * 5

#define AR_LEFT_TS2_X SIDEBAR_SIDEDEF
#define AR_LEFT_TS2_Y HEIGHT / 8 * 6
#define TEX_S2_X  SIDEBAR_SECTOR / 2 - 24 + SIDEBAR_SIDEDEF
#define TEX_S2_Y HEIGHT / 8 * 6
#define AR_RIGHT_TS2_X WIDTH - FRAME_WIDTH
#define AR_RIGHT_TS2_Y HEIGHT / 8 * 6

#define AR_LEFT_TS3_X SIDEBAR_SIDEDEF
#define AR_LEFT_TS3_Y HEIGHT / 8 * 7
#define TEX_S3_X  SIDEBAR_SECTOR / 2 - 24 + SIDEBAR_SIDEDEF
#define TEX_S3_Y HEIGHT / 8 * 7
#define AR_RIGHT_TS3_X WIDTH - FRAME_WIDTH
#define AR_RIGHT_TS3_Y HEIGHT / 8 * 7

#define SIDEDEF_BUTTON_X SIDEBAR_SIDEDEF
#define SIDEDEF_BUTTON_Y HEIGHT - FRAME_WIDTH

#define SECTOR_BUTTON_X WIDTH - FRAME_WIDTH
#define SECTOR_BUTTON_Y HEIGHT - FRAME_WIDTH

#define HF_MAX 30
#define HF_MIN -30
#define HF_DIFF 60
#define HF_X 0
#define HF_Y HEIGHT / 8 * 2
#define HF_HEIGHT 5
#define HF_LEN (float)(WIDTH / 5)

#define HC_MAX 30
#define HC_MIN -30
#define HC_DIFF 60
#define HC_X 0
#define HC_Y HEIGHT / 8 * 3
#define HC_HEIGHT 5
#define HC_LEN (float)(WIDTH / 5)

#define LL_MAX 20
#define LL_MIN 0
#define LL_DIFF 20
#define LL_X 0
#define LL_Y HEIGHT / 8 * 4
#define LL_HEIGHT 5
#define LL_LEN (float)(WIDTH / 5)

enum game_editor_im{plus, arrow_left, arrow_right, arrow_up, arrow_down, garbage, player};

typedef struct s_bar
{
    int min;
    int max;
    int diff;
    int x;
    int y;
    int height;
    int len;
    int cur_height;
}               t_bar;

//remove cause in a different file but couldn't find yet

typedef struct			s_poin {
	double				x;
	double				y;
}						t_poin;

typedef struct			s_point_int {
	int				    x;
	int				    y;
}						t_point_int;

typedef struct  s_angle_line
{
    t_point_int diff;
    t_poin steps;
    t_poin start;
}               t_angle_line;
#endif