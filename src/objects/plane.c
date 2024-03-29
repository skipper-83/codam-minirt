/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/15 12:12:45 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_plane(t_px *ray, t_object *plane, float *hp_info)
{
	float	denominator;
	t_xyz	orig_to_center;

	denominator = v_dot(plane->v_normal, ray->direction);
	if (fabsf(denominator) > EPSILON)
	{
		orig_to_center = v_subtract(plane->p_origin, ray->cam_origin);
		hp_info[0] = v_dot(plane->v_normal, orig_to_center) / denominator;
		if (hp_info[0] > 0)
			return (1);
	}
	hp_info[0] = 0;
	return (0);
}

int	get_plane_surface_data(t_object *plane, t_px *px)
{
	px->hitpoint = \
		v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	px->facing_ratio = v_dot(plane->v_normal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(plane->v_normal, -1);
	else
	{
		px->surface_normal = plane->v_normal;
		px->facing_ratio *= -1;
	}
	return (px->color);
}

/**
 * @brief Get the uvcoord pl object
 * Calculates texture uv by calculating 2 planes
 * 1 (x_plane): the cross product (getting the perendicular plane) of 
 * 				the plane normal with a random other vector.
 * 2 (y_plane): the cross product of x_plane with the plane normal
 * 				to be able to get a cross product for y_plane  
 * 				x_plane cannot be 0. If this is the case another random 
 * 				vector is used.
 * u and v are the distance of these planes to the hitpoint.
 * To solve the problem of infinity u and v are calculated takint the 
 * odulo of the resulting value.
 * 
 * @param pl 
 * @param px 
 * @param scene 
 * @return t_xyz 
 */
t_xyz	get_uvcoord_pl(t_object *pl, t_px *px, t_scene *scene)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	y_plane;

	(void)scene;
	x_plane = v_normalize(v_cross(pl->v_normal, v_create(0, 1, 0)));
	if (x_plane.x == 0 && x_plane.y == 0 && x_plane.z == 0)
		x_plane = v_normalize(v_cross(pl->v_normal, v_create(1, 0, 0)));
	y_plane = v_normalize(v_cross(x_plane, pl->v_normal));
	uv.x = fmod(v_dot(px->hitpoint, x_plane), pl->plane_x);
	uv.y = fmod(v_dot(px->hitpoint, y_plane), pl->plane_y);
	uv.x = 1 - ((uv.x + pl->plane_x) / (pl->plane_x * 2));
	uv.y = 1 - ((uv.y + pl->plane_y) / (pl->plane_y * 2));
	uv.z = 0;
	return (uv);
}
