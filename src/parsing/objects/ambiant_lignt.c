/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_lignt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:09 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:06:11 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

int	add_light(t_vars *mlx, t_light light)
{
	t_obj	*tmp;

	tmp = mlx->scene->lights;
	if (!tmp)
	{
		mlx->scene->lights = new_obj(LIGHT,
				new_light(light.pos, light.lumio, light.color));
		if (!mlx->scene->lights)
			return (1);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj(LIGHT, new_light(light.pos, light.lumio, light.color));
	if (!tmp->next)
		return (1);
	return (0);
}

int	add_ambiant(t_vars *mlx, t_light ambiant)
{
	t_obj	*tmp;

	tmp = mlx->scene->lights;
	if (!tmp)
	{
		mlx->scene->lights = new_obj(AMBIANT,
				new_ambiant(ambiant.lumio, ambiant.color));
		if (!mlx->scene->lights)
			return (1);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj(AMBIANT, new_ambiant(ambiant.lumio, ambiant.color));
	if (!tmp->next)
		return (1);
	return (0);
}

int	parse_ambient_light(const char *line, int *i, t_vars *mlx)
{
	t_light	light;

	if (mlx->scene->numobj[0])
		return (1);
	light = (t_light){0};
	light.lumio = parse_ratio(line, i, ' ');
	if (light.lumio == -1.0)
		return (1);
	light.color = parse_color(line, i);
	if (light.color == -1)
		return (1);
	if (add_ambiant(mlx, light))
		return (1);
	mlx->scene->numobj[0]++;
	return (0);
}

int	parse_light(const char *line, int *i, t_vars *mlx)
{
	t_light	light;

	if (mlx->scene->numobj[1])
		return (1);
	light = (t_light){0};
	if (parse_vect3(line, i, &light.pos))
		return (1);
	if (light.pos.x == -2.0)
		return (1);
	light.lumio = parse_ratio(line, i, ' ');
	if (light.lumio == -2.0)
		return (1);
	light.color = parse_color(line, i);
	if (light.color == -1)
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (1);
	if (add_light(mlx, light))
		return (1);
	mlx->scene->numobj[1]++;
	return (0);
}
