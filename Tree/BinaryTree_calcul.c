//데이터구조 13주차 과제
//이진트리 연산 프로그래밍
//이진트리를 레벨 순서로 순회(원형큐 사용)
//이진트리를 복사하여 동일한 트리를 반환
//두 개의 이진트리가 동일한지 판단
//이진트리를 좌우로 대칭시킨 트리로 바꾸어 반환
//주어진 트리가 균형트리인지 확인
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_SIZE 100

/*
원래트리 
            이진트리
                15
	          /   \ 
            7     10
          /     /    \
       31     25     16
       
새로만든트리
            이진트리
                15
	          /   \ 
            7     10
          /     /    \
       31     25     16
      /        
    17
   /
 2
*/


//TreeNode 정의 
typedef struct TreeNode{
	int data;
	struct TreeNode *left, *right;
}TreeNode;

//Queue 구조체 
typedef TreeNode *element;
typedef struct{
	element data[MAX_SIZE];
	int front, rear;
}Queue;

//오류 함수 
void error(char *message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//큐 생성 함수 
void init_queue(Queue *q){
	q->front=q->rear = 0;
} 

//공백 상태 검출 함수 
int is_empty(Queue *q){
	return (q->front == q->rear);
}

//포화 상태 검출 함수
int is_full(Queue *q){
	return ((q->rear+1) % MAX_SIZE == q->front);
} 

//삽입 함수
void enqueue(Queue *q, element x){
	if(is_full(q)) error("큐가 포화 상태 입니다");
	q->rear = (q->rear+1) % MAX_SIZE;
	q->data[q->rear] = x;
} 

//삭제 함수
element dequeue(Queue *q){
	if(is_empty(q)) error("큐가 공백 상태 입니다");
	q->front = (q->front +1) % MAX_SIZE;
	return q->data[q->front]; 
} 

//레벨 순회
void level_order(TreeNode *node){
	Queue q;
	init_queue(&q);
	
	//node가 NULL이면 return 
	if(node == NULL) return;
	
	//NULL이 아닐경우  
	enqueue(&q, node);
	//큐가 공백상태일 때까지 dequeue와 enqueue 반복 
	while(!is_empty(&q)){
		node = dequeue(&q);
		
		printf("%d ", node->data);
		if(node->left)
		    enqueue(&q, node->left);
		if(node->right)
		    enqueue(&q, node->right);
	}
	printf("\n");
} 

//복사 합수 
TreeNode* copy(TreeNode *root){
	//TreeNode가 NULL이 아니면 
	if(root != NULL){
		//메모리 공간 malloc 
		TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
		
		//왼쪽 서브트리 복사 
		temp->left = copy(root->left);
		//오른쪽 서브트리 복사 
		temp->right = copy(root->right);
	    //데이터 값 복사 
		temp->data = root->data;
		
		//복사한 결과 반환 
		return temp;
	}
}

//동일 여부 판단 함수
//0 거짓 1 참 
int compare(TreeNode *t1, TreeNode *t2){

    //두 개의 이진트리가 모두 NULL이 아닌 경우 
	if(t1 != NULL && t2 != NULL){
		//비교하는 노드의 데이터값 출력 
		printf("1-> %d 2-> %d\n", t1->data, t2->data);
		//만약 데이터 값이 같지않으면 거짓 반환 
		if(t1->data != t2->data) return 0;
		//데이터 값이 같으면 
	    else{
	    	//왼쪽 값 비교 후 1(참)이 아니면 거짓 반환 
		    if(compare(t1->left, t2->left) != 1) return 0;
		    //왼쪽 값이 참일 경우 
	        else{
	        	// 오른쪽 값 비교, 1이 아니면 거짓 반환
	        	if(compare(t1->right, t2->right) != 1) return 0;
			}
		}
	}
	//참 반환 
	return 1;
}
//대칭 복사 
TreeNode *sym_copy(TreeNode *root){
	//NULL이 아니면 
	if(root != NULL){
		//메모리 공간 malloc 
		TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
		
		//root의 왼쪽 서브트리를 temp의 오른쪽 트리로 복사 
		temp->right = sym_copy(root->left);
		//root의 오른쪽 서브트리를 temp의 왼쪽 트리로 복사 
		temp->left = sym_copy(root->right);
		//데이터 복사 
		temp->data = root->data;
		
		//복사한 결과 반환 
		return temp;
	}
} 

//높이 반환 함수 
int get_height(TreeNode *node){
	int height = 0;
	//노드가 NULL이 아닐 경우 
	if(node != NULL){
		//왼쪽의 높이와 오른쪽의 높이 중 큰 값에 루트높이 1을 더한 후 반환 
		height = 1+max(get_height(node->left), get_height(node->right));
		return height;
	}
}
int main(void) {
	//원래 트리 
	TreeNode n1={31, NULL, NULL};
	TreeNode n2={7, &n1, NULL};
	TreeNode n3={25, NULL, NULL};
	TreeNode n4={16, NULL, NULL};
	TreeNode n5={10, &n3, &n4};
	TreeNode n6={15, &n2, &n5};
	TreeNode *root= &n6;
	
	//비교를 위한 다른 트리 
	TreeNode n9 = {2, NULL, NULL};
	TreeNode n10={17, &n9, NULL};
	TreeNode n11={31, &n10, NULL};
	TreeNode n12={7, &n11, NULL};
	TreeNode n13={25, NULL, NULL};
	TreeNode n14={16, NULL, NULL};
	TreeNode n15={10, &n13, &n14};
	TreeNode n16={15, &n12, &n15};
	TreeNode *root1 = &n16;
	
	//복사한 결과를 저장할 result 트리 
	TreeNode *result = NULL;
	
	//사용자 메뉴를 입력 받을 변수, 높이를 비교하기 위한 변수 
	int usr, h1, h2;
	while(1){
		puts("0. 종료");
		puts("1. 레벨 순회");
		puts("2. 트리 복사");
		puts("3. 동일 판단");
		puts("4. 대칭 복사");
		puts("5. 균형트리 확인"); 
		scanf("%d", &usr); 
		switch(usr){
			//프로그램 종료 
			case 0:
				puts("프로그램을 종료합니다");
				exit(1);
			//출력 메뉴 
			case 1:
				puts("기존 트리 출력");
                level_order(root);
                puts("새로운 트리 출력");
				level_order(root1); 
				break;
			//복사 메뉴 
			case 2:
				//result 변수에 copy한 값을 저장 
			    result = copy(root);
			    //복사 완료 메세지와 함께 원래 트리와 복사한 트리 출력 
			    puts("복사가 완료 되었습니다");
			    puts("====원래 트리====");
				level_order(root);
				puts("====복사한 트리====");
				level_order(result);
				break;
			//비교 메뉴 
			case 3:
				//복사한 트리로 비교와 다른 트리의 비교의 서브메뉴  
				puts("\t1. 복사한 트리와 비교");
				puts("\t2. 다른 트리와 비교");
				scanf("%d", &usr);
				//복사한 트리와 비교 
				if(usr == 1){
					//높이를 비교하여 높이가 다르다면 다른 트리이므로 동일하지 않다는 메세지 출력 
					if(get_height(root) != get_height(result))
					    puts("두 개의 트리는 동일하지 않습니다");
					//1(참)이 반환되었으면 동일 
					else if(compare(root, result) == 1)
				        puts("두 개의 트리는 동일합니다");
				    //그렇지 않으면 비동일 
				    else
				        puts("두 개의 트리는 동일하지 않습니다");
			    }
			    //다른 트리와의 비교 
			    else if(usr == 2){
			    	//높이 비교 
			    	if(get_height(root) != get_height(root1))
					    puts("두 개의 트리는 동일하지 않습니다");
					//참 반환 
					else if(compare(root, root1) == 1)
				        puts("두 개의 트리는 동일합니다");
				    else
				        puts("두 개의 트리는 동일하지 않습니다");
				}
				break;
				
			//대칭 복사 
			case 4:
				//result 변수에 대칭 복사 결과 값 저장 
				result = sym_copy(root);
				//복사 완료 메세지와 함께 원래 트리와 복사한 결과 트리값 출력 
				puts("복사가 완료 되었습니다");
				puts("====원래 트리====");
				level_order(root);
				puts("====복사한 트리====");
				level_order(result); 
				break;
			//균형트리인지 확인하는 메뉴 
			case 5:
				//복사한 트리로 비교, 다른 트리로 비교 서브 메뉴 
				puts("1. 복사한 트리로 비교");
				puts("2. 다른 트리로 비교");
				scanf("%d", &usr);
				// 복사한 트리로 비교 
				if(usr == 1){
					//h1, h2 변수에 각각의 높이 값 저장 
					h1 = get_height(root);
				    h2 = get_height(result);
			    }
			    //다른 트리로 비교 
			    else if(usr == 2){
			    	//각 변수에 각 높이 저장 
			    	h1 = get_height(root);
				    h2 = get_height(root1);
				}
				//두 트리의 높이 값 출력 
			    printf("두 트리의 높이\n1-> %d\t 2-> %d\n", h1, h2);
			    //두 트리의 빼기 연산 값이 1, 0, -1일 경우에만 균형트리 
				if(h1-h2 == -1 || 1 == h1-h2 || h1-h2 == 0)
			        puts("균형트리 입니다");
			    //이외의 값은 비균형 트리 
				else
				    puts("균형트리가 아닙니다.");
			    break; 
		}
	}
	return 0;
}
