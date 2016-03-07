/*
** multi.c for  in /home/consta_n/Documents/tests/MUL_2014_rtracer/NICO/v14
**
** Made by consta_n
** Login   <consta_n@epitech.net>
**
** Started on  Fri Jun  5 22:51:15 2015 consta_n
** Last update Wed Jun 10 01:26:19 2015 Nicolas Constanty
*/

#include "system.h"

int			count;

char			main_check(int nb_thread, t_system **multi_th, uint wh)
{
  int			i;
  uint			min;
  int			id;
  int			j;

  i = -1;
  count = 0;
  while (42)
    {
      i = -1;
      count = 0;
      while (++i < nb_thread)
	{
	  if (!multi_th[i]->is_active)
	    ++count;
	  if (!multi_th[i]->is_active && !multi_th[i]->can_end)
	    {
	      printf("Search thread\n");
	      min = 0xFFFFFFFF;
	      j = -1;
	      id = 0;
	      while (++j < nb_thread)
		if (min > (multi_th[j]->pos_thread - multi_th[j]->limit))
		  {
		    min = multi_th[j]->pos_thread;
		    id = j;
		  }
	      if (multi_th[id]->is_active)
		{
		  printf("Find thread\n");
		  --count;
		  multi_th[i]->is_active = 1;
		  multi_th[i]->xy = multi_th[id]->xy;
		  multi_th[id]->limit = ((wh / nb_thread)
					 - multi_th[id]->pos_thread) / 2;
		  multi_th[i]->pos_thread = multi_th[id]->limit
		    + multi_th[id]->pos_thread;
		  printf("Help thread ready\n");
		  if (multi_th[id]->is_active)
		    {
		      printf("Rescue thread %d\n", id + 1);
		      multi_th[i]->can_end = 2;
		    }
		  else
		    ++count;
		}
	      else
		{
		  printf("No thread found\nClose thread %d\n", i + 1);
		  multi_th[i]->can_end = 1;
		}
	    }
     	  else if (!multi_th[i]->is_active && multi_th[i]->can_end != 1)
	    {
	      printf("Close thread %d\n", i + 1);
	      multi_th[i]->can_end = 1;
	    }
	}
      if (count == nb_thread)
	return (0);
      usleep(20);
    }
  return (0);
}

 /*if (multi_th[1] && !multi_th[0]->is_active
	  && multi_th[1]->is_active && !multi_th[0]->can_end)
	{
	  --count;
	  multi_th[0]->is_active = 1;
	  multi_th[0]->xy = multi_th[1]->xy;
	  multi_th[1]->limit = ((wh / nb_thread) - multi_th[1]->pos_thread) / 2;
	  multi_th[0]->pos_thread = multi_th[1]->limit
	    + multi_th[1]->pos_thread;
	  multi_th[0]->can_end = 2;
	}*/

  //else if (multi_th[1] && !multi_th[1]->is_active)
  //multi_th[1]->can_end = 1;

char			rand_mode(t_system **multi_th, t_thread *thread,
				  int nb_thread)
{
  int			i;
  pthread_attr_t	attr;
  int			**xy;
  uint			wh;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  wh = multi_th[0]->cam.width * multi_th[0]->cam.height;
  if (!(xy = malloc(sizeof(int *) * nb_thread)))
    return (1);
  i = -1;
  while (++i < nb_thread)
    if (!(xy[i] = malloc(sizeof(int) * wh / nb_thread + 1)))
      return (1);
  if (gen_xy(xy, wh, multi_th[0]->cam.mode, nb_thread))
    return (1);
  i = -1;
  while (++i < nb_thread)
    {
      multi_th[i]->xy = xy[i];
      create_thread(multi_th, &attr, i, thread);
    }
  main_check(nb_thread, multi_th, wh);
  return (0);
}
