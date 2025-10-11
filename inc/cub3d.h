/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:11:36 by tsilva            #+#    #+#             */
/*   Updated: 2025/06/23 17:48:56 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <errno.h>
# include "../inc/structs.h"
# include "../lib/libft/src/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/mlx/mlx_int.h"
# include "../src/gnl/get_next_line.h"

# define ERR_SCENE_FILE		"Invalid or empty scene file."
# define ERR_ARG			"Invalid argument."
# define ERR_MALLOC			"Malloc failed."

void	check_entry(char *map_name, int argc);
void	exit_clean(char *error_msg, t_game *game);
void	init_game_vars(char *filename, t_game *game);
bool	check_file(char *filepath);
bool	is_file_empty(int fd);
bool	validate_texture_file(char *filepath);
void	free_vars(t_game *game);
void	free_textures(t_game *game);
void	free_str_array(char **str_array);
void	free_doors(t_game *game);
double	get_time(void);

#endif