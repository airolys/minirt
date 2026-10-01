/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:32:18 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 15:39:14 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

void	skip_chars(const char *line, int *i, char c)
{
	while (line[*i] && line[*i] == c)
		(*i)++;
}

int	parse_decimal(const char *line, int *i, double *result)
{
	while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
	{
		*result = *result * 10 + (line[*i] - '0');
		(*i)++;
	}
	if (line[*i] && (line[*i] != ',' && line[*i] != '\n' && line[*i] != ' '))
		return (1);
	return (0);
}

int	handle_factor(const char *line, int *i, double *ratio, char end_char)
{
	float	factor;

	factor = 0;
	if (line[*i] == '.')
	{
		(*i)++;
		factor = 0.1f;
		if (!(line[*i] >= '0' && line[*i] <= '9'))
			return (1);
		while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
		{
			*ratio += (factor * (line[*i] - '0'));
			factor *= 0.1f;
			(*i)++;
		}
		if (!line[*i])
			return (1);
		if ((!(line[*i] >= '0' && line[*i] <= '9') && line[*i] != end_char))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	parse_double(const char *line, int *i, double *result, char end_char)
{
	int	sign;

	sign = 1;
	if (!line[*i] || (line[*i] != '-' && (line[*i] < '0' || line[*i] > '9')))
		return (1);
	if (line[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	while (line[*i] && (line[*i] >= '0' && line[*i] <= '9'))
	{
		*result = *result * 10 + (line[*i] - '0');
		(*i)++;
	}
	if (line[*i] == '.')
		handle_factor(line, i, result, end_char);
	if (!end_char)
		return (0);
	*result *= sign;
	if (!line[*i] || (line[*i] != end_char && line[*i] != '\n'))
		return (1);
	return (0);
}

double	parse_ratio(const char *line, int *i, char end_char)
{
	double	ratio;
	int		j;

	ratio = 0.0f;
	j = *i;
	skip_chars(line, &j, ' ');
	if (!line[j] || (line[j] != '0' && line[j] != '1'))
		return (-1.0);
	skip_chars(line, &j, '0');
	if (!line[j])
		return (-1.0);
	if (line[j] != '1' && line[j] != '.')
		return (-1.0);
	if (line[j] == '1')
	{
		ratio = 1.0;
		j++;
	}
	if (handle_factor(line, &j, &ratio, end_char))
		return (-1.0);
	return (skip_chars(line, &j, ' '), *i = j, ratio);
}
