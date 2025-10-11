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

void	validate_scene(t_game *game)
{
	validate_textures(game);
	if (game->floor_color[0] < 0 || game->floor_color[0] > 255
		|| game->floor_color[1] < 0 || game->floor_color[1] > 255 
		|| game->floor_color[2] < 0 || game->floor_color[2] > 255)
		exit_clean(ERR_RGB_COLOR, game);
	if (game->ceiling_color[0] < 0 || game->ceiling_color[0] > 255
		|| game->ceiling_color[1] < 0 || game->ceiling_color[1] > 255
		|| game->ceiling_color[2] < 0 || game->ceiling_color[2] > 255)
		exit_clean(ERR_RGB_COLOR, game);
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
