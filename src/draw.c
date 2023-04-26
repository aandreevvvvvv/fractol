/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:33:36 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:30:43 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

static t_complex	get_pos(size_t w, size_t h, t_fractal *fractal)
{
	return (init_complex(fractal->corner.real + fractal->zoom * w / WIDTH, \
			fractal->corner.imag - fractal->zoom * h / HEIGHT));
}

static int	get_color(int depth, int max_depth, int color)
{
	if (depth == max_depth)
		return (create_trgb(0, 0, 0, 0));
	else
		return (create_trgb(0, (depth + color) % 16 * 16, \
							(depth + 3 * color + 4) % 16 * 16, \
							(depth + 7 * color + 8) % 16 * 16));
}

void	*calculate(void* arg)
{
	t_thread_state	*thread_state;
	size_t			w;
	size_t			h;

	thread_state = (t_thread_state *) arg;
	w = 0;
	while (w < WIDTH)
	{
		if (w % THREADS_COUNT != thread_state->thread_number)
		{
			++w;
			continue;
		}
		h = 0;
		while (h < HEIGHT)
		{
			thread_state->fractal->depth[w][h] = thread_state->fractal->formula(get_pos(w, h, thread_state->fractal), thread_state->fractal);
			my_mlx_pixel_put(thread_state->fractal->mlx, w, h, get_color(thread_state->fractal->depth[w][h], MAX_ITERS, thread_state->fractal->color));
			++h;
		}
		++w;
	}
	return (NULL);
}

void	draw(t_fractal *fractal)
{
	struct timeval	start_timeval;
	struct timeval	end_timeval;
	t_thread_state	*thread_states;
	pthread_t		*threads;
	size_t			thread_idx;

	threads = malloc(THREADS_COUNT * sizeof(pthread_t *));
	thread_states = malloc(THREADS_COUNT * sizeof(t_thread_state));
	gettimeofday(&start_timeval, NULL);
	thread_idx = 0;
	while (thread_idx < THREADS_COUNT)
	{
		thread_states[thread_idx].fractal = fractal;
		thread_states[thread_idx].thread_number = thread_idx;
		pthread_create(&threads[thread_idx], NULL, calculate, &thread_states[thread_idx]);
		++thread_idx;
	}
	thread_idx = 0;
	while (thread_idx < THREADS_COUNT)
	{
		pthread_join(threads[thread_idx++], NULL);
	}
	mlx_put_image_to_window(fractal->mlx->mlx, fractal->mlx->win, fractal->mlx->img, 0, 0);
	gettimeofday(&end_timeval, NULL);
	printf("calc time: %ld ms\n", (end_timeval.tv_sec - start_timeval.tv_sec) * 1000 + (end_timeval.tv_usec - start_timeval.tv_usec) / 1000);
	free(threads);
	free(thread_states);
}
