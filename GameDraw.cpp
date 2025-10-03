#include <DxLib.h>
#include "main.h"
#include "GameDraw.h"
#include "GameManager.h"

void drawTitleScene() {
    //タイトル画面じゃない場合は終了する
    if (game_status != GameStatus::TITLE) {
        return;
    }

    //スペースキーを押し、ゲームを開始する
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        game_status = GameStatus::RUNNING;
    }
}

void drawRunningScene() {
    //ゲーム中じゃない場合は、終了する
    if (game_status != GameStatus::RUNNING) {
        return;
    }

    //プレイヤーを動かす
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        player_data.obj_loc.x = player_data.obj_loc.x - player_data.obj_vec.x; //左キーで現在のベクトルX分、左に移動する（数値を引く）
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        player_data.obj_loc.x = player_data.obj_loc.x + player_data.obj_vec.x; //右キーで現在のベクトルX分、右に移動する（数値を足す）
    }

    //プレイヤーの描画
    DrawBox(
        player_data.obj_loc.x - player_data.width, player_data.obj_loc.y - player_data.height,
        player_data.obj_loc.x + player_data.width, player_data.obj_loc.y + player_data.height,
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
                    screen_x - MAP_PIXEL / 2, screen_y - MAP_PIXEL / 2, 
                    screen_x + MAP_PIXEL / 2, screen_y + MAP_PIXEL / 2, 
                    GetColor(255, 255, 255), 
                    true
                );
            }
        }
    }

}
