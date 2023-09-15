/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 08:17:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/15 21:32:10 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief tests whether two floating points are close to being equal
 * 
 * @param f1 
 * @param f2 
 * @return true 
 * @return false 
 */
bool	close_points(float f1, float f2)
{
	return (fabs(f1-f2) < EPSILON);
}

/**
 * @brief 
 * 1. comput the location of the screen point in world coordinates
 * 2. use this point and the pamera position to comput the ray
 * 
 * @param screen_x (float)
 * @param screen_y (float)
 * @return t_ray 
 */
bool	generate_ray(t_camera *cam, float screen_x, float screen_y, t_ray *cameraRay)
{
	t_xyz	screenWorldPart1;
	t_xyz	screenWorldCoord;
	
	screenWorldPart1 = v_add(cam->screenCentre, v_mulitply(cam->screenU, screen_x));
	screenWorldCoord = v_add(screenWorldPart1, v_mulitply(cam->screenV, screen_y));
	cameraRay->p1 = v_copy(cam->view_point);
	cameraRay->p2 = v_copy(screenWorldCoord);
	cameraRay->p1_p2 = v_subtract(cameraRay->p2, cameraRay->p1);
	return (1);
}

/**
 * @brief creates a ray based on start and endpoint
 * 
 * @param p1 (t_xyz) starting point of the cast ray
 * @param p2 (t_xyz) end point
 * @param p1_p2 (t_xyz) distance between p1 and p2
 * @return t_ray 
 */
t_ray	ray(t_xyz p1, t_xyz p2)
{
	t_ray	ray;

	ray.p1 = p1;
	ray.p2 = p2;
	ray.p1_p2 = v_subtract(p2, p1);
	return (ray);
}

void	render_sphere(t_scene *scene, t_sphere *sphere)
{
	uint32_t	x;
	uint32_t	y;
	float		xFact;
	float		yFact;
	t_ray		*cameraRay;
	int			localColor;
	float		normX;
	float		normY;

	x = 0;
	y = 0;

	xFact = 1.0 / ((float)scene->image->width / 2);
	yFact = 1.0 / ((float)scene->image->height / 2);
	cameraRay = malloc(sizeof(t_ray));
	if (!cameraRay)
		exit_error(ERROR_MEM, NULL, scene);	
	while (x < scene->image->width)
	{
		while (y < scene->image->height)
		{
			normX = ((float)x * xFact) - 1.0;
			normY = ((float)y * yFact) - 1.0;
			generate_ray(scene->camera, normX, normY, cameraRay);
			if (test_spIntersection(*cameraRay, &localColor, sphere))
				mlx_put_pixel(scene->image, x, y, localColor);
			else
				mlx_put_pixel(scene->image, x, y, 0 << 24 | 0 << 16 | 0 << 8 | 255);
			y++;
		}
		x++;
		y = 0;
	}
}