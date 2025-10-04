#define _CRT_SECURE_NO_WARNINGS
#include <DxLib.h>
#include "main.h"
#include "GameDraw.h"
#include "GameManager.h"
#include "GameUtil.h"

void drawTitleScene() {
    //タイトル画面じゃない場合は終了する
    if (game_status != GameStatus::TITLE) {
        return;
    }

    if (time % 100 < 80) drawTextC(WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.5, 
        "ゲームを開始するにはスペースキー", 30, 
            GetColor(255, 255, 255), GetColor(0, 0, 0)
        );

    //スペースキーを押し、ゲームを開始する
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        game_status = GameStatus::RUNNING;
        time = 0;
    }

    time++;
}

void drawRunningScene() {
    //ゲーム中じゃない場合は、終了する
    if (game_status != GameStatus::RUNNING) {
        return;
    }

    time++;
    char timer_text[100] = "";
    sprintf(timer_text, "%d", time);
    drawTextC(WINDOW_WIDTH - 50, 20, timer_text, 30, GetColor(255, 255, 255), GetColor(0, 0, 0));

    //プレイヤーを動かす
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        player_data.obj_loc.x = player_data.obj_loc.x - player_data.obj_vec.x; //左キーで現在のベクトルX分、左に移動する（数値を引く）
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        player_data.obj_loc.x = player_data.obj_loc.x + player_data.obj_vec.x; //右キーで現在のベクトルX分、右に移動する（数値を足す）
    }
    if (CheckHitKey(KEY_INPUT_SPACE) && isPlayerOnGround()) {
        player_data.obj_vec.y = 10;
    }

    jumpPlayer();

    //プレイヤーが画面外に出た場合はゲーム終了
    if (0 > player_data.obj_loc.x || player_data.obj_loc.x > WINDOW_WIDTH ||
        0 > player_data.obj_loc.y || player_data.obj_loc.y > WINDOW_HEIGHT) {
        game_status = GameStatus::ENDING;
        time = 0;
    }

    //プレイヤーの描画
    DrawBox(
        player_data.obj_loc.x - player_data.width / 2, player_data.obj_loc.y - player_data.height / 2,
        player_data.obj_loc.x + player_data.width / 2, player_data.obj_loc.y + player_data.height / 2,
        player_data.color,
        true
    );

    //マップの描画
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            //画面の座標に直すため、ピクセルを掛ける
            int screen_x = x * MAP_PIXEL; 
            int screen_y = y * MAP_PIXEL;    

            //1だった場合は、床ブロックに置き換える
            if (MAP[y][x] == 1) {
                DrawBox(
                    screen_x, screen_y, 
                    screen_x + MAP_PIXEL, screen_y + MAP_PIXEL, 
                    GetColor(255, 255, 255), 
                    true
                );
            }
        }
    }

}

void drawEndingScene() {
    if (game_status != GameStatus::ENDING) {
        return;
    }

    time++;
    drawTextC(WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.5, "ゲームオーバー", 30, GetColor(255, 255, 255), GetColor(0,0, 0));

    if (time > 200) {
        initGame();
        game_status = GameStatus::TITLE;
    }
}