/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:32:11 by dkermia           #+#    #+#             */
/*   Updated: 2022/12/31 14:25:38 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	draw_pixel(t_texture_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0))
	{
		dst = data->data + (y * data->size + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_image_d screen, t_vect2 pos, int size, int color)
{
	int	i;
	int	j;

	i = pos.y;
	while (i < pos.y + size)
	{
		j = pos.x;
		while (j < pos.x + size)
		{
			draw_pixel(&screen.addr, j, i, color);
			j++;
		}
		i++;
	}
}
