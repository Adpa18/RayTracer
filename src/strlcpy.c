/*
** strlcpy.c for strlcpy in /home/wilmot_g/.ssh/MUL_2014_rtracer/G/v14
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Fri Jun  5 21:50:09 2015 guillaume wilmot
** Last update Sun Jun  7 19:25:56 2015 guillaume wilmot
*/

char	*strlcpy(char *dest, char *src, int nb)
{
  int	i;

  i = 0;
  while (src[i] && i < nb)
    {
      dest[i] = src[i];
      i = i + 1;
    }
  if (!src[nb - 1])
    dest[i] = '\0';
  return (dest);
}
