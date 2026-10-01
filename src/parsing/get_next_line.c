/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:32:04 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 14:32:05 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	isbackn(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

void	cutline(char *line, int size, char *stash)
{
	int	i;
	int	strlen;

	strlen = ft_strlen(line);
	i = 0;
	while (i < (strlen - size))
	{
		stash[i] = line[size + i];
		i++;
	}
	stash[i] = 0;
}

char	*trimline(char *line)
{
	unsigned long	size;
	unsigned long	linesize;
	unsigned long	i;
	char			*str;

	i = 0;
	linesize = ft_strlen(line);
	size = isbackn(line);
	str = malloc(sizeof(char) * (linesize - (linesize - size) + 1));
	while (i < (linesize - (linesize - size)))
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	return (free(line), str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	stash[BUFFER_SIZE + 1];
	int			readpos;

	readpos = read(fd, stash, 0);
	if (fd < 0 || readpos < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	line = ft_strjoin(line, stash, 0);
	while (!isbackn(line) && readpos >= 0)
	{
		ft_bzero(stash, BUFFER_SIZE + 1);
		readpos = read(fd, stash, BUFFER_SIZE);
		if (!readpos)
		{
			if (line[0] == 0)
				return (free(line), NULL);
			return (line);
		}
		line = ft_strjoin(line, stash, 1);
	}
	cutline(line, isbackn(line), stash);
	return (line = trimline(line), line);
}
