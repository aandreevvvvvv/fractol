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

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	fractal = parse(argc, argv);
	fractal->mlx = init(fractal);
	draw(fractal);
	mlx_loop(fractal->mlx->mlx);
}
