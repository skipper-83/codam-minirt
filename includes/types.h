/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:32 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/18 23:13:20 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef	enum	e_type
{
	SP = 0,
	PL,
	CY
}	t_type;

typedef struct s_m44
{
	float	arr[4][4];
}	t_m44;

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

/**
 * @brief struct containing boundry values of a rectangle
 * @param	top
 * @param	rigth
 * @param	bottom;
 * @param	left;
 */
typedef struct s_window
{
	float	top;
	float	right;
	float	bottom;
	float	left;
}			t_window;

/**
 * @brief 	object struct containing parameters for each object type
 * 
 * @param	id (t_type) SP: sphere, PL: plane, CY: cylinder
 * @param	pOrigin (t_xyz) x,y,z coordinates of the object origin
 * @param	diameter (float) the diameter (of sphere or cylinder)
 * @param	rgb	(uint32_t[3]) R,G,B colors in range [0-255]
 * @param	vNormal (t_xyz) 33d normalized normal vector (of plane). 
 * @param	vAxis (t_xyz) 3d normalized vector of axis of cylinder. 
 * 			In range [-1,1] for each x,y,z axis
 * @param	height (float) the cylinder height
 */
typedef struct s_object
{
	t_type		id;
	t_xyz		pOrigin;
	float		diameter;
	uint32_t	rgb[3];
	t_xyz		vNormal;
	t_xyz		vAxis;
	float		height;
}				t_object;

/**
 * @brief Ambient lighting (id: "A")
 * @param	ratio (float) ambient lighting ratio in range [0.0,1.0]
 * @param	rgb	(uint32_t[3]) R,G,B colors in range [0-255]
 */
typedef struct ambient_s
{
	float		ratio;
	uint32_t	rgb[3];	
}				t_ambient;

/**
 * @brief Camera (id: "C")
 * @param	view_point (t_xyz) x,y,z coordinates of the camera's origing
 * @param	orientation_v (t_xyz) 3d normalized orientation vector. 
 * In range [-1,1] for each x,y,z axis
 * @param	fov[2]	(float) Horizontal and vertical field of view in degrees in range [0,180]
 * @param	principal_axis (t_xyz) vector from camera positon to lookAt position
 */
typedef struct camera_s
{
	t_xyz	view_point;		//used by albert
	t_xyz	orientation_v;	//used by albert
	int		fov;			//used by albert
	t_xyz	look_at;
	float	plane_dist;
	float	c_width;
	float	c_height;
	t_xyz	principal_axis;
	t_xyz	screenU;
	t_xyz	screenV;
	t_xyz	screenCentre;
// stuff added by albert
	t_xyz	origin;
	int		image_width;
	int		image_height;
	float	aspect_ratio;
	float	fov_scale;
	t_m44	cam2world;
}			t_camera;

/**
 * @brief Light (id: "L")
 * @param	light_point (t_xyz) x,y,z coordinates of the light point
 * @param	brightness (float) the light brightness ratio in range [0.0,1.0]
 * @param	rgb	(uint32_t[3]) R,G,B colors 
 * in range [0-255] (unused in mandatory part)
 */
typedef struct light_s
{
	t_xyz		light_point;
	float		brightness;
	uint32_t	rgb[3];
}				t_light;

#endif
