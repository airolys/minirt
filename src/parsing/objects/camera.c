/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:00 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 18:17:14 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

t_camera	*new_cam(t_vect3 pos, t_vect3 dir, double fov)
{
	t_camera	*out;

	out = malloc(sizeof(t_camera));
	if (!out)
		return (NULL);
	out->pos = pos;
	out->dir = dir;
	out->fov = fov;
	return (out);
}

int	parse_camera(const char *line, int *i, t_vars *mlx)
{
	t_camera	camera;

	if (mlx->scene->numobj[2])
		return (1);
	camera = (t_camera){0};
	if (parse_vect3(line, i, &camera.pos))
		return (1);
	if (camera.pos.x == -1.0)
		return (1);
	if (parse_vect3(line, i, &camera.dir))
		return (1);
	if (camera.dir.x == 0 && camera.dir.y == 0 && camera.dir.z == 0)
		return (1);
	if (parse_double(line, i, &camera.fov, '\0'))
		return (1);
	if (camera.fov < 0 || camera.fov > 180)
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (1);
	mlx->scene->cam = camera;
	mlx->scene->numobj[2]++;
	return (0);
}
