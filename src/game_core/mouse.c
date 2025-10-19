
#include "../../inc/game_core.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	dx;

	(void)y;
	if (!game->mouse_initted)
	{
		game->last_mouse_x = x;
		game->mouse_initted = true;
		return (0);
	}
	dx = x - game->last_mouse_x;
	game->last_mouse_x = x;
	if (dx != 0)
	{
		rotate_player(&game->player, dx * MOUSE_SENS);
		game->refresh_screen = true;
	}
	return (0);
}

static double  deg2rad(double d)
{
    return (d * PI / 180.0);
}

// Calculation of camera plane from current dir and desired FOV.
// plane = perp(dir) * tan(FOV/2)
// perp(dir) = (-dir_y, +dir_x)
void    set_fov(t_game *game, double fov_deg)
{
    double L;

    if (fov_deg < FOV_MIN)
        fov_deg = FOV_MIN;
    if (fov_deg > FOV_MAX)
        fov_deg = FOV_MAX;
    game->player.fov_deg = fov_deg;
    L = tan(deg2rad(fov_deg * 0.5));
    game->player.plane_x = -game->player.dir_y * L;
    game->player.plane_y = game->player.dir_x * L;
    game->refresh_screen = true;
}

int mouse_wheel(int wheel, int x, int y, t_game *game)
{
    (void)x;
    (void)y;
    if (wheel == BTN_WHEEL_UP)
        set_fov(game, game->player.fov_deg - FOV_STEP);
    else if (wheel == BTN_WHEEL_DOWN)
        set_fov(game, game->player.fov_deg + FOV_STEP);
    return (0);
}
