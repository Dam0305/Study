//이진탐색프로그래밍
//C언어 소스코드 파일에 각 예약어가 얼마나 자주 등장하는지 계산
//임의의 C파일을 bst_in.txt로 지정, 출현빈도 파일 bst_out.txt로 지정
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10 //단어길이 
#define STRMAX 256 //파일 읽어올 버퍼 길이 

//트리노드 정의 
typedef struct TreeNode{
	//예약어 
	char reserved_w[MAX];
	//빈도수 
	int cnt;
	//자식트리 
	struct TreeNode *left, *right;
}TreeNode;

//노드 생성 함수 
//예약어를 저장한 char형 변수를 매개변수로 설정 
TreeNode* new_node(char *w){
	//메모리 malloc 
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	//예약어 복사 
	strcpy(temp->reserved_w, w);
	//빈도수 1로 초기화 
	temp->cnt = 1;
	
	//자식노드 NULL설정 
	temp->left = temp->right = NULL;
	//생성한 노드 반환 
	return temp;
}

//노드 삽입 함수 
//노드와 문자열 매개변수로 설정 
TreeNode* insert(TreeNode *node, char *w){
	//노드가 NULL이면 새로운 노드 생성 
	if(node == NULL) return new_node(w);
	
	//문자열 비교해서 -1이면
	//삽입하려는 예약어가 더 작은 것이므로 왼쪽 자식트리에 삽입 
	if(strcmp(w, node->reserved_w) == -1)
	    node->left = insert(node->left, w);
	    
	//문자열 비교 후 1이면 삽입하려는 예약어가 더 큰 것이므로 오른쪽 자식 트리에 삽입 
	else if(strcmp(w, node->reserved_w) == 1)
	    node->right = insert(node->right, w);
	    
	//문자열이 같다면 이미 존재한다는 것이므로 빈도수 1증가 
	else if(strcmp(w, node->reserved_w) == 0)
	    node->cnt++;
	
	//노드 반환 
	return node;
}

//이진탐색트리 생성 함수 
TreeNode* creat(TreeNode *root){
	//파일을 읽기 모드로 오픈 
	FILE *f = fopen("bst_in.txt", "r");
	
	//파일 포인터가 NULL이면 read 실패, 프로그램 종료 
	if(f == NULL){
		printf("Read Fail!");
		exit(1);
	}
	
	//파일에서 읽어올 버퍼 
	char buffer[STRMAX];
	//예약어 리스트 
	char reserved_list[MAX][MAX] = {"break", "case", "do", "else", "for", "if", "int", "return", "switch", "while"};
	int i;
	
	//파일이 EOF 만날 때까지 반복 
	while(!feof(f)){
		//버퍼에 파일 내용 저장 
		fgets(buffer, STRMAX, f);
		
		//버퍼에 저장된 내용을 개행문자, 탭, 공백으로 토큰화 
		char *ptr = strtok(buffer, "\n\t ");
		//포인터가 널이 아닐 때까지 반복 
		while(ptr != NULL){
			//반복문을 통해 문자열 포인터랑 예약어 리스트랑 비교 
			for(i=0; i<MAX; i++){
				//비교해서 같은 경우에 트리에 삽입 
			    if(strcmp(ptr, reserved_list[i]) == 0){
			    	printf("%s\n", ptr); 
			    	root = insert(root, ptr);
		    	}
	    	}
	    	//토큰화 
	    	ptr = strtok(NULL, "\n\t ");
		}
	}
	//파일 닫기 
	fclose(f);
	//루트 반환 
	return root;
}

//파일에 쓰기 함수 
//중위순회를 돌 때 파일을 오픈해서 쓰는 것만 하는 함수 
//매개변수로 예약어 문자열과 빈도수 
void file_write(char *w, int c){
	//파일을 추가모드로 오픈 
	FILE * f = fopen("bst_out.txt", "a+");
		
	//NULL인 경우 쓰기 실패, 프로그램 종료 
	if(f == NULL) {
	    printf("Write Fail!");
		exit(1);
	}
	//오픈된 파일에 예약어와 빈도수 작성 
	fprintf(f, "%s\t%d\n", w, c);
	//파일 닫기 
	fclose(f);
}

//쓰기를 위한 중위순회 함수 
void inorder_write(TreeNode *root){
	//루트가 NULL이 아닐 경우 
	if(root != NULL){
		//순환 함수 
		inorder_write(root->left);
		//파일 쓰기 함수에 예약어와 빈도수 넘겨주어 파일에 작성 
		file_write(root->reserved_w, root->cnt);
		inorder_write(root->right);
	}
}

//중위순회로 출력하는 함수 
void inorder(TreeNode *root){
	if(root != NULL){
		inorder(root->left);
		printf("%s\t%d\n", root->reserved_w, root->cnt);
		inorder(root->right);
	}
}

//최대값을 가지고 있는 노트의 포인터 반환 
TreeNode* find_max(TreeNode *root){
	if(root != NULL){
		//후위 순회 순서로 왼쪽의 최대값과 오른쪽의 최대값을 탐색 
		TreeNode *Lmax = find_max(root->left);
		TreeNode *Rmax = find_max(root->right);
		
		//왼쪽의 최대값 포인터가 NULL이 아닐 경우 
		if(Lmax != NULL)
		    //루트의 데이터 값과 비교하여서 더 큰 값의 포인터 반환 
			return ((root->cnt >= Lmax->cnt) ? root : Lmax);
		else
		    //NULL일 경우에는 루트 반환 
			return root;
		//오른쪽의 최대값 포인터가 NULL이 아닐 경우 
		if(Rmax != NULL)
		    //루트의 데이터 값과 비교하여 더 큰 값의 포인터 반환 
			return ((root->cnt >= Rmax->cnt) ? root : Rmax);
		else
			return root;
	}
}

int main(void) {

	int usr;
	//루트 노드 NULL로 초기화 
	TreeNode *root = NULL;

	while(1){
		puts("0. 종료");
		puts("1. 이진탐색트리 생성");
		puts("2. 이진탐색트리 중위순회");
		puts("3. 자주 사용된 예약어");
		puts("4. 파일에 쓰기");
		scanf("%d", &usr);
		switch(usr){
			//종료 메뉴 
			case 0:
				puts("프로그램을 종료 합니다");
				free(root);
				exit(1);
			
			//이진탐색트리 생성 함수 
			case 1:
				//루트에 생성한 트리 저장 
				puts("저장된 예약어"); 
				root = creat(root);
				//완료했다는 메세지 출력 
				puts("이진탐색트리 생성을 완료했습니다");
				break; 
			
			//중위순회로 출력 메뉴 
			case 2: 
				puts("==================");
				//예약어와 빈도수 안내 메세지 출력 
				puts("예약어\t빈도수");
				puts("------------------");
				//중위순회 돌면서 내용 출력 
				inorder(root);
				puts("==================");
				break;
			
			//가장 자주 사용된 예약어 출력 메뉴  
			case 3:
			    puts("==================");
			    puts("예약어\t빈도수");
			    puts("------------------");
			    //max 변수에 함수 결과 저장 
			    TreeNode *max = find_max(root);
			    //값 출력 
				printf("%s\t%d\n", max->reserved_w, max->cnt);
				puts("==================");
				break;
			
			//파일에 쓰기 메뉴 
			case 4:
			    inorder_write(root);
			    puts("파일을 저장했습니다");
			    break;
		} 
	}
	
	return 0;
}
