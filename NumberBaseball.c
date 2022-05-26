#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define seed() srand((int)time(NULL)) // seed()값을 매번 변화시키기 위한 함수를 간단히 정의
#define random(n) rand() % n // 0 ~ n - 1까지의 랜덤 숫자를 뽑아내기 위한 함수를 간단히 정의
#define MAX_INPUT 5

typedef struct num {
	int n; // 숫자를 저장하는 변수
	int index; // 숫자가 어느 위치에 저장되있는지 확인하는 인덱스 변수
	struct node* next; // 다음 노드의 주소 값을 저장
} SETNUM;

SETNUM* Rand_set(SETNUM* COMPUTER); // 컴퓨터 랜덤 숫자를 정함
SETNUM* Save_inp(SETNUM* PLAYER, int* n); // 입력받은 숫자를 연결리스트에 저장

int Get_inp(char* p); // 플레이어 입력을 받음
int Trans_int(char c); // getchar()를 통해 입력 받은 숫자를 int형으로 변환
int Compare_num(SETNUM* COMPUTER, SETNUM* PLAYER); // 컴퓨터 숫자와 플레이어 숫자를 비교

void Warning_Not_Int(); // 숫자를 제외한 문자열을 입력한 경우 오류 출력
void Warning_Overrap(); // 중복된 숫자를 입력한 경우 오류 출력
void Warning_Five(); // 숫자가 5자리가 아닌 경우 오류 출력

main() {
	SETNUM* COMPUTER = NULL; // 컴퓨터 랜덤 숫자 저장 연결 리스트
	SETNUM* PLAYER = NULL; // 플레이어 입력 숫자 저장 연결 리스트
	int win_check = 0; // 플레이어가 맞췄는지 확인하는 플래그 변수
	int game_cnt = 0; // 총 게임 수 카운트

	COMPUTER = Rand_set(COMPUTER);

	SETNUM* _COPUTER = COMPUTER; // 임의의 연결리스트에 컴퓨터의 랜덤 숫자를 저장해서 매번 초기화 시켜주기 위함

	printf("------------- 숫자 야구 게임------------- \n");
	printf("1 ~ 9 숫자 중 5개만 입력해주세요.\n");

	while (!win_check) {
		char p_inp[MAX_INPUT]; // 플레이어가 입력하는 숫자를 문자열로 저장
		int n_inp[MAX_INPUT]; // 저장된 문자열 5개를 숫자로 저장
		int num_list[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 중복 숫자를 확인하기 위한 배열 리스트
		int overrap = 0, wrong = 0, inp_five = 0; // 중복 되는 수 플래그 변수, 잘못된 입력 플래그 변수, 5자리 검사 플래그 변수
		int inp_count = 0; // 숫자가 5자리가 맞는지 확인하는 변수

		printf("\n현재 입력 횟수 - %d번\n", game_cnt);
		printf("플레이어 입력 >> ");

		inp_count = Get_inp(p_inp);

		if (inp_count != MAX_INPUT) inp_five = 1; // 입력 받은 문자가 5자리가 아닌 경우

		for (int j = 0; j < MAX_INPUT; j++) {
			n_inp[j] = Trans_int(p_inp[j]);
			if (num_list[Trans_int(p_inp[j]) - 1] == 0) overrap = 1; // 중복된 문자를 입력한 경우
			num_list[Trans_int(p_inp[j]) - 1] = 0;
			if (n_inp[j] > 9 || n_inp[j] <= 0) wrong = 1; // 숫자외 다른 문자열 입력
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

	printf("컴퓨터 숫자 >> ");
	while (COMPUTER != NULL) {
		printf("%d ", COMPUTER->n);
		COMPUTER = COMPUTER->next;
	}
	printf("\n총 걸린 횟수 >> %d", game_cnt);
}

SETNUM* Rand_set(SETNUM* COMPUTER) { // 컴퓨터 랜덤 숫자 생성
	int num_list[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 중복 숫자를 확인하기 위한 배열 리스트
	seed();
	for (int i = MAX_INPUT - 1; i >= 0; i--) {
		int r_num; // 랜덤 숫자를 임시적으로 저장하는 변수
		int ch = 1; // 중복되지 않은 숫자를 확인하는 플래그 변수
		while (ch) {
			r_num = random(9) + 1;
			if (num_list[r_num - 1] != 0) {
				num_list[r_num - 1] = 0;
				ch = 0;
			}
			if (i == 4) num_list[r_num - 1] = 0; // 첫번째 자리 숫자는 무조건 제외하기 위해서 if문 설정
		}
		SETNUM* node = (SETNUM*)malloc(sizeof(SETNUM));
		node->n = r_num;
		node->index = i;
		node->next = COMPUTER;
		COMPUTER = node;
	}

	return COMPUTER;
}

SETNUM* Save_inp(SETNUM* PLAYER, int* n) { // 입력 받은 숫자를 배열 n에 저장하여 PLAYER 연결리스트에 저장
	for (int i = MAX_INPUT - 1; i >= 0; i--) {
		SETNUM* node = (SETNUM*)malloc(sizeof(SETNUM));
		node->n = n[i];
		node->index = i;
		node->next = PLAYER;
		PLAYER = node;
	}

	return PLAYER;
}

int Get_inp(char* p) { // getchar()로 입력을 받는 함수
	int i = 0;
	char c;

	while ((c = getchar()) != '\n') {
		if (i < MAX_INPUT) p[i] = c;
		i++;
	}

	return i;
}

int Trans_int(char c) { // char형식의 숫자를 int형으로 바꿔주는 함수
	int num = c - '0';

	return num;
}

int Compare_num(SETNUM* COMPUTER, SETNUM* PLAYER) { // COMPUTER와 PLAYER 연결리스트를 서로 비교하는 함수
	int ball_count = 0, strike_count = 0;
	int player_win = 0; // 플레이어가 맞췄는지 확인하는 플래그 변수

	SETNUM* a = PLAYER;
	while (COMPUTER != NULL) {
		PLAYER = a;
		while (PLAYER != NULL) {
			if (COMPUTER->n == PLAYER->n) {
				if (COMPUTER->index == PLAYER->index) strike_count++; // index와 n값이 모두 같다면 strike
				else ball_count++; // index는 다르지만 n값이 같다면 ball
			}
			PLAYER = PLAYER->next;
		}
		COMPUTER = COMPUTER->next;
	}

	printf("----> %d Strike\n----> %d Ball\n", strike_count, ball_count);

	if (strike_count == 5) player_win = 1;

	return player_win;
}

void Warning_Not_Int() { // 숫자가 아닌 다른 수를 입력하거나 5자리를 초과하여 입력한 경우
	printf("숫자외 다른 문자 입력!\n");
}

void Warning_Overrap() { // 중복된 숫자를 입력한 경우
	printf("중복된 숫자 입력!\n");
}

void Warning_Five() { // 숫자가 5자리가 아닌 경우
	printf("5자리 입력 필요!\n");
}