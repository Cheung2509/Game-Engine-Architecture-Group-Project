#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

//=================================================================
//Possible GameStates
//=================================================================

enum GameState {
	GS_NULL = 0,
	GS_ATTRACT,
	GS_PLAY_MAIN_CAM,
	GS_PLAY_DEBUG_CAM,
	GS_GAME_OVER,
	GS_COUNT
};
enum MenuState {
	MS_NULL = 0,
	MS_MAIN = 1,
	MS_PLAY = 2,
	MS_EXIT = 3,
	MS_PAUSE = 4,
	MS_GAMEMENU = 5,
	MS_GAMEOVER = 6
	
};

#endif
