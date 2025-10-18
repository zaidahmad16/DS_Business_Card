#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zaidCard.h"   // your converted image header

#define NUM_BARS 64
#define SCREEN_W 256
#define SCREEN_H 192

typedef struct {
    int height;
    u16 color;
} Bar;

Bar bars[NUM_BARS];

// ------------------ DRAWING UTILITIES ------------------

void drawGrid(u16 *buffer) {
    u16 gridColor = RGB15(3, 3, 3);  // faint gridlines
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            if (y % 8 == 0 || x % 8 == 0)
                buffer[y * SCREEN_W + x] = gridColor;
            else
                buffer[y * SCREEN_W + x] = RGB15(0, 0, 0);
        }
    }
}

void drawBars(u16 *buffer) {
    int barWidth = SCREEN_W / NUM_BARS;
    for (int i = 0; i < NUM_BARS; i++) {
        int h = bars[i].height;
        for (int y = SCREEN_H - 1; y >= SCREEN_H - h; y--) {
            for (int x = i * barWidth; x < (i + 1) * barWidth; x++) {
                buffer[y * SCREEN_W + x] = bars[i].color;
            }
        }
    }
}

void randomizeBars(void) {
    for (int i = 0; i < NUM_BARS; i++) {
        bars[i].height = rand() % (SCREEN_H - 40);
        bars[i].color = RGB15(rand() % 31, rand() % 31, rand() % 31);
    }
}

// ------------------ COUNTING SORT VISUAL ------------------

void countingSortVisual(u16 *buffer) {
    int maxH = 0;
    for (int i = 0; i < NUM_BARS; i++)
        if (bars[i].height > maxH) maxH = bars[i].height;

    int *count = (int*)calloc(maxH + 1, sizeof(int));
    for (int i = 0; i < NUM_BARS; i++)
        count[bars[i].height]++;

    int idx = 0;
    for (int i = 0; i <= maxH; i++) {
        while (count[i]-- > 0) {
            bars[idx++].height = i;

            swiWaitForVBlank();
            drawGrid(buffer);
            drawBars(buffer);
            dmaCopy(buffer, VRAM_A, SCREEN_W * SCREEN_H * 2);
        }
    }
    free(count);
}

// ------------------ MAIN FUNCTION ------------------

int main(void) {
    srand(time(NULL));

    // --- Top Screen Setup (O(n) Sorting) ---
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);
    u16 *topBuffer = (u16*)malloc(SCREEN_W * SCREEN_H * 2);

    // --- Bottom Screen Setup (Business Card Image) ---
    videoSetModeSub(MODE_5_2D);
    vramSetBankC(VRAM_C_SUB_BG);

    int bg3 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    dmaCopy(zaidCardBitmap, bgGetGfxPtr(bg3), zaidCardBitmapLen);
    dmaCopy(zaidCardPal, BG_PALETTE_SUB, zaidCardPalLen);

    // --- Animation Loop ---
    while (1) {
        randomizeBars();
        countingSortVisual(topBuffer);
        swiWaitForVBlank();
    }

    free(topBuffer);
    return 0;
}
