#include "../../includes/doom.h"
#include "game_editor.h"


void    draw_bar_point(Uint32 **pixels, t_doom *doom, int x, int y, int len)
{
    double place;
    int i;
    int j;

    (void)len;
    (void)x;
    place = doom->game_design.sector[doom->game_design.cur_sec].height_floor;
    place -= BAR_MIN;
    place /= BAR_DIFF;
    place *= BAR_LEN;
    place += BAR_X;
    i = 0;
    j = 0;
    while (j < 9)
    {
        while (i < 8)
        {
            pixels[0][(((y - 2 + j) * WIDTH) + (int)place - 4 + i)] = 0xff800000;
            i++;
        }
        i = 0;
        j++;
    }
}
void    draw_bar(Uint32 **pixels, int x, int y, int len)
{
    int i;
    int safe;

    i = 0;
    safe = x;
    while ((double)i / len != (double)BAR_HEIGHT)
    {
        pixels[0][((y * WIDTH) + x)] = 0xff333333;
        x++;
        if (x - len == safe)
        {
            x = safe;
            y++;
        }
        i++;
    }
}