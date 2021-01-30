/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:51:13 by mdavid            #+#    #+#             */
/*   Updated: 2021/01/30 16:48:17 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include "libft.h"

/*
** FONCTION : ft_mlx_win_img
** PARAMETRES :
**		mlx [t_mlx*]: pointeur sur structure contenant les pointeurs pour la
					mlx et l'image
**		gdad [t_gdad*]: pointeur pour ...(?)
** DESCRIPTION :
**		Initialisation des pointeurs et variables relatifs à l'utilisation de
**		la mlx.
** RETOUR :
**		Rien.
*/

void	ft_mlx_win_img(t_mlx *mlx, t_gdad *gdad)
{
	mlx->w_ptr = mlx_new_window(mlx->init, W_LX, W_LY, NAME);
	mlx->w_title = NAME;
	mlx->w_lx = W_LX;
	mlx->w_ly = W_LY;
	mlx->img->ptr = mlx_new_image(mlx->init, IMG_LX, IMG_LY);
	mlx->img->pixels = (unsigned int*)mlx_get_data_addr(mlx->img->ptr,
		&(gdad->bpp), &(gdad->s_l), &(gdad->edian));
	mlx->img->nb_c = IMG_LX;
	mlx->img->nb_l = IMG_LY;
	mlx->img->origin.x = (int)(0.5 * IMG_LX);
	mlx->img->origin.y = (int)(0.5 * IMG_LY);
	mlx->img->c.x = (float)CX;
	mlx->img->c.y = (float)CY;
	mlx->img->max_iter = 100;
}

/*
** FONCTION : ft_mlx_hook_loop
** PARAMETRES : *mlx : ptr général.
** DESCRIPTION :
**		.
** RETOUR :
**		RIEN.
*/

void	ft_mlx_hook_loop(t_mlx *mlx)
{
	mlx_hook(mlx->w_ptr, 2, (1L << 0), ft_key_press, mlx);
	mlx_hook(mlx->w_ptr, 3, (1L << 1), ft_key_release, mlx);
	mlx_hook(mlx->w_ptr, 6, (1L << 6), ft_mouse_move, mlx);
	//mlx_mouse_hook(mlx.w_ptr, ft_mouse_event, mlx);
	mlx_hook(mlx->w_ptr, 17, (1L << 17), ft_close, mlx);
	mlx_loop(mlx->init);
}

/*
** FONCTION : ft_close
** PARAMETRES :
**		*mlx : ptr général contenant les struct wind/events/img.
** DESCRIPTION :
**		Détruit la window et quitte le programme.
** RETOUR :
**		RIEN.
*/

int		ft_close(t_mlx *mlx)
{
	ft_putendl("ici 1 ft_close");
	mlx_destroy_image(mlx->init, mlx->img->ptr);
	exit(0);
}

/*
** FONCTION: ft_mlx
** PARAMETRES:
**		frac [char*]: fractale précisé au moment de l'exécution.
** DESCRIPTION:
**		Initialisation des pointeurs relatifs à l'utilisation de la mlx
**		et manipulation des pixels de l'image pour construire le fractale.
*/

int		ft_mlx(char *frac)
{
	t_mlx	mlx;
	t_gdad	gdad;

	mlx.init = mlx_init();
	ft_mlx_win_img(&mlx, &gdad);
	mlx.img->fractal = frac;
	ft_fractal(frac, mlx.img);
	mlx_put_image_to_window(mlx.init, mlx.w_ptr, mlx.img->ptr, 0, W_LY / 10);
	ft_mlx_hook_loop(&mlx);
	return (0);
}

