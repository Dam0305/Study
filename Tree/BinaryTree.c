//중위순회, 전위순회, 후위순회 순서 출력
//이진 트리의 모든 노드들의 데이터 값을 1씩 증가
//이진트리의 모든 노드들의 데이터 값의 총합 계산
//이진트리의 노드들의 데이터 값들 중 최대 값을 갖는 노드들을 찾아 포인터 반환
#include <stdio.h>
#include <stdlib.h>

/*
            이진트리
                15
	          /   \ 
            7     10
          /     /    \
       31     25     16
      /         \
    4            13
TOTAL : 121
*/

//노드 정의 
typedef struct TreeNode{
	int data;
	struct TreeNode *left, *right;
}TreeNode;

//중위 순회 
void inorder(TreeNode *root){
	if(root != NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}
//후위 순회 
void postorder(TreeNode *root){
	if(root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}
//전위 순회 
void preorder(TreeNode *root){
	if(root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//모든 노드의 데이터 값에 1씩 더하는 함수 
void add(TreeNode *root){
	if(root != NULL){
		//후위 순회로 돌면서 값 더해줌 
		add(root->left);
		add(root->right);
		root->data++;
	}
}

//모든 노드 데이터 값의 총 합을 구하는 함수 
int add_all(TreeNode *root){
	if(root != NULL){
		//오른쪽 노드의 데이터 값과 왼쪽 노드의 데이터 값, 그리고 루트의 데이터를 합한 결과를 반환 
		return((add_all(root->right)+add_all(root->left))+root->data);
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
			return ((root->data >= Lmax->data) ? root : Lmax);
		else
		    //NULL일 경우에는 루트 반환 
			return root;
		//오른쪽의 최대값 포인터가 NULL이 아닐 경우 
		if(Rmax != NULL)
		    //루트의 데이터 값과 비교하여 더 큰 값의 포인터 반환 
			return ((root->data >= Rmax->data) ? root : Rmax);
		else
			return root;
	}
}

//기준 수보다 이하인 값 출력 
//기준 값과 루트 매개변수로 전달 받음 
void under(TreeNode *root, int n){
	if(root!= NULL){
		//후위순회 순서로 찾으면서 출력 
		under(root->left, n);
		under(root->right, n);
		//루트의 데이터 값이 전달 받은 기준 값보다 작을 경우 출력 
		if(root->data <= n)
		    printf("%d보다 작은 노드의 값 : %d\n", n, root->data);
	}
}

//자식 노드가 1개인 노드의 개수 
int find_one_child(TreeNode *root){
	int n=0;
	
	if(root != NULL){
		//왼쪽에 값이 존재하고 오른쪽에 값이 존재 하지 않는 경우거나
		//왼쪽에 값이 존재하지 않고 오른쪽에 값이 존재하는 경우 
		if((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL)){
			//어떤 노드인지 출력 
			printf("노드의 값 -> %d\n", root->data);
			//개수의 값인 n에 1을 더하고 왼쪽과 오른쪽을 순회하면서 반환받은 값을 덧셈 
			return (n+1)+find_one_child(root->left)+find_one_child(root->right);
		}
		//그렇지 않은 경우에는
		//늘어나지 않은 개수의 값 n과 왼쪽과 오른쪽을 순회하면서 반환 받은 값을 덧셈 
		else return n+find_one_child(root->left)+find_one_child(root->right);
	}
	//최종적인 n 반환 
	return n;
} 

int main(void) {
	//노드 
	TreeNode n7 = {13, NULL, NULL};
	TreeNode n0 = {4, NULL, NULL};
	TreeNode n1 = {31, &n0, NULL};
    TreeNode n2 = {7, &n1, NULL};
    TreeNode n3 = {25, NULL, &n7};
    TreeNode n4 = {16, NULL, NULL};
    TreeNode n5 = {10, &n3, &n4};
    TreeNode n6 = {15, &n2, &n5};
    TreeNode *root = &n6;
    
	int usr, n;
	
	while(1){
		puts("0. 종료");
		puts("1. 전위순회");
		puts("2. 중위순회");
		puts("3. 후위순회");
		puts("4. 모든 노드에 1씩 증가");
		puts("5. 모든 노드의 데이터 값의 총합");
		puts("6. 최대값");
		puts("7. 기준 수보다 이하 값 찾기");
		puts("8. 자식 노드 1개인 노드의 개수"); 
		scanf("%d", &usr);
		switch(usr){
			case 0:
				puts("종료합니다"); 
				exit(1);
			case 1:
				puts("======전위순회======");
				preorder(root);
				printf("\n"); 
				break;
			case 2:
				puts("======중위순회======");
				inorder(root);
				printf("\n");
				break;
			case 3:
				puts("======후위순회======");
				postorder(root);
				printf("\n");
				break;
			case 4:
				puts("======덧    셈======");
				//더하기 이전 값 출력 
				puts("Before");
				preorder(root);
				printf("\n");
				//덧셈 함수 진행 
				add(root);
				//덧셈 진행 후 값 출력 
				puts("After");
				preorder(root);
				printf("\n");
				break;
			case 5:
			    puts("====모든 값 덧셈====");
			    //함수를 진행하여 반환받은 값을 바로 출력 
				printf("결과 -> %d", add_all(root));
				printf("\n");
				break;
			case 6:
				puts("=====최  대  값=====");
				//함수를 진행하여 반환받은 포인터의 데이터 값 출력 
				printf("%d\n", find_max(root)->data);
			    break; 
			case 7:
				puts("====기준 값 이하====");
				puts("기준 값을 입력해 주세요");
				scanf("%d", &n);
				under(root, n);
				break;
			case 8:
				puts("====자식노드가 1개인 노드====");
				//함수를 진행하여 반환 받은 값을 바로 출력 
				printf("총 %d개\n", find_one_child(root));
			    break; 
		} 
	} 
	return 0;
}
