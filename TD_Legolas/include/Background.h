#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "MiniGfx.h"

// ------------------------------------------------------------
// Cloud structure (elliptical clouds)
// ------------------------------------------------------------
struct Cloud {
    int cx, cy;     // center
    int rx, ry;     // horizontal and vertical radii
};

// ------------------------------------------------------------
// Draw CASTLE + TOWER on the left side
// ------------------------------------------------------------
void drawCastle(SDLWindow& window, int tileSize, int windowH);

// ------------------------------------------------------------
// Draw ENTIRE BACKGROUND (sky, clouds, mountains, castle)
// ------------------------------------------------------------
void drawBackground(SDLWindow& window, int tileSize, int windowW, int windowH);

#endif // BACKGROUND_H
