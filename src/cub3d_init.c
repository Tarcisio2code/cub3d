/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:14:30 by tsilva            #+#    #+#             */
/*   Updated: 2025/10/20 11:48:44 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_map(t_game *game);
static void	init_textures(t_game *game);

void	init_game_vars(char *filename, t_game *game)
{
	game->scene_file = open(filename, O_RDONLY);
	if (game->scene_file < 0)
		exit_clean(ERR_SCENE_FILE, 0);
	init_map(game);
	init_textures(game);
	game->mlx = NULL;
	game->win = NULL;
	game->floor_color[0] = -1;
	game->floor_color[1] = -1;
	game->floor_color[2] = -1;
	game->ceiling_color[0] = -1;
	game->ceiling_color[1] = -1;
	game->ceiling_color[2] = -1;
	game->player.spawn = '\0';
	game->player.x = -1;
	game->player.y = -1;
	game->has_doors = false;
	game->door.frames = NULL;
	game->door.exploding = false;
}

static void	init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_clean("ERR_MALLOC_MAP", NULL);
	game->map->data = NULL;
	game->map->line = NULL;
	game->map->height = 0;
	game->map->width = 0;
	game->map->walkable = false;
}

static void	init_textures(t_game *game)
{
	game->textures.north.img_ptr = NULL;
	game->textures.south.img_ptr = NULL;
	game->textures.east.img_ptr = NULL;
	game->textures.west.img_ptr = NULL;
	game->textures.north.path = NULL;
	game->textures.south.path = NULL;
	game->textures.east.path = NULL;
	game->textures.west.path = NULL;
	game->textures.help_screen.path = ft_strdup("./textures/help_screen.xpm");
	game->textures.game_over.path = ft_strdup("./textures/game_over.xpm");
	if (!game->textures.help_screen.path || !game->textures.game_over.path)
		exit_clean(ERR_MALLOC, game);
	game->textures.help_screen.img_ptr = NULL;
	game->textures.game_over.img_ptr = NULL;
}
