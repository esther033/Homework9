#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); //��带 �����Ҵ��Ͽ� �ʱ�ȭ �ϴ� �Լ�

void inorderTraversal(Node* ptr);	  //������ȸƮ�� �Լ�
void preorderTraversal(Node* ptr);    //������ȸƮ�� �Լ�
void postorderTraversal(Node* ptr);	  //������ȸƮ�� �Լ�
int insert(Node* head, int key);  //��带 Ʈ���� �����ϴ� �Լ�
int deleteLeafNode(Node* head, int key);  //������带 �����ϴ� �Լ�
Node* searchRecursive(Node* ptr, int key);  //��ȯ�� ������� ��带 ã�� �Լ�
Node* searchIterative(Node* head, int key);  //�ݺ��� ������� ��带 ã�� �Լ�
int freeBST(Node* head); //�޸𸮸� �����ϴ� �Լ�

int main()
{
	printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //����ڿ��� �޴��� �Է¹��� ����
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

		switch(command) { //commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z  or Z�϶�
			initializeBST(&head); //initailizeBST �Լ� ȣ��
			break;
		case 'q': case 'Q': //command�� q  or Q�϶�
			freeBST(head); //freeBST �Լ� ȣ��
			break;
		case 'n': case 'N': //command�� n  or N�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insert(head, key); //insert �Լ� ȣ��
			break;
		case 'd': case 'D': //command�� d  or D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			deleteLeafNode(head, key); //deleteLeafNode �Լ� ȣ��
			break;
		case 'f': case 'F': //command�� f  or F�϶�
			printf("Your Key = "); 
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			ptr = searchIterative(head, key); //ptr�� searchIterative �Լ� ȣ�� �� ���ϰ� ����
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� ���� �����ϴ� ��� ���
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr�� ���� �������� ������
			break;
		case 's': case 'S': //command�� s  or S�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			ptr = searchRecursive(head->left, key); //ptr�� searchIterative �Լ� ȣ�� �� ���ϰ� ����
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� ���� �����ϴ� ��� ���
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr�� ���� �������� ������
			break;

		case 'i': case 'I': //command�� i or I�϶�
			inorderTraversal(head->left); //inorderTraversal �Լ� ȣ��
			break;
		case 'p': case 'P': //command�� p or P�϶�
			preorderTraversal(head->left); //preorderTraversal �Լ� ȣ��
			break;
		case 't': case 'T': //command�� t or T�϶�
			postorderTraversal(head->left); //postorderTraversal �Լ� ȣ��
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1;
}

int initializeBST(Node** h) {

	if(*h != NULL) //*h�� NULL�� �ƴϸ� �޸� ����
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node)); //*h�� �����Ҵ��Ѵ�
	(*h)->left = NULL;	//h�� ��� ����ü left�� NULL����
	(*h)->right = *h; //h�� ��� ����ü right�� *h ����
	(*h)->key = -9999; //h�� ������� key�� -9999����
	return 1; //�Լ�����
}



void inorderTraversal(Node* ptr)
{
	if(ptr) { //���ȣ���� ���� ��带 ���ʳ��->�Ѹ�-> ������ ��� ������ ����Ѵ�
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right); 
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) { //���ȣ���� ���� ��带 �Ѹ�-> ���ʳ�� ->������ ��� ������ ����Ѵ�
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {  //���ȣ���� ���� ���� ��� -> ������ ��� -> �Ѹ� ������ ����Ѵ�
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node����ü ������ newNode ������ �����Ҵ�
	newNode->key = key; //newNode�� key�� �Ű�����key�� ����
	newNode->left = NULL; //newNode�� left�� NULL����
	newNode->right = NULL; //newNode�� right�� NULL����

	if (head->left == NULL) { //head�� left�� NULL�̸�
		head->left = newNode; //head�� left�� newNode����
		return 1; //�Լ� ����
	}

	Node* ptr = head->left; //Node ����ü ������ ptr�� head�� left����

	Node* parentNode = NULL; //Node ����ü ������ parentNode�� NULL����
	while(ptr != NULL) {
		
		if(ptr->key == key) return 1;//ptr�� key�� �Ű����� key�� ������ �Լ� ����

		parentNode = ptr; //�θ��忡 ptr ����

		if(ptr->key < key) //ptr�� key���� �Ű����� key�� �� Ŭ��
			ptr = ptr->right; //ptr�� ptr�� right����
		else
			ptr = ptr->left; //ptr�� ptr�� left����
	}

	if(parentNode->key > key) //�θ����� key���� key���� Ŭ��
		parentNode->left = newNode; //�θ����� left�� newNode ����
	else
		parentNode->right = newNode; //�θ����� right�� newNode ����
	return 1; //�Լ�����
}

int deleteLeafNode(Node* head, int key) //������带 �����ϴ� �Լ�
{
	if (head == NULL) { //head�� NULL�϶�
		printf("\n Nothing to delete!!\n"); //�����Ұ��� ����
		return -1; //�Լ�����
	}

	if (head->left == NULL) { //head�� left�� NULL�϶�
		printf("\n Nothing to delete!!\n");// �����Ұ��� ����
		return -1; //�Լ�����
	}

	Node* ptr = head->left; //Node����ü ������ ptr ���� �� head�� left����

	Node* parentNode = head; //Node ����ü ������ parentNode�� head����

	while(ptr != NULL) { //ptr�� NULL�϶����� �ݺ�

		if(ptr->key == key) { //ptr�� key�� �Ű����� key�� �����Ҷ�
			if(ptr->left == NULL && ptr->right == NULL) { //�¿��� ��尡 ���� ���

				if(parentNode == head) //�θ��尡 head�� �����Ҷ�
					head->left = NULL; //head�� left�� NULL����

				if(parentNode->left == ptr)//�θ����� left�� ptr�� ���
					parentNode->left = NULL; //�θ����� left�� NULL����
				else
					parentNode->right = NULL; //�θ����� right�� NULL����

				free(ptr); //ptr �޸� ����
			}  
			else {//������尡 �ƴѰ��
				printf("the node [%d] is not a leaf \n", ptr->key); //key���� ������尡 �ƴϴ�
			}
			return 1; //�Լ� ����
		}

		parentNode = ptr; // �θ��忡 ptr ����

		if(ptr->key < key) //ptr�� key�� key���� ������
			ptr = ptr->right; //ptr�� ptr�� right����
		else
			ptr = ptr->left; //ptr�� ptr�� left����


	}

	printf("Cannot find the node for key [%d]\n ", key); //key���� ���� ��带 ã�� �� ����

	return 1; //�Լ� ����
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) //ptr�� NULL�϶�
		return NULL; //NULL����

	if(ptr->key < key) //ptr�� key�� key���� ������
		ptr = searchRecursive(ptr->right, key); //���ȣ���� ���� ���� ���� �̵�
	else if(ptr->key > key) //ptr�� key�� key���� Ŭ��
		ptr = searchRecursive(ptr->left, key); //���ȣ���� ���� ���� ���� �̵�

	return ptr; //ptr ����

}
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; //Node����ü ������ ptr ���� �� head�� left����

	while(ptr != NULL) //ptr�� NULL�϶� ���� �ݺ�
	{
		if(ptr->key == key) //ptr�� key�� �Ű����� key�� �����Ҷ�
			return ptr; //ptr����

		if(ptr->key < key) ptr = ptr->right; //ptr�� key�� key���� ������ ptr�� ptr�� right����
		else
			ptr = ptr->left; //ptr�� ptr�� left����
	}

	return NULL; //NULL����
}

void freeNode(Node* ptr)
{
	if(ptr) { //ptr�� ���� ������
		freeNode(ptr->left); //ptr�� left�޸� ����
		freeNode(ptr->right); //ptr�� right�޸�����
		free(ptr); //ptr�� �޸� ����
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //head�� left�� head�� ������
	{
		free(head); //head �޸�����
		return 1; //�Լ�����
	}

	Node* p = head->left; //Node ������ ����ü p���� �� head�� left�� ����

	freeNode(p); //p �޸�����

	free(head); //head �޸�����
	return 1; //�Լ�����
}





