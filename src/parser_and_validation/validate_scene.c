/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:04:41 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/29 16:42:16 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/parse_and_validation.h"

static	void	validate_textures(t_game *game);

static bool	has_full_color(int c[3])
{
	return ((c[0] >= 0 && c[0] <= 255)
		&& (c[0] >= 0 && c[0] <= 255)
		&& (c[0] >= 0 && c[0] <= 255));
}

void	validate_scene(t_game *game)
{
	bool	floor_has_color;
	bool	ceil_has_color;
	bool	floor_has_texpath;
	bool	ceil_has_texpath;

	validate_textures(game);
	floor_has_color = has_full_color(game->floor_color);
	ceil_has_color = has_full_color(game->ceiling_color);
	printf("Reached here\n");
	floor_has_texpath = (game->textures.floor.path &&
						validate_texture_file(game->textures.floor.path));
	ceil_has_texpath = (game->textures.ceiling.path &&
						validate_texture_file(game->textures.ceiling.path));
	if (!floor_has_color && !floor_has_texpath)
		exit_clean("error color or texture floor", game);
	if (!ceil_has_color && !ceil_has_texpath)
		exit_clean("error color or texture ceil", game);
	validate_map(game);
}

static	void	validate_textures(t_game *game)
{
	if (!game->textures.north.path || !game->textures.south.path
		|| !game->textures.west.path || !game->textures.east.path)
		exit_clean(ERR_TEXTURE_PATH, game);
	if (!validate_texture_file(game->textures.north.path) 
		|| !validate_texture_file(game->textures.south.path) 
		|| !validate_texture_file(game->textures.west.path)
		|| !validate_texture_file(game->textures.east.path))
		exit_clean(ERR_TEXTURE_FILE, game);
}
