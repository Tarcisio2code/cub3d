/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilva <tsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:20:41 by tsilva            #+#    #+#             */
/*   Updated: 2025/09/25 08:55:59 by tsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_core.h" 
#include "../../inc/rendering.h"

static void	destination_rgb(t_image *img, int idx, int bpp, unsigned int *rgb);
static void	source_rgb(int color, unsigned int *rgb);
static void	blend_colors(unsigned int *dst, unsigned int *src,
				unsigned char *out);

void	draw_transparent_background(t_game *game, int px, int py, int color)
{
	unsigned char	*out;
	unsigned int	src[3];
	unsigned int	dst[3];
	int				idx;
	int				bpp;

	if (px < 0 || py < 0 || px >= WIN_WIDTH || py >= WIN_HEIGHT)
		return ;
	bpp = game->win_img.bpp / 8;
	idx = py * game->win_img.size_line + px * bpp;
	destination_rgb(&game->win_img, idx, bpp, dst);
	source_rgb(color, src);
	out = (unsigned char *)game->win_img.data + idx;
	blend_colors(dst, src, out);
	if (bpp == 4)
		out[3] = 0;
}

static void	destination_rgb(t_image *img, int idx, int bpp, unsigned int *rgb)
{
	unsigned char	*data;

	data = (unsigned char *)img->data;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (bpp >= 3)
	{
		rgb[2] = data[idx + 2];
		rgb[1] = data[idx + 1];
		rgb[0] = data[idx + 0];
		return ;
	}
}

static void	source_rgb(int color, unsigned int *rgb)
{
	unsigned int	src;

	src = (unsigned int)color & 0x00FFFFFF;
	rgb[2] = (src >> 16) & 0xFF;
	rgb[1] = (src >> 8) & 0xFF;
	rgb[0] = src & 0xFF;
}

static void	blend_colors(unsigned int *dst, unsigned int *src,
			unsigned char *out)
{
	int	alpha;
	int	inv;

	alpha = 128;
	inv = 255 - alpha;
	out[2] = (unsigned char)((src[2] * alpha + dst[2] * inv) / 255);
	out[1] = (unsigned char)((src[1] * alpha + dst[1] * inv) / 255);
	out[0] = (unsigned char)((src[0] * alpha + dst[0] * inv) / 255);
}

void	draw_transparent_box(t_game *game, int s_x, int s_y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MINI_TILE_SIZE)
	{
		dx = 0;
		while (dx < MINI_TILE_SIZE)
		{
			draw_transparent_background(game, s_x + dx, s_y + dy, color);
			dx++;
		}
		dy++;
	}
}
