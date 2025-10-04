#include <DxLib.h>
#include "main.h"
#include "GameManager.h"

//ゲームの情報
GameStatus game_status = GameStatus::TITLE;
int time = 0;

//プレイヤーの情報
ObjectData player_data = { "Player", GetColor(0, 0, 0), {30, WINDOW_HEIGHT * 0.75, 0}, {5, 0, 5}, false, 20, 40, 0};

void jumpPlayer() {
	int gravity = 1;

	player_data.obj_loc.y -= player_data.obj_vec.y;
	player_data.obj_vec.y -= gravity;

	if (isPlayerOnGround()) {
		player_data.obj_vec.y = 0;
	}
}

//今床に付いているか
bool isPlayerOnGround() {
	int leftDownX = player_data.obj_loc.x - player_data.width / 2, leftDownY = player_data.obj_loc.y + player_data.height / 2; //左下
	int rightDownX = player_data.obj_loc.x + player_data.width / 2, rightDownY = player_data.obj_loc.y + player_data.height / 2; //右下

	int leftDown_value = MAP[leftDownY / MAP_PIXEL][leftDownX / MAP_PIXEL]; 
	int rightDown_value = MAP[rightDownY / MAP_PIXEL][rightDownX / MAP_PIXEL];

	DrawFormatString(20, 20, GetColor(255, 255, 255), "%d %d", leftDown_value, rightDown_value);
	if (leftDown_value == 1 || rightDown_value == 1) {
		return true;
	}

	return false;
}