#pragma once

//Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

//Player constants
#define MARIO_TEXT_POS 4.0f
#define LUIGI_TEXT_POS 0.75f * SCREEN_WIDTH
#define SCORE_HEIGHT 4.0f
#define INITIAL_LIVES 3
#define LIVES_HEIGHT 40.0f
#define INVULNERABILITY_TIME 5.0f
#define INVULN_MULTIPLIER 4.0f
#define LEVEL1_PLAYER_FRAME_DELAY 0.1f
#define LEVEL2_PLAYER_FRAME_DELAY 0.08f
#define MARIO_IDLE_FRAME_COUNT 1
#define MARIO_IDLE_START_FRAME 0
#define MARIO_JUMP_FRAME_COUNT 1
#define MARIO_JUMP_START_FRAME 5
#define MARIO_MOVE_FRAME_COUNT 4
#define MARIO_MOVE_START_FRAME 1
#define MARIO_FRAME_COUNT 6

//movement constants
#define MOVEMENTSPEED 60.0f
#define GRAVITY 96.0f
#define JUMP_FORCE_DECREMENT 400.0f
#define INITIAL_JUMP_FORCE 400.0f
#define INITIAL_JUMP_FORCE_SMALL 200.0f
#define KOOPA_SPEED 50.0f
#define COIN_SPEED 25.0f
#define GRAVITY_CHECK_FALLOFF 0.1f

//Map constants
#define MAP_HEIGHT 13
#define MAP_WIDTH 16
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define SCREENSHAKE_DURATION 0.25f

//Enemy constants
#define INJURED_TIME 2.5f
#define ENEMY_SPAWN_TIME 10.0f
#define ANIMATION_DELAY 0.25f
#define KOOPA_FRAME_COUNT 5
#define KOOPA_MOVING_FRAME 0
#define KOOPA_MOVING_FRAME_COUNT 4
#define KOOPA_DAMAGED_FRAME 4
#define KOOPA_DAMAGED_FRAME_COUNT 1
#define KOOPA_SCORE 1

//Coin constants
#define COIN_SPAWN_TIME 15.0f
#define COIN_SCORE 2
#define COIN_FRAME_COUNT 5

//Pow block constants
#define POW_COLLISION_INCREASE 0.53125f
#define POW_HITS 3

//Score constants
#define HIGHSCORE_COUNT 5
#define HIGHSCORE_FILE_PATH "highscores.txt"
#define NAME_MAX_LENGTH 10