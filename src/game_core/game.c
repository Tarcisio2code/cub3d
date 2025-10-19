/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:06:27 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 15:02:42 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_core.h"
#include "../../inc/rendering.h"

static int	loop_control(t_game *game);
static int	game_loop(t_game *game);
static int	over_game_loop(t_game *game);

void	start_game(t_game *game)
{
	init_core(game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_wheel, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_loop_hook(game->mlx, loop_control, game);
	mlx_loop(game->mlx);
}

static int	loop_control(t_game *game)
{
	if (!game->is_running)
		return (mlx_loop_end(game->mlx), 0);
	if (!game->game_over)
		game_loop(game);
	else
		over_game_loop(game);
	return (0);
}

static int	game_loop(t_game *game)
{
	void	*window_image;

	if (game->refresh_screen)
	{
		ft_memset(game->win_img.data, 0, game->win_img.size_line * WIN_HEIGHT);
		render_3d_scene(game);
		if (game->show_mini_map)
			draw_mini_map(game);
		if (game->show_help_screen)
			render_help_screen(game);
		window_image = game->win_img.img_ptr;
		mlx_put_image_to_window(game->mlx, game->win, window_image, 0, 0);
		if (!game->game_over)
			game->refresh_screen = false;
	}
	animate_door(game);
	return (0);
}

static int	over_game_loop(t_game *game)
{
	void	*window_image;

	if (game->refresh_screen)
	{
		ft_memset(game->win_img.data, 0, game->win_img.size_line * WIN_HEIGHT);
		render_3d_scene(game);
		if (game->show_mini_map)
			draw_mini_map(game);
		render_game_over_screen(game);
		window_image = game->win_img.img_ptr;
		mlx_put_image_to_window(game->mlx, game->win, window_image, 0, 0);
		game->refresh_screen = false;
	}
	return (0);
}
