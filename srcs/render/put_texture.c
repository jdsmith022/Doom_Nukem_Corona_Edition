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
	char	r;
	char	g;
	char	b;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	r = texture[pixel_dex];
	g = texture[pixel_dex + 1];
	b = texture[pixel_dex + 2];
	add_saturation(&r, &g, &b, doom->distance);
	if (texture[pixel_dex] == (char)255 && texture[pixel_dex + 1] == (char)255 &&\
		texture[pixel_dex + 2] == (char)255 && doom->lib.sidedef[doom->i_sidedef].action == 2)
	{
			;
	}
	else
	{
		pixels[index] = r;
		index++;
		pixels[index] = g;
		index++;
		pixels[index] = b;
	}
}
