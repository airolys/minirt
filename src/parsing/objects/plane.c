/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:29 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 18:17:24 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

int	add_plane(t_vars *mlx, t_plane plane)
{
	t_obj	*tmp;

	tmp = mlx->scene->objs;
	if (!tmp)
	{
		mlx->scene->objs = new_obj(PLANE, new_plane(plane.pos, plane.normale,
					plane.color));
		if (!mlx->scene->objs)
			return (1);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj(PLANE, new_plane(plane.pos, plane.normale,
				plane.color));
	if (!tmp->next)
		return (1);
	return (0);
}

int	parse_plane(const char *line, int *i, t_vars *mlx)
{
	t_plane	plane;

	plane = (t_plane){0};
	if (parse_vect3(line, i, &plane.pos))
		return (1);
	if (parse_vect3(line, i, &plane.normale))
		return (1);
	if (plane.normale.x == 0 && plane.normale.y == 0 && plane.normale.z == 0)
		return (1);
	plane.color = parse_color(line, i);
	if (plane.color == -1)
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (1);
	if (add_plane(mlx, plane))
		return (1);
	return (0);
}
