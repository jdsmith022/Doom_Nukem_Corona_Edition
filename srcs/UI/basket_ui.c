#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

// void		put_textures(int x, int y, int index, t_doom *doom)
// void		draw_sprite(int x, int y, uint8_t index, t_doom *doom)

void	draw_basket_ui(t_doom *doom, t_groceries groceries, t_lib sprites)
{
	t_list *temp;
	t_item *item;

	temp = groceries.basket;
	item = (t_item *)temp->content;
	// draw texture
	draw_texture(sprites.obj_lib[item->sprite_index], doom, 50, 50);
	// item.sprite_index
	return ;
}

void	draw_shopping_ui(t_doom *doom)
{
	// // Banaan 1, apple 2
	// int i = 0;
	// // t_item *item;
	// // item = (t_item *)doom->groceries.basket->content;
	// while (i < doom->lib.len_tex_lib)
	// {
	// 	if (*((uint8_t *)doom->lib.tex_lib[i]->userdata) == 8)
	// 		put_textures(50, 50, i, doom);
	// 	i++;
	// }
	// return ;
}
