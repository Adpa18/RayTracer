/*
** main.c for main in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/src_new
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Tue May 12 18:48:03 2015 Adrien WERY
** Last update Tue Jun  9 21:41:05 2015 Nicolas Constanty
*/

#include "system.h"

t_best		calc_color(t_system *sys, t_vector3 eye, t_vector3 cam,
			   t_best best)
{
  short		i;

  i = -1;
  best.color = 0x00000000;
  best.k = 10000000000;
  while (sys->obj[++i].type != -2)
    {
      if (sys->obj[i].id == best.id);
      else
      	sys->fptr[(int)sys->obj[i].type](eye, cam,
					 sys->obj[i], &(best));
    }
  if (best.k != 10000000000)
    {
      if (best.obj.tex.texture.data && best.obj.type == 0)
      	best.color = texture(eye, cam, best);
      else if (best.obj.damier && best.obj.type == 3)
      	best.color = damier(eye, cam, best);
      best.color = light_color(sys, eye, cam, best);
    }
  return (best);
}

void		loading(unsigned short per, unsigned short mode, char *txt)
{
  if (mode == 0)
    {
      my_putstr("\e[00;34m");
      my_putstr(txt);
      my_putstr("\n\e[00;00m");
      per = 2;
      mode = -1;
      while (++mode != 100 / per)
	write(1, " ", 1);
      my_putstr(" \e[00;35m]\r[\e[00;00m");
    }
  else
    {
      if (per > 33 && per <= 66)
        my_putstr("\e[00;33m=\e[00;00m");
      else if (per > 66)
        my_putstr("\e[00;32m=\e[00;00m");
      else
        my_putstr("\e[00;31m=\e[00;00m");
    }
}

void		effects(t_system *sys)
{
  write(1, "\n", 1);
  if (sys->cam.shading_border > 0)
    shading(sys);
  if (sys->cam.dof > 0)
    dof(sys);
  if (sys->cam.b_a_w == 1)
    black_and_white(sys);
  if (export(sys) == -1)
    my_error("Could not export the image", 0);
}

int		main(int argc, char **argv)
{
  t_system	sys;
  t_system	**multi_th;

  XInitThreads();
  if (argc < 2)
    {
      if (parsing("scenes/scene.rt", &sys) == -1)
  	return (-1);
      init_mlx(&sys);
      if (!(multi_th = set_multi_struct(&sys, "scenes/scene.rt")))
      	return (1);
    }
  else
    {
      if (parsing(argv[1], &sys) == -1)
	return (-1);
      init_mlx(&sys);
      if (!(multi_th = set_multi_struct(&sys, argv[1])))
      	return (1);
    }
  remp_img(multi_th);
  effects(multi_th[0]);
  hooks(multi_th[0]);
  return (free_conf(&sys, 0));
}
