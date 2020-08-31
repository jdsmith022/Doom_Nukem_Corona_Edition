#include "../../includes/doom.h"
#include "game_editor.h"

t_sidedef	*cpy_sidedef(t_doom *doom, t_sidedef *sidedef, int *w_size)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * *w_size * 2);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < *w_size)
	{
		new[i] = sidedef[i];
		i++;
	}
	free(sidedef);
	*w_size *= 2;
	return (new);
}

void		mv_sidedef(t_sidedef **sidedef, int w_len, int id)
{
	int			i;
	t_sidedef	safe;
	t_sidedef	safe2;

	i = id;
	safe = sidedef[0][i];
	sidedef[0][i] = sidedef[0][w_len];
	i++;
	while (i < w_len)
	{
		safe2 = sidedef[0][i];
		sidedef[0][i] = safe;
		safe = safe2;
		i++;
	}
	sidedef[0][i] = safe;
}
