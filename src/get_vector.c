/*
** get_vector.c for get_vector in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/src_new
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Thu May 14 22:51:47 2015 Adrien WERY
** Last update Tue Jun  9 20:42:40 2015 Nicolas Constanty
*/

#include "system.h"

t_vector3	get_normal(t_vector3 vecs, t_vector3 eye, t_best best)
{
  t_vector3	n;

  n.x = eye.x + best.k * vecs.x;
  n.y = eye.y + best.k * vecs.y;
  n.z = eye.z + best.k * vecs.z;
  if (best.obj.type == 1)
    n.y = 0;
  else if (best.obj.type == 2)
    n.y *= -0.6;
  else if (best.obj.type == 3)
    {
      n.x = 100 * best.obj.r.x;
      n.y = 100 * best.obj.r.y;
      n.z = 100 * best.obj.r.z;
    }
  rot_inv(&(n), best.obj.r);
  if (best.obj.s.x + best.obj.s.y + best.obj.s.z > 3.0)
    scale(&(n), best.obj.s);
  return (n);
}

t_vector3	get_vector(t_vector3 v, t_vector3 eye, double k)
{
  t_vector3	l;

  l.x = eye.x + k * v.x;
  l.y = eye.y + k * v.y;
  l.z = eye.z + k * v.z;
  return (l);
}

t_vector3	multi_vector(t_vector3 v, double coef)
{
  v.x *= coef;
  v.y *= coef;
  v.z *= coef;
  return (v);
}

t_vector3	gen_vector(double x, double y, double z)
{
  t_vector3	s;

  s.x = x;
  s.y = y;
  s.z = z;
  return (s);
}
