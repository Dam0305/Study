//원형큐 사용해서 미팅 중개 프로그램 만들기
//두 개의 원형 큐 -> 남학생, 여학생의 대기 큐
//새로운 남(여)학생이 등록을 하면 여(남)학생 큐에서 삭제하여 미팅 성사
//큐에 대기하고 있는 학생이 없으면 큐에 들어가서 대기
//랜덤으로 발생되는 홀수와 짝수로 남녀 구분
//전체 100명의 학생
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef int element;
//큐 타입 
typedef struct{
	element data[MAX];
	int front, rear;
}QUEUE;

//오류 함수 
void error(char *message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화 함수 
void init_queue(QUEUE *q){
	q->front = q->rear = 0;
} 

//공백 상태 검출 함수 
int is_empty(QUEUE *q){
	return (q->front == q->rear);
} 

//포화상태 검출 함수 
int is_full(QUEUE *q){
	return ((q->rear+1)%MAX == q->front);
} 

//출력 함수 
void queue_print(QUEUE *q){
	printf("QUEUE (front = %d rear = %d) = ", q->front, q->rear);
	if(!is_empty(q)){
		int i = q->front;
		do{
			i=(i+1)%MAX;
			printf("%d | ", q->data[i]);
			if(i== q->rear)
			    break;
		}while(i != q->front);
	}
	printf("\n");
}

//삽입 함수
void enqueue(QUEUE *q, element item){
	if(is_full(q))
	    error("큐가 포화상태입니다.");
	q->rear = (q->rear +1) % MAX;
	q->data[q->rear] = item; 
} 

//삭제 함수
element dequeue(QUEUE *q){
	if(is_empty(q))
	    error("큐가 공백 상태입니다.");
	q->front = (q->front+1)%MAX;
	return q->data[q->front]; 
} 

//확인 함수
element peek(QUEUE *q){
	if(is_empty(q))
	    error("큐가 공백상태입니다.");
	    return q->data[(q->front + 1) %MAX];
} 

int main(void){
	//여학생과 남학생을 담을 큐 
	QUEUE women;
	QUEUE men;
	//반복문을 위한 변수, 난수 저장할 변수, 남자 및 여자의 인원수를 저장하기 위한 변수 선언 
	int i, who, w_cnt=0, m_cnt=0, match=0;
	//여자 이름, 남자 이름을 지정하기 위한 변수
	int woman = 1 , man = 1; 
	
	// 두 큐를 초기화 
	init_queue(&women);
	init_queue(&men);
	srand(time(NULL));
	
	for(i=0; i<100; i++){
		//난수 발생
		who = rand()%100;
		//짝수면 여자 홀수면 남자로 가정 
		if(who%2 == 0){
			//난수 발생 시 중복이 있으므로 여학생의 이름을 출력, 
			printf("%d 여학생\n", woman);
			//그 이름으로 큐에 삽입 
			enqueue(&women, woman);
			//여학생의 수와 이름의 수 증가	
			w_cnt++;woman++;
		}
		else{
			//남학생 
			printf("\t%d 남학생\n", man);
			enqueue(&men, man);
			m_cnt++;man++;
		}
		//만약 여학생의 수와 남학생의 수가 0 이상이라면 매칭 가능한 상태이므로
		//매칭 진행 
		if(w_cnt>0 && m_cnt>0){
			//성사된 미팅의 수 증가 
			match++;
			//매칭된 학생들의 정보를 보여주기 위한 변수 선언 
			int matched_woman, matched_man;
			//여학생, 남학생 모두 dequeue 
			matched_woman = dequeue(&women);
			matched_man = dequeue(&men);
      
			//미팅 성사 안내 메세지 출력 
			printf("매칭이 성사 되었습니다. %d 여학생 %d 남학생\n", matched_woman, matched_man);
			//여학생, 남학생의 수를 감소 
			w_cnt--;
			m_cnt--;
		}
	}
	//최종 결과 출력 
	printf("\n여학생 수 : %d, 남학생 수 : %d, 성사된 미팅의 수: %d\n", woman-1, man-1, match);
	
	
	return 0;
}
