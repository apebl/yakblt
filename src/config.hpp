#ifndef __BLT_CONFIG_H__
#define __BLT_CONFIG_H__

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**
 * DEBUG:
 *
 * This macro is defined if debug mode is enabled.
 */

#define TITLE "yakblt: Just A Bullet Game"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define VSYNC false
#define FRAMERATE 60
#define FIXED_DELTA (1.0 / FRAMERATE)

#define WORLD_WIDTH 960
#define WORLD_HEIGHT 720
#define WORLD_CIRCLE_RADIUS 600
#define GRID_TILE_WIDTH 100
#define GRID_TILE_HEIGHT 100

#define WORLD_RECT (FloatRect(0, 0, WORLD_WIDTH, WORLD_HEIGHT))
#define WORLD_CENTER_X (WORLD_WIDTH*0.5f)
#define WORLD_CENTER_Y (WORLD_HEIGHT*0.5f)
#define WORLD_CENTER (Vector2f(WORLD_CENTER_X, WORLD_CENTER_Y))

#endif
