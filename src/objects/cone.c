/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:23:25 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/19 21:28:30 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief Get abc cone
 * 		NB: the a_ha_ht vector is the angle, half angle and hypotenuse, 
 * 		shortened because the norme says its more legible that way.
 * 
 * @param ray 
 * @param cone 
 * @return t_xyz 
 */
t_xyz	get_abc_cone(t_px *ray, t_object *cone)
{
	// t_xyz	abc;
	// t_xyz	d;
	// t_xyz	co;
	// t_xyz	v;
	// t_xyz	a_ha_ht;

	// a_ha_ht.z =  sqrt(pow(cone->diameter * 0.5, 2) + pow(cone->height * 0.5, 2));  // hypothanuse
	// a_ha_ht.x = acos((cone->height * 0.5) / a_ha_ht.z); 							// angle
	// // ft_printf("angle: %f\n", a_ha_ht.x);
	// a_ha_ht.y = 1 + (((cone->diameter * 0.5) / (cone->height)) * (cone->diameter * 0.5));
	// d = ray->direction;
	// co = v_subtract(ray->cam_origin, cone->p_origin);
	// v = cone->v_normal;
	// abc.x = v_dot(d, d) - (a_ha_ht.y * pow(v_dot(v, d), 2));
	// abc.y = 2 * (v_dot(d, co) - (a_ha_ht.y * v_dot(v, d) * v_dot(v, co)));
	// abc.z = (v_dot(co, co) - ((a_ha_ht.y * pow(v_dot(v, co), 2))));

	t_xyz	abc;
	t_xyz	co;
	float	factor;

	factor = 1 + ((cone->diameter * 0.25) / (cone->height)) * (cone->diameter * 0.5);
	co = v_subtract(ray->cam_origin, cone->p_origin);
	abc.x = v_dot(ray->direction, ray->direction) \
			- (pow(v_dot(ray->direction, cone->v_normal), 2) * factor);
	abc.y = 2 * (v_dot(ray->direction, co) \
			- (v_dot(ray->direction, cone->v_normal) \
			* v_dot(co, cone->v_normal) * factor));
	abc.z = v_dot(co, co) \
			- (pow(v_dot(co, cone->v_normal), 2) * factor);

	return (abc); 
}

int	test_cone(t_px *ray, t_object *cone, float *hp_info)
{
	t_xyz	abc;
	t_xyz	orig_to_center;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cone->p_origin);
	abc = get_abc_cone(ray, cone);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cone->v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cone->v_normal);
	hit_param[3] = (v_dot(ray->direction, cone->v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cone->v_normal);
	return (set_hp_info(hit_param, cone->height, hp_info));
}

int	get_cone_surface_data(t_object *co, t_px *px)
{
	t_xyz		hit_to_center;
	float		a;
	float		angle;

	angle = atan2(co->diameter * 0.5, co->height);
	a = px->hit_height * (angle * 0.5) * (angle * 0.5);
	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	if (px->cap)
		px->surface_normal = co->v_normal;
	else
	{

		hit_to_center = v_subtract(px->hitpoint, co->p_origin);
		px->surface_normal = \
				v_subtract(hit_to_center, v_multiply(co->v_normal, px->hit_height));
		px->surface_normal = \
				v_subtract(px->surface_normal, v_multiply(co->v_normal, a));
		v_normalizep(&px->surface_normal);
	}
	px->facing_ratio = v_dot(px->surface_normal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(px->surface_normal, -1);
	else
		px->facing_ratio *= -1;
	return (px->color);
}

t_xyz	get_uvcoord_co(t_object *co, t_px *px, t_scene *scene)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	z_plane;
	t_xyz	v;
	t_xyz	hp_in_object_space;

	ft_printf("cap? %i: %f, ", px->cap, px->hit_distance);
	// if (px->cap)
	// 	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	print_vector(px->hitpoint);
	x_plane = v_cross(co->v_normal, scene->camera->orientation_v);
	z_plane = v_cross(co->v_normal, x_plane);
	v = v_subtract(co->p_origin, px->hitpoint);
	hp_in_object_space.y = v_dot(co->v_normal, v);
	v_normalizep(&v);
	hp_in_object_space.x = v_dot(x_plane, v);
	hp_in_object_space.z = v_dot(z_plane, v);
	m44_multiply_vec3_dir(co->rotate_matrix, hp_in_object_space, \
												&hp_in_object_space);
	// if (!px->cap)
	// {
		uv.x = (atan2(hp_in_object_space.x, hp_in_object_space.z) \
												/ (2 * M_PI)) + 0.5;
		uv.y = (hp_in_object_space.y / co->height) + 1;
	// }
	// else
	// {
	// 	// v_normalizep(&hp_in_object_space);
	// 	print_vector(px->hitpoint);
	// 	uv.x = hp_in_object_space.x;
	// 	uv.y = hp_in_object_space.z;
	// 	uv.z = 0;
	// 	// print_vector(uv);
	// }
	// if (px->cap)
	// {
		
	// 	v_normalizep(&uv);
	// }
	return (uv);
}
