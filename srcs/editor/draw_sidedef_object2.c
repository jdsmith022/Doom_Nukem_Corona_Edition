#include "../../includes/doom.h"
#include "game_editor.h"

void	set_angle(t_angle_line *angle, double *i)
{
	angle->start.x += angle->steps.x;
	angle->start.y += angle->steps.y;
	*i += fabs(angle->steps.x) + fabs(angle->steps.y);
}

void	set_pixels(Uint32 **pixels, t_angle_line angle, int color)
{
	pixels[0][((int)angle.start.y * WIDTH) + \
		(int)angle.start.x] = color;
	pixels[0][((int)(angle.start.y + 1) * WIDTH) + \
		(int)angle.start.x] = color;
	pixels[0][((int)angle.start.y * WIDTH) + \
		(int)angle.start.x + 1] = color;
}
