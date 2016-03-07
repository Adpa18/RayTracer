/*
** shading.c for shading in /home/wilmot_g/RAYTRACER/MUL_2014_rtracer/New_light
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu May 28 15:53:07 2015 guillaume wilmot
** Last update Sun Jun  7 19:22:14 2015 guillaume wilmot
*/

#include "system.h"

unsigned int	get_shade(unsigned int color)
{
  if (color <= (15 * 255 / 100))
    color = (7 * 255 / 100);
  if (color >= (15 * 255 / 100) && color <= (35 * 255 / 100))
    color = (25 * 255 / 100);
  if (color >= (35 * 255 / 100) && color <= (60 * 255 / 100))
    color = (47 * 255 / 100);
  if (color >= (60 * 255 / 100) && color <= (100 * 255 / 100))
    color = (80 * 255 / 100);
  return (color);
}

unsigned int	shade_this(unsigned int color)
{
  unsigned int	rgb[3];
  unsigned int	final;

  rgb[0] = (color >> 8) & 255;
  rgb[1] = (color >> 16) & 255;
  rgb[2] = (color >> 24) & 255;
  rgb[0] = get_shade(rgb[0]);
  rgb[1] = get_shade(rgb[1]);
  rgb[2] = get_shade(rgb[2]);
  final = 0;
  final |= rgb[0] << 8;
  final |= rgb[1] << 16;
  final |= rgb[2] << 24;
  return (final);
}

void		init_shading(int *pos, short *xy, int *per)
{
  *pos = 0;
  *xy = -1;
  *per = 0;
  loading(2, 0, "Generate Shading ...");
}

void		shading(t_system *sys)
{
  short		xy[2];
  int		pos;
  int		per;
  unsigned int	color;

  init_shading(&pos, & xy[0], &per);
  while (++xy[0] < sys->cam.height)
    {
      xy[1] = -1;
      while (++xy[1] < sys->cam.width)
        {
          pos = xy[0] * sys->image.sizeline + xy[1] * sys->image.bpp / 8;
	  color = sys->color[pos / 4];
	  if (need_aa_outlines(sys, xy[0], xy[1], sys->cam.shading_border) == 0)
	    color = sys->cam.border_color;
	  else
	    color = shade_this(color);
	  sys->color[xy[0] * sys->cam.width + xy[1]] = color;
	  my_pixel_put_to_image(sys->image.data, pos, color);
        }
      if (pos * 100 / (sys->cam.height * sys->image.sizeline) > per)
        loading(per += 2, 1, "");
      mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
    }
  anti_aliasing(sys, 0);
}
