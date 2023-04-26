/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:16:09 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 15:46:50 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

void	init_depth(t_fractal *fractal)
{
	size_t	w;

	fractal->depth = malloc(WIDTH * sizeof(int *));
	if (!fractal->depth)
		exit(1);
	w = 0;
	while (w < WIDTH)
	{
		fractal->depth[w] = malloc(HEIGHT * sizeof(int));
		if (!fractal->depth[w])
			exit(1);
		++w;
	}
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	fractal = parse(argc, argv);
	fractal->mlx = init(fractal);
	init_depth(fractal);
	draw(fractal);
	mlx_loop(fractal->mlx->mlx);
}
