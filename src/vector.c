/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 08:31:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 22:21:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/**
 * @brief Creates new vector (t_xyz) with input values x, y, and z
 * 
 * @param x (float)
 * @param y (float)
 * @param z (float)
 * @return t_xyz 
 */
t_xyz	v_create(float x, float y, float z)
{
	t_xyz	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

/**
 * @brief Creates and returs a copy of the provided vector
 * 
 * @param a (t_xyz);
 * @return t_xyz 
 */
t_xyz	v_copy(t_xyz a)
{
	t_xyz	new;

	new.x = a.x;
	new.y = a.y;
	new.z = a.z;
	return (new);
}

/**
 * @brief  copies values from a into pointer b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz *)
 */
void	v_copyValues(t_xyz a, t_xyz *b)
{
	b->x = a.x;
	b->y = a.y;
	b->z = a.z;
}

/**
 * @brief Creates new vector (t_xyz), the sum of vector a and vector b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_add(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), the result of vector a minus vector b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_subtract(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), the result of vector a * scaler b
 * 
 * @param a (t_xyz)
 * @param b (float)
 * @return t_xyz 
 */
t_xyz	v_mulitply(t_xyz a, float b)
{
	t_xyz	new;

	new.x = a.x * b;
	new.y = a.y * b;
	new.z = a.z * b;
	return (new);
}

/**
 * @brief Creates scalar number (float), dot product of vector a and vector b.
 * The dot product, also called scalar product, is a measure of how closely 
 * two vectors align, in terms of the directions they point.
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return float
 */
float	v_dot(t_xyz a, t_xyz b)
{
	float	new;

	new = a.x * b.x + a.y * b.y + a.z * b.z;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), cross product of vector a and vector b.
 * It results in a vector that is perpendicular to both vectors.
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_cross(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.y * b.z - b.y * a.z;
	new.y = b.x * a.z - a.x * b.z;
	new.z = a.x * b.y - b.x * a.y;
	return (new);
}

float	v_magnitude(t_xyz a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y,2) + pow(a.z, 2)));
}

void	v_normalize(t_xyz *a)
{
	float mag = v_magnitude(*a);
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
}
