/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:20:48 by acharra           #+#    #+#             */
/*   Updated: 2023/12/11 11:18:10 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	does_disc_intersect(t_ray *ray, t_plane *disc, double ra, t_inter *i)
{
	double	d;
	t_vect3	a;
	t_vect3	b;

	d = does_plane_intersect(ray, disc, i);
	if (d < 0)
		return (-1);
	a = disc->pos;
	b = addvec(ray->pos, multvec(ray->dir, d));
	if (dist_ab(a, b) > ra)
		return (-1);
	return (d);
}
