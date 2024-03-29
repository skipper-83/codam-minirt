/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:21:26 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/11 12:08:24 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

/**
 * @brief struct with points x, y and z. Can be used to represent 
 * either a point(p), vector(v) or normal(n)
 */
typedef struct xyz_s
{
	float	x;
	float	y;
	float	z;
}			t_xyz;

t_xyz	v_create(float x, float y, float z);
t_xyz	v_copy(t_xyz a);
void	v_copy_values(t_xyz a, t_xyz *b);
t_xyz	v_add(t_xyz a, t_xyz b);
t_xyz	v_subtract(t_xyz a, t_xyz b);
t_xyz	v_multiply(t_xyz a, float b);
t_xyz	v_divide(t_xyz a, float b);
float	v_dot(t_xyz a, t_xyz b);
t_xyz	v_cross(t_xyz a, t_xyz b);
float	v_magnitude(t_xyz a);
t_xyz	v_normalize(t_xyz a);
void	v_normalizep(t_xyz *a);
float	v_square_of_self(t_xyz a);
float	v_angle(t_xyz a, t_xyz b);

#endif
