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

void	paint(t_fractal *fractal)
{
	size_t	w;
	size_t	h;

	w = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			my_mlx_pixel_put(fractal->mlx, w, h, \
		get_color(fractal->depth[w][h], MAX_ITERS, fractal->color));
			++h;
		}
		++w;
	}
	mlx_put_image_to_window(fractal->mlx->mlx, fractal->mlx->win, \
							fractal->mlx->img, 0, 0);
}

void	draw(t_fractal *fractal)
{
	size_t	w;
	size_t	h;

	free_depth(fractal);
	fractal->depth = malloc(WIDTH * sizeof(int *));
	if (!fractal->depth)
		exit(1);
	w = 0;
	while (w < WIDTH)
	{
		fractal->depth[w] = malloc(HEIGHT * sizeof(int));
		if (!fractal->depth[w])
			exit(1);
		h = 0;
		while (h < HEIGHT)
		{
			fractal->depth[w][h] = fractal->formula(get_pos(w, h, fractal), \
																fractal);
			++h;
		}
		++w;
	}
	paint(fractal);
}
