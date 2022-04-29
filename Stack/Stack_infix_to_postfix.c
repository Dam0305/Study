//중위표기수식 -> 후위표기수식으로 변환
//후위표기수식 연산 실행
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

//연산자 우선순위
int prec(char op){
	
	switch(op){
		//우향 결합을 위해 부등호를 제일 작은 숫자로 설정
		//거듭제곱은 제일 먼저 계산하기 위해서 제일 높은 숫자로 설정 
		case '(': case ')': return 0;
		case '>': case '<': return 1;
		case '+': case '-': return 2;
		case '*': case '/': case '%': return 3;
		case '^': return 4;
	}
} 

//변환 함수
//매개변수 - 입력받은 중위 표기식 문자열, 새로 저장할 후위표기식 문자열 
void infix_to_postfix(char exp[], char store_s[]){
	//중위표기식 인덱스, 후위표기식 인덱스 
	int i, j=0;
	char ch;
	int len = strlen(exp);
	STACK s;
	
	//스택 초기화 
	init_stack(&s);
	
	//중위표기식 문자열 길이만큼 반복문 실행 
	for(i=0; i<len; i++){
		ch = exp[i];
		
		switch(ch){
			//연산자일 경우 
			case '+': case '-': case '*': case '/': case '%': case '>': case '<':
				//연산자 우선순위 비교하여 POP 혹은 PUSH 
				while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))){
					//POP한 값을 후위표기식 문자열에 저장 
				    store_s[j] = pop(&s);
				    printf("연산자 우선순위 혹은 결합성 %c %c\n", ch, store_s[j]);
					printf("연산자 POP : %c\n", store_s[j]);
					j++;
			    }
				push(&s, ch);
				printf("연산자 PUSH : %c\n", peek(&s));
				break;
			
			//거듭제곱 연산자의 경우 우선순위가 같아도 POP, PUSH 할 필요가 없기 때문에 따로 작성 
			//연산순위가 제일 높으므로 바로 push 
			case '^':
				push(&s, ch);
				printf("연산자 PUSH : %c\n", peek(&s));
				break;
				
			//왼쪽 괄호 만나면 push 
			case '(':
				push(&s, ch);
				printf("연산자 PUSH : %c\n", peek(&s));
				break;
			
			//오른쪽 괄호 만나면 
			case ')':
				//오른쪽 괄호 보여주고, POP 해야하는 이유 출력 
				printf("%c -> 연산자들 POP\n", ch); 
				//연산자 POP, 후위표기식 문자열에 저장 
				store_s[j] = pop(&s);
				//저장된 값과 비교 
				while(store_s[j] != '('){
					//POP 요소 출력 
					printf("연산자 POP : %c\n", store_s[j]);
					//후위표기식 문자열 인덱스 증가 
					j++;
					//다음 비교
					// 오른쪽 괄호도 문자열에 저장되지만 인덱스 값을 늘려주지 않고
					//다음 요소가 덮어씀
					store_s[j] = pop(&s);
				}
				//왼쪽 괄호 POP 출력 
				printf("\"(\" POP\n");
				break;

			default:
				//피연산자 후위표기식 문자열에 저장 
				store_s[j] = ch;
				printf("피연산자 출력 : %c\n", store_s[j]);
				j++;
				break;
		}
	}
	while(!is_empty(&s)){
		//스택에 남아있는 연산자 POP&출력 
		store_s[j] = pop(&s);
		printf("연산자 POP : %c\n", store_s[j]);
		j++;
	}
	    
} 

//후위표기식 연산 실행 함수 
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
 
int main(void){
	int i, usr; 
	//후위표기식 저장할 문자열 
	char store_s[MAX];
	//입력받을 중위표기식 저장할 문자열 
	char usr_s[MAX];
	
	while(1){
		puts("1. 중위표기 입력 -> 후위 표기 변환");
		puts("2. 변환한 후위표기 연산 결과 출력");
		puts("3. 종료");
		scanf("%d", &usr);
		switch(usr){
			case 1:
				puts("중위표기식을 입력해 주세요.");
				scanf("%s", usr_s);
				//입력받은 중위표기식과 후위표기식 저장할 배열 매개변수로 넘겨줌 
				infix_to_postfix(usr_s, store_s);
				//저장된 후위표기식 출력 
				printf("\n후위표기 결과 : %s\n\n", store_s);
				break;
			
			case 2:
			    printf("%s\n", store_s);
				printf("\n연산 결과\n");
				//저장된 후위표기식 문자열 넘겨주어 연산 진행 
				printf("%d\n", eval(store_s)); 
				break;
				
			case 3:
				exit(1);
				break; 
		} 
	}
	return 0;
}
