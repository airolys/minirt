/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:18 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 15:34:19 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vect3	cross_prod(t_vect3 u, t_vect3 v)
{
	t_vect3	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

void	cam_rot_mat(t_camera *cam)
{
	t_vect3	forward;
	t_vect3	right;
	t_vect3	up;
	t_vect3	tup;

	up = (t_vect3){0.0, 1.0, 0.0};
	forward = normalize(cam->dir);
	right = cross_prod(up, forward);
	tup = cross_prod(forward, right);
	cam->vmat[0][0] = right.x;
	cam->vmat[0][1] = right.y;
	cam->vmat[0][2] = right.z;
	cam->vmat[1][0] = tup.x;
	cam->vmat[1][1] = tup.y;
	cam->vmat[1][2] = tup.z;
	cam->vmat[2][0] = forward.x;
	cam->vmat[2][1] = forward.y;
	cam->vmat[2][2] = forward.z;
}

t_vect3	apply_cam_mat(double m[3][3], t_ray ray)
{
	t_vect3	out;

	out.x = ray.dir.x * m[0][0] + ray.dir.y * m[1][0] + ray.dir.z * m[2][0];
	out.y = ray.dir.x * m[0][1] + ray.dir.y * m[1][1] + ray.dir.z * m[2][1];
	out.z = ray.dir.x * m[0][2] + ray.dir.y * m[1][2] + ray.dir.z * m[2][2];
	return (out);
}

t_ray	init_camera_ray(t_vars *mlx, t_vect2 xy)
{
	t_ray	out;
	double	half_width;
	double	aspect_ratio;

	aspect_ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	half_width = tan((mlx->scene->cam.fov * M_PI / 180) / 2);
	out.pos = mlx->scene->cam.pos;
	out.dir.x = (2 * ((xy.x + 0.5) / SCREEN_WIDTH) - 1) * half_width
		* aspect_ratio;
	out.dir.y = (1 - 2 * ((xy.y + 0.5) / SCREEN_HEIGHT)) * half_width;
	out.dir.z = 1;
	out.dir = normalize(out.dir);
	out.dir = apply_cam_mat(mlx->scene->cam.vmat, out);
	return (out);
}
