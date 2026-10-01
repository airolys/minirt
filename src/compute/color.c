/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:49:47 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 14:41:58 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_light	*get_light(t_scene *scene, int type)
{
	t_light	*light;
	t_obj	*tmp;

	light = NULL;
	tmp = scene->lights;
	while (tmp)
	{
		if (tmp->type == LIGHT && type == LIGHT)
			light = (t_light *)tmp->inf;
		else if (tmp->type == AMBIANT && type == AMBIANT)
			light = (t_light *)tmp->inf;
		if (light)
			break ;
		tmp = tmp->next;
	}
	return (light);
}

void	get_rgb(int *r, int *g, int *b, int color)
{
	*r = color >> 16;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

void	cap_rgb(int *r, int *g, int *b)
{
	if (*r > 255)
		*r = 255;
	if (*g > 255)
		*g = 255;
	if (*b > 255)
		*b = 255;
	if (*r < 0)
		*r = 0;
	if (*g < 0)
		*g = 0;
	if (*b < 0)
		*b = 0;
}

int	set_color(int hit_color, t_lights l, int shadow, double dot_p)
{
	int		color[3];

	get_rgb(color + RED, color + GREEN, color + BLUE, hit_color);
	color[RED] = (color[RED] + (l.ambiant->color >> 16)) * l.ambiant->lumio;
	if (shadow)
		color[RED] += ((((hit_color >> 16) & 0xFF)
					+ (l.light->color >> 16)) & 0xFF) * l.light->lumio * dot_p;
	color[GREEN] = (color[GREEN] + (l.ambiant->color >> 8 & 0xFF))
		* l.ambiant->lumio;
	if (shadow)
		color[GREEN] += (((hit_color >> 8) & 0xFF)
				+ ((l.light->color >> 8) & 0xFF)) * l.light->lumio * dot_p;
	color[BLUE] = (color[BLUE] + (l.ambiant->color & 0xFF)) * l.ambiant->lumio;
	if (shadow)
		color[BLUE] += ((hit_color & 0xFF) + (l.light->color & 0xFF))
			* l.light->lumio * dot_p;
	cap_rgb(color + RED, color + GREEN, color + BLUE);
	return ((color[RED] << 16) + (color[GREEN] << 8) + color[BLUE]);
}

int	get_color(int hit_color, t_lights l, t_inter_info info)
{
	int		shadow;
	double	dot_p;

	dot_p = dot(info.primary.normale, info.light_inter.ray->dir);
	shadow = 1;
	if (dot_p < 0)
		dot_p = 0;
	if (info.light_inter.dist < l.dist && info.light_inter.dist > 1e-8)
		shadow = 0;
	return (set_color(hit_color, l, shadow, dot_p));
}
