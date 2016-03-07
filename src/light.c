/*
** light.c for light.c in /home/wery_a/rendu/RayTracer/rtv1/v6
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Wed Mar 11 02:45:50 2015 adrien wery
** Last update Tue Jun  9 21:32:51 2015 Nicolas Constanty
*/

#include "system.h"

double		sumlight_sp(t_light *light, t_best best)
{
  short		i;
  short		pow;
  double	sum;
  double	angle;
  double	res;
  t_vector3	light_vec;

  i = -1;
  sum = 0;
  while (light[++i].name)
    {
      pow = 0;
      res = 1;
      light_vec = add_sub_vector(light[i].p, best.inter, -1);
      angle = scalaire(unitaire(best.normal), unitaire(light_vec));
      while (++pow < best.obj.sp)
	res *= angle;
      sum += res * best.rgb_sp * light[i].intensity;
    }
  return (sum / i);
}

double		sumlight(t_system *sys, t_light *light, t_best best, short dec)
{
  short		i;
  double	sum;
  double	angle;
  double	br;
  t_vector3	light_vec;

  i = -1;
  sum = 0;
  while (light[++i].name)
    {
      br = (double)((light[i].color >> 8 * (dec + 1)) & 255) / 255;
      light_vec = add_sub_vector(light[i].p, best.inter, -1);
      angle = scalaire(best.normal, unitaire(light_vec));
      sum += (angle * best.rgb * light[i].intensity *
	(1.0 - best.obj.br) + br * best.obj.br) * shadow(sys, best, light[i].p);
    }
  return (sum / i);
}

int		final_color(double rgb[3])
{
  int		color;

  color = 0;
  rgb[0] = MAX(rgb[0], 0, 1);
  rgb[1] = MAX(rgb[1], 0, 1);
  rgb[2] = MAX(rgb[2], 0, 1);
  color |= MAX_RGB(rgb[0] * 255) << 8;
  color |= MAX_RGB(rgb[1] * 255) << 16;
  color |= MAX_RGB(rgb[2] * 255) << 24;
  return (color);
}

int		init_light(t_best *best, t_vecs *new_vecs, t_vector3 eye,
			   t_vector3 cam)
{
  translate(&eye, best->obj.p, 1);
  if (best->obj.type != 3)
    {
      rot(&eye, best->obj.r);
      rot(&cam, best->obj.r);
    }
  best->normal = unitaire(get_normal(cam, eye, *best));
  best->inter = get_vector(cam, eye, best->k);
  translate(&(best->inter), best->obj.p, -1);
  if (best->obj.type != 3)
    rot(&(best->inter), best->obj.r);
  new_vecs->eye = best->inter;
  new_vecs->vector = add_sub_vector(cam,
				    multi_vector(best->normal,
						 (2 * scalaire(best->normal,
							       cam))),
				    -1);
  return (best->obj.id);
}
/*int		init_light(t_best *best, t_vecs *new_vecs, t_vector *eye,
			   t_vector *cam)
{
  translate(eye, best->obj.p, 1);
  if (best->obj.type != 3)
    {
      rot(eye, best->obj.r);
      rot(cam, best->obj.r);
    }
  best->normal = unitaire(get_normal(vecs->vector, vecs->eye, *best));
  best->inter = get_vector(vecs->vector, vecs->eye, best->k);
  translate(&(best->inter), best->obj.p, -1);
  if (best->obj.type != 3)
    rot(&(best->inter), best->obj.r);
  new_vecs->eye = best->inter;
  new_vecs->vector = add_sub_vector(vecs->vector,
				    multi_vector(best->normal,
						 (2 * scalaire(best->normal,
							       vecs->vector))),
				    -1);
  return (best->obj.id);
  }*/

int		light_color(t_system *sys, t_vector3 eye, t_vector3 cam,
			    t_best best)
{
  double	rgb[3];
  unsigned int	color;
  short		i;
  t_vecs	new_vecs;
  t_best	new_best;

  init_vecs_best(&new_vecs, &new_best);
  new_best.cam = best.cam;
  new_best.id = init_light(&best, &new_vecs, eye, cam);
  color = 0;
  if (best.obj.kr != 0.0)
    color = calc_color(sys, new_vecs.eye, new_vecs.vector, new_best).color;
  i = -1;
  while (++i < 3)
    {
      best.rgb = (double)((best.color >> 8 * (i + 1)) & 255) / 255;
      best.rgb_sp = (double)((best.obj.color_sp >> 8 * (i + 1)) & 255) / 255;
      best.rgb_re = (double)((color >> 8 * (i + 1)) & 255) / 255;
      rgb[i] = best.obj.kd * best.rgb * best.cam.ia
	+ best.obj.kd * sumlight(sys, sys->light, best, i)
	+ best.obj.ks * sumlight_sp(sys->light, best)
	+ best.obj.kr * best.rgb * best.rgb_re;
    }
  return (final_color(rgb));
}
