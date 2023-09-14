/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 10:58:21 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Creates and initiates ambient lighting in the scene
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param data (t_scene) passed to clean up when input is invallid
 */
void	ambient(char **param, t_scene *data)
{
	int	i;

	if (data->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lighting", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->ambient = malloc(sizeof(t_ambient));
	if (!data->ambient)
		exit_error(ERROR_MEM, NULL, data);
	data->ambient->ratio = to_float(param[1], data);
	set_rgb(param[2], data->ambient->rgb, data);
	ft_putstr_fd("\033[34;1mAmbient lighting config: \033[0m", 1);
}

/**
 * @brief Creates and initiates the camera in the scene
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param data (t_scene) passed to clean up when input is invallid
 */
void	camera(char **param, t_scene *data)
{
	int	i;

	if (data->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->camera = malloc(sizeof(t_camera));
	if (!data->camera)
		exit_error(ERROR_MEM, NULL, data);
	data->camera->view_point = set_xyz(param[1], data);
	data->camera->orientation_v = set_xyz(param[2], data);
	data->camera->fov = ft_atoi(param[3]);
	if (!data->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, data);
	// printf("set to int:%d\n", data->camera->fov); // testing
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

/**
 * @brief Creates and initiates the light in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param data (t_scene) passed to clean up when input is invallid
 */
void	light(char **param, t_scene *data)
{
	int	i;

	if (data->light)
		exit_error(ERROR_SCENE, "redefinition of light", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->light = malloc(sizeof(t_light));
	if (!data->light)
		exit_error(ERROR_MEM, NULL, data);
	data->light->light_point = set_xyz(param[1], data);
	data->light->brightness = to_float(param[2], data);
	set_rgb(param[3], data->light->rgb, data);
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}