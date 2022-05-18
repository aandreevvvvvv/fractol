/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:03:54 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:27:09 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int	julia(t_complex pos, t_fractal *fractal)
{
	int		i;
	double	real_tmp;

	i = 0;
	while (i < MAX_ITERS)
	{
		if (pos.real * pos.real + pos.imag * pos.imag > 4)
			return (i);
		real_tmp = pos.real * pos.real - pos.imag * pos.imag + fractal->c.real;
		pos.imag = 2.0 * pos.real * pos.imag + fractal->c.imag;
		pos.real = real_tmp;
		++i;
	}
	return (i);
}

int	mandelbrot(t_complex pos, t_fractal *fractal)
{
	int			i;
	t_complex	z;
	double		real_tmp;

	fractal->c.real++;
	i = 0;
	z = init_complex(0, 0);
	while (i < MAX_ITERS)
	{
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		real_tmp = z.real * z.real - z.imag * z.imag + pos.real;
		z.imag = 2.0 * z.real * z.imag + pos.imag;
		z.real = real_tmp;
		++i;
	}
	return (i);
}

int	ship(t_complex pos, t_fractal *fractal)
{
	int			i;
	t_complex	z;
	double		re_tmp;

	fractal->c.real++;
	i = 0;
	z = init_complex(0, 0);
	while (i < MAX_ITERS)
	{
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		re_tmp = z.real * z.real - z.imag * z.imag + pos.real;
		z.imag = pos.imag - fabs(2.0 * z.real * z.imag);
		z.real = re_tmp;
		++i;
	}
	return (i);
}
