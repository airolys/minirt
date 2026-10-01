/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:40:16 by dkermia           #+#    #+#             */
/*   Updated: 2023/11/07 14:44:39 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + 48, fd);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	j;

	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) <= len)
		str = (char *)malloc(ft_strlen(s) - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] && j < len)
			str[j++] = s[start++];
	str[j] = 0;
	return (str);
}

char	*ft_subsecure(char *s, int *i, char **str)
{
	char	*stri;
	int		j;

	j = 0;
	stri = ft_substr(s, (i[0] - i[1]), i[1]);
	if (!stri)
	{
		while (j <= i[2])
			free(str[j++]);
		free(str);
	}
	return (stri);
}

int	wordn(char *s, char c)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			i[1]++;
			while (s[i[0]] != c && s[i[0]])
				i[0]++;
		}
		while (s[i[0]] == c && s[i[0]])
			i[0]++;
	}
	return (i[1]);
}

char	**ft_split(char *s, char c)
{
	int		i[3];
	char	**str;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	str = malloc(sizeof(char *) * (wordn(s, c) + 1));
	if (!str)
		return (NULL);
	while (i[2] < wordn(s, c))
	{
		while (s[i[0]] == c && s[i[0]])
			i[0]++;
		while (s[i[0]] != c && s[i[0]])
		{
			i[0]++;
			i[1]++;
		}
		str[i[2]++] = ft_subsecure(s, i, str);
		if (!str)
			return (NULL);
		i[1] = 0;
	}
	str[i[2]] = NULL;
	return (str);
}
