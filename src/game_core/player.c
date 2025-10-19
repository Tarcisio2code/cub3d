/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:27:14 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 10:36:45 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/game_core.h"
#include "../../inc/rendering.h"

static void	check_and_move(t_player *player, t_map *map, t_directions dir);
static bool	set_pos(double *x, double *y, t_player *player, t_directions dir);
void	rotate_player(t_player *p, double r_speed);

void	set_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->x = game->player.col * TILE_SIZE + TILE_SIZE / 2.0;
	player->y = game->player.row * TILE_SIZE + TILE_SIZE / 2.0;
	if (player->spawn == 'N')
		player->angle = 3 * PI / 2;
	else if (player->spawn == 'S')
		player->angle = PI / 2;
	else if (player->spawn == 'W')
		player->angle = PI;
	else if (player->spawn == 'E')
		player->angle = 0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->fov_deg = 0.66;
	set_fov(game, player->fov_deg);
	//player->plane_x = -player->dir_y * 0.66;
	//player->plane_y = player->dir_x * 0.66;
}
// set_fov for zoom instead of hardcoding 0.66


void	move_player(t_game *game, t_directions dir)
{
	t_player	*player;

	player = &game->player;
	if (dir == MOVE_FORWARD)
		check_and_move(player, game->map, dir);
	else if (dir == MOVE_BACKWARD)
		check_and_move(player, game->map, dir);
	else if (dir == STRAFE_LEFT)
		check_and_move(player, game->map, dir);
	else if (dir == STRAFE_RIGHT)
		check_and_move(player, game->map, dir);
	else if (dir == TURN_LEFT)
		rotate_player(player, -ROTATE_SPEED);
	else if (dir == TURN_RIGHT)
		rotate_player(player, ROTATE_SPEED);
	else
		return ;
	game->refresh_screen = true;
}

static void	check_and_move(t_player *player, t_map *map, t_directions dir)
{
	double	new_x;
	double	new_y;

	if (!set_pos(&new_x, &new_y, player, dir))
		return ;
	if (!wall_collision(map, new_x + PLAYER_RADIUS, player->y) 
		&& !wall_collision(map, new_x - PLAYER_RADIUS, player->y))
		player->x = new_x;
	if (!wall_collision(map, player->x, new_y + PLAYER_RADIUS) 
		&& !wall_collision(map, player->x, new_y - PLAYER_RADIUS))
		player->y = new_y;
}

static bool	set_pos(double *x, double *y, t_player *player, t_directions dir)
{
	if (dir == MOVE_FORWARD)
	{
		*x = player->x + cos(player->angle) * MOVE_SPEED;
		*y = player->y + sin(player->angle) * MOVE_SPEED;
	}
	else if (dir == MOVE_BACKWARD)
	{
		*x = player->x - cos(player->angle) * MOVE_SPEED;
		*y = player->y - sin(player->angle) * MOVE_SPEED;
	}
	else if (dir == STRAFE_LEFT)
	{
		*x = player->x + sin(player->angle) * MOVE_SPEED;
		*y = player->y - cos(player->angle) * MOVE_SPEED;
	}
	else if (dir == STRAFE_RIGHT)
	{
		*x = player->x - sin(player->angle) * MOVE_SPEED;
		*y = player->y + cos(player->angle) * MOVE_SPEED;
	}
	else
		return (false);
	return (true);
}

void	rotate_player(t_player *p, double r_speed)
{
	double	old_x;
	double	old_y;

	old_x = p->dir_x;
	p->dir_x = p->dir_x * cos(r_speed) - p->dir_y * sin(r_speed);
	p->dir_y = old_x * sin(r_speed) + p->dir_y * cos(r_speed);
	old_y = p->plane_x;
	p->plane_x = p->plane_x * cos(r_speed) - p->plane_y * sin(r_speed);
	p->plane_y = old_y * sin(r_speed) + p->plane_y * cos(r_speed);
	p->angle += r_speed;
	if (p->angle < 0)
		p->angle += 2 * PI;
	if (p->angle >= 2 * PI)
		p->angle -= 2.0 * PI;
}
