
#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

static void		print_missing_groceries(t_doom *doom)
{
	char		*score;
	t_item		*info;
	size_t		index;

	index = 0;
	info = doom->groceries->info.groceries_to_display;
	info->position.y = HEIGHT - 200;
	info->position.x = WIDTH / SHOPPING_LIST_L - 25;
	while (index < SHOPPING_LIST_L)
	{
		info->position.x += 100;
		if (info[index].amount != 0)
		{
			draw_img(info[index].sprite, doom, info->position);
			draw_grocery_amount(doom, \
				info->position, ft_itoa(info[index].amount));
		}
		index++;
	}
}

void			menu_print_loop(t_doom *doom)
{
	doom->hud_display = FALSE;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(doom->cursor);
	mouse_settings(doom);
	print_background(doom, 0x00002E);
	if (doom->groceries->info.won == FALSE && \
	doom->menu->state == finished)
		print_missing_groceries(doom);
	font_to_screen(doom);
	SDL_UpdateWindowSurface(doom->window);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}
