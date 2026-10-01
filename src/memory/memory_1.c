/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:40:18 by dkermia           #+#    #+#             */
/*   Updated: 2022/12/27 20:24:49 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_image(t_vars *mlx, t_image_d *sheet, int i)
{
	if (i == 0)
		return ;
	i--;
	while (i >= 0)
	{
		mlx_destroy_image(mlx->lib, sheet[i].img);
		i--;
	}
}

unsigned long	ft_strlen(char *str)
{
	unsigned long	size;

	size = 0;
	if (str)
		while (str[size])
			size++;
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*number;
	long	n;

	n = (long)nb;
	number = malloc(sizeof(char) * (ft_numsize(n) + 1));
	if (!number)
		return (0);
	number = ft_writenum(number, n);
	if (n < 0)
		number[0] = '-';
	return (number);
}

char	*path_builder(char *folder, int i)
{
	char	*tmp;
	char	*file;

	tmp = NULL;
	file = ft_itoa(i + 1);
	if (!file)
		return (0);
	tmp = ft_strjoin(folder, file, 0);
	free(file);
	if (!tmp)
		return (0);
	tmp = ft_strjoin(tmp, ".xpm", 1);
	if (!tmp)
		return (0);
	return (tmp);
}
