/*
** dof.c for dof in /home/wilmot_g/RAYTRACER/MUL_2014_rtracer/aa
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Jun  1 14:44:51 2015 guillaume wilmot
** Last update Sun Jun  7 18:48:12 2015 maxime mollonguet
*/

#include "system.h"

int			is_dof(short x, short y, t_system *sys)
{
  if (sys->outlines[y * sys->cam.width + x] != sys->cam.dof)
    return (1);
  return (0);
}

int			blur(t_system *sys, short y, short x,
                                      unsigned int *pixels)
{
  t_blur		blur;

  blur.i = 0;
  blur.y1 = (y - DOF_STRENGH / 8 < 0) ? 0 : y;
  blur.pos1 = y * sys->image.sizeline + x * sys->image.bpp / 8;
  while (blur.i < DOF_STRENGH)
    pixels[blur.i++] = sys->color[blur.pos1 / 4];
  blur.i = 0;
  while (blur.i < DOF_STRENGH && blur.y1 < y
	 + (DOF_STRENGH / 8) && blur.y1 < sys->cam.height)
    {
      blur.x1 = (x - DOF_STRENGH / 8) < 0 ? 0 : x - (DOF_STRENGH / 8);
      while (blur.i < DOF_STRENGH && blur.x1 < x
	     + (DOF_STRENGH / 8) && blur.x1 < sys->cam.width)
        {
	  blur.pos2 = blur.y1 *
	    sys->image.sizeline + blur.x1 * sys->image.bpp / 8;
	  pixels[blur.i] = is_dof(blur.x1, blur.y1, sys) ?
	    sys->color[blur.pos2 / 4] : sys->color[blur.pos1 / 4];
	  blur.x1 = ((blur.i++) != -42) ? blur.x1 + 1 : blur.x1 + 1;
        }
      ++(blur.y1);
    }
  return (color_interpolation(pixels, DOF_STRENGH));
}

int			init_dof(unsigned int **pixels, unsigned short *per,
				 short *coord)
{
  if ((*pixels = malloc(sizeof(int) * DOF_STRENGH)) == NULL)
    return (-1);
  *per = 0;
  loading(2, 0, "Generate DOF ...");
  *coord = -1;
  return (0);
}

void			dof(t_system *sys)
{
  short			coord[2];
  int			pos;
  unsigned short	per;
  unsigned int		*pixels;

  pos = 0;
  if ((init_dof(&pixels, &per, &coord[1])) == -1)
    return;
  while (++coord[1] < sys->cam.height)
    {
      coord[0] = -1;
      while (++coord[0] < sys->cam.width)
        {
          pos = coord[1] * sys->image.sizeline + coord[0] * sys->image.bpp / 8;
          if (is_dof(coord[0], coord[1], sys))
	    my_pixel_put_to_image(sys->image.data, pos, blur(sys, coord[1],
							     coord[0], pixels));
        }
      if (pos * 100 / (sys->cam.height * sys->image.sizeline) > per)
        loading(per += 2, 1, "");
      mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
    }
  free(pixels);
  write(1, "\n", 1);
}
