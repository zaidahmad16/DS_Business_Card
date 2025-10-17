#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BARS 64
#define MAX_HEIGHT 120

typedef struct {
    int height;
    u16 color;
} Bar;

void drawBars(u16* buffer, Bar* bars) {
    dmaFillHalfWords(RGB15(0, 0, 0), buffer, LCD_WIDTH * LCD_HEIGHT * 2); // clear screen
    int spacing = LCD_WIDTH / NUM_BARS;

    for (int i = 0; i < NUM_BARS; i++) {
        for (int h = 0; h < bars[i].height; h++) {
            int y = LCD_HEIGHT - h - 1;
            for (int w = 0; w < spacing - 1; w++) {
                buffer[y * LCD_WIDTH + i * spacing + w] = bars[i].color;
            }
        }
    }
}

void randomizeBars(Bar* bars) {
    for (int i = 0; i < NUM_BARS; i++) {
        bars[i].height = rand() % MAX_HEIGHT + 10;
        bars[i].color = RGB15(rand() % 31, (i * 2) % 31, 31 - (i % 31));
    }
}

void countingSortVisual(u16* buffer, Bar* bars) {
    int count[MAX_HEIGHT + 1] = {0};
    for (int i = 0; i < NUM_BARS; i++) count[bars[i].height]++;

    int index = 0;
    for (int h = 0; h <= MAX_HEIGHT; h++) {
        while (count[h] > 0) {
            bars[index].height = h;
            bars[index].color = RGB15(h % 31, 31 - (h % 31), (h * 2) % 31);
            index++;
            count[h]--;
            drawBars(buffer, bars);
            swiWaitForVBlank();
        }
    }
}

int main(void) {
    // --- Top screen (graphics only) ---
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);
    u16* screen = (u16*)VRAM_A;

    // --- Bottom screen (business card) ---
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);
    consoleDemoInit();

    iprintf("*****************************\n");
    iprintf("*        Zaid Ahmad          *\n");
    iprintf("*  Computer Science Student  *\n");
    iprintf("*  Carleton University       *\n");
    iprintf("*  Ottawa, Canada 🇨🇦        *\n");
    iprintf("*****************************\n\n");
    iprintf("📧 zaidahmad8060@gmail.com\n");
    iprintf("🌐 www.zaidahmad.dev\n");
    iprintf("📱 +1 (613) 262-2906\n");

    srand(time(NULL));
    Bar bars[NUM_BARS];

    while (1) {
        swiWaitForVBlank();
        randomizeBars(bars);
        drawBars(screen, bars);
        countingSortVisual(screen, bars);
        for (int i = 0; i < 90; i++) swiWaitForVBlank();
    }

    return 0;
}
