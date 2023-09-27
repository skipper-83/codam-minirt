/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:58:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/26 23:56:11 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

#define SHADOW_BIAS 0.001

float	v_square_of_self(t_xyz a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

int	trace_shadow(t_px *px, t_scene s)
{
	float				hp_distance;
	static t_hit_test	*hit_test[3] = {test_sphere, test_plane, test_cylinder};
	t_list				*objects;
	t_object			*object;

	objects = s.objects;
	while (objects)
	{
		object = (t_object *)objects->content;
		if (hit_test[object->id](*px, *object, &hp_distance))
		{
			if (px->hit_distance > hp_distance)
			{
				px->hitobject = object;
				px->hit_distance = hp_distance;
				return (1);
			}
		}
		objects = objects->next;
	}
	return (0);
}

float	get_shadow_ray(t_px *shadow_ray, t_light light, t_px *px)
{
	float	light_radius;
	
	shadow_ray->cam_origin = v_add(px->hitpoint, v_multiply(px->surface_normal, SHADOW_BIAS));
	shadow_ray->direction = v_subtract(light.origin, shadow_ray->cam_origin);
	light_radius = v_square_of_self(shadow_ray->direction);
	shadow_ray->hit_distance = sqrtf(light_radius);
	shadow_ray->direction.x /= shadow_ray->hit_distance ;
	shadow_ray->direction.y /= shadow_ray->hit_distance ;
	shadow_ray->direction.z /= shadow_ray->hit_distance ;
	return (light_radius);
}

int	loop_lights(t_scene scene, t_px *px)
{
	t_light	light;
	t_px	shadow_ray;
	float	light_radius;
	float	fallof;
	t_xyz	ratio;

	px->ratios = v_create(0, 0, 0);
	if (!scene.lights)
		return (0);
	while (scene.lights)
	{
		light = *(t_light *)scene.lights->content;
		ft_bzero(&shadow_ray, sizeof(shadow_ray));
		light_radius = get_shadow_ray(&shadow_ray, light, px);
		fallof = ((light.brightness * 1000 / (4 / M_PI * light_radius)));
		if (trace_shadow(&shadow_ray, scene))
			return (0);
		ratio = v_multiply(light.rgb_ratios, fallof);
		ratio = v_multiply(ratio, v_dot(shadow_ray.direction, px->surface_normal));
		ratio = v_multiply(ratio, 0.18 / M_PI);
		px->ratios = v_add(px->ratios, ratio);
		scene.lights = scene.lights->next;
	}
	return (1);
}
