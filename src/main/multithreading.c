/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:21:20 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/10 17:15:38 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <pthread.h>  //check with Nicolas it is ok to use this

t_block	set_block(t_scene *scene, int y, int blocksize)
{
	t_block	block;

	block.scene = scene;
	block.y = y;
	block.y_max = y + blocksize;
	return (block);
}

pthread_t	*create_threads(t_scene *scene, pthread_t *threads, t_block *blocks)
{
	int			blocksize;
	int			y;
	int			i;

	i = 0;
	y = 0;
	blocksize = scene->p_height / THREADS;
	while (i < THREADS)
	{
		blocks[i] = set_block(scene, y, blocksize);
		y = y + blocksize;
		if (pthread_create(threads + i, NULL, &routine, &blocks[i]))
			exit_error(ERROR_THREAD, "failed to create thread\n", scene);
		i++;
	}
	return (threads);
}

void	join_threads(pthread_t *threads, t_scene *scene)
{
	int		i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(threads[i], NULL))
			exit_error(ERROR_THREAD, "failed to join thread\n", scene);
		i++;
	}
}

void	render_threads(t_scene *scene)
{
	pthread_t	*threads;
	t_block		*blocks;

	blocks = malloc(THREADS * sizeof(t_block));
	threads = malloc(THREADS * sizeof(pthread_t));
	if (!threads || !blocks)
		exit_error(ERROR_MEM, NULL, scene);
	create_threads(scene, threads, blocks);
	join_threads(threads, scene);
	free(threads);
	free(blocks);
}
