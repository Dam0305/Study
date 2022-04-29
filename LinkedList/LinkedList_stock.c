//연결리스트 활용한 재고 관리 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 50

//Element 정의 
typedef struct{
	char name[NAME_MAX];
	char category;
	int qty;
	int price;
}element;
 
//리스트 노드 정의 
typedef struct ListNode{
	element data;
	struct ListNode *link;
}ListNode;

/*리스트 오름차순으로 삽입하기 위한 함수 
파라미터는 헤드 포인터와 삽입하려는 품목의 이름
새로 삽입되려는 노드는 큰 값 앞에 삽입되어야 하므로 
삽입하려는 품목의 이름(n)과 기존 노드(p)를 비교하여 p보다 n이 크면
pre를 p로 변경해주고 p보다 n이 작을 때 pre를 반환하여
pre와 p사이에 n을 삽입*/ 
ListNode* check(ListNode *head, char *n){
	//비교할 노드 
	ListNode *p;
	//비교한 노드의 이전 노드 
	ListNode *pre;
	
	//head가 NULL이면 그대로 head 반환 
	if(head == NULL)
	    return head;
	    
	//비교할 노드의 링크가 NULL일 때까지 반복 
	for(p=head; p != NULL; p=p->link){
		//삽입하려는 품목의 이름이 비교하려는 노드의 이름 첫글자보다 작을 때 
		if(*n < p->data.name[0]){
			//비교하는 노드가 head라면 새로 입력하려는 노드는 현재 head의 자리에 와야하기 때문에 
			//pre를 NULL로 바꿔준 후 pre 반환 
			if(head == p){
				pre = NULL;
				return pre;
			}
			//비교하는 노드가 head가 아니라면 pre 반환 
			else{
				return pre;
			}
		}
		//삽입하려는 품목의 이름이 비교하는 노드의 이름 첫글자보다 클 때 
		else{
			//pre를 비교하는 값으로 변경 
			pre = p;
		}
	}
	//반복문 끝까지 다 돌면 새로 삽입하려는 노드의 이름이 제일 크므로
	//pre값 반환 
	return pre;
}


//노드 삽입 함수 
ListNode* insert_node(ListNode *head, char *n, char c, int q, int price){
	ListNode *p = (ListNode*)malloc(sizeof(ListNode));
	ListNode *pre;
	 
	pre = check(head, n);
	//헤드 포인터에 아무런 연결 리스트가 없을 때(초기) 
	if(head == NULL){
		//문자열은 strcpy 함수 통하여 복사 
	    strcpy(p->data.name, n);
       	p->data.category = c;
       	p->data.qty = q;
        p->data.price = price;
        head = p;
        return head;
	}
	//새로 추가할 노드의 위치가 head위치일 때 
	else if(pre == NULL){
	    strcpy(p->data.name, n);
       	p->data.category = c;
       	p->data.qty = q;
        p->data.price = price;
        p->link = head;
        head = p;
        return head;
	}
	//새로 추가할 노드의 위치가 특정노드 뒤일 때 
	else{
	    strcpy(p->data.name, n);
       	p->data.category = c;
       	p->data.qty = q;
        p->data.price = price;
        p->link = pre->link;
        pre->link = p;
        return head;
	}
}

//연결리스트 출력 함수 
void display_all(ListNode *head){
	ListNode *p;
	
	printf("==========================NODE LIST==========================\n");
	//반복문 NULL 만날 때까지 
	for(p = head; p != NULL; p = p->link){
		printf("NAME: %s \t CATEGORY: %c \t QTY: %d \t PRICE: %d\n",
		        p->data.name ,p->data.category, p->data.qty, p->data.price);
	}
	printf("NULL\n");
}

//연결된 노드의 개수 계산 함수 
int get_length(ListNode *head){
	int cnt = 0;
	ListNode *p;
	
	//반복문 돌면서 cnt 값 증가 
	for(p = head; p != NULL; p = p->link){
		cnt++;
	}
	//증가된 cnt 값 반환 
	return cnt;
}

//카테고리 입력 오류 방지 위한 함수 
char trans(char c){
	//카테고리가 정확하게 입력 되었을 땐 그대로 반환 
	if(c == 'B' || c == 'D' || c == 'F' || c == 'N' || c == 'O')
	    return c;
	    
	//개행문자 지우기 위함 
	getchar();
	
	//무한루프문으로 연속하여 카테고리 변수 확인 
	while(1){
		//만약 소문자로 입력했다면 
		if(c == 'b' || c == 'd' || c == 'f' || c == 'n' || c == 'o'){
			//대문자와 소문자의 아스키코드 값의 차이 만큼 연산 진행 후 반환 
			c -= 32;
			return c; 
		}
		//아예 다른 알파벳을 입력했을 경우 
		else{
			//재입력 메세지 출력 및 재입력 요청-> 제대로 입력할 때까지 무한 반복 
			puts("카테고리를 다시 입력해 주세요");
			scanf("%c", &c);
		}
		//제대로 입력했다면 무한루프 빠져나가고 카테고리 변수 반환 
		if(c == 'B' || c == 'D' || c == 'F' || c == 'N' || c == 'O')
		    break;
	}
	return c;
}

//메인함수 
int main(void) {
	ListNode *head = NULL;
	int usr;
	//상품 정보 입력 받기 위한 변수 선언 
	char n[NAME_MAX], c;
	int q, p;
	
	while(1){
		puts("1. 입력");
		puts("2. 출력");
		puts("3. 노드 개수 출력");
		puts("4. 종료");
		scanf("%d", &usr);
		switch(usr){
			//1번 입력 받기 위한 메뉴 
			case 1:
				//상품 정보를 순서대로 입력 받고 변수에 저장 
				puts("이름");
        	    scanf("%s", n);
        	    getchar();
                puts("카테고리");
            	scanf("%c", &c); 
            	//카테고리의 경우 trans 함수 통하여 제대로 입력 받았는지 확인 
            	c = trans(c);
             	puts("수량");
             	scanf("%d", &q); 
             	puts("가격");
                scanf("%d", &p);
                //head에 리스트 삽입 진행 후 리스트 다시 저장 
				head = insert_node(head, n, c, q, p);
				break;
			case 2:
				//출력하기 위한 함수 
				display_all(head);
				break;
			case 3:
				//노드의 개수를 보여주기 위한 출력문과 동시에 개수를 세는 함수 실행 
				printf("노드의 개수 : %d개\n", get_length(head));
				break;
			case 4:
				//종료 
				exit(1);
		}
	}
	
	
	return 0;
}
