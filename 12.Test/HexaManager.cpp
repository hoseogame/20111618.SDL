#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "HexaManager.h"
#include "Block.h"
#include <ctime>

#define DELAY_TIME 600

void HexaManager::update()
{
	Play();
}

void HexaManager::render()
{
	for (int i = 0; i < objectMaxCount; i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool HexaManager::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/Block_ap3.png",
		"hexaicon", TheGame::Instance()->get_Renderer()))
	{
		return false;
	}

	Init();

	objectMaxCount = m_gameObjects.size();

	return true;
}

bool HexaManager::onExit()
{
	/*if ( m_Blocks != nullptr )
	{
		delete[] m_Blocks;
	}
	if ( m_nextBlocks != nullptr )
	{
		delete[] m_nextBlocks;
	}*/

	for ( int i = m_gameObjects.size() - 1; i >= 0; i-- )
	{
		m_gameObjects[i]->clean();
		m_gameObjects.pop_back();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("hexaicon");
	return false;
}

void HexaManager::Init()
{
	cur_x = 4;
	cur_y = -2;
	blocks = 0;
	m_stage[0].speed = 40 * 3;
	m_stage[0].clear_block = 60;
	m_stage[0].triple_rate = 5;
	m_stage[1].speed = 37 * 3;
	m_stage[1].clear_block = 70;
	m_stage[1].triple_rate = 4;
	m_stage[2].speed = 33 * 3;
	m_stage[2].clear_block = 75;
	m_stage[2].triple_rate = 3;
	m_stage[3].speed = 30 * 3;
	m_stage[3].clear_block = 80;
	m_stage[3].triple_rate = 2;
	m_stage[4].speed = 27 * 3;
	m_stage[4].clear_block = 90;
	m_stage[4].triple_rate = 2;
	m_stage[5].speed = 22 * 3;
	m_stage[5].clear_block = 100;
	m_stage[5].triple_rate = 1;
	m_stage[6].speed = 18 * 3;
	m_stage[6].clear_block = 110;
	m_stage[6].triple_rate = 1;
	m_stage[7].speed = 10 * 3;
	m_stage[7].clear_block = 99999;
	m_stage[7].triple_rate = 1;

	LoaderParams* tempLP = new LoaderParams();

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_Blocks[i][j] = new Block();
			tempLP->setLoaderParams((j * 25) + 100, (i * 25) + 100, 25, 25, "hexaicon");
			m_Blocks[i][j]->load(tempLP);
			m_gameObjects.push_back(m_Blocks[i][j]);

			if (i == 20 || j == 0 || j == 9) m_Blocks[i][j]->SetType(WALL);
			else m_Blocks[i][j]->SetType(NONE);
		}
	}

	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			m_nextBlocks[i][j] = new Block();
			tempLP->setLoaderParams((j * 25) + 375, (i * 25) + 100, 25, 25, "hexaicon");
			m_nextBlocks[i][j]->load(tempLP);
			m_gameObjects.push_back(m_nextBlocks[i][j]);

			if (i == 0 || i == 4 || j == 0 || j == 4) m_nextBlocks[i][j]->SetType(WALL);
			else m_nextBlocks[i][j]->SetType(NONE);
		}
	}

	delete tempLP;

	srand((unsigned)time(NULL));

	makeNewBlock(cur_block);
	makeNewBlock(next_block);
	showNextBlock(next_block);
}

bool HexaManager::downMoveBlock(int* x, int* y)
{
	if (m_Blocks[(*y) + 3][*x]->GetType() != NONE)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int m = 0; m < m_gameObjects.size(); m++)
			{
				if (m_Blocks[*y + j][*x] == m_gameObjects[m])
				{
					m_Blocks[*y + j][*x]->SetType(cur_block[j]);
				}
			}
		}
		cur_block[0] = next_block[0];
		cur_block[1] = next_block[1];
		cur_block[2] = next_block[2];
		makeNewBlock(next_block);
		showNextBlock(next_block);
		*x = 4;	*y = -2;
		return 1;
	}
	else
	{
		(*y)++;
	}
	return 0;
}
void HexaManager::showCurBlock(int* shape, int x, int y)
{
	for (int i = 0; i<3; i++)
	{
		if (y + i <0)		//화면 위쪽의 블럭은 보여주지 않음
			continue;

		if (m_Blocks[y + i][x] != 0)
		{
			m_Blocks[y + i][x]->SetType(shape[i]);
		}
	}
}
void HexaManager::showNextBlock(int* shape)
{
	for (int i = 0; i < 3; i++) m_nextBlocks[i + 1][2]->SetType(shape[i]);
}
void HexaManager::makeNewBlock(int* shape)
{
	int rtn_tmp;
	rtn_tmp = rand() % 100;
	if (m_stage[level].triple_rate > rtn_tmp)	//트리플 확률로 트리플이 나올때
	{
		rtn_tmp = rand() % 5 + 1;
		shape[0] = rtn_tmp;
		shape[1] = rtn_tmp;
		shape[2] = rtn_tmp;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			shape[i] = rand() % 5 + 1;
		}
	}
}
bool HexaManager::CheckHexa(int combo)
{
	int i = 0, j = 1, k = 0, l = 1;
	int fair_num = 0;
	int tmp_shape;
	int tmp_x, tmp_y;
	int fair_arr[21][10];
	int is_del_block = 0;

	for (i = 0; i<21; i++)		//fair_arr 초기화
		for (j = 0; j<10; j++)
			fair_arr[i][j] = 0;

	for (i = 0; i<20; i++)			//세로
	{
		for (j = 1; j<9; j++)		//가로
		{
			tmp_shape = (int)(m_Blocks[i][j]->GetType());

			if (tmp_shape == 0)	//빈칸일경우 기준점을 다음칸으로 옮김
				continue;

			for (k = 0; k<4; k++)	//방향
			{
				tmp_y = i;
				tmp_x = j;
				fair_num = 0;
				for (l = 1; l<5; l++)	//깊이
				{
					switch (k)
					{
					case 0:		//기준점에서 왼쪽 아래 대각선 방향을
						tmp_y++;
						tmp_x--;
						break;
					case 1:		//기준점에서 아래 방향
						tmp_y++;
						break;
					case 2:		//기준점에서 오른쪽 아래 대각선 방향
						tmp_y++;
						tmp_x++;
						break;
					case 3:		//기준점에서 오른쪽 방향
						tmp_x++;
						break;
					}
					if (tmp_x <1 || tmp_x >12 || tmp_y > 20)
						break;
					if (m_Blocks[tmp_y][tmp_x]->GetType() == tmp_shape)
						fair_num++;
					else
						break;
				}
				if (fair_num >= 2)
				{
					is_del_block = 1;
					tmp_y = i;
					tmp_x = j;
					for (l = 0; l <= fair_num; l++)
					{
						fair_arr[tmp_y][tmp_x] = 1;
						switch (k)
						{
						case 0:		//기준점에서 왼쪽 아래 대각선 방향을
							tmp_y++;
							tmp_x--;
							break;
						case 1:		//기준점에서 아래 방향
							tmp_y++;
							break;
						case 2:		//기준점에서 오른쪽 아래 대각선 방향
							tmp_y++;
							tmp_x++;
							break;
						case 3:		//기준점에서 오른쪽 방향
							tmp_x++;
							break;
						}
					}
				}

			}
		}
	}
	if (is_del_block == 1)	//3개이상이 연달아 있을때
	{
		combo++;
		DeleteBlock(fair_arr, combo);

		if (combo > max_combo)
			max_combo = combo;

		CheckHexa(combo);
		return 1;
	}
	return 0;
}
void HexaManager::DeleteBlock(int block_arr[21][10], int combo)
{
	int i, j, k;
	int block_num = 0;		//없애는 블럭의 개수
	for (i = 19; i >= 0; i--)
	{
		for (j = 1; j<9; j++)
		{

			if (block_arr[i][j] == 1)
			{
				m_Blocks[i][j]->SetType(0);
				block_num++;
				blocks++;

			}

		}
	}
	for (i = 0; i<20; i++)
	{
		for (j = 1; j<9; j++)
		{
			if (m_Blocks[i][j]->GetType() != 0)
				continue;

			for (k = i; k >= 0; k--)	//블럭을비운 빈공간을 위에 있는 블럭으로 채운다.
			{
				if (k == 0)
				{
					m_Blocks[k][j]->SetType(0);

				}
				else {
					m_Blocks[k][j]->SetType(m_Blocks[k - 1][j]->GetType());

				}
			}

		}
	}
	m_UIData.score += combo*1.3*(block_num * 12);
}
void HexaManager::Play()
{
	if (is_gameover == 1)
	{
		return;
	}
	InputPlay();
	TimePlay();
}

void HexaManager::InputPlay()
{
	int blank_block[3] = { 0,0,0 };
	int shape_tmp;
	if (key_delay >= DELAY_TIME)
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
		{
			shape_tmp = cur_block[2];
			cur_block[2] = cur_block[1];
			cur_block[1] = cur_block[0];
			cur_block[0] = shape_tmp;
			key_delay = 0;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
		{
			showCurBlock(blank_block, cur_x, cur_y);
			if (cur_x>1)
			{
				if (m_Blocks[cur_y + 2][cur_x - 1]->GetType() == 0)
				{
					cur_x--;
				}
			}
			key_delay = 0;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
		{
			showCurBlock(blank_block, cur_x, cur_y);
			if (cur_x<8)
			{
				if (m_Blocks[cur_y + 2][cur_x + 1]->GetType() == 0)
				{
					cur_x++;
				}
			}
			key_delay = 0;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		{
			showCurBlock(blank_block, cur_x, cur_y);
			return_tmp = downMoveBlock(&cur_x, &cur_y);
			if (return_tmp == 1)		//블럭이 바닥에 닿았을때
			{
				if ((cur_y<0) && (m_Blocks[cur_y + 3][cur_x]->GetType() != 0))
				{
					is_gameover = 1; 
				}
				else {
					CheckHexa(0);
				}
			}
			key_delay = 0;
		}
	}
	else
	{
		showCurBlock(cur_block, cur_x, cur_y);
		key_delay += 100;
	}
}
void HexaManager::TimePlay()
{
	m_UIData.stage = level + 1;
	m_UIData.maxcombo = max_combo;
	m_UIData.blockcount = m_stage[level].clear_block - blocks;
	m_time++;
	int blank_block[3] = { 0,0,0 };
	if (m_time%m_stage[level].speed == 0)
	{
		if (blocks>m_stage[level].clear_block)
			if (level <7)
			{
				level++;
				blocks = 0;
			}
		showCurBlock(blank_block, cur_x, cur_y);	//이동하기전 위치의 블럭 모양을지운다
		return_tmp = downMoveBlock(&cur_x, &cur_y);		//블럭을 이동한다.

		if (return_tmp == 1)		//블럭이 바닥에 닿았을때	
		{
			if ((cur_y < 0) && (m_Blocks[cur_y + 3][cur_x]->GetType() != 0))
			{
				is_gameover = 1;
			}
			else {

				CheckHexa(0);
			}
		}
		showCurBlock(cur_block, cur_x, cur_y);
	}
}