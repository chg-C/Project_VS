#define SCREEN_WITH 1280	// ȭ�� ���� �ȼ�ũ��
#define SCREEN_HEIGHT 768	// ȭ�� ���� �ȼ�ũ��

#define FRAME 1000
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

// ����Ÿ ���̽�
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "Ws05290529*"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' ' // �����ٰ� �Ⱦ�...

enum gamechap
{
	LOGO = 0,
	MENU = 1,
	GAME = 2,
	OVER = 3,
	TOTALCHAP
};

enum alphabet
{
	A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_
};
enum gamework
{
	INIT = 0,
	WORK = 1,
	DRAW = 2
};