/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/21 13:59:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <pthread.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# define ASCII_WIDTH  120
# define ASCII_HEIGHT 40

# define IM_WIDTH 512
# define IM_HEIGHT 512

# define	THREADS 4


typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_ambient		*ambient; // bij één ambient light kan dit op de stack?
	t_camera		*camera; // bij éen camera kan dit op de stack?
	t_light			*light;
	t_list			*objects;
	t_px			**pixels;
	int				p_width;
	int				p_height;
	t_object		*search;
}					t_scene;

typedef struct s_block
{
	t_scene		*scene;
	int			y;
	int			y_max;
}	t_block;

typedef void	t_f(char **param, t_scene *scene);

void	parse_type(char *line, t_scene *scene);
t_xyz	set_xyz(char *param, t_scene *scene);
void	set_rgb(char *param, uint32_t *rgb, t_scene *scene);
float	to_float(char *param, t_scene *scene);
void	init_ambient(char **param, t_scene *scene);
void	init_camera(char **param, t_scene *scene);
void	cameraGeometry(t_camera *cam);
void	init_light(char **param, t_scene *scene);
void	init_sphere(char **param, t_scene *scene);
void	init_plane(char **param, t_scene *scene);
void	init_cylinder(char **param, t_scene *scene);

#endif
