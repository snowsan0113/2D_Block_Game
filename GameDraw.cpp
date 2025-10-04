#define _CRT_SECURE_NO_WARNINGS
#include <DxLib.h>
#include "main.h"
#include "GameDraw.h"
#include "GameManager.h"
#include "GameUtil.h"

void drawTitleScene() {
    //�^�C�g����ʂ���Ȃ��ꍇ�͏I������
    if (game_status != GameStatus::TITLE) {
        return;
    }

    if (time % 100 < 80) drawTextC(WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.5, 
        "�Q�[�����J�n����ɂ̓X�y�[�X�L�[", 30, 
            GetColor(255, 255, 255), GetColor(0, 0, 0)
        );

    //�X�y�[�X�L�[�������A�Q�[�����J�n����
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        game_status = GameStatus::RUNNING;
        time = 0;
    }

    time++;
}

void drawRunningScene() {
    //�Q�[��������Ȃ��ꍇ�́A�I������
    if (game_status != GameStatus::RUNNING) {
        return;
    }

    time++;
    char timer_text[100] = "";
    sprintf(timer_text, "%d", time);
    drawTextC(WINDOW_WIDTH - 50, 20, timer_text, 30, GetColor(255, 255, 255), GetColor(0, 0, 0));

    //�v���C���[�𓮂���
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        player_data.obj_loc.x = player_data.obj_loc.x - player_data.obj_vec.x; //���L�[�Ō��݂̃x�N�g��X���A���Ɉړ�����i���l�������j
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        player_data.obj_loc.x = player_data.obj_loc.x + player_data.obj_vec.x; //�E�L�[�Ō��݂̃x�N�g��X���A�E�Ɉړ�����i���l�𑫂��j
    }
    if (CheckHitKey(KEY_INPUT_SPACE) && isPlayerOnGround()) {
        player_data.obj_vec.y = 10;
    }

    jumpPlayer();

    //�v���C���[����ʊO�ɏo���ꍇ�̓Q�[���I��
    if (0 > player_data.obj_loc.x || player_data.obj_loc.x > WINDOW_WIDTH ||
        0 > player_data.obj_loc.y || player_data.obj_loc.y > WINDOW_HEIGHT) {
        game_status = GameStatus::ENDING;
        time = 0;
    }

    //�v���C���[�̕`��
    DrawBox(
        player_data.obj_loc.x - player_data.width / 2, player_data.obj_loc.y - player_data.height / 2,
        player_data.obj_loc.x + player_data.width / 2, player_data.obj_loc.y + player_data.height / 2,
        player_data.color,
        true
    );

    //�}�b�v�̕`��
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            //��ʂ̍��W�ɒ������߁A�s�N�Z�����|����
            int screen_x = x * MAP_PIXEL; 
            int screen_y = y * MAP_PIXEL;    

            //1�������ꍇ�́A���u���b�N�ɒu��������
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
    drawTextC(WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.5, "�Q�[���I�[�o�[", 30, GetColor(255, 255, 255), GetColor(0,0, 0));

    if (time > 200) {
        initGame();
        game_status = GameStatus::TITLE;
    }
}