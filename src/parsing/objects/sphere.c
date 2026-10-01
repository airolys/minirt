/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:11 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:05:16 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

int	add_sphere(t_vars *mlx, t_sphere sphere)
{
	t_obj		*tmp;

	tmp = mlx->scene->objs;
	if (!tmp)
	{
		mlx->scene->objs = new_obj(SPHERE, new_sphere(sphere.pos, sphere.radius,
					sphere.color));
		if (!mlx->scene->objs)
			return (1);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj(SPHERE, new_sphere(sphere.pos, sphere.radius,
				sphere.color));
	if (!tmp->next)
		return (1);
	return (0);
}

int	parse_sphere(const char *line, int *i, t_vars *mlx)
{
	t_sphere	sphere;

	sphere = (t_sphere){0};
	if (parse_vect3(line, i, &sphere.pos))
		return (1);
	if (sphere.pos.x == -1.0)
		return (1);
	sphere.radius = 0.0;
	if (parse_double(line, i, &sphere.radius, ' '))
		return (1);
	skip_chars(line, i, ' ');
	sphere.color = parse_color(line, i);
	if (sphere.color == -1)
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (1);
	if (add_sphere(mlx, sphere))
		return (1);
	return (0);
}
