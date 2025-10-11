/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:07:01 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 15:20:30 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_vars(t_game *game)
{
	if (game->map->data)
		free_str_array(game->map->data);
	if (game->map->line)
		free(game->map->line);
	if (game->map)
		free(game->map);
	free_textures(game);
	free_doors(game);
	if (game->mlx)
	{
		if (game->win)
		{
			if (game->win_img.img_ptr)
				mlx_destroy_image(game->mlx, game->win_img.img_ptr);
			mlx_destroy_window(game->mlx, game->win);
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_textures(t_game *game)
{
	if (game->textures.north.path)
		free(game->textures.north.path);
	if (game->textures.south.path)
		free(game->textures.south.path);
	if (game->textures.east.path)
		free(game->textures.east.path);
	if (game->textures.west.path)
		free(game->textures.west.path);
	if (game->textures.north.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.north.img_ptr);
	if (game->textures.south.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.south.img_ptr);
	if (game->textures.east.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.east.img_ptr);
	if (game->textures.west.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.west.img_ptr);
	if (game->textures.game_over.path)
		free(game->textures.game_over.path);
	if (game->textures.game_over.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.game_over.img_ptr);
	if (game->textures.help_screen.path)
		free(game->textures.help_screen.path);
	if (game->textures.help_screen.img_ptr)
		mlx_destroy_image(game->mlx, game->textures.help_screen.img_ptr);
}

void	free_str_array(char **str_array)
{
	int	i;

	if (!str_array)
		return ;
	i = 0;
	while (str_array[i])
		free(str_array[i++]);
	free(str_array);
	str_array = NULL;
}

void	free_doors(t_game *game)
{
	int	i;

	if (!game->door.frames)
		return ;
	i = 0;
	while (i <= game->door.last_frame)
	{
		if (game->door.frames[i])
		{
			if (game->door.frames[i]->path)
				free(game->door.frames[i]->path);
			if (game->door.frames[i]->img_ptr)
				mlx_destroy_image(game->mlx, game->door.frames[i]->img_ptr);
			free(game->door.frames[i]);
		}
		i++;
	}
	free(game->door.frames);
}
