#include "stdafx.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init();

	imageInit();

	_scene = MAINSCENE;

	_mainS.init(this);
	_selectS.init(this);
	_playS.init(this);
	_result.init(this);



	return S_OK;
}

void mainGame::release()
{

	gameNode::release();

}

void mainGame::update()
{
	gameNode::update();



	switch (_scene)
	{
	case MAINSCENE:
		_mainS.update();
		break;
	case SELECTSCENE:
		_selectS.update();
		break;
	case PLAYSCENE:
		_playS.update();
		break;
	case RESULTSCENE:
		_result.update();
		break;
	}


}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	switch (_scene)
	{
	case MAINSCENE:
		_mainS.render();
		break;
	case SELECTSCENE:
		_selectS.render();
		break;
	case PLAYSCENE:
		_playS.render();
		break;
	case RESULTSCENE:
		_result.render();
		break;
	default:
		break;
	}


	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void mainGame::imageInit()
{
	//�÷��� ������ 481  563 ��  x ���� 24  ��  505   y ���� 12   ��  575
	IMAGEMANAGER->addImage("player", "image/touhou/player.bmp", 684, 100, true, RGB(255, 0, 255), 18, 2);
	IMAGEMANAGER->addImage("plBullet", "image/touhou/plBullets.bmp", 48, 65, true, RGB(255, 0, 255), 2, 1);
	IMAGEMANAGER->addImage("back", "image/touhou/playBack.bmp", 481, 563, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("number", "image/touhou/number.bmp", 160, 16, true, RGB(0, 0, 0), 10, 1);
	IMAGEMANAGER->addImage("enemy", "image/touhou/enemy.bmp", 46, 25, true, RGB(255, 0, 255), 2, 1);
	IMAGEMANAGER->addImage("bullet", "image/touhou/bossBullet.bmp", 256, 16, true, RGB(255, 0, 255), 16, 1);
	IMAGEMANAGER->addImage("bigBullet", "image/touhou/BossBigBullet.bmp", 256, 30, true, RGB(255, 0, 255), 8, 1);
	IMAGEMANAGER->addImage("����â", "image/touhou/����â2.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��Ʋ", "image/touhou/Ÿ��Ʋâ.bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ������", "image/touhou/ĳ���ͼ���â.bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ���͵�", "image/touhou/ĳ���͵�.bmp", 1024, 512, true, RGB(255, 0, 255), 2, 1);
	IMAGEMANAGER->addImage("start", "image/touhou/start.bmp", 168, 41, true, RGB(255, 0, 255), 2, 1);
	IMAGEMANAGER->addImage("item", "image/touhou/items.bmp", 48, 16, true, RGB(255, 0, 255), 3, 1);
	IMAGEMANAGER->addImage("���̵�����", "image/touhou/���̵�����.bmp", 436, 400, true, RGB(255, 0, 255), 2, 5);
	IMAGEMANAGER->addImage("plHomingBullet", "image/PlayerHomingBullet.bmp", 13, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ź��", "image/touhou/�������̽�/��ź��.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/������.bmp", 132, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̳�", "image/���̳�.bmp", 256, 300, true, RGB(255, 0, 255), 4, 4);
	IMAGEMANAGER->addImage("effect1", "image/effect1.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyDeath", "image/enemyDeath.bmp", 248, 28, true, RGB(255, 0, 255), 8, 1);
	IMAGEMANAGER->addImage("��ų���", "image/��ų���.bmp", 481, 563, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("��ų���2", "image/��ų���2.bmp", 481, 1126, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("��ų���", "image/��ų���.bmp", 481, 563, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ŀ�", "image/touhou/�������̽�/�Ŀ�,�׷�����.bmp", 38, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("numbers", "image/numbers.bmp", 160, 19, true, RGB(255, 0, 255), 10, 1);
	IMAGEMANAGER->addImage("max", "image/max.bmp", 40, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("redStar", "image/touhou/redStar.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("burst1", "image/bursteffect1.bmp", 2280, 151, true, RGB(255, 0, 255), 15, 1);
	IMAGEMANAGER->addImage("burst2", "image/bursteffect1_1.bmp", 2020, 151, true, RGB(255, 0, 255), 10, 1);
	IMAGEMANAGER->addImage("miniBullet", "image/miniBullet.bmp", 128, 8, true, RGB(255, 0, 255), 16, 1);
	IMAGEMANAGER->addImage("bossHp", "image/bossHP.bmp", 258, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossDead", "image/BossDeadSmall.bmp", 951, 100, true, RGB(255, 0, 255), 10, 1);
	IMAGEMANAGER->addImage("logo", "image/logo.bmp", 400, 176, true, RGB(255, 0, 255), 2, 1);
	IMAGEMANAGER->addImage("logoBig", "image/logoBig.bmp", 909, 400, true, RGB(255, 0, 255), 2, 1);
}
