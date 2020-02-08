/* config.hpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __YAKBLT_CONFIG_H__
#define __YAKBLT_CONFIG_H__

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**
 * DEBUG:
 *
 * This macro is defined if debug mode is enabled.
 */

#define TITLE "yakblt: A simple bullet-dodging game"
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
