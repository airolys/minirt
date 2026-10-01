/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:40:20 by dkermia           #+#    #+#             */
/*   Updated: 2022/12/27 14:45:38 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_bzero(void *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)b)[i++] = 0;
}

char	*ft_strdup(char *str )
{
	size_t	i;
	char	*s;
	size_t	size;

	i = 0;
	size = ft_strlen(str) + 1;
	s = malloc(size * sizeof(char));
	if (!s)
		return (NULL);
	while (i < size -1)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	fill_s1(char *str, char *s1, int *i)
{
	while (s1[*i])
	{
		str[*i] = s1[*i];
		(*i)++;
	}
}

char	*ft_strjoin(char *s1, char *s2, int upend)
{
	char	*str;
	int		i;
	int		n;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s2));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	n = 0;
	if (s1)
		fill_s1(str, s1, &i);
	while (s2[n])
	{
		str[i] = s2[n];
		n++;
		i++;
	}
	str[i] = '\0';
	if (upend == 1)
		free(s1);
	return (str);
}
