/*
** delta.c for delta in /home/wery_a/rendu/RayTracer/rtv1/v1
** 
** Made by adrien wery
** Login   <wery_a@epitech.net>
** 
** Started on  Wed Feb  4 23:24:59 2015 adrien wery
** Last update Tue Jun  9 22:20:24 2015 Nicolas Constanty
*/

#include "system.h"

int		check_limit(const t_vector3 *eye, const t_vector3 *cam,
			    t_obj obj, double x)
{
  if (obj.min_x == -1)
    obj.min_x = -1000;
  if (obj.max_x == -1)
    obj.max_x = 1000;
  if (obj.min_y == -1)
    obj.min_y = -1000;
  if (obj.max_y == -1)
    obj.max_y = 1000;
  if (obj.min_z == -1)
    obj.min_z = -1000;
  if (obj.max_z == -1)
    obj.max_z = 1000;
  if (eye->x + x * cam->x > obj.min_x &&
      eye->x + x * cam->x < obj.max_x &&
      eye->y + x * cam->y > obj.min_y &&
      eye->y + x * cam->y < obj.max_y &&
      eye->z + x * cam->z > obj.min_z &&
      eye->z + x * cam->z < obj.max_z)
    return (1);
  return (0);
}

void		delta(const t_vector3 *eye, const t_vector3 *cam,
		      double *a, t_obj obj, t_best *best)
{
  double        x1;
  double        x2;

  x1 = (-a[1] - sqrt(a[3])) / (2 * a[0]);
  x2 = (-a[1] + sqrt(a[3])) / (2 * a[0]);
  if (x1 > ZERO && (x1 < x2 || x2 < ZERO) && x1 < best->k &&
      check_limit(eye, cam, obj, x1) == 1)
    {
      best->k = x1;
      best->color = obj.color;
      best->obj = obj;
    }
  if (x2 > ZERO && x2 < best->k && check_limit(eye, cam, obj, x2) == 1)
    {
      best->k = x2;
      best->color = obj.color_in;
      best->obj = obj;
    }
}
