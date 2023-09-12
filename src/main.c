/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 18:35:42 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h> //remove

void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		exit_error(ERROR_ARGS, NULL);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH, NULL);
}

t_scene	*init_scene(char *file)
{
	t_scene *scene;
	char	*line;
	int		fd;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL);
	ft_memset(scene, 0, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
			parse_type(line, scene);
		else // what if error in gnl?
			break;
	}
	close(fd);
	return (scene);
}

int	main(int argc, char **argv)
{
	t_scene *scene;
	
	check_args(argc, argv);
	scene = init_scene(argv[1]);
	return (0);
}
