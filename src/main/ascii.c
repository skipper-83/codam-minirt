/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:08:47 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/09 00:24:45 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_ascii(t_px *px, t_scene *scene)
{
	float	color_ratio;

	color_ratio = 0;
	if (px->hitobject)
	{
		px->color = get_color(px, scene);
		color_ratio = ((px->color >> 24) & 0xFF) / (float)255 * 0.299;
		color_ratio += ((px->color >> 16) & 0xFF) / (float)255 * 0.587;
		color_ratio += ((px->color >> 8) & 0xFF) / (float)255 * 0.114;
		ft_printf("\e[48;5;%im \e[0m", (int)(232 + color_ratio * 23));
	}
	else
		ft_printf("\e[48;5;232m \e[0m");
}

void	set_ascii_params(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->p_height)
		free(scene->pixels[i++]);
	free(scene->pixels);
	i = 0;
	scene->camera->aspect_ratio = (float)ASCII_WIDTH / ASCII_HEIGHT * 0.6;
	scene->camera->image_width = ASCII_WIDTH;
	scene->camera->image_height = ASCII_HEIGHT;
	scene->pixels = ft_calloc(ASCII_HEIGHT, sizeof(t_px *));
	scene->p_height = ASCII_HEIGHT;
	scene->p_width = ASCII_WIDTH;
	if (!scene->pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < ASCII_HEIGHT)
	{
		scene->pixels[i] = ft_calloc(ASCII_WIDTH, sizeof(t_px));
		if (!scene->pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
}

void	render_ascii(t_scene *scene)
{
	int	x;
	int	y;

	set_ascii_params(scene);
	y = 0;
	while (y < scene->camera->image_height)
	{
		x = 0;
		while (x < scene->camera->image_width)
		{
			get_pixel_data(scene->pixels[y] + x, scene, x, y);
			print_ascii(scene->pixels[y] + x, scene);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	exit_error(SUCCESS, NULL, scene);
}
