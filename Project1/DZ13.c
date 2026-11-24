#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>

void write_to_file(FILE *file, char* date,char *upr, int podh, int povt, int all_povt);

int main() {
	setlocale(LC_CTYPE, "RUS");
	time_t now = time(NULL);
	char date[16];
	strftime(date, sizeof date, "%Y-%m-%d", localtime(&now));

	int end = 1;
	int session_total = 0;

	while (end != 0) {
		FILE* file = fopen("workout.log", "a");

		if (file == 0) {
			perror("Не удалось открыть workout.log");
			return 1;
		}

		char upr[50];
		printf("ВВЕДИТЕ ВИД УПРАЖНЕНИЯ: ");
		scanf("%49s", upr);

		if (strcmp(upr, "STOP") == 0) {
			printf("\n\nПОВТОРЕНИЙ ЗА ВВСЕ ВРЕМЯ: %d", session_total);
			fprintf(file, "\n\nПОВТОРЕНИЙ ЗА ВВСЕ ВРЕМЯ: %d", session_total);
			break;
		}

		int podh;
		printf("ВВЕДИТЕ КОЛ-ВО ПОДХОДОВ: ");
		scanf("%d", &podh);

		int povt;
		printf("ВВЕДИТЕ КОЛ-ВО ПОВТОРЕНИЕ: ");
		scanf("%d", &povt);

		int all_povt = podh * povt;
		session_total += all_povt;

		write_to_file(file, date, upr, podh, povt, all_povt);
		fclose(file);
	}
}

void write_to_file(FILE *file, char *date, char *upr, int podh, int povt, int all_povt) {
	fprintf(file, "%s | %s | %d*%d | всего: %d\n", date, upr, podh, povt, all_povt);
	printf("%s | %s | %d*%d | всего: %d\n", date, upr, podh, povt, all_povt);
	printf("РЕЗУЛЬТАТЫ ЗАПИСАННЫ В ФАЙЛ: workout.log\n");
}