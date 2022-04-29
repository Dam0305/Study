//LinkedList_stock.c의 확장 프로그램
//자료 검색, 품목 삭제, 재고가 가장 많은 품목, 적은 품목 출력
//특정 카테고리의 품목에 대한 정보만 출력
//재고량 업데이트
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


ListNode* check(ListNode *head, char *n){
	ListNode *p;
	ListNode *pre = NULL;
	
	//head가 NULL이면 그대로 head 반환 
	if(head == NULL)
	    return head;
	    
	//비교할 노드의 링크가 NULL일 때까지 반복 
	for(p=head; p != NULL; p=p->link){
		//삽입하려는 품목의 이름이 비교하려는 노드의 이름보다 작을 때 
		if(strcmp(p->data.name, n) > 0){
			//head자리에 삽입 해야할 경우 아직 NULL값인 pre 반환 
			if(head == p){
				return pre;
			}
			//비교하는 노드가 head가 아니라면 pre 반환 
			else{
				return pre;
			}
		}
		//같은 경우 
		else if(strcmp(p->data.name, n) == 0){
			if(head == p){
				return head;
			}
			//비교하는 노드가 head가 아니라면 pre 반환 
			else{
				return pre;
			}
		}
		//삽입하려는 품목의 이름이 비교하는 노드의 이름보다 클 때 
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

//찾기 함수 
ListNode* seek(ListNode *head, char *n){
	ListNode *p;
	for(p=head; p != NULL; p=p->link){
		//품목이름이 똑같은 경우 해당 포인터 반환 
		if(strcmp(p->data.name, n) == 0){
			return p;
		}
	}
	//없는 경우 NULL반환 
	return;
} 

//삭제 함수 
ListNode* del(ListNode *head, char *n){
	ListNode *pre;
	ListNode *removed;
	
	//pre값 찾기 
	pre = check(head, n);
	
	//head가 NULL이면 NULL반환 
	if(head == NULL){
		puts("리스트가 비어있습니다"); 
		return;
	}
	//삭제하려는 노드가 head 위치에 있을 경우 
	else if(pre == head){
		removed = head;
		head = removed->link;
		free(removed);
		puts("삭제 되었습니다");
		return head;
	}
	else{
		removed = pre->link;
		pre->link = removed->link;
		free(removed);
		puts("삭제 되었습니다");
		return head;
	}
}
//최소값 출력 함수 
void min_qty(ListNode *head){
	ListNode *p;
	//최소값을 임의로 지정 
	int min = 10000;
	
	//리스트를 한바퀴 돌면서 min값 저장 
	for(p=head; p!=NULL; p=p->link){
		if(min > p->data.qty){
			min = p->data.qty;
		}
	}
	printf("============================ MIN ============================\n");
	//저장된 min값과 같은 노드 모두 출력 
	for(p=head; p!=NULL; p=p->link){
		if(min == p->data.qty){
			printf("NAME: %s \t CATEGORY: %c \t QTY: %d \t PRICE: %d\n",
		        p->data.name ,p->data.category, p->data.qty, p->data.price);
		}
	}
	printf("NULL\n");
} 

//최대값 출력 
void max_qty(ListNode *head){
	ListNode *p;
	int max;
	
	//반복문 돌면서 최대값 저장 
	for(p=head; p!=NULL; p=p->link){
		if(max < p->data.qty){
			max = p->data.qty;
		}
	}
	printf("============================ MAX ============================\n");
	//저장된 최대값과 같은 수량의 노드 모두 출력 
	for(p=head; p!=NULL; p=p->link){
		if(max == p->data.qty){
			printf("NAME: %s \t CATEGORY: %c \t QTY: %d \t PRICE: %d\n",
		        p->data.name ,p->data.category, p->data.qty, p->data.price);
		}
	}
	printf("NULL\n");
} 

//지정된 카테고리 정보만 출력 
void display_category(ListNode *head, char c){
	ListNode *p;
	
	printf("==========================NODE LIST==========================\n");
	for(p=head; p!=NULL; p=p->link){
		//반복문을 돌면서 같은 카테고리만 출력 
		if(p->data.category == c){
			printf("NAME: %s \t CATEGORY: %c \t QTY: %d \t PRICE: %d\n",
		        p->data.name ,p->data.category, p->data.qty, p->data.price);
		}
	}
	printf("NULL\n");
} 

//수량 수정 함수 
ListNode* update(ListNode *head, char *n){
	//수정할 수량 변수 
	int new_qty; 
	ListNode *node;
	
	//매개변수로 받은 품목이름으로 해당하는 노드 찾기 
	node = seek(head, n);
	
	//찾은 노드의 현재 수량 출력 
	printf("현재 수량 -> %d \n", node->data.qty);
	
	//수정할 수량 입력 받음 
	puts("변경할 수량을 연산자와 함께 입력해 주세요");
	scanf("%d", &new_qty);
	
	//수량 수정 
	node->data.qty = node->data.qty + new_qty;
	
	//수정된 결과 출력 
	printf("변경된 수량 -> %d \n", node->data.qty);
	
	//수정된 head 반환 
	return head;
}

//메인함수 
int main(void) {
	ListNode *head = NULL;
	ListNode *result;
	int usr;
	//상품 정보 입력 받기 위한 변수 선언 
	char n[NAME_MAX], c;
	int q, p;
	
	
	while(1){
		puts("=============================================================");
		puts("0. 종료\t  1. 입력\t 2. 출력\t  3. 삭제");
		puts("4. 노드 개수 출력 \t 5. 품목이름으로 찾기");
		puts("6. 재고 수량이 가장 많은 품목과 가장 적은 품목 출력"); 
		puts("7. 카테고리 별 출력 \t 8. 수량 수정");
		scanf("%d", &usr);
		switch(usr){
			case 0:
				//종료
				//공간 해제 
	            free(head);
				exit(1);
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
				//삭제 
				puts("삭제하려는 품목을 입력해 주세요");
				scanf("%s", n);
				if(seek(head, n) != NULL){
					head = del(head, n);
				}
				else{
					puts("품목이 존재하지 않습니다");
				}
				 
				break;
				
			case 4:
				//노드의 개수를 보여주기 위한 출력문과 동시에 개수를 세는 함수 실행 
				printf("노드의 개수 : %d개\n", get_length(head));
				break;
				
			case 5: 
			    //품목이름으로 찾기 
		    	puts("품목이름을 입력해 주세요");
				scanf("%s", n); 
				//result 포인터에 결과 저장 
			    result = seek(head, n);
			    //결과가 NULL이면 
			    if(result == NULL){
			    	//리스트에 없다는 내용의 메세지 출력 
			    	printf("==========================NODE LIST==========================\n");
			    	puts("찾는 품목이 없습니다.");
				}
				//존재하면 
				else{
					printf("==========================NODE LIST==========================\n");
					printf("NAME: %s \t CATEGORY: %c \t QTY: %d \t PRICE: %d\n",
		        		result->data.name ,result->data.category, result->data.qty, result->data.price);
				}
				break;
				
			case 6:
				//재고 수량이 가장 많은 품목과 가장 적은 품목 출력 
				min_qty(head);
				max_qty(head);
			    break; 
				
			case 7:
				//카테고리 별로 출력 
				puts("카테고리를 입력해 주세요");
				//character 하나만 입력 받기 위해 버퍼 비움 
				fflush(stdin);
				scanf("%c", &c);
				//제대로 입력 받았나 확인 
				c = trans(c);
				//카테고리만 출력하는 함수 실행 
				display_category(head, c);
			    break; 
				
			case 8:
				//수량 수정 
				puts("수정하려는 품목을 입력해 주세요");
				scanf("%s", n);
				head = update(head, n);
			    break;		 
		}
	}
	
	return 0;
}
