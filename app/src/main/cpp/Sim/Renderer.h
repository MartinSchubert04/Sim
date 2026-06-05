#pragma once

#include "pch.h"
#include "rlgl.h"
#include "Global.h"

#define LETTER_BOUNDRY_SIZE     0.25f
#define LETTER_BOUNDRY_COLOR    VIOLET


class Renderer {

public:
    static bool SHOW_LETTER_BOUNDRY;

    static void
    drawArrow(Vector3 startPos, Vector3 endPos, float radius, float coneLen, float sides = 8,
              Color color = RAYWHITE);

    static void
    drawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing,
               float lineSpacing, bool backface, Color tint);

    static void drawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
    static void drawLabel(const char* text, Vector3 worldPos, float fontSize, Camera3D camera, Color color);
    static void drawGrid(Vector3 pos, int slices, float spacing, float arrowRadius, float coneLen);

};
