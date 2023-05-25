#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); //노드를 동적할당하여 초기화 하는 함수

void inorderTraversal(Node* ptr);	  //중위순회트리 함수
void preorderTraversal(Node* ptr);    //전위순회트리 함수
void postorderTraversal(Node* ptr);	  //후위순회트리 함수
int insert(Node* head, int key);  //노드를 트리에 삽입하는 함수
int deleteLeafNode(Node* head, int key);  //리프노드를 삭제하는 함수
Node* searchRecursive(Node* ptr, int key);  //순환법 방식으로 노드를 찾는 함수
Node* searchIterative(Node* head, int key);  //반복법 방식으로 노드를 찾는 함수
int freeBST(Node* head); //메모리를 해제하는 함수

int main()
{
	printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 메뉴를 입력받을 변수
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { //commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z  or Z일때
			initializeBST(&head); //initailizeBST 함수 호출
			break;
		case 'q': case 'Q': //command가 q  or Q일때
			freeBST(head); //freeBST 함수 호출
			break;
		case 'n': case 'N': //command가 n  or N일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insert(head, key); //insert 함수 호출
			break;
		case 'd': case 'D': //command가 d  or D일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			deleteLeafNode(head, key); //deleteLeafNode 함수 호출
			break;
		case 'f': case 'F': //command가 f  or F일때
			printf("Your Key = "); 
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			ptr = searchIterative(head, key); //ptr에 searchIterative 함수 호출 후 리턴값 저장
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 값이 존재하는 경우 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr의 값이 존재하지 않을때
			break;
		case 's': case 'S': //command가 s  or S일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			ptr = searchRecursive(head->left, key); //ptr에 searchIterative 함수 호출 후 리턴값 저장
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 값이 존재하는 경우 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr의 값이 존재하지 않을때
			break;

		case 'i': case 'I': //command가 i or I일때
			inorderTraversal(head->left); //inorderTraversal 함수 호출
			break;
		case 'p': case 'P': //command가 p or P일때
			preorderTraversal(head->left); //preorderTraversal 함수 호출
			break;
		case 't': case 'T': //command가 t or T일때
			postorderTraversal(head->left); //postorderTraversal 함수 호출
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	if(*h != NULL) //*h가 NULL이 아니면 메모리 해제
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node)); //*h를 동적할당한다
	(*h)->left = NULL;	//h의 멤버 구조체 left에 NULL저장
	(*h)->right = *h; //h의 멤버 구조체 right에 *h 저장
	(*h)->key = -9999; //h의 멤버변수 key에 -9999저장
	return 1; //함수종료
}



void inorderTraversal(Node* ptr)
{
	if(ptr) { //재귀호출을 통해 노드를 왼쪽노드->뿌리-> 오른쪽 노드 순으로 출력한다
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right); 
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) { //재귀호출을 통해 노드를 뿌리-> 왼쪽노드 ->오른쪽 노드 순으로 출력한다
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {  //재귀호출을 통해 왼쪽 노드 -> 오른쪽 노드 -> 뿌리 순으로 출력한다
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node구조체 포인터 newNode 선언후 동적할당
	newNode->key = key; //newNode의 key에 매개변수key값 저장
	newNode->left = NULL; //newNode의 left에 NULL저장
	newNode->right = NULL; //newNode의 right에 NULL저장

	if (head->left == NULL) { //head의 left가 NULL이면
		head->left = newNode; //head의 left에 newNode저장
		return 1; //함수 종료
	}

	Node* ptr = head->left; //Node 구조체 포인터 ptr에 head의 left저장

	Node* parentNode = NULL; //Node 구조체 포인터 parentNode에 NULL저장
	while(ptr != NULL) {
		
		if(ptr->key == key) return 1;//ptr의 key와 매개변수 key가 같을때 함수 종료

		parentNode = ptr; //부모노드에 ptr 저장

		if(ptr->key < key) //ptr의 key보다 매개변수 key가 더 클때
			ptr = ptr->right; //ptr에 ptr의 right저장
		else
			ptr = ptr->left; //ptr에 ptr의 left저장
	}

	if(parentNode->key > key) //부모노드의 key값이 key보다 클때
		parentNode->left = newNode; //부모노드의 left에 newNode 저장
	else
		parentNode->right = newNode; //부모노드의 right에 newNode 저장
	return 1; //함수종료
}

int deleteLeafNode(Node* head, int key) //리프노드를 삭제하는 함수
{
	if (head == NULL) { //head가 NULL일때
		printf("\n Nothing to delete!!\n"); //삭제할것이 없다
		return -1; //함수종료
	}

	if (head->left == NULL) { //head의 left가 NULL일때
		printf("\n Nothing to delete!!\n");// 삭제할것이 없다
		return -1; //함수종료
	}

	Node* ptr = head->left; //Node구조체 포인터 ptr 선언 후 head의 left저장

	Node* parentNode = head; //Node 구조체 포인터 parentNode에 head저장

	while(ptr != NULL) { //ptr이 NULL일때까지 반복

		if(ptr->key == key) { //ptr의 key가 매개변수 key가 동일할때
			if(ptr->left == NULL && ptr->right == NULL) { //좌우측 노드가 없는 경우

				if(parentNode == head) //부모노드가 head와 동일할때
					head->left = NULL; //head의 left에 NULL저장

				if(parentNode->left == ptr)//부모노드의 left가 ptr인 경우
					parentNode->left = NULL; //부모노드의 left가 NULL저장
				else
					parentNode->right = NULL; //부모노드의 right에 NULL저장

				free(ptr); //ptr 메모리 해제
			}  
			else {//리프노드가 아닌경우
				printf("the node [%d] is not a leaf \n", ptr->key); //key값이 리프노드가 아니다
			}
			return 1; //함수 종료
		}

		parentNode = ptr; // 부모노드에 ptr 저장

		if(ptr->key < key) //ptr의 key가 key보다 작을때
			ptr = ptr->right; //ptr에 ptr의 right저장
		else
			ptr = ptr->left; //ptr에 ptr의 left저장


	}

	printf("Cannot find the node for key [%d]\n ", key); //key값에 대한 노드를 찾을 수 없다

	return 1; //함수 종료
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) //ptr의 NULL일때
		return NULL; //NULL리턴

	if(ptr->key < key) //ptr의 key가 key보다 작을때
		ptr = searchRecursive(ptr->right, key); //재귀호출을 통해 우측 노드로 이동
	else if(ptr->key > key) //ptr의 key가 key보다 클때
		ptr = searchRecursive(ptr->left, key); //재귀호출을 통해 좌측 노드로 이동

	return ptr; //ptr 리턴

}
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; //Node구조체 포인터 ptr 선언 후 head의 left저장

	while(ptr != NULL) //ptr이 NULL일때 까지 반복
	{
		if(ptr->key == key) //ptr의 key가 매개변수 key가 동일할때
			return ptr; //ptr리턴

		if(ptr->key < key) ptr = ptr->right; //ptr의 key가 key보다 작을때 ptr에 ptr의 right저장
		else
			ptr = ptr->left; //ptr에 ptr의 left저장
	}

	return NULL; //NULL리턴
}

void freeNode(Node* ptr)
{
	if(ptr) { //ptr의 값이 있을때
		freeNode(ptr->left); //ptr의 left메모리 해제
		freeNode(ptr->right); //ptr의 right메모리해제
		free(ptr); //ptr의 메모리 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //head의 left와 head가 같을때
	{
		free(head); //head 메모리해제
		return 1; //함수종료
	}

	Node* p = head->left; //Node 포인터 구조체 p선언 후 head의 left에 저장

	freeNode(p); //p 메모리해제

	free(head); //head 메모리해제
	return 1; //함수종료
}





