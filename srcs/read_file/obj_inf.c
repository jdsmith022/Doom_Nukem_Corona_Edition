#include "../../includes/doom.h"

void		add_coordinates_obj(t_sprite *sprite, int i, int safe)
{
	int	mod;

	mod = i % 5;
	if (((((mod > 1 && mod < 5) || mod == 0) && i > 5 && \
	i < sprite->amount * 5 + 6) || i == 1 || i == 2) && safe < 0)
		error("Impossible to have negative coordinates", line_num(0));
	if (i == 1)
	{
		sprite->pos.x = safe;
	}
	else if (i == 2)
	{
		sprite->pos.y = safe;
	}
	else if (mod == 2)
	{
		sprite->lines[(i - 6) / 5].start.x = safe;
	}
	else if (mod == 3)
	{
		sprite->lines[(i - 6) / 5].start.y = safe;
	}
	else if (mod == 4)
	{
		sprite->lines[(i - 6) / 5].end.x = safe;
	}
	else if (mod == 0)
	{
		sprite->lines[(i - 6) / 5].end.y = safe;
	}
}

static void	add_lines(t_sprite *sprite, int i, int safe, int obj_len)
{
	if (i == 5)
	{
		if (safe > 0)
		{
			sprite->amount = safe;
			sprite->textures = (int*)malloc(sizeof(int) * safe);
			sprite->lines = (t_line*)malloc(sizeof(t_line) * 4);
		}
		else
			error("Sprite needs a texture", line_num(0));
	}
	if (i > 5 && i < sprite->amount * 5 + 6)
	{
		if (i % 5 == 1)
		{
			if (safe >= 0 && safe < obj_len)
			{
				sprite->textures[(i - 6) / 5] = safe;
			}
			else
				error("Sprite texture is not available", line_num(0));
		}
		add_coordinates_obj(sprite, i, safe);
	}
}

static void	add_inf_to_obj(t_sprite *sprite, int i, int safe, int obj_len)
{
	if (i == 0)
	{
		sprite->index = safe;
	}
	else if (i == 1 || i == 2)
		add_coordinates_obj(sprite, i, safe);
	else if (i == 3)
	{
		sprite->action = safe;
	}
	else if (i == 4)
	{
		sprite->size = safe;
	}
	else if (i >= 5)
		add_lines(sprite, i, safe, obj_len);
}

t_sprite	object_inf(int fd, int sector, int obj_len)
{
	int			i;
	char		*line;
	t_sprite	sprite;
	int			safe;

	i = 0;
	(void)sector; //why is this here
	sprite.amount = 0; //what is this?
	// printf("obj_inf 2\n");
	while (i < 6 + /*sprite.amount*/ 4 * 5) //added 4 in stead of sprite amount, because every sprite should have 4 lines
	{
		safe = get_line(&line, fd, "object informations does not exist", 1);
		// printf("before add inf to obj 1\n");
		add_inf_to_obj(&sprite, i, safe, obj_len);
		sprite.sector = sector;
		// printf("after add inf to obj 1\n");
		free(line);
		i++;
	}
	return (sprite);
}
