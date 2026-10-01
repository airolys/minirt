/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:12:44 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 12:57:08 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//return the mult of a vect3 by a double
t_vect3	multvec(t_vect3 a, double d)
{
	t_vect3	out;

	out.x = a.x * d;
	out.y = a.y * d;
	out.z = a.z * d;
	return (out);
}

t_vect3	normalize(t_vect3 v)
{
	t_vect3	out;
	double	mag_squared;
	double	mag;

	mag_squared = v.x * v.x + v.y * v.y + v.z * v.z;
	mag = sqrt(mag_squared);
	if (mag > 0.0)
	{
		out.x = v.x / mag;
		out.y = v.y / mag;
		out.z = v.z / mag;
	}
	else
	{
		out.x = 0.0;
		out.y = 0.0;
		out.z = 0.0;
	}
	return (out);
}

double	mag(t_vect3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//return the dot prod of two vect3
double	dot(t_vect3 a, t_vect3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//return the sum of two vect3
t_vect3	addvec(t_vect3 a, t_vect3 b)
{
	t_vect3	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	out.z = a.z + b.z;
	return (out);
}
