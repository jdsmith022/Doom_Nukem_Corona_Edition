#include "../../includes/doom.h"

double		cmin(double a, double b, double c)
{
	if (a >= b && c >= b)
		return (b);
	if (b >= a && c >= a)
		return (a);
	else
		return (c);
}

double		cmax(double a, double b, double c)
{
	if (a <= b && c <= b)
		return (b);
	if (b <= a && c <= a)
		return (a);
	else
		return (c);
}

static void	add_light(t_rgb_d *sat, double light)
{
	sat->r *= light;
	sat->g *= light;
	sat->b *= light;
	if (sat->r < 0.0)
		sat->r = 0;
	if (sat->r > 255.0)
		sat->r = 255.0;
	if (sat->g < 0.0)
		sat->g = 0;
	if (sat->g > 255.0)
		sat->g = 255.0;
	if (sat->b < 0.0)
		sat->b = 0;
	if (sat->b > 255.0)
		sat->b = 255.0;
}

void		add_saturation(char *r, char *g, char *b, double light)
{
	t_rgb_d sat;

	sat.r = (double)*r;
	sat.g = (double)*g;
	sat.b = (double)*b;
	if (sat.r < 0.0)
		sat.r += 255.0;
	if (sat.g < 0.0)
		sat.g += 255.0;
	if (sat.b < 0.0)
		sat.b += 255.0;
	add_light(&sat, light);
	*r = sat.r;
	*g = sat.g;
	*b = sat.b;
}

void		put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;
	char	r;
	char	g;
	char	b;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	r = texture[pixel_dex];
	g = texture[pixel_dex + 1];
	b = texture[pixel_dex + 2];
	add_saturation(&r, &g, &b, doom->distance);
	pixels[index] = r;
	index++;
	pixels[index] = g;
	index++;
	pixels[index] = b;
}
