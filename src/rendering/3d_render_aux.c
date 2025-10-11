/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_render_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:01:02 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 09:01:03 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_core.h" 
#include "../../inc/rendering.h" 

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;
	int	bytes_per_pixel;
	int	size_line;

	bytes_per_pixel = img->bpp / 8;
	size_line = img->size_line;
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		offset = (y * size_line) + (x * bytes_per_pixel);
		if (offset < 0 || offset + bytes_per_pixel > WIN_HEIGHT * size_line)
			return ;
		*(unsigned int *)(img->data + offset) = color;
	}
}

int	argb_color(int *rgb_color)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = 255;
	r = rgb_color[0];
	g = rgb_color[1];
	b = rgb_color[2];
	return (((r & a) << 16) | ((g & a) << 8) | (b & a));
}

t_image	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (game->map->data[ray->map_y][ray->map_x] == 'D')
		return (game->door.frames[0]);
	else if (game->map->data[ray->map_y][ray->map_x] == 'X')
		return (game->door.frames[game->door.curr_frame]);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->textures.east);
		return (&game->textures.west);
	}
	if (ray->dir_y > 0)
		return (&game->textures.south);
	return (&game->textures.north);
}

int	get_texture_color(t_image *tex, int x, int y)
{
	int	*data;
	int	color;

	x = x % tex->width;
	y = y % tex->height;
	if (x < 0) 
		x = 0;
	if (y < 0) 
		y = 0;
	data = (int *)tex->data;
	color = data[y * tex->width + x];
	return (color);
}
