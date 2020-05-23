#pragma once
#include <memory>
#include "GameTask.h"

class TitleScene;
class GameScene;
class ResultScene;

struct ControlButton
{
	bool Space;
	bool Up_Chair;
	bool Down_Chair;
};

struct Button
{
	ControlButton nowButton;
	ControlButton oldButton;
};


class GameTask
{
public:
	static void Create(void);
	static void Destroy(void);
	static GameTask &GetInstance(void)
	{
		Create();
		return *s_Instance;
	}
	void Initialize(void);
	void Run(void);
	int Update(void);
private:
	GameTask();
	~GameTask();
	//�V�X�e��
	int System(void);
	//�V�[���Y
	int Title(void);
	int Game(void);
	int Result(void);
	void UpdateButton(void);
	//�Q�[���J��
	int (GameTask::*Scene)(void);
	//�R���g���[��
	Button controlButton;

	// �V�[���̃X�}�[�g�|�C���^
	std::unique_ptr<TitleScene> title;
	std::unique_ptr<GameScene> game;
	std::unique_ptr<ResultScene> result;


	static GameTask *s_Instance;
};

