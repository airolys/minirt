/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:24 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 16:30:51 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//return the closest in height, root
double	check_height(t_ray *ray, t_cylinder *cyl, double x[2], double h[1])
{
	t_vect3	inter;
	double	magnitude;

	h[0] = -1;
	inter = addvec(subvec(ray->pos, cyl->pos), multvec(ray->dir, x[0]));
	magnitude = mag(inter);
	*h = magnitude * magnitude - cyl->radius * cyl->radius;
	if (*h < (cyl->height / 2) * (cyl->height / 2))
		return (x[0]);
	inter = addvec(subvec(ray->pos, cyl->pos), multvec(ray->dir, x[1]));
	magnitude = mag(inter);
	*h = magnitude * magnitude - cyl->radius * cyl->radius;
	if (*h < (cyl->height / 2) * (cyl->height / 2))
		return (x[1]);
	*h = -1;
	return (-1.0);
}

void	compute_quadratic(double x[2], double a, double b, double c)
{
	double	delta;
	double	tmp;

	delta = b * b - 4 * a * c;
	x[0] = -1;
	x[1] = -1;
	if (delta <= 0)
		return ;
	delta = sqrt(delta);
	x[0] = (-b - delta) / (2 * a);
	tmp = (-b + delta) / (2 * a);
	if (tmp < x[0] || x[0] < 1e-8)
	{
		x[1] = x[0];
		x[0] = tmp;
	}
	else
		x[1] = tmp;
}
/*
int	cyl_height(t_ray *ray, t_cylinder *cyl, t_inter *inter, double hy[2])
{
	double	newt1;
	double	newt2;
	t_vect3	oc;	

	oc = subvec(ray->pos, cyl->pos);
	newt1 = does_disc_intersect(ray, cyl->disc1, cyl->radius, inter);
	newt2 = does_disc_intersect(ray, cyl->disc2, cyl->radius, inter);
	if (newt1 > 0 && (newt1 < hy[1] || hy[1] < 0))
		return (inter->normale = multvec(cyl->dir, -1.0), newt1);
	if (newt2 > 0 && (newt2 < hy[1] || hy[1] < 0))
		return (inter->normale = cyl->dir, newt2);
	if (hy[0] <= -1.0)
		return (-1);
	if (hy[0] < 1e-8)
		return (inter->normale = \
		normalize(addvec(oc, multvec(ray->dir, hy[1]))), hy[1]);
	inter->normale = subvec(addvec(oc, multvec(ray->dir, hy[1])),
			multvec(cyl->dir, sqrt(hy[0])));
	if (mag(inter->normale) > cyl->radius + 1e-8)
		inter->normale = subvec(addvec(oc, multvec(ray->dir, hy[1])),
				multvec(cyl->dir, -sqrt(hy[0])));
	return (inter->normale = normalize(inter->normale), hy[1]);
}

double	does_cylinder_intersect(t_ray *ray, t_cylinder *cyl, t_inter *inter)
{
	double	x[2];
	t_vect3	oc;
	double	hy[2];

	hy[0] = -1;
	hy[1] = -1;
	oc = subvec(ray->pos, cyl->pos);
	compute_quadratic(x,
		dot(ray->dir, ray->dir) - pow(dot(ray->dir, cyl->dir), 2),
		2 * (dot(ray->dir, oc) - dot(ray->dir, cyl->dir) * dot(oc, cyl->dir)),
		dot(oc, oc) - pow(dot(oc, cyl->dir), 2) - cyl->radius * cyl->radius);
	hy[1] = check_height(ray, cyl, x, &hy[0]);
	return (cyl_height(ray, cyl, inter, hy));
}
*/

t_vect3	cyl_norm_func(t_ray *ray, t_cylinder *cyl, double hy[2], double x[2])
{
	t_vect3	oc;

	oc = subvec(ray->pos, cyl->pos);
	compute_quadratic(x,
		dot(ray->dir, ray->dir) - pow(dot(ray->dir, cyl->dir), 2),
		2 * (dot(ray->dir, oc) - dot(ray->dir, cyl->dir) * dot(oc, cyl->dir)),
		dot(oc, oc) - pow(dot(oc, cyl->dir), 2) - cyl->radius * cyl->radius);
	hy[1] = check_height(ray, cyl, x, hy);
	return (oc);
}

double	does_cylinder_intersect(t_ray *ray, t_cylinder *cyl, t_inter *inter)
{
	double	x[2];
	t_vect3	oc;
	double	hy[2];
	double	newt[2];

	oc = cyl_norm_func(ray, cyl, hy, x);
	newt[0] = does_disc_intersect(ray, cyl->disc1, cyl->radius, inter);
	newt[1] = does_disc_intersect(ray, cyl->disc2, cyl->radius, inter);
	if (newt[0] > 0 && (newt[0] < hy[1] || hy[1] < 0))
		return (inter->normale = multvec(cyl->dir, -1.0), newt[0]);
	if (newt[1] > 0 && (newt[1] < hy[1] || hy[1] < 0))
		return (inter->normale = cyl->dir, newt[1]);
	if (hy[0] <= -1.0)
		return (-1);
	if (hy[0] < 1e-8)
		return (inter->normale = normalize(addvec(oc,
					multvec(ray->dir, hy[1]))), hy[1]);
	inter->normale = subvec(addvec(oc, multvec(ray->dir, hy[1])),
			multvec(cyl->dir, sqrt(hy[0])));
	if (mag(inter->normale) > cyl->radius + 1e-8)
		inter->normale = subvec(addvec(oc, multvec(ray->dir, hy[1])),
				multvec(cyl->dir, -sqrt(hy[0])));
	return (inter->normale = normalize(inter->normale), hy[1]);
}
