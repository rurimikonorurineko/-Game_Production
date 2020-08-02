#pragma once
#include <memory>
#include "GameTask.h"

class TitleScene;
class GameScene;
class ResultScene;
class Timer;

struct ControlButton
{
	bool Space;			//�X�y�[�X
	bool Up_Chair;		//�֎q���グ��
	bool Down_Chair;	//�֎q��������
};

struct Button
{
	ControlButton nowButton;	//���̃{�^��
	ControlButton oldButton;	//��O�̃{�^��
};


class GameTask
{
public:
	static void Create(void);			//�N���G�C�g
	static void Destroy(void);			//�f�X�g���C
	static GameTask &GetInstance(void)	//�C���X�^���X
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
	int System(void);					//�V�X�e��
	//�V�[���Y
	int TitleInit(void);
	int Title(void);
	int GameInit(void);
	int Game(void);
	int ResultInit(void);
	int Result(void);

	void UpdateButton(void);		//�{�^���̍X�V
	int (GameTask::*Scene)(void);	//�Q�[���J��
	Button controlButton;			//�R���g���[��

	// �V�[���̃X�}�[�g�|�C���^
	std::unique_ptr<TitleScene> title;
	std::unique_ptr<GameScene> game;
	std::unique_ptr<ResultScene> result;
	std::unique_ptr<Timer> timer;
	VECTOR screen;					//��ʃT�C�Y
	static GameTask *s_Instance;	//�C���X�^���X�|�C���^
};

