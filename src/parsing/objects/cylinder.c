/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:17 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 18:17:00 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

t_cylinder	*new_cylinder(t_cylinder info)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (!out)
		return (NULL);
	out->pos = info.pos;
	out->dir = info.dir;
	out->radius = info.radius;
	out->height = info.height;
	out->color = info.color;
	out->disc1 = new_plane(addvec(info.pos,
				multvec(info.dir, -info.height / 2)), info.dir, info.color);
	out->disc2 = new_plane(addvec(info.pos,
				multvec(info.dir, info.height / 2)),
			multvec(info.dir, -1.0), info.color);
	return (out);
}

int	add_cylinder(t_vars *mlx, t_cylinder cyl)
{
	t_obj	*tmp;

	tmp = mlx->scene->objs;
	if (!tmp)
	{
		mlx->scene->objs = new_obj(CYLINDRE,
				new_cylinder((t_cylinder){cyl.color, cyl.pos, cyl.dir,
					cyl.height, cyl.radius, NULL, NULL}));
		if (!mlx->scene->objs)
			return (1);
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj(CYLINDRE, new_cylinder((t_cylinder){cyl.color, cyl.pos,
				cyl.dir, cyl.height, cyl.radius, NULL, NULL}));
	if (!tmp->next)
		return (1);
	return (0);
}

int	parse_cylinder(const char *line, int *i, t_vars *mlx)
{
	t_cylinder	cylinder;

	cylinder = (t_cylinder){0};
	if (parse_vect3(line, i, &cylinder.pos))
		return (1);
	if (parse_vect3(line, i, &cylinder.dir))
		return (1);
	if (cylinder.dir.x == 0 && cylinder.dir.y == 0 && cylinder.dir.z == 0)
		return (1);
	if (mag(cylinder.dir) != 1.0)
		cylinder.dir = normalize(cylinder.dir);
	if (parse_double(line, i, &cylinder.radius, ' '))
		return (1);
	skip_chars(line, i, ' ');
	if (parse_double(line, i, &cylinder.height, ' '))
		return (1);
	skip_chars(line, i, ' ');
	cylinder.color = parse_color(line, i);
	if (cylinder.color == -1)
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (1);
	return (add_cylinder(mlx, cylinder));
}
