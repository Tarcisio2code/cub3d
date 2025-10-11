/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:03:43 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/22 18:24:17 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_core.h" 
#include "../../inc/rendering.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->pos_x = game->player.x;
	ray->pos_y = game->player.y;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
}

void	calc_step_and_side_dist(t_ray *r)
{
	r->dt_dist_x = fabs(1 / r->dir_x);
	r->dt_dist_y = fabs(1 / r->dir_y);
	r->map_x = (int)(r->pos_x / TILE_SIZE);
	r->map_y = (int)(r->pos_y / TILE_SIZE);
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->sd_dist_x = (r->pos_x / TILE_SIZE - r->map_x) * r->dt_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->sd_dist_x = (r->map_x + 1.0 - r->pos_x / TILE_SIZE) * r->dt_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->sd_dist_y = (r->pos_y / TILE_SIZE - r->map_y) * r->dt_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->sd_dist_y = (r->map_y + 1.0 - r->pos_y / TILE_SIZE) * r->dt_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (true)
	{
		if (ray->sd_dist_x < ray->sd_dist_y)
		{
			ray->sd_dist_x += ray->dt_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sd_dist_y += ray->dt_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0 || 
			ray->map_y >= game->map->height || 
			ray->map_x >= game->map->width)
			break ;
		if (game->map->data[ray->map_y][ray->map_x] == '1'
			|| game->map->data[ray->map_y][ray->map_x] == 'D'
			|| game->map->data[ray->map_y][ray->map_x] == 'X')
			break ;
	}
}

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ((ray->map_x * TILE_SIZE - ray->pos_x) 
				+ ((1 - ray->step_x) * TILE_SIZE / 2)) / ray->dir_x;
	else
		ray->perp_wall_dist = ((ray->map_y * TILE_SIZE - ray->pos_y)
				+ ((1 - ray->step_y) * TILE_SIZE / 2)) / ray->dir_y;
	ray->line_height = (int)(WIN_HEIGHT / (ray->perp_wall_dist / TILE_SIZE));
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
}

void	calc_texture_x(t_ray *ray, t_image *tex)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x /= TILE_SIZE;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x < 0) 
		|| (ray->side == 1 && ray->dir_y > 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}
