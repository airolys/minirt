/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:56:47 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 15:58:38 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_obj	*new_obj(enum e_obj type, void *info)
{
	t_obj	*out;

	out = malloc(sizeof(t_obj));
	if (!out)
		return (NULL);
	out->inf = info;
	out->next = NULL;
	out->type = type;
	return (out);
}

t_light	*new_light(t_vect3 pos, double lumio, int color)
{
	t_light	*out;

	out = malloc(sizeof(t_light));
	if (!out)
		return (NULL);
	out->pos = pos;
	out->lumio = lumio;
	out->color = color;
	return (out);
}

t_light	*new_ambiant(double lumio, int color)
{
	t_light	*out;

	out = malloc(sizeof(t_light));
	if (!out)
		return (NULL);
	out->lumio = lumio;
	out->color = color;
	return (out);
}
