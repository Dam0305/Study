//음악 플레이리스트를 원형 연결리스트로 구현하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //실행 중간에 입력이 있나 확인하기 위한 함수 사용을 위한 헤더 
#define MAX 100  

//element 구조 
typedef struct{
	char title[MAX];
	char genre[MAX];
	char singer[MAX];
	float time; //재생 시간의 분과 초를 소수로 나타내기 위해 float형으로 선언 
}element;

//이중연결리스트 정의 
typedef struct PlayList{
	element data;
	struct PlayList *pre;
	struct PlayList *next;
}PlayList;

//플레이 리스트에 넣을 기본 10곡의 데이터 구조체 배열
//재생시간의 정수는 분, 소수는 초
element data_set[10] = {{"살다가", "발라드", "SG워너비", 3.24},
                        {"해바라기", "발라드", "SG워너비", 3.30},
						{"라라라", "발라드", "SG워너비", 3.00},
						{"내사람", "발라드", "SG워너비", 3.20},
						{"롤린", "댄스", "브레이브걸스", 3.14},
						{"아로하", "발라드", "조정석  ", 3.24},
						{"안녕", "발라드", "폴킴   ", 3.04},
						{"기다릴게", "발라드", "하동균, 봉구", 3.13},
						{"Memories", "POP", "Maroon 5", 3.24},
						{"한숨", "발라드", "이하이 ", 3.20}};

//헤드노드 초기화 함수 
void init(PlayList *head){
	head->pre = head;
	head->next = head;
}

//삽입 함수 
PlayList* insert(PlayList *before, element data){
	PlayList *newnode = (PlayList*)malloc(sizeof(PlayList));
	
	//데이터 복사 
	strcpy(newnode->data.title, data.title);
	strcpy(newnode->data.genre, data.genre);
	strcpy(newnode->data.singer, data.singer);
	newnode->data.time = data.time;
	//링크 지정 
	newnode->pre = before;
	newnode->next = before->next;
	before->next->pre = newnode;
	before->next = newnode;
	
	//리스트의 마지막에 삽입하기 위하여 마지막 노드의 포인터 반환 
	return newnode;
}

//전체 플레이 리스트를 보여주기 위한 함수 
void display_all(PlayList *head){
	PlayList *p;

	puts("================================ PLAY LIST ================================");
	for(p=head->next; p!=head; p=p->next){
		printf("TITLE %s \t\t GENRE %s \t SINGER %s \t TIME %0.2f\n",
		        p->data.title, p->data.genre, p->data.singer, p->data.time);
	}
}

//플레이 리스트에서 현재의 위치만 보여주기 위한 함수 
void display_one(PlayList *node){
	
	printf("TITLE %s \t\t GENRE %s \t SINGER %s \t TIME %0.2f\n",
		        node->data.title, node->data.genre, node->data.singer, node->data.time);
}

//재생 함수
//첫번째 노드의 이전, 마지막 노드의 다음을 지정할 때 헤드 노드를 피하기 위하여
//매개변수로 헤드 노드와 현재 노드로 지정 
PlayList* play(PlayList *head, PlayList *n){
	//재생시간이 0이 되면 종료하기 위해서 시간을 저장할 변수 선언 
	float now_time = n->data.time;
	//중간에 입력이 있으면 종료하고 입력된 명령을 수행하기 위한 변수 
	char usr;
	
	//만일 재생시간이 0인 경우를 대비한 조건문 
	//0인 경우 다음 곡으로 넘어간다 
	if(now_time == 0.0){
		if(n->next == head)
		    return head->next;
		return n->next;
	}
	//재생시간이 0이 아닌 경우 정상적으로 재생 
	else{
		//현재 재생중이라는 메세지와 재생 중인 곡의 정보 출력 
		puts("Now playing...=============================================================(</>/e)");
		printf("TITLE %s \t\t GENRE %s \t SINGER %s \t TIME %0.2f\n",
		        n->data.title, n->data.genre, n->data.singer, n->data.time);
	    
		//재생시간을 0.5(50초)씩 감소하며 0보다 클 떄까지만 반복 
		for(now_time; now_time > 0; now_time-=0.5){
			//남은 재생 시간 출력 
	    	printf("%0.2f/", now_time);
	    	//1초마다 진행하기 위한 sleep 함수 
	    	sleep(1);
	    	
	    	//입력이 있으면 진행하기 위한 kbhit 함수
			//구글에서 검색을 통하여 해당 함수를 알게 되어서 사용해보았습니다
			//kblit 함수는 키보드 입력이 있을 경우 1, 없을 경우 0을 반환 
			//입력이 있을 경우 
	    	if(kbhit() == 1){
	    		//usr 변수에 getchar를 이용하여 입력한 내용 저장 
			    usr = getchar();
			    //개행문자 지우기 위한 getchar 
			    getchar();
			    switch(usr){
			    	//>를 입력하면 다음 곡(노드)으로 이동 
			    	case '>':
			    		//만약 다음곡이 헤드노드라면 
			    		if(n->next == head)
			    		    //반환할 때 헤드의 다음 노드 반환 
		                    return head->next;
		                //그렇지 않다면 현재 노드의 다음 노드 반환 
		                return n->next;
		                
		            //이전 곡으로 이동 
		            case '<':
		            	//다음 곡이 헤드 노드라면 
			    		if(n->pre == head)
			    		    //반환할 때 헤드노드의 이전 노드 반환 
		                    return head->pre;
		                //그렇지 않으면 현재 노드의 이전노드 반환 
		                return n->pre;
		             
					//e를 누르면 현재 노드 반환하여 연속 재생 멈춤   
		            case 'E': case 'e':
		            	return n;
			    }
		    }
		}
		printf("\n");
		//만약 키보드의 입력 없이 한 곡이 모두 재생 됐을 경우
		//현재 노드의 다음 노드가 헤드 노드라면 
		if(n->next == head)
		    //헤드 노드의 다음 노드를 반환 
		    return head->next;
		//그렇지 않다면 현재 노드의 다음 노드를 반환 
		return n->next;
	}
}

//메인 함수 
int main(void) {
	PlayList *head = (PlayList*)malloc(sizeof(PlayList));
	//이중 연결리스트에서 현재의 위치를 파악하기 위한 포인터 now
	//직전에 재생했던 곡의 정보를 저장하는 포인터 pre 
    PlayList *now, *pre;
	int i;
	char usr;
	
	//헤드 노드 초기화 
	init(head);
	
	//현재 위치를 헤드 노드로 초기화 
	now = head;
	
	//반복문을 돌며 상수로 선언한 데이터를 연결리스트에 삽입 
	for(i=0; i<10; i++){
		//insert함수에서 삽입한 노드의 포인터를 반환
		//초기 현재 위치는 헤드 노드로 헤드노드부터 차례로 다음 노드에 연결
		now = insert(now, data_set[i]);
	}
	
	//현재 위치를 헤드노드의 다음 노드로 초기화  
	now = head->next;
	
	//전체 플레이 리스트 출력 
	display_all(head);
	//입력받을 메뉴와 키 출력 
	puts("===========================================================================");
		puts("P -> 재생 \t F -> 맨 처음 곡 재생\t L -> 맨 마지막 곡 재생\t 원하는 곡 선택 '<' or '>'");
	    puts("A -> 전체 플레이 리스트  \t  E -> 종료");
	
	//반복문 시작 
	while(1){
		//현재 곡 정보 출력 
		//now 출력문 끝에 메뉴에 대한 키를 출력하여 키의 입력에 도움 
		puts("NOW =======================================================================(P/L/F/</>/A/E)");
		display_one(now);
		//반복문 이전에 출력한 메뉴에 대한 입력 받기 
		scanf("%c", &usr);
		//개행문자 지우기 위한 getchar 
		getchar();
		switch(usr){
			//재생 
			case 'P':case 'p': 
			    //pre값 now값으로 초기화 
			    pre = now;
			    //연속재생을 위한 반복문 
				while(1){
					//재생 함수의 반환 값이 재생한 노래의 이전, 혹은 다음이므로
					//그 값을 now에 저장 
					now = play(head, now);
					
					//반환 받은 now의 값과 이전에 실행했던 pre의 값이 같으면 반복문 탈출 
					if(now == pre){
						break;
					}
					//그렇지 않으면 이전 값을 현재 재생했던 값으로 바꿔주고 다시 반복문 실행 
					pre = now;
				}
				break;
			
			//다음으로 이동 
			case '>':
				//만약 현재의 다음 위치가 헤드 노드라면  
				if(now->next == head)
				    //현재 값을 헤드 노드의 다음 노드로 저장 
				    now = head->next;
				//그렇지 않다면 현재의 다음 노드로 저장 
				else now = now->next;
				break;
			
			//이전으로 이동 
			case '<':
				//현재의 이전 노드가 헤드 노드라면 
				if(now->pre == head)
				    //현재 위치를 헤드 노드의 이전 노드로 저장 
				    now = head->pre;
				//그렇지 않다면 현재의 이전 노드로 저장 
				else now = now->pre;
				break;
				
			//처음부터 재생 
			case 'F':case 'f':
				//now의 값을 헤드의 다음 노드(첫번째 노드)로 변경 
				now = head->next;
				//pre값은 now로 변경 
				pre = now;
				//연속 재생을 위한 반복문 
				while(1){
					//재생 
					now = play(head, now);
					 
					//값이 같은지 확인 
					if(now == pre){
						break;
					}
					//pre값 변경 
					pre = now;
				}
				break;
			
			case 'L':case 'l':
				//now의 값을 헤드의 이전 노드(마지막 노드)로 변경 
				now = head->pre;
				//pre값은 now로 변경 
				pre = now;
				//연속 재생을 위한 반복문 
				while(1){
					//재생 
					now = play(head, now);
					 
					//값이 같은지 확인 
					if(now == pre){
						break;
					}
					//pre값 변경 
					pre = now;
				}
				break;
			
			//전체 리스트 출력 
			case 'A':case 'a':
				display_all(head);
				break;
			
			//메모리 할당 모두 해제 후 종료 
			case 'E':case'e':
				free(head);
				free(now);
				exit(1);
		}
	} 

	return 0;
}





