#include <DxLib.h>
#include "main.h"
#include "GameManager.h"

//�Q�[���̏��
GameStatus game_status = GameStatus::TITLE;
int time = 0;

//�v���C���[�̏��
ObjectData player_data = { "Player", GetColor(0, 0, 0), {30, WINDOW_HEIGHT * 0.75, 0}, {5, 5, 5}, false, 20.0, 40.0, 0};
