//hansan.c
#include <stdio.h>

#define CMD_RELOAD			0x01 // Bit 0 - 장전 준비	 0000 0001
#define CMD_FIRE			0x02 // Bit 1 - 발포 명령	 0000 0010
#define CMD_CHARGE			0x04 // Bit 2 - 돌격 전진	 0000 0100	
#define CMD_HOLD			0x08 // Bit 3 - 후퇴 준비	 0000 1000
#define CMD_CRANE_FORM		0x10 // Bit 4 - 학익진 유지  0001 0000
#define CMD_EVAC			0x20 // Bit 5 - 부상병 후송  0010 0000
#define CMD_DAMAGE			0x40 // Bit 6 - 피해 경고	 0100 0000
#define CMD_ENDWAR			0x80 // Bit 7 - 전쟁 종료	 1000 0000 /*수정사항*/

//Toggle 명령 On
unsigned char CommandOn (unsigned char fleet, unsigned char bit) {
	if (bit < 8)
		fleet |= (0x01 << bit);
	return fleet;
}

//Toggle 명령 Off
unsigned char CommandOff(unsigned char fleet, unsigned char bit) {
	if (bit < 8)
		fleet &= ~(0x01 << bit);
	return fleet;
}

//상태 표시
void showStatus(unsigned char fleet) {
	printf("\n[현재 함선 상태] HEX: %02X | BIN: ", fleet);
	for (int i = 7; i >= 0; i--) {
		printf("%d", (fleet >> i) & 1);
	}
	printf("\n");

	if (fleet & CMD_RELOAD)		printf("장전 준비\n");
	if (fleet & CMD_FIRE)		printf("발포 명령\n");
	if (fleet & CMD_CHARGE)		printf("돌격 전진\n");
	if (fleet & CMD_HOLD)		printf("후퇴 준비\n");
	if (fleet & CMD_CRANE_FORM)	printf("학익진 유지\n");
	if (fleet & CMD_EVAC)		printf("부상병 후송\n");
	if (fleet & CMD_DAMAGE)		printf("피해 경고\n");
	if (fleet & CMD_ENDWAR)		printf("전쟁 종료\n");/*수정사항*/
	if (fleet == 0)				printf("모든 함선 대기 상태\n");
}

void printMenu(void) {
	printf("\n=== 충무공 이순신 한산 전쟁!===\n");
	printf("1. Toggle 장전 준비\n");
	printf("2. Toggle 발포 명령\n");
	printf("3. Toggle 돌격 전진\n");
	printf("4. Toggle 후퇴 준비\n");
	printf("5. Toggle 학익진 유지\n");
	printf("6. Toggle 부상병 후송\n");
	printf("7. Toggle 피해 경고\n");
	printf("8. Reset ALL(초기화)\n");
	printf("9. Inspection(충무공 점검)\n");
	printf("10. Full Attack Mode(전면 돌격)\n");
	printf("11. Exit\n");
	printf("12. End War(전쟁 종료)\n");/*수정사항*/
	printf("명령 선택(1-12): ");
}

int main(void) {

	unsigned char fleet = 0;
	int choice;
	int hp = 100;

	while (1) {
		printMenu(); //나중에 작성
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
			if (fleet & CMD_RELOAD) {
				fleet = CommandOff(fleet, 0);
				printf("장전 중지!\n");
			}
			else {
				fleet = CommandOn(fleet, 0);
				printf("전 함선, 포를 장전하라!\n");
			}
			break;
		case 2:
			if (fleet & CMD_FIRE) {
				fleet = CommandOff(fleet, 1);
				printf("발포 중지! 포신을 내린다!\n");
			}
			else {
				fleet = CommandOn(fleet, 1);
				printf("발포 하라! 적을 향해 쏴라!\n");
			}
			break;
		case 3:
			if (fleet & CMD_CHARGE) {
				fleet = CommandOff(fleet, 2);
				printf("돌격 중지!\n");
			}
			else {
				fleet = CommandOn(fleet, 2);
				printf("전 함선 돌격 전진 개시!\n");
			}
			break;
		case 4:
			if (fleet & CMD_HOLD) {
				fleet = CommandOff(fleet, 3);
				printf("후퇴 중지!\n");
			}
			else {
				fleet = CommandOn(fleet, 3);
				printf("후퇴 준비! 적 움직임 감시!\n");
			}
			break;
		case 5:
			if (fleet & CMD_CRANE_FORM) {
				fleet = CommandOff(fleet, 4);
				printf("학익진 진영 해제!\n");
			}
			else {
				fleet = CommandOn(fleet, 4);
				printf("학익진 진영 유지!\n");
			}
			break;
		case 6:
			if (fleet & CMD_EVAC) {
				fleet = CommandOff(fleet, 5);
				printf("부상병 후송 중지!\n");
			}
			else {
				fleet = CommandOn(fleet, 5);
				printf("부상병 후송 시작!\n"); 
				hp += 5; //hp 증가 /*수정사항*/
			}
			break;
		case 7:
			if (fleet & CMD_DAMAGE) {
				fleet = CommandOff(fleet, 6);
				printf("피해 경고 해제!!\n");
			}
			else {
				fleet = CommandOn(fleet, 6);
				printf("함선 피해 발생 경고!\n");
				hp -= 10; //hp 감소 /*수정사항*/
			}
			break;
		case 8:
			fleet = 0;
			printf("모든 함선 상태 초기화 완료!\n");
			break;
		case 9:
			printf("충무공 점검 : 현재 모든 함선 상태 확인!\n");
			break;
		case 10:
			fleet = 0x7F; // 모든 비트 on 0111 1111
			printf("전면 돌격 모드! 모든 명령 활성!\n");
			break;
		case 11:
			printf("프로그램을 종료합니다.\n");
			return 0;
		case 12:
			fleet = CommandOn(fleet, 7);
			printf("전쟁이 끝났습니다.\n"); /*수정사항*/
			showStatus(fleet);
			return 0;
		default:
			printf("잘못된 입력입니다. (1~12)선택!\n");
		} //switch 끝
		
		if (hp <= 0) {
			printf("현재 HP: %d\n", hp);  /*수정사항*/
			printf("You are dead. Game Over.\n");
			return 0;
		}

		showStatus(fleet);
	} //while 끝

		return 0;
}