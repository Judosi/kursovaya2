#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>

#define M_PI 3.141592

double fun1(double x)
{
	double y;
	y = 2 * sin(M_PI * x) * sin(3 * M_PI * x) - 0, 5;
	return y;
}

double fun2(double x)
{
	double y;

	if (x <= 0)
	{
		y = (1 + x) / (pow((1 + pow(x, 2)), 1 / 3.f));
	}

	else if (x > 0 && x < 1)
	{
		y = 2 * exp(-2 * x);
	}

	else if (x >= 1)
	{
		y = pow(fabs(2 - x), 1. / 3);
	}
	return y;
}

typedef double (*Fuction)(double);
double fun1(double);
double fun2(double);

void interval(Fuction f, double xn, double xk, double h)
{
	char space = ' ';
	for (double x = xn; x <= xk; x += h)
	{
		printf("\n|%3cx%3c|%6cF(x)%3c|", space, space, space, space);
		printf("\n| %5.2f | %10.6f |", x, f(x));
	}
}

void plot(double x0, double x1, Fuction f)
{
	int SCREENW = 60, SCREENH = 40;//������� ���� ������ � ��������
	char screen[60][40];
	double x, y[60];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;
	hx = (x1 - x0) / (SCREENW - 1);
	for (i = 0, x = x0; i < SCREENW; ++i, x += hx)
	{
		y[i] = f(x); //������ �������� ������� ��� ������ ����� ���� ������ �������
		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}
	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - x0) / hx + 0.5);
	//���������� ���� � ���������� ������� ����������� ���������
	for (j = 0; j < SCREENH; ++j)
		for (i = 0; i < SCREENW; ++i)
		{
			if (j == yz && i == xz) screen[i][j] = '+';
			else if (j == yz) screen[i][j] = '-';
			else if (i == xz) screen[i][j] = '|';
			else screen[i][j] = ' ';
		}
	//����������� ��������� �������� ������� �� ���� ������
	for (i = 0; i < SCREENW; ++i)
	{
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}
	//������ ������� ��������
	for (j = 0; j < SCREENH; ++j)
	{
		for (i = 0; i < SCREENW; ++i) putchar(screen[i][j]);
		putchar('\n');
	}
}

int main(void)
{
	setlocale(LC_ALL, "RUS");
	double x, x_1, x_2, h;
	char c = '0', bracket_1, bracket_2;

	printf("***************************** ���� *************************\n");
	printf("*                                                          *\n");
	printf("* 1 �������� ������� Y(x).                                 *\n");
	printf("* 2 �������� ������� V(x).                                 *\n");
	printf("* 3 �������� ������� Y(x) � �������� ����������.           *\n");
	printf("* 4 �������� ������� V(x) � �������� ����������.           *\n");
	printf("* 5 ������ ������� Y(x) ��� V(x).                          *\n");
	printf("* 6 ����� �� ���������.                                    *\n");
	printf("*                                                          *\n");
	printf("************************************************************\n");
	puts("\n\n������� ����� ������ ���� : ");

	while (c != 6)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("\n������� �������� x: ");
			scanf("%lf", &x);
			if (x == 0)
				printf("������� ������ ��������");
			printf("\nY(%.2lf)=%.2lf", x, fun1(x));
			break;

		case '2':
			printf("\n������� �������� x: ");
			scanf("%lf", &x);
			if (x == 0)
				printf("������� ������ ��������");
			printf("\nY(%.2lf)=%.2lf", x, fun2(x));
			break;

		case '3':
			puts("\n������� ��������, ������������ ��� ������� �������(�� ��������):");
			scanf(" %c%lf;%lf%c", &bracket_1, &x_1, &x_2, &bracket_2);
			puts("\n������� ��� ���������:");
			scanf(" %lf", &h);
			if (bracket_1 == '(') x_1 += h;
			if (bracket_2 == ')') x_2 -= h;
			interval(fun1, x_1, x_2, h);
			break;

		case '4':
			puts("\n������� ��������, ������������ ��� ������� �������(�� ��������):");
			scanf(" %c%lf;%lf%c", &bracket_1, &x_1, &x_2, &bracket_2);
			puts("\n������� ��� ���������:");
			scanf(" %lf", &h);
			if (bracket_1 == '(') x_1 += h;
			if (bracket_2 == ')') x_2 -= h;
			interval(fun2, x_1, x_2, h);
			break;

		case '5':
			puts("\n������� ��������, ������������ ��� ������� �������(�� ��������):");
			scanf(" %c%lf;%lf%c", &bracket_1, &x_1, &x_2, &bracket_2);
			puts("\n������� ��� ���������:");
			scanf(" %lf", &h);
			if (bracket_1 == '(') x_1 += h;
			if (bracket_2 == ')') x_2 -= h;

			puts("������� ����� �������:\nY(x) - 1;\nV(x) - 2.\n");
			scanf("%d", &c);
			switch (c)
			{
			case 1:
				plot(x_1, x_2, fun1);
				break;
			case 2:
				plot(x_1, x_2, fun2);
				break;
			default:
				puts("������: ������� ��� ����� ������� �� ����������.");
			}
			break;


		default:
			puts("�������� ������ ��������");
			break;
		}

		printf("\n\n������� ����� ������ ����: ");
		getchar();
		scanf("%d", &c);

	}
}
