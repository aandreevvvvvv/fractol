/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:52:09 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:38:31 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

void	write_help(void)
{
	ft_putstr_fd("usage: fractol type [re] [im]\n", 1);
	exit(0);
}

void	write_types(void)
{
	ft_putstr_fd("supported types:\njulia\nmandelbrot\nburning ship\n", 1);
	exit(0);
}

void	free_depth(t_fractal *fractal)
{
	size_t	w;

	if (!fractal->depth)
		return ;
	w = 0;
	while (w < WIDTH)
	{
		free(fractal->depth[w]);
		++w;
	}
	free(fractal->depth);
}

int	free_all(t_fractal *fractal)
{
	free_depth(fractal);
	mlx_destroy_image(fractal->mlx->mlx, fractal->mlx->img);
	mlx_destroy_window(fractal->mlx->mlx, fractal->mlx->win);
	free(fractal->mlx);
	free(fractal);
	exit(0);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
