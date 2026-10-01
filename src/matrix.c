/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:48:49 by acharra           #+#    #+#             */
/*   Updated: 2023/12/12 13:07:25 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// [1, 0    , 0     , 0]
// [0, cos_t, -sin_t, 0]
// [0, sin_t, cos_t , 0]
// [0, 0    , 0     , 1]
void	rot_x(double matrix[4][4], double invert[4][4], double theta)
{
	double	cos_t;
	double	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	new_id_matrix(matrix);
	matrix[1][1] = cos_t;
	matrix[1][2] = -sin_t;
	matrix[2][1] = sin_t;
	matrix[2][2] = cos_t;
	new_id_matrix(invert);
	transpose_matrix(matrix, invert);
}

// [ cos_t, 0, sin_t, 0]
// [ 0    , 1, 0    , 0]
// [-sin_t, 0, cos_t, 0]
// [ 0    , 0, 0    , 1]
void	rot_y(double matrix[4][4], double invert[4][4], double theta)
{
	double	cos_t;
	double	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	new_id_matrix(matrix);
	matrix[0][0] = cos_t;
	matrix[0][2] = sin_t;
	matrix[2][0] = -sin_t;
	matrix[2][2] = cos_t;
	new_id_matrix(invert);
	transpose_matrix(matrix, invert);
}

//MATRIX Z
// [cos_t, -sin_t, 0, 0]
// [sin_t, cos_t , 0, 0]
// [0    , 0     , 1, 0]
// [0    , 0     , 0, 1]

//INVERT
// [ cos_t, sin_t , 0, 0]
// [-sin_t, cos_t , 0, 0]
// [ 0    , 0     , 1, 0]
//  [0    , 0     , 0, 1]
void	rot_z(double matrix[4][4], double invert[4][4], double theta)
{
	double	cos_t;
	double	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	new_id_matrix(matrix);
	matrix[0][0] = cos_t;
	matrix[0][1] = -sin_t;
	matrix[1][0] = sin_t;
	matrix[1][1] = cos_t;
	new_id_matrix(invert);
	transpose_matrix(matrix, invert);
}

void	get_theta_xyz(double theta[3], t_vect3 normal)
{
	theta[X] = normal.x * 3.14 / 2;
	theta[Y] = normal.y * 3.14 / 2;
	theta[Z] = normal.z * 3.14 / 2;
}

void	get_rotation_matrix(t_camera *cam)
{
	double	theta[3];

	get_theta_xyz(theta, cam->dir);
	rot_x(cam->mat[SIMPLE][X], cam->mat[INVERT][X], theta[X]);
	rot_y(cam->mat[SIMPLE][Y], cam->mat[INVERT][Y], theta[Y]);
	rot_z(cam->mat[SIMPLE][Z], cam->mat[INVERT][Z], theta[Z]);
}
