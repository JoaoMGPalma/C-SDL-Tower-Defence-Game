#include "Background.h"

void drawCastle(SDLWindow& window, int tileSize, int windowH)
{
    SDLColor stone1(120, 120, 140, 255);
    SDLColor stone2(100, 100, 120, 255);
    SDLColor doorColor(80, 50, 30, 255);
    SDLColor windowColor(30, 30, 50, 255);

    int castleWidth = 200;
    int castleHeight = 250;
    int castleX = 0;
    int castleY = windowH - castleHeight;

    int towerWidth = 80;
    int towerHeight = 320;
    int towerX = 0;
    int towerY = windowH - towerHeight;

    // Castle block
    for (int y = castleY; y < windowH; y += tileSize){
        for (int x = castleX; x < castleWidth; x += tileSize){
            SDLColor c = ((x / tileSize + y / tileSize) % 2 == 0) ? stone1 : stone2;
            window.setColor(c);
            window.drawFilledRect(x, y, tileSize, tileSize);
        }
    }

    // Tower block
    for (int y = towerY; y < windowH; y += tileSize){
        for (int x = towerX; x < towerWidth; x += tileSize){
            SDLColor c = ((x / tileSize + y / tileSize) % 2 == 0) ? stone1 : stone2;
            window.setColor(c);
            window.drawFilledRect(x, y, tileSize, tileSize);
        }
    }

    // Castle battlements
    for (int x = 0; x < castleWidth; x += tileSize * 2){
        window.setColor(stone2);
        window.drawFilledRect(x, castleY - tileSize, tileSize, tileSize);
    }

    // Tower battlements
    for (int x = 0; x < towerWidth; x += tileSize * 2){
        window.setColor(stone2);
        window.drawFilledRect(x, towerY - tileSize, tileSize, tileSize);
    }

    // Door
    int doorW = 40;
    int doorH = 70;
    int doorX = castleWidth / 2 - doorW / 2;
    int doorY = windowH - doorH;

    for (int y = doorY; y < windowH; y += tileSize){
        for (int x = doorX; x < doorX + doorW; x += tileSize){
            window.setColor(doorColor);
            window.drawFilledRect(x, y, tileSize, tileSize);
        }
    }

    // Tower windows
    int winW = 20;
    int winH = 20;
    int winX = towerWidth / 2 - winW / 2;

    for (int y = towerY + 60; y < towerY + 200; y += 60){
        for (int yy = y; yy < y + winH; yy += tileSize){
            for (int xx = winX; xx < winX + winW; xx += tileSize){
                window.setColor(windowColor);
                window.drawFilledRect(xx, yy, tileSize, tileSize);
            }
        }
    }
}

// ------------------------------------------------------------
// Draw ENTIRE BACKGROUND (sky, clouds, mountains, castle)
// ------------------------------------------------------------
void drawBackground(SDLWindow& window, int tileSize, int windowW, int windowH)
{
    // Sky gradient
    SDLColor skyTop(70, 120, 200, 255);
    SDLColor skyBottom(20, 40, 100, 255);

    // Clouds
    SDLColor cloud1(230, 230, 240, 255);
    SDLColor cloud2(210, 210, 220, 255);

    // Mountains
    SDLColor mountain1(29, 89, 26, 255);
    SDLColor mountain2(40, 130, 35, 255);

    // Dirt road colors
    SDLColor dirtDark(120, 85, 50, 255);     // deeper brown
    SDLColor dirtLight(160, 120, 80, 255);   // lighter dirt
    SDLColor dirtEdge(180, 150, 110, 255);   // dusty edges

    // Road height (2 tiles tall)
    int roadHeight = tileSize * 2;
    int roadStartY = windowH - roadHeight;

    // Cloud clumps
    std::vector<Cloud> clouds = {
        {150, 120, 70, 25},
        {350,  80, 90, 30},
        {600, 140, 60, 20}
    };

    // Draw sky, clouds, mountains, and road
    for (int y = 0; y < windowH; y += tileSize)
    {
        for (int x = 0; x < windowW; x += tileSize)
        {
            SDLColor color;

            // --- DIRT ROAD (bottom 2 tile rows) ---
            if (y >= roadStartY)
            {
                // Top row of road = lighter dirt
                if (y < roadStartY + tileSize)
                    color = dirtLight;
                else
                    color = dirtDark;

                // Dusty edges on left/right
                if (x < tileSize * 2 || x > windowW - tileSize * 3)
                    color = dirtEdge;

                window.setColor(color);
                window.drawFilledRect(x, y, tileSize, tileSize);
                continue;
            }

            // --- SKY GRADIENT ---
            float t = (float)y / windowH;
            color.r = skyTop.r * (1 - t) + skyBottom.r * t;
            color.g = skyTop.g * (1 - t) + skyBottom.g * t;
            color.b = skyTop.b * (1 - t) + skyBottom.b * t;
            color.a = 255;

            // --- CLOUDS ---
            for (const Cloud& c : clouds)
            {
                float dx = (float)(x - c.cx) / c.rx;
                float dy = (float)(y - c.cy) / c.ry;
                float dist = dx*dx + dy*dy;

                if (dist < 1.0f) { color = cloud1; break; }
                else if (dist < 1.4f) { color = cloud2; break; }
            }

            // --- MOUNTAINS ---
            int mountainHeight1 = windowH * 0.65 + (int)(20 * sin(x * 0.01));
            int mountainHeight2 = windowH * 0.75 + (int)(25 * sin(x * 0.02));

            if (y > mountainHeight2)
                color = mountain2;
            else if (y > mountainHeight1)
                color = mountain1;

            window.setColor(color);
            window.drawFilledRect(x, y, tileSize, tileSize);
        }
    }

    // Draw castle on top of background
    drawCastle(window, tileSize, windowH);
}
