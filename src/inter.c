/*
** inter.c for inter in /home/wery_a/rendu/RayTracer/rtv1/v1
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Wed Feb  4 23:29:38 2015 adrien wery
** Last update Tue Jun  9 21:22:24 2015 Nicolas Constanty
*/

#include "system.h"

void		inter_sphere(t_vector3 eye, t_vector3 cam,
			     t_obj obj, t_best *best)
{
  double	a[4];

  translate(&eye, obj.p, 1);
  rot_inv(&eye, obj.r);
  rot_inv(&cam, obj.r);
  if (obj.s.x + obj.s.y + obj.s.z > 3.0)
    scale(&cam, obj.s);
  a[0] = cam.x * cam.x
    + cam.y * cam.y
    + cam.z * cam.z;
  a[1] = 2.0 * (eye.x * cam.x + eye.y * cam.y
		+ eye.z * cam.z);
  a[2] = eye.x * eye.x + eye.y * eye.y
    + eye.z * eye.z - obj.ra * obj.ra;
  a[3] = a[1] * a[1] - 4.0 * a[0] * a[2];
  if (a[3] >= 0)
    delta(&eye, &cam, a, obj, best);
}

void		inter_cylinder(t_vector3 eye, t_vector3 cam,
			       t_obj obj, t_best *best)
{
  double	a[4];

  translate(&eye, obj.p, 1);
  rot_inv(&eye, obj.r);
  rot_inv(&cam, obj.r);
  if (obj.s.x > 1 && obj.s.y > 1 && obj.s.z > 1)
    scale(&cam, obj.s);
  a[0] = pow(cam.x, 2) + pow(cam.z, 2);
  a[1] = 2.0 * (eye.x * cam.x + eye.z * cam.z);
  a[2] = pow(eye.x, 2) + pow(eye.z, 2) - pow(obj.ra, 2);
  a[3] = a[1] * a[1] - 4 * a[0] * a[2];
  if (a[3] >= 0)
    delta(&eye, &cam, a, obj, best);
}

void		inter_cone(t_vector3 eye, t_vector3 cam,
			   t_obj obj, t_best *best)
{
  double	a[4];

  translate(&eye, obj.p, 1);
  rot_inv(&eye, obj.r);
  rot_inv(&cam, obj.r);
  if (obj.s.x > 1 && obj.s.y > 1 && obj.s.z > 1)
    scale(&cam, obj.s);
  a[0] = pow(cam.x, 2) + pow(cam.z, 2) -
    (pow(cam.y, 2) / pow(tan(obj.ra), 2));
  a[1] = 2.0 * (eye.x * cam.x + eye.z * cam.z -
		eye.y * cam.y / pow(tan(obj.ra), 2));
  a[2] = pow(eye.x, 2) + pow(eye.z, 2)
    - pow(eye.y, 2) / pow(tan(obj.ra), 2);
  a[3] = a[1] * a[1] - 4 * a[0] * a[2];
  if (a[3] >= 0)
    delta(&eye, &cam, a, obj, best);
}

void		inter_plan(t_vector3 eye, t_vector3 cam,
			   t_obj obj, t_best *best)
{
  double	k;
  double       	div;

  translate(&eye, obj.p, 1);
  div = cam.x * obj.r.x + cam.y * obj.r.y
    + cam.z * obj.r.z;
  k = 0;
  if (div != 0)
    k = -((eye.x * obj.r.x + eye.y
	   * obj.r.y + eye.z * obj.r.z)
	  / div);
  if (k < best->k && k > ZERO && check_limit(&eye, &cam, obj, k) == 1)
    {
      best->k = k;
      best->color = obj.color;
      best->obj = obj;
    }
}
