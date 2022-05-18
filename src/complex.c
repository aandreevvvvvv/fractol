/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:29:14 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/16 19:09:20 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	init_complex(double real, double imag)
{
	t_complex	ans;

	ans.real = real;
	ans.imag = imag;
	return (ans);
}
