/*
** str2.c for str2 in /home/wery_a/rendu/CPE/Lem-In/Test/v1
** 
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
** 
** Started on  Sat Apr 25 15:14:13 2015 Adrien WERY
** Last update Sun Jun  7 19:50:27 2015 Matthieu Tavernier
*/

#include <stdlib.h>
#include <unistd.h>

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  if (s1 == NULL || s2 == NULL)
    return (-1);
  i = 0;
  while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
    i += 1;
  return (s1[i] - s2[i]);
}

int	my_strncmp(char *s1, char *s2, int nb)
{
  int	i;

  if (s1 == NULL || s2 == NULL)
    return (-1);
  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0' && i < nb - 1)
    i += 1;
  return (s1[i] - s2[i]);
}

void	my_memset(char *s, char c, int size)
{
  int	i;

  i = -1;
  while (++i < size)
    s[i] = c;
}

char	*my_strncpy(char *s, int start, int end)
{
  char	*cp;
  int	i;

  if ((cp = malloc(sizeof(char) * (end - start + 1))) == NULL)
    return (NULL);
  my_memset(cp, '\0', end - start);
  i = -1;
  while (end - start != 0)
    cp[++i] = s[start++];
  cp[i] = '\0';
  return (cp);
}
