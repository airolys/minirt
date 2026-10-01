/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:36:37 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 12:53:51 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_sphere	*new_sphere(t_vect3 pos, double radius, int color)
{
	t_sphere	*out;

	out = malloc(sizeof(t_sphere));
	if (!out)
		return (NULL);
	out->pos = pos;
	out->radius = radius;
	out->color = color;
	return (out);
}

double	does_sphere_intersect(t_ray *ray, t_sphere *sphere, t_inter *inter)
{
	double	x[2];
	double	dist;
	t_vect3	oc;

	if (sphere->radius < 0)
		return (-1.0);
	oc = subvec(ray->pos, sphere->pos);
	compute_quadratic(x,
		dot(ray->dir, ray->dir),
		2 * dot(oc, ray->dir),
		dot(oc, oc) - sphere->radius * sphere->radius);
	if (x[0] <= 0 && x[1] <= 0)
		return (-1);
	dist = min_sup_zero(x[0], x[1]);
	inter->normale = normalize(subvec(addvec(ray->pos, multvec(ray->dir, dist)),
				sphere->pos));
	return (dist);
}
