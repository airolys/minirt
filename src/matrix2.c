/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:00:41 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 13:06:48 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//CA MARCHE PAS CA FAUT LE FAIRE SUR LE 3x3 et LE 1x4 SEPAREMENT
void	transpose_matrix(double matrix[4][4], double invert[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			invert[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
}

/*
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/
// [1, 0, 0, x]
// [0, 1, 0, y]
// [0, 0, 1, z]
// [0, 0, 0, 1]
void	ntm(double matrix[4][4], double invert[4][4], t_vect3 pos)
{
	new_id_matrix(matrix);
	matrix[0][3] = pos.x;
	matrix[1][3] = pos.y;
	matrix[2][3] = pos.z;
	new_id_matrix(invert);
	invert[0][3] = -pos.x;
	invert[1][3] = -pos.y;
	invert[2][3] = -pos.z;
}

t_vect4	mult_vec4_matrix(t_vect4 vector, double matrix[4][4])
{
	t_vect4	res;

	res.x = vector.x * matrix[0][0]
		+ vector.y * matrix[0][1]
		+ vector.z * matrix[0][2]
		+ vector.w * matrix[0][3];
	res.y = vector.x * matrix[1][0]
		+ vector.y * matrix[1][1]
		+ vector.z * matrix[1][2]
		+ vector.w * matrix[1][3];
	res.z = vector.x * matrix[2][0]
		+ vector.y * matrix[2][1]
		+ vector.z * matrix[2][2]
		+ vector.w * matrix[2][3];
	res.w = vector.x * matrix[3][0]
		+ vector.y * matrix[3][1]
		+ vector.z * matrix[3][2]
		+ vector.w * matrix[3][3];
	return (res);
}

void	mmm(double res[4][4], double matrix1[4][4], double matrix2[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = matrix1[i][0] * matrix2[0][j]
				+ matrix1[i][1] * matrix2[1][j]
				+ matrix1[i][2] * matrix2[2][j]
				+ matrix1[i][3] * matrix2[3][j];
			j++;
		}
		i++;
	}
}

// [1, 0, 0, 0]
// [0, 1, 0, 0]
// [0, 0, 1, 0]
// [0, 0, 0, 1]
void	new_id_matrix(double matrix[4][4])
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}
