/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:31:46 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 17:41:08 by dkermia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

typedef int		(*t_parse_funct)(const char *, int *, t_vars *);

typedef struct s_parser
{
	char			*keyword;
	t_parse_funct	parser;
}	t_parser;

int	get_object_with_parser(char *line, int line_number, t_vars *mlx,
	t_parser *p)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (p[j].keyword != NULL)
	{
		if (strncmp(&line[i], p[j].keyword, strlen(p[j].keyword)) == 0)
		{
			i += strlen(p[j].keyword);
			if (p[j].parser(line, &i, mlx))
				return (1);
			return (0);
		}
		j++;
	}
	if (line[0] == '\n' || !line[0])
		return (0);
	return (printf("Error at line %d\n", line_number), 1);
}

int	get_object(char *line, int line_number, t_vars *mlx)
{
	t_parser	*p;

	p = (t_parser[]){
	{"A ", parse_ambient_light},
	{"C ", parse_camera},
	{"L ", parse_light},
	{"pl ", parse_plane},
	{"sp ", parse_sphere},
	{"cy ", parse_cylinder},
	{NULL, NULL}};
	return (get_object_with_parser(line, line_number, mlx, p));
}

int	name_check(char *str, char *extenstion)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (extenstion[j])
		j++;
	if (i < j)
		return (1);
	while (j >= 0)
	{
		if (str[i] != extenstion[j])
			return (1);
		i--;
		j--;
	}
	return (0);
}

int	parsing(int argc, char **argv, t_vars *mlx)
{
	char	*line;
	int		fd;
	int		line_number;

	if (name_check(argv[1], ".rt"))
		return (fprintf(stderr, "Error\nWrong file extension\n"), 1);
	if (argc != 2)
		return (fprintf(stderr, "Usage: %s <filename>\n", argv[0]), 1);
	line_number = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (fprintf(stderr, "Could not open %s\n", argv[1]), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (get_object(line, line_number, mlx))
			return (fprintf(stderr, "Error at line %d\n", line_number), 1);
		free(line);
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	return (0);
}
