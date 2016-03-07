/*
** inter.c for inter in /home/wery_a/rendu/RayTracer/rtv1/v1
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Wed Feb  4 23:29:38 2015 adrien wery
** Last update Tue Jun  9 21:19:34 2015 Nicolas Constanty
*/

#include "system.h"

void		check_light_inter(t_system *sys, t_best best,
				  t_vecs vecs, short *tru)
{
  cpt		i;

  i = 0;
  while (sys->obj[i].type != -2)
    {
      if (sys->obj[i].id == best.obj.id);
      else if (sys->obj[i].type >= 0 && sys->obj[i].type < 4)
	{
	  if (sys->obj[i].type == 3)
	    translate(&(vecs.eye), sys->obj[i].p, 1);
	  sys->fptr[(int)sys->obj[i].type](vecs.eye, vecs.vector,
					   sys->obj[i], &(best));
	}
      if (best.k != 10000000000 && best.k < 1)
	{
	  ++(*tru);
	  break;
	}
      ++i;
    }
}

void		init_mat(t_system *sys)
{
  double	inc;
  double	mx;
  double	my;
  double	mz;
  int		i;
  short		mssp;

  i = -1;
  mssp = sys->cam.pass_mssp;
  inc = sys->cam.range_mssp / (mssp + 1.0);
  mx = -inc;
  my = inc;
  mz = -inc;
  while (++i < mssp)
    {
      sys->mxyz[0][i] = mx;
      sys->mxyz[1][i] = my;
      sys->mxyz[2][i] = my;
      mx += inc;
      my -= inc;
      mz += inc;
    }
}

void		set_vecs_sampling(t_system *sys, t_best best, t_vecs *vecs,
				  t_vector3 light, short *tru)
{
  short		c[3];
  short		mssp;

  vecs->eye = gen_vector(best.inter.x, best.inter.y, best.inter.z);
  check_light_inter(sys, best, *vecs, tru);
  if (!tru)
    return;
  *tru = 0;
  mssp = 1 + 2 * best.cam.pass_mssp;
  /* init_mat(sys, best, 1 + 2 * best.cam.pass_mssp); */
  c[2] = -1;
  while (++c[2] < mssp)
    {
      c[1] = -1;
      while (++c[1] < mssp)
	{
	  c[0] = -1;
	  while (++c[0] < mssp)
	    {
	      vecs->eye.x = best.inter.x + sys->mxyz[0][c[0]];
	      vecs->eye.y = best.inter.y + sys->mxyz[1][c[1]];
	      vecs->eye.z = best.inter.z + sys->mxyz[2][c[2]];
	      vecs->vector = add_sub_vector(light, vecs->eye, -1);
	      check_light_inter(sys, best, *vecs, tru);
	    }
	}
    }
}

double		shadow(t_system *sys, t_best best, t_vector3 light)
{
  t_vecs	vecs;
  short		tru;
  double	res;
  short		ssp;

  best.k = 10000000000;
  vecs.eye = best.inter;
  tru = 0;
  srand((unsigned)time(NULL));
  ssp = pow(1 + 2 * best.cam.pass_mssp, 3);
  set_vecs_sampling(sys, best, &vecs, light, &tru);
  res = 1 - ((double)tru / ssp);
  if (res < 0)
    return (0);
  return (res);
}
