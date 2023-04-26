/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:23:39 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:38:56 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "keys.h"
#include <stdlib.h>

static int	mouse_handler(int button, int x, int y, void *param)
{
	t_fractal	*frac;
	t_complex	p;

	frac = param;
	p = init_complex(frac->corner.real + frac->zoom * x / WIDTH, \
					frac->corner.imag - frac->zoom * y / HEIGHT);
	if (button == SCROLL_UP)
	{
		frac->zoom *= ZOOM_STEP;
		frac->corner.real = (frac->corner.real - p.real) * ZOOM_STEP + p.real;
		frac->corner.imag = (frac->corner.imag - p.imag) * ZOOM_STEP + p.imag;
	}
	else if (button == SCROLL_DOWN)
	{
		frac->zoom /= ZOOM_STEP;
		frac->corner.real = (frac->corner.real - p.real) / ZOOM_STEP + p.real;
		frac->corner.imag = (frac->corner.imag - p.imag) / ZOOM_STEP + p.imag;
	}
	else
		return (0);
	draw(frac);
	return (0);
}

static int	key_handler2(int key_code, t_fractal *frac)
{
	if (key_code == W)
		frac->c.imag /= 0.9;
	else if (key_code == S)
		frac->c.imag *= 0.9;
	else if (key_code == D)
		frac->c.real /= 0.9;
	else if (key_code == A)
		frac->c.real *= 0.9;
	else
		return (0);
	draw(frac);
	return (0);
}

static int	key_handler(int key_code, void *param)
{
	t_fractal	*frac;

	frac = param;
	if (key_code == ESC)
		free_all(frac);
	else if (key_code == C)
	{
		frac->color += 2;
		draw(frac);
		return (0);
	}
	else if (key_code == UP)
		frac->corner.imag += frac->zoom / MOVE_STEP;
	else if (key_code == DOWN)
		frac->corner.imag -= frac->zoom / MOVE_STEP;
	else if (key_code == RIGHT)
		frac->corner.real += frac->zoom / MOVE_STEP;
	else if (key_code == LEFT)
		frac->corner.real -= frac->zoom / MOVE_STEP;
	else
		return (key_handler2(key_code, frac));
	draw(frac);
	return (0);
}

t_mlx	*init(t_fractal *fractal)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		exit(1);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fractol");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
						&mlx->line_length, &mlx->endian);
	mlx_mouse_hook(mlx->win, mouse_handler, fractal);
	mlx_key_hook(mlx->win, key_handler, fractal);
	mlx_hook(mlx->win, 17, 0, free_all, fractal);
	return (mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
