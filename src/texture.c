/*
** textur.c for textur in /home/wilmot_g/.ssh/MUL_2014_rtracer/G/v14
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Fri Jun  5 21:44:57 2015 guillaume wilmot
** Last update Tue Jun  9 21:45:16 2015 Nicolas Constanty
*/

#include "system.h"

void		load_texture(t_system *sys)
{
  int		i;

  i = -1;
  while (sys->obj[++i].type != -2)
    {
      if (sys->obj[i].tex.file)
	{
	  my_putstr("Loading ");
	  my_putstr(sys->obj[i].tex.file);
	  my_putstr("\n");
	  sys->obj[i].tex.texture.img =
	    mlx_xpm_file_to_image(sys->mlx,
				  sys->obj[i].tex.file,
				  &(sys->obj[i].tex.w),
				  &(sys->obj[i].tex.h));
	  sys->obj[i].tex.texture.data =
	    mlx_get_data_addr(sys->obj[i].tex.texture.img,
			      &(sys->obj[i].tex.texture.bpp),
			      &(sys->obj[i].tex.texture.sizeline),
			      &(sys->obj[i].tex.texture.endian));
	}
      else
	sys->obj[i].tex.texture.data = NULL;
    }
}

int		damier(t_vector3 eye, t_vector3 cam, t_best best)
{
  double	x;
  double	z;

  translate(&eye, best.obj.p, 1);
  rot_inv(&eye, best.obj.r);
  rot_inv(&cam, best.obj.r);
  scale(&cam, best.obj.s);
  best.inter = get_vector(cam, eye, best.k);
  translate(&(best.inter), best.obj.p, -1);
  if (best.inter.x < 0)
    best.inter.x -= 40;
  if (best.inter.z < 0)
    best.inter.z -= 40;
  x = (int)(abs(best.inter.x) % 80);
  z = (int)(abs(best.inter.z) % 80);
  if ((z <= 40 && x <= 40) || (z > 40 && x > 40))
    return (0xFFFFFF00);
  else
    return (0x00000000);
  return (best.color);
}

int		texture(t_vector3 eye, t_vector3 cam, t_best best)
{
  unsigned int	color;
  int		c;
  double	v;
  double	u;
  double	pos;

  translate(&eye, best.obj.p, 1);
  rot_inv(&eye, best.obj.r);
  rot_inv(&cam, best.obj.r);
  scale(&(cam), best.obj.s);
  best.normal = unitaire(get_normal(cam, eye, best));
  u = (int)(best.obj.tex.w * (0.5 + atan2(best.normal.z, best.normal.x)
			      / (2 * M_PI)));
  v = (int)(best.obj.tex.h * (0.5 - asin(best.normal.y) / M_PI));
  pos = 4 * u + 4 * v * best.obj.tex.w;
  c = (int)pos;
  color = 0;
  color += best.obj.tex.texture.data[c++] << 8;
  color += best.obj.tex.texture.data[c++] << 16;
  color += best.obj.tex.texture.data[c++] << 24;
  return (color);
}
