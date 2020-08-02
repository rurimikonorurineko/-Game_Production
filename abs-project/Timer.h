#pragma once
#include "DxLib.h"
struct TIME_ELEMENT
{
	int actual;		//����
	int Graph;		//�摜
	int W, H;		//�摜�T�C�Y
	float rad;		//�摜�̉�]�p�x(���W�A��)
};
struct TIMER
{
	TIME_ELEMENT second;	//�b
	TIME_ELEMENT minute;	//��
	TIME_ELEMENT hour;		//��
};

class Timer
{
public:
	Timer();
	Timer(VECTOR screen);
	~Timer();
	void Initialize(void);
	void Update(void);
	void ConventTimer(int fleamCount);			//�t���[���J�E���g�����Ԃɍ��ւ���
	void DrawTimer(void);
	TIMER GetTimer(void) { return timer; };		//�^�C�}�[�̃Q�b�^�[
private:
	//���v�̐j�̉�]�p���`��
	void MakeHourRad(void);			//���j�̊p�x���`��
	void MakeMinuteRad(void);		//���j�̊p�x���`��
	void MakeSecondRad(void);		//�b�j�̊p�x���`��

	TIMER timer;		//�^�C�}�[�̒��g
	int fleamCount;		//�t���[���J�E���g
	VECTOR screen;		//��ʃT�C�Y
	TIME_ELEMENT clock;	//������
};

