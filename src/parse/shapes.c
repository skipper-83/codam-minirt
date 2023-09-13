/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 11:47:40 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	sphere(char **param, t_scene *data)
{
	t_list		*new_node;
	t_sphere	*new_sphere;
	int			i;

	i = 0;
	while(param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	new_node = malloc(sizeof(t_list));
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_node || !new_sphere)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], new_sphere->center, data);
	new_sphere->diameter = to_float(param[2], data);
	set_rgb(param[3], new_sphere->rgb, data);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&data->spheres, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}

void	plane(char **param, t_scene *data)
{
	t_list		*new_node;
	t_plane		*new_plane;
	int			i;

	i = 0;
	while(param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_PLANE, "incorrect number of arguments", data);
	new_node = malloc(sizeof(t_list));
	new_plane = malloc(sizeof(t_plane));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], new_plane->point, data);
	set_xyz(param[2], new_plane->normal_v, data);
	set_rgb(param[3], new_plane->rgb, data);
	new_node->content = (void *)new_plane;
	ft_lstadd_back(&data->planes, new_node);
	ft_putstr_fd("\033[34;1mPlane config:\t\t  \033[0m", 1);
}

void	cylinder(char **param, t_scene *data)
{
	t_list		*new_node;
	t_cylinder	*new_cylinder;
	int			i;

	i = 0;
	while(param[i])
		i++;
	if (i != 6)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", data);
	new_node = malloc(sizeof(t_list));
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], new_cylinder->center, data);
	set_xyz(param[2], new_cylinder->axis_v, data);
	new_cylinder->diameter = to_float(param[3], data);
	new_cylinder->height = to_float(param[4], data);
	set_rgb(param[5], new_cylinder->rgb, data);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&data->cylinders, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
}
