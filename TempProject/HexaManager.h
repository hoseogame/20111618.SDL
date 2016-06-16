#pragma once
#include "GameObject.h"
#include "BaseManager.h"
#include "LoaderParams.h"
#include <vector>


class Block;

struct UIData
{
	int stage;
	int score;
	int blockcount;
	int maxcombo;
};

struct STAGE
{
	int speed;
	int triple_rate;
	int clear_block;
};

class HexaManager : public BaseManager
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	bool GameOver() { return is_gameover; }
	UIData GetUIdata() { return m_UIData; }

private:
	void Init();
	void makeNewBlock(int *shape);
	void showNextBlock(int *shape);
	void showCurBlock(int* shape, int x, int y);
	bool downMoveBlock(int* x, int* y);
	bool CheckHexa(int combo);
	void DeleteBlock(int block_arr[21][10], int combo);

	void Play();

	void InputPlay();
	void TimePlay();
private:
	int objectMaxCount;

	float key_delay;
	int m_time;

	int level;
	int cur_block[3];
	int next_block[3];
	int cur_x, cur_y;
	int blocks;
	int max_combo;

	bool is_gameover;
	bool return_tmp;
	bool check;
	Block* m_Blocks[21][10];
	Block* m_nextBlocks[5][5];

	STAGE m_stage[8];
	UIData m_UIData;
	std::vector<GameObject*> m_gameObjects;
	std::vector<std::string> m_textureIDList;
};