/*
** hexa.c for hexa in /home/wilmot_g/.ssh/asm/asm/wilmot_g/src
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Tue Mar 31 16:01:27 2015 guillaume wilmot
** Last update Sun Jun  7 16:16:06 2015 guillaume wilmot
*/

#include "system.h"

void		my_revstr(unsigned char *str)
{
  int		i;
  int		j;
  int		maximum;
  int		empty_glass;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  i = i - 1;
  maximum = i;
  while (i > (maximum / 2))
    {
      empty_glass = str[i];
      str[i] = str[j];
      str[j] = empty_glass;
      i = i - 1;
      j = j + 1;
    }
}

unsigned char	value(unsigned char *str, char *base)
{
  int		i;
  unsigned char	res;

  i = 0;
  while (base[i] && str[0] != base[i])
    i++;
  res = i * 16;
  i = 0;
  while (base[i] && str[1] != base[i])
    i++;
  res += i;
  return (res);
}

unsigned char	**cut_bytes_endian(unsigned char *str)
{
  unsigned char	**new;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((new = malloc((4) * sizeof(char *))) == NULL)
    return (NULL);
  while (str[i])
    {
      if ((new[j] = malloc((3) * sizeof(char *))) == NULL)
	return (NULL);
      new[j][0] = str[i++];
      new[j][1] = str[i++];
      new[j][2] = '\0';
      j++;
    }
  free(str);
  return (new);
}

unsigned char	**convert_hexa(int nbr, int octet)
{
  char		*base;
  unsigned char	*result;
  int		neg;
  int		i;

  neg = (nbr < 0) ? 1 : 0;
  nbr = (neg == 1) ? -nbr - 1 : nbr;
  base = "0123456789abcdef";
  i = 0;
  if ((result = malloc((octet * 2 + 20) * sizeof(char))) == NULL)
    return (NULL);
  while (i < octet * 2)
    result[i++] = (neg == 1) ? 'f' : '0';
  i = 0;
  while (nbr / 16 != 0)
    {
      result[i++] = (neg == 1) ? base[15 - (nbr % 16)] : base[nbr % 16];
      nbr = nbr / 16;
    }
  result[i++] = (neg == 1) ? base[15 - (nbr % 16)] : base[nbr % 16];
  result[octet * 2] = '\0';
  my_revstr(result);
  return (cut_bytes_endian(result));
}
