//원형 큐 사용하여 2명의 은행의 창구행원이 서비스하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
	int id;
	int arrival_time;
	int service_time;
}element;
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


int main(void) {
	int minutes = 60;
	int total_wait = 0;
	int total_customers = 0;
	int service_time_1 = 0, service_time_2 = 0;
	int service_customer_1, service_customer_2;
	
	QUEUE staff_1;
	int clock;
	
	//큐 초기화 
	init_queue(&staff_1);
	srand(time(NULL));
	
	for(clock = 0; clock < minutes; clock++){
		printf("\n현재시각= %d\n\n", clock);
		//은행원에게 업무 받을 고객 생성 
		if((rand()%10) < 3){
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3+1;
			enqueue(&staff_1, customer);
		    printf("고객 %d이 %d분에 들어옵니다. 업무처리시간 = %d분\n",
			        customer.id, customer.arrival_time, customer.service_time);
		}
		//1번 은행원이 고객 응대 중 
		if(service_time_1 > 0){
			printf("A창구에서 고객 %d 업무 처리중입니다. \n", service_customer_1);
			service_time_1--;
		}
		//1번 은행원이 고객 응대 중이 아닐 때 
		else{
			if(!is_empty(&staff_1)){
				//은행원 큐에서 dequeue, 
				element customer = dequeue(&staff_1);
				service_customer_1 = customer.id;
				service_time_1 = customer.service_time;
				//A창구에서 업무 시작이라는 메세지 출력 
				printf("고객 %d 이 %d분에 A에서 업무를 시작합니다 대기시간은 %d분이었습니다. \n",
				        customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
		//2번 은행원이 고객 응대 중 
		if(service_time_2 > 0){
			printf("B창구에서 고객 %d 업무 처리중입니다. \n", service_customer_2);
			service_time_2--;
		}
		//2번 은행원이 고객 응대 중이 아닐 때 
		else{
			//은행원 큐에서 dequeue 
			if(!is_empty(&staff_1)){
				element customer = dequeue(&staff_1);
				service_customer_2 = customer.id;
				service_time_2 = customer.service_time;
				//B창구에서 업무 시작이라는 메세지 출력 
				printf("고객 %d 이 %d분에 B에서 업무를 시작합니다 대기시간은 %d분이었습니다. \n",
				        customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
	}
	
	printf("전체 대기 시간 %d 분\n", total_wait);
	
	return 0;
}
