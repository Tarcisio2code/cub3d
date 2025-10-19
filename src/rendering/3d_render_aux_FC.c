
#include "../../inc/game_core.h" 
#include "../../inc/rendering.h" 

//return the coordinates in pixels of the wall-floor contact for a ray
void floor_wall_point(t_ray *ray, double *wx, double *wy)
{
    if (ray->side == 0)
    {
        if (ray->step_x < 0)
            *wx = (ray->map_x + 1) * TILE_SIZE;
        else 
            *wx = ray->map_x * TILE_SIZE;
        *wy = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
    }
    else
    {
        if (ray->step_y < 0)
            *wy = (ray->map_y + 1) * TILE_SIZE;
        else 
            *wy = ray->map_y * TILE_SIZE;   
        *wx = ray->pos_x + ray->perp_wall_dist * ray->dir_x;       
    }
}

void render_floor_ceil_color_column(t_game *game, int x, int top, int bot)
{
    int y;

    y = 0;
    while (y < top)
    {
        put_pixel(&game->win_img, x, y, argb_color(game->ceiling_color));
        y++;
    }
    y = bot;
    while (y < WIN_HEIGHT)
    {
        put_pixel(&game->win_img, x, y, argb_color(game->floor_color));
        y++;
    }
}

t_floor_params floor_row_params(t_game *game, t_ray *r)
{
    double  wx;
    double  wy;
    t_floor_params  p;

    floor_wall_point(r, &wx, &wy);
    p.px = game->player.x / TILE_SIZE;
    p.py = game->player.y / TILE_SIZE;
    p.bx = wx / TILE_SIZE;
    p.by = wy / TILE_SIZE;
    p.wall_dist_tiles = r->perp_wall_dist / TILE_SIZE;
    if (p.wall_dist_tiles <= 0.0)
        p.wall_dist_tiles = 1e-6;
    return (p);
}

void    draw_floor_row(t_game *game, int x, int y, t_floor_params *p, bool textured)
{
    double  denom;
    double  rowDist;
    double  w;
    double  worldX;
    double  worldY;
    int     tx;
    int     ty;
    int     col;

    denom = y - WIN_HEIGHT / 2.0;
    if (denom == 0.0)
        return ;
    rowDist = (WIN_HEIGHT / 2.0) / denom;
    w = rowDist / p->wall_dist_tiles;
    worldX = (1.0 - w) * p->px + w * p->bx;
    worldY = (1.0 - w) * p->py + w * p->by;
    if (textured)
    {
        tx = (int)(worldX * game->textures.floor.width);
        ty = (int)(worldY * game->textures.floor.height);
        col = get_texture_color(&game->textures.floor, tx, ty);
        put_pixel(&game->win_img, x, y, col);
    }
    else
        put_pixel(&game->win_img, x, y, argb_color(game->floor_color));
}

void    draw_ceiling_row(t_game *game, int x, int y2, t_floor_params *p, bool textured)
{
    double  denom;
    double  rowDist;
    double  w;
    double  worldX;
    double  worldY;
    int     tx;
    int     ty;
    int     col;

    if (y2 < 0 || y2 >= WIN_HEIGHT)
        return ;
    denom = ((WIN_HEIGHT - 1 - y2) - WIN_HEIGHT / 2.0);
    if (denom == 0.0)
        return ;
    rowDist = (WIN_HEIGHT / 2.0) / denom;
    w = rowDist / p->wall_dist_tiles;
    worldX = (1.0 - w) * p->px + w * p->bx;
    worldY = (1.0 - w) * p->py + w * p->by;
    if (textured)
    {
        tx = (int)(worldX * game->textures.ceiling.width);
        ty = (int)(worldY * game->textures.ceiling.height);
        col = get_texture_color(&game->textures.ceiling, tx, ty);
        put_pixel(&game->win_img, x, y2, col);
    }
    else
        put_pixel(&game->win_img, x, y2, argb_color(game->ceiling_color));
}

void render_floor_ceil_textured_column(t_game *game, int x, int top, int bot)
{
    bool use_floor;
    bool use_ceiling;
    t_floor_params p;
    int y;
    int y2;

    use_floor = game->textures.floor.img_ptr != NULL;
    use_ceiling = game->textures.ceiling.img_ptr != NULL;
    p = floor_row_params(game, &game->ray);
    y = bot;
    while (y < WIN_HEIGHT)
    {
        draw_floor_row(game, x, y, &p, use_floor);
        y2 = WIN_HEIGHT -1 - y;
        if (y2 >= 0 && y2 < top)
            draw_ceiling_row(game, x, y2, &p, use_ceiling);
        y++;
    }
    y = 0;
    if (!use_ceiling)
    {
        while (y < top)
        {
            put_pixel(&game->win_img, x, y, argb_color(game->ceiling_color));
            y++;
        }
    }
}

void render_floor_ceil_column(t_game *game, int x, int top, int bot)
{
    if (!game->textures.floor.img_ptr && !game->textures.ceiling.img_ptr)
    {
        render_floor_ceil_color_column(game, x, top, bot);
        return ;
    }
    render_floor_ceil_textured_column(game, x, top, bot);
}