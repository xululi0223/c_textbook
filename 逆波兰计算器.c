//�沨��������
#include<stdio.h>
#include<stdlib.h>		//Ϊ��ʹ��atof()����
#include<ctype.h>

#define MAXOP 100		//�����������������󳤶�
#define NUMBER '0'		//��ʶ�ҵ�һ����
#define MAXVAL 100		//ջval��������
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int sp = 0;				//��һ������ջλ��
double val[MAXVAL];		//ֵջ
char buf[BUFSIZE];		//����ungetchar�����Ļ�����
int bufp = 0;		//buf����һ������λ��

int getch(void);		//ȡһ���ַ���������ѹ�ص��ַ���
void ungetch(int);		//���ַ�ѹ��������
void push(double f);	//��fѹ��ֵջ��
double pop(void);		//����������ջ����ֵ
int getop(char s[]);		//��ȡ��һ�����������ֵ������

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case'*':
			push(pop() * pop());
			break;
		case'-':
			op2 = pop();
			push(pop() - op2);
			break;
		case'/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error:zero divisor\n");
			break;
		case'\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error:unknown command %s\n", s);
		}
	}
	return 0;
}

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (pop > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')	//������
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));		//�ռ���������
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));		//�ռ�С������
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}