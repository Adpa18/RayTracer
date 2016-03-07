/*
** system.h for system in /home/wery_a/rendu/minilibX
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Tue Nov 25 18:16:43 2014 adrien wery
** Last update Tue Jun  9 19:03:31 2015 consta_n
*/

#ifndef SYSTEM_H_
# define SYSTEM_H_

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <pthread.h>
# include <limits.h>
# include "struct.h"
# include "functs.h"

# define BUFF_SIZE (1)
# define END_KEY (65307)
# define ZERO (0.00000001)
# define DISTANCE (1000)
# define AA (16)
# define AA_lEN (4)
# define DOF_STRENGH (64)
# define MAX(x, min, max) ((x) > (max)) ? (max) : ((x) < (min)) ? (min) : (x)
# define MAX_RGB(x) ((x) > (255)) ? (255) : (int)(x)
# define RADIAN(r) (r) * (M_PI) / (180.0)
# define cpt register unsigned int
# define uint unsigned int

#endif /* !SYSTEM_H_ */
