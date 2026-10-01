/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:41:24 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 18:08:29 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_plane	*new_plane(t_vect3 pos, t_vect3 normale, int color)
{
	t_plane	*out;

	out = malloc(sizeof(t_plane));
	if (!out)
		return (NULL);
	out->pos = pos;
	out->normale = normale;
	out->color = color;
	return (out);
}

double	does_plane_intersect(t_ray *ray, t_plane *plane, t_inter *inter)
{
	double	denominateur;
	t_vect3	polo;
	double	tout;

	(void)inter;
	denominateur = dot(plane->normale, ray->dir);
	if (denominateur > 1e-15)
	{
		polo = subvec(plane->pos, ray->pos);
		tout = dot(polo, plane->normale) / denominateur;
		if (tout >= 0)
		{
			inter->normale = multvec(plane->normale, -1);
			return (tout);
		}
	}
	return (-1.0);
}
