/*
** get.c for get in /home/wery_a/rendu/RayTracer/rtv1/v5
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Fri Feb 27 16:53:02 2015 adrien wery
** Last update Sun Jun  7 19:15:15 2015 guillaume wilmot
*/

#include "system.h"

long		my_getnbr_base(char *s, char *base)
{
  long		nb;
  short		i;
  short		n;
  short		p;
  short		len;

  len = my_strlen(base);
  i = my_strlen(s);
  p = 0;
  nb = 0;
  while (--i > -1)
    {
      if (s[i] == '-')
        return (-1 * nb);
      n = -1;
      while (s[i] != base[++n] && base[n] != '\0');
      if (base[n] == '\0' || n > len)
        n = 0;
      nb += n * pow(len, p++);
    }
  return (nb);
}

short		float_pos(char *s)
{
  short		i;

  i = -1;
  while (s[++i])
    if (s[i] == '.')
      return (i);
  return (-1);
}

double		my_getnbr_float(char *s)
{
  double	nb;
  short		i;
  short		pos;
  short		p;

  nb = 0;
  pos = float_pos(s);
  if (pos == -1)
    return (my_getnbr_base(s, "0123456789"));
  i = pos;
  p = 0;
  while (s[++pos])
    {
      if (s[pos] > 47 && s[pos] < 58)
        nb += (s[pos] - 48) * pow( 10, --p);
    }
  p = 0;
  while (--i > -1)
    {
      if (s[i] == '-')
        return (-1 * nb);
      if (s[i] > 47 && s[i] < 58)
        nb += (s[i] - 48) * pow( 10, ++p);
    }
  return (nb);
}

short		get_data_short(char *cmp, char *s, short nb)
{
  if (my_strncmp(cmp, s, my_strlen(cmp)) == 0)
    nb = (short)my_getnbr_base(s, "0123456789");
  return (nb);
}

float		get_data_float(char *cmp, char *s, float nb)
{
  if (my_strncmp(cmp, s, my_strlen(cmp)) == 0)
    nb = my_getnbr_float(s);
  return (nb);
}
