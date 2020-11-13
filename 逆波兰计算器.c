//逆波兰计算器
#include<stdio.h>
#include<stdlib.h>		//为了使用atof()函数
#include<ctype.h>

#define MAXOP 100		//操作数或运算符的最大长度
#define NUMBER '0'		//标识找到一个数
#define MAXVAL 100		//栈val的最大深度
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int sp = 0;				//下一个空闲栈位置
double val[MAXVAL];		//值栈
char buf[BUFSIZE];		//用于ungetchar函数的缓冲区
int bufp = 0;		//buf中下一个空闲位置

int getch(void);		//取一个字符（可能是压回的字符）
void ungetch(int);		//把字符压回输入中
void push(double f);	//把f压入值栈中
double pop(void);		//弹出并返回栈顶的值
int getop(char s[]);		//获取下一个运算符或数值操作数

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
	if (!isdigit(c) && c != '.')	//不是数
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));		//收集整数部分
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));		//收集小数部分
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