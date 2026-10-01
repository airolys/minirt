/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:16:44 by dkermia           #+#    #+#             */
/*   Updated: 2023/11/07 14:44:54 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_putchar_fd(char c, int fd)
{
	put_fd_len(fd, &c, 1);
}

int	ft_numsize(long n)
{
	long	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_writenum(char *number, long n)
{
	int		i;
	long	tenpow;
	long	tmp;

	i = ft_numsize(n);
	tenpow = 10;
	tmp = n;
	if (tmp < 0)
		tmp = tmp * (-1);
	while (i > 0)
	{
		number[i - 1] = (tmp % tenpow) / (tenpow / 10) + 48;
		tenpow = tenpow * 10;
		i--;
	}
	number[ft_numsize(n)] = '\0';
	return (number);
}
