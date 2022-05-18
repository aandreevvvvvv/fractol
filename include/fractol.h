/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:10:12 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/18 16:37:06 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>

# define WIDTH 500
# define HEIGHT 500
# define MAX_ITERS 150
# define ZOOM_STEP 0.8
# define MOVE_STEP 5

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_fractal
{
	int			(*formula)(t_complex pos, struct s_fractal *fractal);
	t_complex	c;
	t_mlx		*mlx;
	t_complex	corner;
	double		zoom;
	int			color;
	int			**depth;
}	t_fractal;

t_fractal		*parse(int argc, char **argv);
t_mlx			*init(t_fractal *fractal);
void			draw(t_fractal *fractal);
void			paint(t_fractal *fractal);

void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
void			write_help(void);
void			write_types(void);
void			free_depth(t_fractal *fractal);
int				free_all(t_fractal *fractal);

int				julia(t_complex z, t_fractal *fractal);
int				mandelbrot(t_complex z, t_fractal *fractal);
int				ship(t_complex z, t_fractal *fractal);

t_complex		init_complex(double real, double imag);

#endif