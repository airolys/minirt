/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:15:36 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:02:09 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	destroy_render(t_vars *mlx, int i)
{
	mlx_destroy_window(mlx->lib, mlx->win);
	if (i == 2)
		mlx_destroy_image(mlx->lib, mlx->screen.img);
	if (i)
		mlx_destroy_display(mlx->lib);
	free(mlx->lib);
	return (0);
}

int	render_init(t_vars *mlx)
{
	mlx->lib = mlx_init();
	if (!mlx->lib)
		return (put_fd_len(2, "Error : mlx_lib\n", 17), 0);
	mlx->win = mlx_new_window(mlx->lib, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	if (!mlx->win)
		return (put_fd_len(2, "Error : mlx_new_window\n", 24),
			destroy_render(mlx, 0), 0);
	mlx->screen.img = mlx_new_image(mlx->lib, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx->screen.img)
		return (put_fd_len(2, "Error : mlx_new_image\n", 23),
			destroy_render(mlx, 1), 1);
	mlx->screen.addr.data = mlx_get_data_addr(mlx->screen.img,
			&mlx->screen.addr.bpp, &mlx->screen.addr.size,
			&mlx->screen.addr.endian);
	return (1);
}

int	scene_init(t_vars *mlx)
{
	mlx->pixel = 10;
	mlx->screen.img = NULL;
	mlx->scene->numobj[0] = 0;
	mlx->scene->numobj[1] = 0;
	mlx->scene->numobj[2] = 0;
	mlx->scene->objs = NULL;
	mlx->scene->cam.pos = (t_vect3){-1, -1, -1};
	mlx->scene->cam.dir = (t_vect3){-1, -1, -1};
	mlx->scene->cam.fov = -1;
	mlx->scene->lights = NULL;
	return (1);
}

int	initialisation(t_vars *mlx, int ac, char **av)
{
	if (!scene_init(mlx))
		return (0);
	if (parsing(ac, av, mlx))
		return (0);
	if (mlx->scene->numobj[0] != 1)
		return (0);
	if (mlx->scene->numobj[1] != 1)
		return (0);
	if (mlx->scene->numobj[2] != 1)
		return (0);
	if (!render_init(mlx))
		return (0);
	return (1);
}
