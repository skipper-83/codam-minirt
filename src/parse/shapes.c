/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/08 21:03:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	set_procedure(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > TEXT_PROCEDURES)
		exit_error("error texture procedure", "id invallid", scene);
	return (n);
}

int	set_bump_procedure(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > BUMP_PROCEDURES)
		exit_error("error bump map", "id invallid", scene);
	return (n);
}

float	set_albedo(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error albedo", "provide positive integer", scene);
	return ((float)n / 100.0);
}

float	set_specular_size(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error specular size", "provide positive integer", scene);
	return (300 / (float)n);
}

float	set_specular_weight(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error specular weight", "provide positive integer", scene);
	return ((float)n / 100);
}

mlx_texture_t	*set_texture(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > NR_TEXTURES)
		exit_error(ERROR_PNG, "texture id invallid", scene);
	if (n && n <= NR_TEXTURES)
		return (scene->textures[n - 1]);
	return (NULL);
}

void	set_surface_properties(char **param, t_object *object, int i, t_scene *s)
{
	object->text = set_texture(param[i++], s);
	object->bump = set_texture(param[i++], s);
	object->text_proc = set_procedure(param[i++], s);
	object->bump_proc = set_bump_procedure(param[i++], s);
	object->albedo = set_albedo(param[i++], s);
	object->specular_size = set_specular_size(param[i++], s);
	object->specular_weight = set_specular_weight(param[i++], s);
	set_rgb(param[i], object->rgb, s);
}

/**
 * @brief Initialises a plane in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_plane(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_plane;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 11)
		exit_error(ERROR_PLANE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_plane = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, scene);
	new_plane->id = PL;
	new_plane->pOrigin = set_xyz(param[1], scene);
	new_plane->vNormal = set_xyz(param[2], scene);
	new_plane->rotate_matrix = m44_init();
	set_surface_properties(param, new_plane, 3, scene);
	new_node->content = (void *)new_plane;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mPlane config:\t\t  \033[0m", 1);
}

/**
 * @brief Initialises a cylinder in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_cylinder(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_cylinder;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 13)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cylinder = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, scene);
	new_cylinder->id = CY;
	new_cylinder->pOrigin = set_xyz(param[1], scene);
	new_cylinder->vNormal = v_normalize(set_xyz(param[2], scene));
	new_cylinder->diameter = to_float(param[3], scene);
	new_cylinder->height = to_float(param[4], scene);
	new_cylinder->rotate_matrix = m44_init();
	set_surface_properties(param, new_cylinder, 5, scene);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
}

/**
 * @brief Initialises a cylinder in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_cone(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_cone;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 13)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cone = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cone)
		exit_error(ERROR_MEM, NULL, scene);
	new_cone->id = CO;
	new_cone->pOrigin = set_xyz(param[1], scene);
	new_cone->vNormal = v_normalize(set_xyz(param[2], scene));
	new_cone->diameter = to_float(param[3], scene);
	new_cone->height = to_float(param[4], scene);
	new_cone->rotate_matrix = m44_init();
	set_surface_properties(param, new_cone, 5, scene);
	new_node->content = (void *)new_cone;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCone config:\t\t  \033[0m", 1);
}



/**
 * @brief Initialises a sphere in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_sphere(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_sphere;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 11)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_sphere = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_sphere)
		exit_error(ERROR_MEM, NULL, scene);
	new_sphere->id = SP;
	new_sphere->vNormal = v_create(0, 1, 0);
	new_sphere->pOrigin = set_xyz(param[1], scene);
	new_sphere->diameter = to_float(param[2], scene);
	new_sphere->rotate_matrix = m44_init();
	set_surface_properties(param, new_sphere, 3, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}
