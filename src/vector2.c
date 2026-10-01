/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:49:04 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 12:37:53 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//return the substraction of vect3 a by b
t_vect3	subvec(t_vect3 a, t_vect3 b)
{
	t_vect3	out;

	out.x = a.x - b.x;
	out.y = a.y - b.y;
	out.z = a.z - b.z;
	return (out);
}

double	ft_sqrt(double x)
{
	double	ret;
	double	div;
	int		i;

	ret = 0;
	div = 1;
	i = 0;
	while (i < 10)
	{
		while (ret * ret <= x)
			ret += div;
		ret -= div;
		div /= 10;
		i++;
	}
	return (ret);
}

double	dist_ab(t_vect3 a, t_vect3 b)
{
	double	dx;
	double	dy;
	double	dz;

	dx = b.x - a.x;
	dy = b.y - a.y;
	dz = b.z - a.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

double	min_sup_zero(double a, double b)
{
	if (a < b)
	{
		if (a > 0)
			return (a);
	}
	if (b > 0)
		return (b);
	return (-1);
}
