#include "../../includes/doom.h"

void		add_saturation(char *r, char *g, char *b, double light)
{
	double R;
	double G;
	double B;

	R = (double)*r;
	G = (double)*g;
	B = (double)*b;
	if (R < 0.0)
		R += 255.0;
	if (G < 0.0)
		G += 255.0;
	if (B < 0.0)
		B += 255.0;
	 R *= light;
	 G *= light;
	 B *= light;
	if (R < 0.0)
		R = 0;
	if (G < 0.0)
		G = 0;
	if (B < 0.0)
		B = 0;
	if (R > 255.0)
		R = 255.0;
	if (G > 255.0)
		G = 255.0;
	if (B > 255.0)
		B = 255.0;
	*r = R;
	*g = G;
	*b = B;
}

void		put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;
	char	R;
	char	G;
	char	B;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	R = texture[pixel_dex];
	G = texture[pixel_dex + 1];
	B = texture[pixel_dex + 2];
	add_saturation(&R, &G, &B, doom->distance);
	pixels[index] = R;
	index++;
	pixels[index] = G;
	index++;
	pixels[index] = B;
}
