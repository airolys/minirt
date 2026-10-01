/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:32:21 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 15:39:29 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

int	parse_color(const char *line, int *i)
{
	t_vect3	color;

	color = (t_vect3){0.0, 0.0, 0.0};
	if (parse_decimal(line, i, &color.x))
		return (1);
	if (!line[*i] || (line[*i] != ','))
		return (-1);
	else
		(*i)++;
	if (parse_decimal(line, i, &color.y))
		return (1);
	if (!line[*i] || (line[*i] != ','))
		return (-1);
	else
		(*i)++;
	if (parse_decimal(line, i, &color.z))
		return (1);
	skip_chars(line, i, ' ');
	if (line[*i] && line[*i] != '\n')
		return (-1);
	return (((int)color.x << 16) + ((int)color.y << 8) + (int)color.z);
}

int	parse_vect3(const char *line, int *i, t_vect3 *result)
{
	skip_chars(line, i, ' ');
	if (parse_double(line, i, &result->x, ','))
		return (1);
	if (!line[*i] || line[*i] != ',')
		return (1);
	else
		(*i)++;
	if (parse_double(line, i, &result->y, ','))
		return (1);
	if (!line[*i] || line[*i] != ',')
		return (1);
	else
		(*i)++;
	if (parse_double(line, i, &result->z, ' '))
		return (1);
	skip_chars(line, i, ' ');
	return (0);
}
