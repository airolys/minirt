/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:21:46 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:00:22 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	put_fd_len(int fd, char *s, int l)
{
	int	status;

	status = write (fd, s, l);
	return (status);
}

	// render_scene(&mlx);
int	main(int ac, char **av)
{
	t_vars	mlx;

	ft_bzero(&mlx, sizeof(mlx));
	if (!initialisation(&mlx, ac, av))
		return (put_fd_len(2, "INIT ERROR\n", 11), ft_close(&mlx), 0);
	mlx_hook(mlx.win, 17, 0, ft_close, &mlx);
	mlx_hook(mlx.win, 2, KeyPressMask, press_in, &mlx);
	mlx_loop_hook(mlx.lib, render_scene, &mlx);
	mlx_loop(mlx.lib);
	return (0);
}
