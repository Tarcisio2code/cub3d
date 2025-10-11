/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:29:45 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 09:00:47 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_core.h" 
#include "../../inc/rendering.h"

static void	render_ceiling(t_game *game, int x, int wall_top);
static void	render_wall(t_game *game, int x, int top, int bottom);
static void	render_floor(t_game *game, int x, unsigned int wall_bottom);

void	render_3d_scene(t_game *game)
{
	int		x;
	t_ray	*ray;

	x = 0;
	ray = &game->ray;
	while (x < WIN_WIDTH)
	{
		init_ray(game, ray, x);
		calc_step_and_side_dist(ray);
		perform_dda(game, ray);
		calc_wall_height(ray);
		render_ceiling(game, x, ray->draw_start);
		render_wall(game, x, ray->draw_start, ray->draw_end);
		render_floor(game, x, ray->draw_end);
		x++;
	}
}

static void	render_ceiling(t_game *game, int x, int wall_top)
{
	int	y;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_top > WIN_HEIGHT)
		wall_top = WIN_HEIGHT;
	y = 0;
	while (y >= 0 && y < wall_top)
	{
		put_pixel(&game->win_img, x, y, argb_color(game->ceiling_color));
		y++;
	}
}

static void	render_wall(t_game *game, int x, int top, int bottom)
{
	t_image	*tex;
	t_ray	*ray;
	int		y;
	int		color;
	double	step;

	ray = &game->ray;
	tex = get_wall_texture(game, ray);
	calc_texture_x(&game->ray, tex);
	step = 1.0 * tex->height / ray->line_height;
	ray->tex_pos = (top - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = top;
	while (y < bottom)
	{
		if (y >= 0 && y < WIN_HEIGHT)
		{
			ray->tex_y = (int)ray->tex_pos & (tex->height - 1);
			color = get_texture_color(tex, ray->tex_x, ray->tex_y);
			put_pixel(&game->win_img, x, y, color);
		}
		ray->tex_pos += step;
		y++;
	}
}

static void	render_floor(t_game *game, int x, unsigned int wall_bottom)
{
	int	y;

	y = wall_bottom;
	while (y >= 0 && y < WIN_HEIGHT)
	{
		put_pixel(&game->win_img, x, y, argb_color(game->floor_color));
		y++;
	}
}
