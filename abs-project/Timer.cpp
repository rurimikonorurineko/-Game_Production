#include <math.h>
#include "DxLib.h"
#include "Timer.h"
#include "ImageMng.h"

#define CHANGE_TIME 60			//���Ԃ����ւ���Ƃ���1�̑傫��
#define PAI 3.141592653589793	//�~����(��)
#define ANGLE_MAX 360			//����̊p�x
#define CLOCK_ROUND	12			//���v����̎��Ԑ���
Timer::Timer()
{

}

Timer::Timer(VECTOR screen)
{
	this->screen = screen;
	//���Ԃ�������
	fleamCount = 0;
	timer.second.actual = 0;
	timer.minute.actual = 0;
	timer.hour.actual = 0;
	//�p�x��������
	//���W�A��
	timer.second.rad = 0;
	timer.minute.rad = 0;
	timer.hour.rad = 0;
	//�p�x
	clock.actual = 0;

	Initialize();
}

Timer::~Timer()
{
}
//�C�j�V�����C�Y
void Timer::Initialize(void)
{
	//�����l�ݒ�
	timer.minute.actual = 14;
	timer.hour.actual = 1;
	//�b�j�̉摜�ǂݍ��݁��摜�T�C�Y�擾
	timer.second.Graph = ImageMng::GetInstance().GetID("image/second-hand.png")[0];
	GetGraphSize(timer.second.Graph, &timer.second.W, &timer.second.H);

	//���j�̉摜�ǂݍ��݁��摜�T�C�Y�擾
	timer.minute.Graph = ImageMng::GetInstance().GetID("image/minute-hand.png")[0];
	GetGraphSize(timer.minute.Graph, &timer.minute.W, &timer.minute.H);

	//���j�̉摜�ǂݍ��݁��摜�T�C�Y�擾
	timer.hour.Graph = ImageMng::GetInstance().GetID("image/hour-hand.png")[0];
	GetGraphSize(timer.hour.Graph, &timer.hour.W, &timer.hour.H);

	//�����Ղ̉摜�ǂݍ��݁��摜�T�C�Y�擾
	clock.Graph = ImageMng::GetInstance().GetID("image/clock-dial.png")[0];
	GetGraphSize(clock.Graph, &clock.W, &clock.H);
}
//�X�V
void Timer::Update(void)
{
	fleamCount+=2;
	ConventTimer(fleamCount);
}
//�t���[���J�E���g�����Ԃɍ��ւ���
void Timer::ConventTimer(int fleamCount)
{
	//�t���[�����b
	if (fleamCount != 0 && fleamCount % (CHANGE_TIME/10) == 0)
	{
		timer.second.actual++;
	}
	//�b����
	if (timer.second.actual >= CHANGE_TIME)
	{
		timer.minute.actual++;
		timer.second.actual = 0;
	}
	//��������
	if (timer.minute.actual >= CHANGE_TIME)
	{
		timer.hour.actual++;
		timer.minute.actual = 0;
	}
	//���v�j�̊p�x���`��
	MakeHourRad();
	MakeMinuteRad();
	MakeSecondRad();
	
}

//�`��
void Timer::DrawTimer(void)
{
	//���v�̍��W���Z�b�g
	VECTOR tPos = { screen.x / 2 - clock.W / 4, 0, 0};
	//�����Ղ̕`��
	DrawGraph(tPos.x, tPos.y, clock.Graph, true);

	//���j�E���j�E�b�j�̕`��
	DrawRotaGraph(tPos.x + timer.hour.W / 2, tPos.y + timer.hour.H / 2, 1.0,
					timer.hour.rad, timer.hour.Graph,true);
	DrawRotaGraph(tPos.x + timer.minute.W / 2, tPos.y + timer.minute.H / 2, 1.0,
					timer.minute.rad, timer.minute.Graph, true);
	DrawRotaGraph(tPos.x + timer.second.W /2, tPos.y + timer.second.H / 2, 1.0, 
					timer.second.rad, timer.second.Graph, true);
	//DrawGraph(tPos.x, tPos.y, timer.second.Graph,true);
}

//���j�̊p�x���`��
void Timer::MakeHourRad(void)
{
	int hr = timer.hour.actual * (ANGLE_MAX / CLOCK_ROUND) + timer.minute.actual /2;
	timer.hour.rad = hr * PAI / (ANGLE_MAX /2);
}
//���j�̊p�x���`��
void Timer::MakeMinuteRad(void)
{
	int mi = timer.minute.actual * (ANGLE_MAX / CHANGE_TIME);
	timer.minute.rad = mi * PAI / (ANGLE_MAX /2);
}
//�b�j�̊p�x���`��
void Timer::MakeSecondRad(void)
{
	int sc = timer.second.actual * (ANGLE_MAX / CHANGE_TIME);
	timer.second.rad = sc * PAI / (ANGLE_MAX /2);
}


