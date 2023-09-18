/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:38:40 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/18 23:12:52 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "errors.h"
# include "types.h"
# include "parser.h"
# include "test.h"
# include <stdbool.h>
# include <stdlib.h>


# include <stdio.h> //remove

# define EPSILON exp(-21)


/**
 * @brief ray struct that contains:
 * @param	p1 (t_xyz) camera origin
 * @param	p2 (t_xyz) camera direction
 * @param	p1_p2 (t_xyz) distance between p1 and p2
 */
typedef struct s_ray
{
	t_xyz	p1;
	t_xyz	p2;
	t_xyz	p1_p2;
}	t_ray;

/**
 * @brief struct containing two floats
 * @param	t0 (float)
 * @param	t1 (float)
 */
typedef struct s_t
{
	float	t0;
	float	t1;
}			t_t;

/**
 * @brief struct with relevant render information for each pixel
 * @param	type		(enum)
 * @param	tNear		(float)
 * @param	hitobject	(void *)
 */
typedef struct s_renderInfo
{
	// enum		type;
	float		tNear;
	t_object 	*hitObject;
}				t_rederInfo;

// fuction pointer for intersection test functions of different objects
typedef bool f_testHit(t_ray cameraRay, t_object *object, float *t);

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);

// main.c
t_scene	*init_scene(char *file);

// objects/camera.c
t_ray	ray(t_xyz p1, t_xyz p2);
t_ray	generate_ray(t_scene * scene, int x, int y);
void	update_camera(t_scene *scene);



// render.c
void	render(t_scene *scene);

// objects
bool	testHitSP(t_ray castRay, t_object *sphere, float *intPoint);
// bool	testHitPL(t_ray castRay, t_object *plane, float *intPoint);
// bool	testHitCY(t_ray castRay, t_object *cylinder, float *intPoint);

#endif
