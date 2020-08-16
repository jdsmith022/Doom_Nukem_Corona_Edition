#include "../includes/doom.h"
#include "sprites.h"
#include "game_editor.h"

t_sidedef	*cpy_object(t_doom *doom, t_sprite *object, int *o_size)
{
	t_sprite	*new;
	int			i;

	new = (t_sprite*)malloc(sizeof(t_sprite) * *o_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < *o_size)
	{
		new[i] = object[i];
		i++;
	}
	free(object);
	*o_size *= 2;
	return (new);
}

void    add_object_to_array(int x, int y, int doom)
{
    
}


void    add_object(t_doom *doom, int x, int y)
{
    if (OBJECT == NULL)
	{
		OBJECT = (t_sidedef*)malloc(sizeof(t_sidedef) * 2);
		OBJECT.w_size = 2;
		OBJECT.w_len = 0;
		start = 0;
		id = 0;
	}
    if (OBJECT.w_size < OBJECT.w_len + 1)
			OBJECT = cpy_object(doom, object, &OBJECT.w_size);
    add_object_to_array(x, y, doom);
}