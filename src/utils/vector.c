/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 08:31:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/16 14:13:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
 * @brief Creates new vector (t_xyz), 
 * the sum of vector a and vector b
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
 * @brief Creates new vector (t_xyz), 
 * the result of vector a minus vector b
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
 * @brief Creates new vector (t_xyz), 
 * the result of vector a * scaler b
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
 * @brief Creates new vector (t_xyz), 
 * the result of vector a / scaler b
 * 
 * @param a (t_xyz)
 * @param b (float)
 * @return t_xyz 
 */
t_xyz	v_devide(t_xyz a, float b)
{
	t_xyz	new;

	new.x = a.x / b;
	new.y = a.y / b;
	new.z = a.z / b;
	return (new);
}

/**
 * @brief Creates scalar number (float), dot product of vector a and vector b.
 * The dot product, also called scalar product, is a measure of how closely 
 * two vectors align, in terms of the directions they point. It is the projection
 * of one vector onto another
 * (A dot B)
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
 * It results in a vector that is perpendicular to the plane defined by a and b.
 * The order of the parameters affects (negates) the resulting vector.
 * Use hand to determine the orientation of resulting vector (c).
 * Index finger = a, middle finger = b, thumb = c
 * (A X B = C) (B X A = -C)
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
/**
 * @brief Calculates the length of a vector (|| V ||)
 * Vector lenth is also called norm
 * @param a 
 * @return float 
 */
float	v_magnitude(t_xyz a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y,2) + pow(a.z, 2)));
}

/**
 * @brief returns a normalized version of the vector that it is called with
 * by deviding all elements by the vector magnitude
 * @param a (t_xyz) vector to normalize
 */
t_xyz	v_normalize(t_xyz a)
{
	t_xyz new;
	float mag;
	float magInv;
	
	mag = v_magnitude(a);
	if (mag > 0)
	{	
		magInv = 1 / mag;
		new = v_create(a.x *= magInv, a.y *= magInv, a.z *= magInv);
		return new;
	}
	return v_copy(a);
}

/**
 * @brief normalizes the vector that it is called with
 * by deviding all elements by the vector magnitude
 * @param a (t_xyz) vector to normalize
 */
void	v_normalizep(t_xyz *a)
{
	float mag;
	float magInv;
	
	mag = v_magnitude(*a);
	if (mag > 0)
	{	
		magInv = 1 / mag;
		a->x *= magInv;
		a->y *= magInv;
		a->z *= magInv;
	}
}