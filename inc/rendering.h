/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:00:30 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 15:07:14 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

void	render_3d_scene(t_game *game);
void	put_pixel(t_image *img, int x, int y, int color);
int		argb_color(int *rgb_color);
void	init_ray(t_game *game, t_ray *ray, int x);
int		get_texture_color(t_image *tex, int x, int y);
void	calc_step_and_side_dist(t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_height(t_ray *ray);
void	calc_texture_x(t_ray *ray, t_image *tex);
t_image	*get_wall_texture(t_game *game, t_ray *ray);
void	draw_mini_map(t_game *game);
void	draw_transparent_background(t_game *game, int x, int y, int color);
void	draw_transparent_box(t_game *game, int s_x, int s_y, int color);
void	render_game_over_screen(t_game *game);
void	render_help_screen(t_game *game);
void    floor_wall_point(t_ray *ray, double *wx, double *wy);
void    render_floor_ceil_column(t_game *game, int x, int top, int bot);

#endif