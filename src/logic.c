/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:32:21 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 16:46:33 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// return the distance at which the ray hit the obj if it does
double	does_intersect(t_ray *ray, t_obj *curr, t_inter *inter)
{
	if (curr->type == PLANE)
		return (does_plane_intersect(ray, (t_plane *)curr->inf, inter));
	if (curr->type == SPHERE)
		return (does_sphere_intersect(ray, (t_sphere *)curr->inf, inter));
	if (curr->type == CYLINDRE)
		return (does_cylinder_intersect(ray, (t_cylinder *)curr->inf, inter));
	return (-1.0);
}

int	compute_intersect(t_inter inter, t_scene *scene, int mxd)
{
	t_generic	*hit;
	t_ray		newray;
	t_light		*newlight;
	t_light		*ambiant;
	t_inter		newinter;

	(void)mxd;
	ambiant = get_light(scene, AMBIANT);
	newlight = get_light(scene, LIGHT);
	if (!newlight || !ambiant)
		return (0);
	if (!inter.hit || !inter.hit->inf)
		return (ambiant->color);
	hit = (t_generic *)inter.hit->inf;
	newray.pos = addvec(inter.ray->pos, multvec(inter.ray->dir, inter.dist));
	newray.dir = normalize(subvec(newlight->pos, newray.pos));
	newinter = trace(&newray, scene, HUGE_VAL);
	return (get_color(hit->color, (t_lights){ambiant, newlight,
			.dist = dist_ab(newlight->pos, newray.pos)}, (t_inter_info){inter,
		newinter}));
}

t_inter	trace(t_ray *ray, t_scene *scene, double maxdepth)
{
	t_inter	intersection[1];
	t_vect3	tmpnorm;
	t_obj	*curr;
	double	t;

	intersection->hit = NULL;
	intersection->dist = maxdepth;
	intersection->ray = ray;
	curr = scene->objs;
	while (curr)
	{
		tmpnorm = intersection->normale;
		t = does_intersect(ray, curr, intersection);
		if (t > 1e-8 && t < intersection->dist)
		{
			intersection->hit = curr;
			intersection->dist = t;
		}
		else
			intersection->normale = tmpnorm;
		curr = curr->next;
	}
	return (*intersection);
}

int	get_pixel_color(t_texture_data *data, int x, int y)
{
	char	*dst;

	if (!(x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0))
	{
		dst = data->data + (y * data->size + x * (data->bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

int	render_scene(t_vars *mlx)
{
	int		i;
	int		j;
	t_ray	curr;
	int		color;

	i = 0;
	cam_rot_mat(&(mlx->scene->cam));
	while (mlx->pixel > 0 && i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			curr = init_camera_ray(mlx, (t_vect2){j, i});
			color = compute_intersect(trace(&curr, mlx->scene, HUGE_VAL),
					mlx->scene, 2);
			draw_square(mlx->screen, (t_vect2){j, i}, mlx->pixel, color);
			j += mlx->pixel;
		}
		i += mlx->pixel;
	}
	mlx->pixel--;
	mlx_put_image_to_window(mlx->lib, mlx->win, mlx->screen.img, 0, 0);
	return (1);
}
