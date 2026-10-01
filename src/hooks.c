/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:46:58 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:02:19 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	free_cyl(t_cylinder	*cyl)
{
	if (!cyl)
		return ;
	free(cyl->disc1);
	free(cyl->disc2);
	free(cyl);
}

void	free_obj(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->type == SPHERE)
		free(((t_sphere *)obj->inf));
	if (obj->type == PLANE)
		free(((t_plane *)obj->inf));
	if (obj->type == CYLINDRE)
		free_cyl(((t_cylinder *)obj->inf));
	free(obj);
}

void	free_light(t_obj *light)
{
	if (!light)
		return ;
	if (light->type == AMBIANT || light->type == LIGHT)
		free(((t_light *)light->inf));
	free(light);
}

int	ft_close(t_vars *mlx)
{
	t_obj	*tmp;
	t_obj	*tmp2;

	tmp = mlx->scene->objs;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_obj(tmp);
		tmp = tmp2;
	}
	tmp = mlx->scene->lights;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_light(tmp);
		tmp = tmp2;
	}
	if (mlx->screen.img)
		destroy_render(mlx, 2);
	exit(EXIT_SUCCESS);
	return (0);
}

int	press_in(int keypress, t_vars *mlx)
{
	int	i;

	i = 0;
	mlx->pixel = 20;
	if (keypress == XK_Escape)
		ft_close(mlx);
	if (keypress == XK_w)
		mlx->scene->cam.pos.z += 1;
	if (keypress == XK_s)
		mlx->scene->cam.pos.z -= 1;
	if (keypress == XK_a)
		mlx->scene->cam.pos.x -= 1;
	if (keypress == XK_d)
		mlx->scene->cam.pos.x += 1;
	if (keypress == XK_space)
		mlx->scene->cam.pos.y += 1;
	if (keypress == XK_Shift_L)
		mlx->scene->cam.pos.y -= 1;
	if (keypress == XK_equal)
		mlx->scene->cam.fov += 1;
	if (keypress == XK_minus)
		mlx->scene->cam.fov -= 1;
	return (0);
}

/* 	if (keypress == XK_Left)
		mlx->scene->cam.dir = rotate_vect3(mlx->scene->cam.dir,
		(t_vect3){0, 1, 0}, -mlx->scene->cam.fov * 0.0005);
	if (keypress == XK_Right)
		mlx->scene->cam.dir = rotate_vect3(mlx->scene->cam.dir,
		(t_vect3){0, 1, 0}, mlx->scene->cam.fov * 0.0005);
	if (keypress == XK_Up)
		mlx->scene->cam.dir = rotate_vect3(mlx->scene->cam.dir,
		(t_vect3){1, 0, 0}, -mlx->scene->cam.fov * 0.0005);
	if (keypress == XK_Down)
		mlx->scene->cam.dir = rotate_vect3(mlx->scene->cam.dir,
		(t_vect3){1, 0, 0}, mlx->scene->cam.fov * 0.0005);
 */
/* t_vect3	rotate_vect3(t_vect3 v, t_vect3 axis, double angle)
{
	t_vect3	out;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	out.x = (cos_a + (1 - cos_a) * axis.x * axis.x) * v.x;
	out.x += ((1 - cos_a) * axis.x * axis.y - axis.z * sin_a) * v.y;
	out.x += ((1 - cos_a) * axis.x * axis.z + axis.y * sin_a) * v.z;
	out.y = ((1 - cos_a) * axis.x * axis.y + axis.z * sin_a) * v.x;
	out.y += (cos_a + (1 - cos_a) * axis.y * axis.y) * v.y;
	out.y += ((1 - cos_a) * axis.y * axis.z - axis.x * sin_a) * v.z;
	out.z = ((1 - cos_a) * axis.x * axis.z - axis.y * sin_a) * v.x;
	out.z += ((1 - cos_a) * axis.y * axis.z + axis.x * sin_a) * v.y;
	out.z += (cos_a + (1 - cos_a) * axis.z * axis.z) * v.z;
	return (out);
} */