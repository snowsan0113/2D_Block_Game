#include <DxLib.h>
#include "main.h"
#include "GameManager.h"
#include "GameDraw.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    SetWindowText("Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†Ç†");
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLORBIT);
    ChangeWindowMode(true);
    if (DxLib_Init() == -1) {
        MessageBox(NULL, "ÉQÅ[ÉÄÇèâä˙âªÇ∑ÇÈÇ±Ç∆Ç™Ç≈Ç´Ç‹ÇπÇÒÇ≈ÇµÇΩÅB", NULL, MB_OK | MB_ICONERROR);
        DxLib_End();
        return -1;
    }
    SetBackgroundColor(0, 255, 0);
    SetDrawScreen(DX_SCREEN_BACK);

    while (true) {
        ClearDrawScreen();

        switch (game_status) {
        case GameStatus::TITLE : 
            drawTitleScene();
            break;
        case GameStatus::RUNNING :
            drawRunningScene();
            break;
        }

        ScreenFlip();
        WaitTimer(1000 / FPS);

        if (ProcessMessage() == -1) {
            return 0;
        }
    }

    DxLib_End();
    return 0;
}