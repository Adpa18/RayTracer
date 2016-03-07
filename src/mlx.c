/*
** mlx.c for mlx in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/src_new
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Tue May 12 14:17:39 2015 Adrien WERY
** Last update Tue Jun  9 19:44:42 2015 Nicolas Constanty
*/

#include "system.h"

int	init_mlx(t_system *sys)
{
  if ((sys->mlx = mlx_init()) == NULL)
    return (my_error("Could not initiate MiniLibX", -1));
  sys->win = mlx_new_window(sys->mlx,sys->cam.width,
			    sys->cam.height, "RayTracer");
  sys->image.img = mlx_new_image(sys->mlx, sys->cam.width,
				 sys->cam.height);
  sys->image.data = mlx_get_data_addr(sys->image.img,
				      &(sys->image.bpp),
				      &(sys->image.sizeline),
				      &(sys->image.endian));
  mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
  return (0);
}

void	my_pixel_put_to_image(char *data, unsigned int pos, int color)
{
  if (data[pos] != ((color >> 8) & 255))
    data[pos] = (color >> 8) & 255;
  ++pos;
  if (data[pos] != ((color >> 16) & 255))
    data[pos] = (color >> 16) & 255;
  ++pos;
  if (data[pos] != ((color >> 24) & 255))
    data[pos] = (color >> 24) & 255;
}

int	gere_key(int keycode, t_system *sys)
{
  if (keycode == END_KEY)
    {
      my_putstr("This is the END !!!\n");
      exit(free_conf(sys, EXIT_SUCCESS));
    }
  return (0);
}

int	expose(t_system *sys)
{
  mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
  return (0);
}

void	hooks(t_system *sys)
{
  mlx_key_hook(sys->win, &gere_key, sys);
  mlx_expose_hook(sys->win, &expose, sys);
  mlx_loop(sys->mlx);
}
