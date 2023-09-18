/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:03:11 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/17 15:19:08 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"

void	print_camera(t_camera cam)
{
	printf("cam height\t:%f\n", cam.c_height);
	printf("cam width\t:%f\n", cam.c_width);
	printf("viewpoint\t:");
	print_vector(cam.view_point);
	printf("Orientation\t:");
	print_vector(cam.orientation_v);
	printf("lookA\t\t:");
	print_vector(cam.look_at);
	printf("Principal axis\t:");
	print_vector(cam.principal_axis);
	printf("center\t\t:");
	print_vector(cam.screenCentre);
	printf("U\t\t:");
	print_vector(cam.screenU);
	printf("V\t\t:");
	print_vector(cam.screenV);
	printf("aspect\t\t:%f\n", cam.aspect_ratio);
	printf("image_w\t\t:%i\n", cam.image_width);
	printf("image_h\t\t:%i\n", cam.image_height);
}

void	print_vector(t_xyz vector)
{
	printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);
}

char	*vtostr(t_xyz vector)
{
	return (ft_msprintf("%.3f,%.3f,%.3f", vector.x, vector.y, vector.z));
}

void	compare(char *result, char *check, int test)
{
	if (!ft_strcmp(result, check))
		printf("\033[32;1mTest %3d:\tOK!\n\033[0m", test);
	else
		printf("\033[31;1mTest %3d:\tKO!\033[0m\n   expected:\t%s\n   result:\t%s\n", test, check, result);
	free(result);
}