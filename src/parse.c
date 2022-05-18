/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:34:51 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:29:43 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>

static double	den(long long n)
{
	double	ans;

	ans = 1;
	while (n)
	{
		n /= 10;
		ans /= 10;
	}
	return (ans);
}

static double	ft_atod(char *s)
{
	size_t		i;
	long long	integ;
	long long	frac;

	if (!s)
		return (0);
	i = 0;
	integ = ft_atol(s + i);
	while (s[i] && s[i] != '.')
		++i;
	if (!s[i])
		return (integ);
	++i;
	frac = ft_atol(s + i);
	return ((double)integ + (double)frac * den(frac));
}

static void	initialize(t_fractal *fractal)
{
	fractal->corner = init_complex(-1, 1);
	fractal->zoom = 2;
	fractal->color = 0;
	fractal->depth = NULL;
}

t_fractal	*parse(int argc, char **argv)
{
	t_fractal	*fractal;

	if (argc < 2 || argc > 4)
		write_help();
	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		exit(1);
	if (ft_streq(argv[1], "julia"))
		fractal->formula = &julia;
	else if (ft_streq(argv[1], "mandelbrot"))
		fractal->formula = &mandelbrot;
	else if (ft_streq(argv[1], "burning ship"))
		fractal->formula = &ship;
	else
		write_types();
	if (argc == 2)
		fractal->c = init_complex(-0.81, 0.156);
	else if (argc == 3)
		fractal->c = init_complex(ft_atod(argv[2]), 0);
	else
		fractal->c = init_complex(ft_atod(argv[2]), ft_atod(argv[3]));
	initialize(fractal);
	return (fractal);
}
