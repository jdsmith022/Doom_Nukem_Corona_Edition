#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/textures.h"

static bool			is_valid_type(uint8_t type, t_item *tex_types, int len)
{
	int i;

	if (type == 0)
		return (false);
	i = 0;
	while ((i + 1) < len)
	{
		if (tex_types[i].type == type)
			return (false);
		i++;
	}
	return (true);
}

static void			save_groceries_in_level(t_doom *doom)
{
	doom->groceries->groceries_in_level =
		(t_item*)ft_memalloc(sizeof(t_item)\
			* doom->groceries->num_of_groceries);
	if (!doom->groceries->groceries_in_level)
		doom_exit_failure(doom, "error: saving groceries in editor");
	ft_memcpy(
		doom->groceries->groceries_in_level,
		groceries, sizeof(t_item) * doom->groceries->num_of_groceries);
}

void				set_groceries_in_level(t_doom *doom, t_item *t_types)
{
	int				i;
	int				j;
	int				len;
	t_item			groceries[GROC_TYPES];

	i = 0;
	j = 0;
	len = doom->game_design.sd_len;
	doom->groceries = (t_groceries*)ft_memalloc(sizeof(t_groceries));
	if (!doom->groceries)
		doom_exit_failure(doom, "error: saving groceries in editor");
	doom->groceries->num_of_groceries = 0;
	while (i < len)
	{
		if (is_valid_type(t_types[i].type, &t_types[i], len - i))
		{
			doom->groceries->num_of_groceries++;
			groceries[j] = t_types[i];
			j++;
		}
		i++;
	}
	save_groceries_in_level(doom);
}
