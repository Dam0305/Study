//데이터 구조 5주차 과제
//후위표기수식의 값을 계산하는 프로그램
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#define MAX 100

//스택 
typedef int element;
typedef struct{
	element data[MAX];
	int top;
}STACK; 

//스택 초기화 
void init_stack(STACK *s){
	s->top = -1;
}

//스택 공백 검사 
int is_empty(STACK *s){
	return (s->top == -1);
}

//스택 포화 검사 
int is_full(STACK *s){
	return (s->top == (MAX -1));
}

//push 함수 
void push(STACK *s, element x){
	if(is_full(s)){
		fprintf(stderr, "스택 포화 에러");
		return;
	}
	else s->data[++(s->top)] = x;
}

//pop 함수 
element pop(STACK *s){
	if(is_empty(s)){
		fprintf(stderr, "스택 공백 에러");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//peek 함수 
element peek(STACK *s){
	if(is_empty(s)){
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

//후위표기식 계산 함수 
int eval(char exp[]){
	int op1, op2, value, i;
	int len = strlen(exp);
	char ch;
	STACK s;
	
	init_stack(&s);
  
	for(i=0; i<len; i++){
		ch = exp[i];
		//peek연산자로 제대로 push되고 pop되었는지 확인
		//피연산자인 경우 스택에 값 저장 
		if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '<' && ch != '>'){
			value = ch-'0';
			push(&s, value);
			printf("PUSH %d\n", peek(&s));
		}
    
		//연산자인 경우 스택에서 피연산자 pop하여 계산 진행 
		else{
			//pop
			printf("POP %d\n", peek(&s));
			op2 = pop(&s);
			printf("POP %d\n", peek(&s));
			op1 = pop(&s);
			 
			switch(ch){
				//덧셈 연산 
				case '+':
					push(&s, op1+op2);
					printf("%d + %d PUSH %d\n",op1, op2, peek(&s));
					break;
          
				//뺄셈 연산 
				case '-':
					push(&s, op1-op2);
					printf("%d - %d PUSH %d\n",op1, op2, peek(&s));
					break; 
          
				//곱셈 연산 
				case '*':
					push(&s, op1*op2);
					printf("%d * %d PUSH %d\n",op1, op2, peek(&s));
					break;
          
				//나눗셈 연산 
				case '/':
					push(&s, op1/op2);
					printf("%d / %d PUSH %d\n",op1, op2, peek(&s));
					break;
          
				//모듈로 연산 
				case '%':
					push(&s, op1%op2);
					printf("%d %% %d MODULO PUSH %d\n", op1, op2, peek(&s));
					break;
          
				//거듭제곱 연산 
				case '^':
					push(&s, (pow(op1, op2)));
					printf("%d ^ %d POW PUSH %d\n", op1, op2, peek(&s));
					break;
          
				//부등호 연산 
				case '<':
					push(&s, op1<op2);
					printf("%d < %d PUSH %d\n", op1, op2, peek(&s));
					break;
          
				case '>':
					push(&s, op1>op2);
					printf("%d > %d PUSH %d\n", op1, op2, peek(&s));
					break;	
			}
		}
	}
	return pop(&s);
}

int main(void) {
  //1번예제 후위표기수식
	char *s1 = "573%+23*-";
  //2번예제 후위표기수식
	char *s2 = "3232^^+1-";
  //3번예제 후위표기수식
	char *s3 = "34+2-23*2^>";
	char s[MAX];
	int usr;
	
	while(1){
		puts("1번 예제");
		puts("2번 예제");
		puts("3번 예제");
		puts("4번 입력한 식 계산");
		puts("5번 종료");
		scanf("%d", &usr);
    
		switch(usr){
			//1번 예제 
			case 1:
				printf("%s\n", s1);
				printf("%d\n", eval(s1));
				break;
        
			//2번 예제 
			case 2:
				printf("%s\n", s2);
				printf("%d\n", eval(s2));
				break;
        
			//3번 예제 
			case 3:
				printf("%s\n", s3);
				printf("%d\n", eval(s3));
				break;
        
			//직접 입력한 식 계산 
			case 4:
			    puts("입력");
				scanf("%s", s);
				printf("%d\n", eval(s)); 
				break;
       
      //종료
			case 5:
				exit(1);
		}
	}
	
	return 0;
}
