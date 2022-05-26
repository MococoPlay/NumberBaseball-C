#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define seed() srand((int)time(NULL)) // seed()���� �Ź� ��ȭ��Ű�� ���� �Լ��� ������ ����
#define random(n) rand() % n // 0 ~ n - 1������ ���� ���ڸ� �̾Ƴ��� ���� �Լ��� ������ ����
#define MAX_INPUT 5

typedef struct num {
	int n; // ���ڸ� �����ϴ� ����
	int index; // ���ڰ� ��� ��ġ�� ������ִ��� Ȯ���ϴ� �ε��� ����
	struct node* next; // ���� ����� �ּ� ���� ����
} SETNUM;

SETNUM* Rand_set(SETNUM* COMPUTER); // ��ǻ�� ���� ���ڸ� ����
SETNUM* Save_inp(SETNUM* PLAYER, int* n); // �Է¹��� ���ڸ� ���Ḯ��Ʈ�� ����

int Get_inp(char* p); // �÷��̾� �Է��� ����
int Trans_int(char c); // getchar()�� ���� �Է� ���� ���ڸ� int������ ��ȯ
int Compare_num(SETNUM* COMPUTER, SETNUM* PLAYER); // ��ǻ�� ���ڿ� �÷��̾� ���ڸ� ��

void Warning_Not_Int(); // ���ڸ� ������ ���ڿ��� �Է��� ��� ���� ���
void Warning_Overrap(); // �ߺ��� ���ڸ� �Է��� ��� ���� ���
void Warning_Five(); // ���ڰ� 5�ڸ��� �ƴ� ��� ���� ���

main() {
	SETNUM* COMPUTER = NULL; // ��ǻ�� ���� ���� ���� ���� ����Ʈ
	SETNUM* PLAYER = NULL; // �÷��̾� �Է� ���� ���� ���� ����Ʈ
	int win_check = 0; // �÷��̾ ������� Ȯ���ϴ� �÷��� ����
	int game_cnt = 0; // �� ���� �� ī��Ʈ

	COMPUTER = Rand_set(COMPUTER);

	SETNUM* _COPUTER = COMPUTER; // ������ ���Ḯ��Ʈ�� ��ǻ���� ���� ���ڸ� �����ؼ� �Ź� �ʱ�ȭ �����ֱ� ����

	printf("------------- ���� �߱� ����------------- \n");
	printf("1 ~ 9 ���� �� 5���� �Է����ּ���.\n");

	while (!win_check) {
		char p_inp[MAX_INPUT]; // �÷��̾ �Է��ϴ� ���ڸ� ���ڿ��� ����
		int n_inp[MAX_INPUT]; // ����� ���ڿ� 5���� ���ڷ� ����
		int num_list[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // �ߺ� ���ڸ� Ȯ���ϱ� ���� �迭 ����Ʈ
		int overrap = 0, wrong = 0, inp_five = 0; // �ߺ� �Ǵ� �� �÷��� ����, �߸��� �Է� �÷��� ����, 5�ڸ� �˻� �÷��� ����
		int inp_count = 0; // ���ڰ� 5�ڸ��� �´��� Ȯ���ϴ� ����

		printf("\n���� �Է� Ƚ�� - %d��\n", game_cnt);
		printf("�÷��̾� �Է� >> ");

		inp_count = Get_inp(p_inp);

		if (inp_count != MAX_INPUT) inp_five = 1; // �Է� ���� ���ڰ� 5�ڸ��� �ƴ� ���

		for (int j = 0; j < MAX_INPUT; j++) {
			n_inp[j] = Trans_int(p_inp[j]);
			if (num_list[Trans_int(p_inp[j]) - 1] == 0) overrap = 1; // �ߺ��� ���ڸ� �Է��� ���
			num_list[Trans_int(p_inp[j]) - 1] = 0;
			if (n_inp[j] > 9 || n_inp[j] <= 0) wrong = 1; // ���ڿ� �ٸ� ���ڿ� �Է�
		}

		if (inp_five) {
			Warning_Five();
			continue;
		}

		if (wrong) {
			Warning_Not_Int();
			continue;
		}

		if (overrap) {
			Warning_Overrap();
			continue;
		}

		PLAYER = Save_inp(PLAYER, n_inp);

		win_check = Compare_num(COMPUTER, PLAYER);

		COMPUTER = _COPUTER;
		PLAYER = NULL;
		game_cnt++;
	}

	printf("��ǻ�� ���� >> ");
	while (COMPUTER != NULL) {
		printf("%d ", COMPUTER->n);
		COMPUTER = COMPUTER->next;
	}
	printf("\n�� �ɸ� Ƚ�� >> %d", game_cnt);
}

SETNUM* Rand_set(SETNUM* COMPUTER) { // ��ǻ�� ���� ���� ����
	int num_list[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // �ߺ� ���ڸ� Ȯ���ϱ� ���� �迭 ����Ʈ
	seed();
	for (int i = MAX_INPUT - 1; i >= 0; i--) {
		int r_num; // ���� ���ڸ� �ӽ������� �����ϴ� ����
		int ch = 1; // �ߺ����� ���� ���ڸ� Ȯ���ϴ� �÷��� ����
		while (ch) {
			r_num = random(9) + 1;
			if (num_list[r_num - 1] != 0) {
				num_list[r_num - 1] = 0;
				ch = 0;
			}
			if (i == 4) num_list[r_num - 1] = 0; // ù��° �ڸ� ���ڴ� ������ �����ϱ� ���ؼ� if�� ����
		}
		SETNUM* node = (SETNUM*)malloc(sizeof(SETNUM));
		node->n = r_num;
		node->index = i;
		node->next = COMPUTER;
		COMPUTER = node;
	}

	return COMPUTER;
}

SETNUM* Save_inp(SETNUM* PLAYER, int* n) { // �Է� ���� ���ڸ� �迭 n�� �����Ͽ� PLAYER ���Ḯ��Ʈ�� ����
	for (int i = MAX_INPUT - 1; i >= 0; i--) {
		SETNUM* node = (SETNUM*)malloc(sizeof(SETNUM));
		node->n = n[i];
		node->index = i;
		node->next = PLAYER;
		PLAYER = node;
	}

	return PLAYER;
}

int Get_inp(char* p) { // getchar()�� �Է��� �޴� �Լ�
	int i = 0;
	char c;

	while ((c = getchar()) != '\n') {
		if (i < MAX_INPUT) p[i] = c;
		i++;
	}

	return i;
}

int Trans_int(char c) { // char������ ���ڸ� int������ �ٲ��ִ� �Լ�
	int num = c - '0';

	return num;
}

int Compare_num(SETNUM* COMPUTER, SETNUM* PLAYER) { // COMPUTER�� PLAYER ���Ḯ��Ʈ�� ���� ���ϴ� �Լ�
	int ball_count = 0, strike_count = 0;
	int player_win = 0; // �÷��̾ ������� Ȯ���ϴ� �÷��� ����

	SETNUM* a = PLAYER;
	while (COMPUTER != NULL) {
		PLAYER = a;
		while (PLAYER != NULL) {
			if (COMPUTER->n == PLAYER->n) {
				if (COMPUTER->index == PLAYER->index) strike_count++; // index�� n���� ��� ���ٸ� strike
				else ball_count++; // index�� �ٸ����� n���� ���ٸ� ball
			}
			PLAYER = PLAYER->next;
		}
		COMPUTER = COMPUTER->next;
	}

	printf("----> %d Strike\n----> %d Ball\n", strike_count, ball_count);

	if (strike_count == 5) player_win = 1;

	return player_win;
}

void Warning_Not_Int() { // ���ڰ� �ƴ� �ٸ� ���� �Է��ϰų� 5�ڸ��� �ʰ��Ͽ� �Է��� ���
	printf("���ڿ� �ٸ� ���� �Է�!\n");
}

void Warning_Overrap() { // �ߺ��� ���ڸ� �Է��� ���
	printf("�ߺ��� ���� �Է�!\n");
}

void Warning_Five() { // ���ڰ� 5�ڸ��� �ƴ� ���
	printf("5�ڸ� �Է� �ʿ�!\n");
}