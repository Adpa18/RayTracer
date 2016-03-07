/*
** black_and_white.c for black_and_white.c in /home/wilmot_g/.ssh/MUL_2014_rtracer/v15
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Sun Jun  7 14:54:53 2015 guillaume wilmot
** Last update Sun Jun  7 22:10:10 2015 Adrien WERY
*/

#include "system.h"

int		baw(int color)
{
  double	c[3];
  int		comp;
  int		new_color;

  c[0] = (double)((color >> 8) & 255);
  c[1] = (double)((color >> 16) & 255);
  c[2] = (double)((color >> 24) & 255);
  comp = c[0] / 3 + c[1] / 3 + c[2] / 3;
  new_color = 0;
  new_color |= comp << 8;
  new_color |= comp << 16;
  new_color |= comp << 24;
  return (new_color);
}

void		black_and_white(t_system *sys)
{
  short		x;
  short		y;
  short		per;
  int		pos;

  y = -1;
  per = 0;
  pos = 0;
  loading(2, 0, "Black and White effect ...");
  while (y++ < sys->cam.height)
    {
      x = -1;
      while (++x < sys->cam.width)
	{
	  pos = y * sys->image.sizeline + x * sys->image.bpp / 8;
	  my_pixel_put_to_image(sys->image.data, pos, baw(sys->color[pos / 4]));
	}
      if (pos * 100 / (sys->cam.height * sys->image.sizeline) > per)
        loading(per += 2, 1, "");
      mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
    }
  write(1, "\n", 1);
}
