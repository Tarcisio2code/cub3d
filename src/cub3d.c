/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:30:13 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/20 12:25:02 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/parse_and_validation.h"
#include "../inc/game_core.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_entry(argv[1], argc);
	init_game_vars(argv[1], &game);
	parse_scene(&game);
	validate_scene(&game);
	start_game(&game);
	free_vars(&game);
	return (0);
}

//  Bonus list:
//  • Wall collisions. 							[ V ]
//  • Aminimap system.							[ V ]
//  • Doors which can open and close.			[ V ]
//  • Animated sprites.							[ ? ]
//  • Rotate the point of view with the mouse.  [   ]