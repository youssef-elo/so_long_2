/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:49:54 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/06/06 17:35:08 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// zeros all of the pointers in the struct to avoid any segfaults
// from freeing image pointers that werent allocated but are just garbage value
// before destroying the image i check if the pointer is valid or null
// but bcuz of garbage value i get valid response even i didnt allocate it
void	ft_zero(t_data *data)
{
	data->con = NULL;
	data->win = NULL;
	data->w = NULL;
	data->bg = NULL;
	data->p = NULL;
	data->c = NULL;
	data->e1 = NULL;
	data->e2 = NULL;
	data->map = NULL;
	data->coins = 0;
	data->moves = 0;
}

// initialise the connection to the X server and
void	initialize_struct(t_data *d, int map_size, char **map)
{
	int	w;
	int	h;

	d->con = mlx_init();
	if (!d->con)
	{
		ft_putstr("Error\nMlx connection failed.\n");
		ft_exit(d);
	}
	d->w = mlx_xpm_file_to_image(d->con, "textures/w.xpm", &w, &h);
	d->bg = mlx_xpm_file_to_image(d->con, "textures/b.xpm", &w, &h);
	d->p = mlx_xpm_file_to_image(d->con, "textures/p.xpm", &w, &h);
	d->c = mlx_xpm_file_to_image(d->con, "textures/c.xpm", &w, &h);
	d->e1 = mlx_xpm_file_to_image(d->con, "textures/ec.xpm", &w, &h);
	d->e2 = mlx_xpm_file_to_image(d->con, "textures/eo.xpm", &w, &h);
	d->win = mlx_new_window(d->con, d->map_w * 60, d->map_size * 60, "so_long");
	if (!d->win)
	{
		ft_putstr("Error\nWindow creation failed.\n");
		ft_exit(d);
	}
	check_struct(d, map_size, map);
}

// check if the struct initialazationwas successeful and count coins
void	check_struct(t_data *d, int map_size, char **map)
{
	int	i;
	int	j;

	if (!d->w || !d->bg || !d->p || !d->c || !d->e1 || !d->e2)
	{
		ft_putstr("Error\nCant open image(s).\n");
		ft_exit(d);
	}
	i = 0;
	j = 0;
	while (i < map_size)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				d->coins++;
			j++;
		}
		i++;
	}
}
