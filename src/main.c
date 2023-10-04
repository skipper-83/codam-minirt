/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/04 11:38:21 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief checks that there are 2 arguments provided 
 * and that argv[1] has an .rt extension
 * @param argc 
 * @param argv 
 */
void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 2 || argc > 3)
		exit_error(ERROR_ARGS, USAGE_MSG, NULL);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH, USAGE_MSG, NULL);
	if (argc == 3 && !(!ft_strcmp(argv[2], "-ai") || !ft_strcmp(argv[2], "-a")))
		exit_error(ERROR_FLAG, USAGE_MSG, NULL);
}

void	init_pixels(t_scene *scene)
{
	int	i;

	i = 0;
	scene->pixels = ft_calloc(scene->p_height, sizeof(t_px *));
	if (!scene->pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < scene->p_height)
	{
		scene->pixels[i] = ft_calloc(scene->p_width, sizeof(t_px));
		if (!scene->pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
}

void	init_textures(t_scene *scene)
{
	scene->textures = ft_calloc(NR_TEXTURES, sizeof(mlx_texture_t *));
	if (!scene->textures)
		exit_error(ERROR_MEM, NULL ,scene);
	scene->textures[0] = mlx_load_png("src/textures/checker.png");
	scene->textures[1] = mlx_load_png("src/textures/wereld.png");
	scene->textures[2] = mlx_load_png("src/textures/rendering.png");
	if (!scene->textures[0] || !scene->textures[1] || !scene->textures[2])
		exit_error(ERROR_PNG, "error loading png" ,scene);
}

void	clean_scene(t_scene *scene)
{
	int	y;

	y = 0;
	ft_printf("i was called to clean\n");
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->objects, free);
	ft_printf("pixels add %p, p_beight %i\n", scene->pixels, scene->p_height);
	if (scene->pixels)
	{
		// ft_printf("cleaning pixelsn\n");
		while (y < scene->p_height)
		{
			// ft_printf("\t row %i\n", y);
			free(scene->pixels[y]);
			scene->pixels[y] = NULL;
			y++;
		}
	}
	free(scene->pixels);
	// scene->pixels = NULL;
	// free(scene);
	// scene = NU
}

/**
 * @brief initiates the scene based on the file contents
 * 
 * @param file (char **) input file with .rt extension
 * @return t_scene* 
 */
t_scene	*init_scene(char *file)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL, NULL);
	scene->p_width = IM_WIDTH;
	scene->p_height = IM_HEIGHT;
	scene->must_resize = false;
	init_textures(scene);
	parse_file(file, scene);
	if (!scene->ambient || !scene->camera)
		exit_error(ERROR_SCENE, "not all required elements provided", scene);
	ft_putendl_fd("\033[32;1m\nScene set up\n\033[0m", 2);
	init_pixels(scene);
	return (scene);
}

void	do_resize(void *param)
{
	t_scene 	*scene;
	mlx_image_t	*buf;
	int			i;

	scene = (t_scene *)param;
	if (scene->must_resize)
	{
		i = 0;
		if (scene->pixels)
		{
			while (i < scene->p_height)
			{
				free(scene->pixels[i]);
				scene->pixels[i] = NULL;
				i++;
			}
			free(scene->pixels);
			scene->pixels = NULL;
		}
		scene->p_width = scene->n_width;
		scene->p_height = scene->n_height;
		buf = scene->image;
		scene->image = mlx_new_image(scene->mlx, scene->p_width, scene->p_height);
		init_pixels(scene);
		cameraGeometry(scene);
		render_image(scene);
		image_to_window(scene);
		mlx_delete_image(scene->mlx, buf);
		scene->must_resize = 0;
	}
}

void	leaks_f()
{
	system("leaks -q miniRT");
}

int	main(int argc, char **argv)
{
	t_scene			*scene;

	// atexit(leaks_f); leaks!!
	check_args(argc, argv);
	scene = init_scene(argv[1]);
	if (argv[2] && (!ft_strcmp(argv[2], "-a") || !ft_strcmp(argv[2], "-ai")))
		renderAscii(scene);
	if (argc == 2 || !ft_strcmp(argv[2], "-ai"))
	{
		scene->mlx = mlx_init(scene->p_width, scene->p_height, "RAY'S TRACERS", true);
		if (!scene->mlx)
			exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
		scene->image = mlx_new_image(scene->mlx, scene->p_width, scene->p_height);
		render_image(scene);
		image_to_window(scene);
		mlx_key_hook(scene->mlx, key_input, scene);
		mlx_mouse_hook(scene->mlx, select_object, scene);
		mlx_resize_hook(scene->mlx, set_resize_flag, scene);
		mlx_loop_hook(scene->mlx, do_resize, scene);
		mlx_loop(scene->mlx);
	}
	// clean_scene(scene);
	return (0);
}
