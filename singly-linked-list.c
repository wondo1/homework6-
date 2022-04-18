#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node { // typedef ����� listNode ����ü ����
	int key; // ������ ���� ���� 
	struct Node* link; // ��ũ ��� ����
} listNode;

typedef struct Head { // typedef ����� headNode ����ü ����
	struct Node* first; // first ��� ����
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); // �ʱ�ȭ �Լ� 
int freeList(headNode* h); // ����Ʈ �޸� ��ü �Լ� 

int insertFirst(headNode* h, int key); // ù��° ��� �Լ�
int insertNode(headNode* h, int key); //  ��� ���� �Լ� 
int insertLast(headNode* h, int key); // ������ ��� �Լ�

int deleteFirst(headNode* h); // ù��° ��� ���� �Լ�
int deleteNode(headNode* h, int key); // ��� ���� �Լ�
int deleteLast(headNode* h); // ������ ��� ���� �Լ�
int invertList(headNode* h); // ����Ʈ ���� �Լ� 

void printList(headNode* h); // ����Ʈ ��� �Լ� 

int main()
{
	char command; // ������ ���� ����
	int key; // ������ ���� ���� 
	headNode* headnode=NULL; // ����� null �� 
    printf("[----- [�����] [2018038099] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // ��� �ʱ�ȭ 
			break;
		case 'p': case 'P':
			printList(headnode); // ����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է� 
			insertNode(headnode, key); // �Էµ� �� ��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			deleteNode(headnode, key); // �Էµ� �� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertLast(headnode, key); // �Էµ� ���� ������ ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); // ������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertFirst(headnode, key); // �Էµ� ���� ù��° ��ġ�� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); // ù��° ��� ���� 
			break;
		case 'r': case 'R':
			invertList(headnode); // ���� ���ġ 
			break;
		case 'q': case 'Q':
			freeList(headnode); // �޸� ���� 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) { // �ʱ�ȭ �Լ� 

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL) // h�� null�� �ƴϸ�
		freeList(h); // �޸� ��ü 

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // temp�� �����޸� �Ҵ� 
	temp->first = NULL; // first ��� null �� 
	return temp; // temp ��ȯ 
}

int freeList(headNode* h){ // �޸� ���� �Լ� 
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; // p�� first ����

	listNode* prev = NULL; // prev null �� 
	while(p != NULL) { // p�� null�� �ƴϸ� �ݺ�
		prev = p; // p�� ���� 
		p = p->link; // p�� ���� ��� ����
		free(prev); // prev �����޸� ���� 
	}
	free(h); // h �����޸� ���� 
	return 0; // 0�� ��ȯ 
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { // ��� ���� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key; // ��忡 �Էµ� Ű�� ���� 
	node->link = NULL; // link null ��

	if (h->first == NULL) // ù��° ��尡 null �̸� 
	{
		h->first = node; // node�� ���� 
		return 0; // 0�� ��ȯ
	}

	listNode* n = h->first; // n�� first�� ����
	listNode* trail = h->first; // trail�� first�� ���� 

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { // n�� NULL�̸� �ݺ�
		if(n->key >= key) { // ��� Ű�� �Էµ� Ű�� ���ų� ũ��
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { // n �� first�� ������
				h->first = node; // first�� ��尪 ����
				node->link = n; // link�� n �� ���� 
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n; // ��� link�� n�� ����
				trail->link = node; // trail link�� node �� ���� 
			}
			return 0; // 0 �� ��ȯ 
		}

		trail = n; // n�� ���� 
		n = n->link; // link�� ���� 
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node; // trail link�� ��尪 ����
	return 0; // 0 �� ��ȯ
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) { // ������ ��� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸��Ҵ� 
	node->key = key; // key�� ����
	node->link = NULL; // null �� ���� 

	if (h->first == NULL) // first�� null�̸� 
	{
		h->first = node; // first�� node�� ���� 
		return 0; // 0 �� ��ȯ
	}

	listNode* n = h->first; // n �� first�� ����
	while(n->link != NULL) { // link�� null�� �ƴϸ� �ݺ�
		n = n->link; // n�� link �� ���� 
	}
	n->link = node; // link�� node�� ���� 
	return 0; // 0�� ��ȯ
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) { // ù��° ��� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key; // key�� ����

	node->link = h->first; // ��� link�� ����� ����Ű�� first�� ���� 
	h->first = node; // first�� node ���� 

	return 0; // 0 �� ��ȯ 
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) { // ��� ���� �Լ� 

	if (h->first == NULL) // first �� null �̸�
	{
		printf("nothing to delete.\n"); // ���
		return 0; // 0�� ��ȯ
	}

	listNode* n = h->first; // n�� ����� ����Ű�� first ���� 
	listNode* trail = NULL; // trail�� null �� 

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { // n�� null�� �ƴϸ� �ݺ� 
		if(n->key == key) { // ��� Ű�� �Է� Ű�� ������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { // n�� first�� ������ 
				h->first = n->link; // first�� link�� ���� 
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link; // trail�� ����Ű�� link�� n�� ����Ű�� link�� ���� 
			}
			free(n); // �����޸� ���� 
			return 0; // 0�� ��ȯ 
		}

		trail = n; //n �� ���� 
		n = n->link; // n�� ����Ű�� link�� ���� 
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) { // ������ ��� ���� �Լ� 

	if (h->first == NULL) // first�� null�� ������
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // n�� ����� ����Ű�� first ����
	listNode* trail = NULL; // trail�� null ��

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) { // link�� null�� ������ 
		h->first = NULL; // first�� null �� 
		free(n); // �����޸� ����
		return 0; // 0 �� ��ȯ
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) { // link�� null�� �ƴϸ� �ݺ�
		trail = n; // n �� ���� 
		n = n->link; // n�� ����Ű�� link�� ����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL; // trail �� ����Ű�� link�� null �� 
	free(n); // �޸� ���� 

	return 0; // 0�� ��ȯ 
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) { // ù��° ��� ���� �Լ� 

	if (h->first == NULL) // first�� null�� ������ 
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // n�� ����� ����Ű�� first ����

	h->first = n->link; // ����� ����Ű�� first�� ��� link�� ����
	free(n); // �޸� ���� 

	return 0; // 0 �� ��ȯ
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) { // ���� ���ġ �Լ� 


	if(h->first == NULL) { // first�� null�� ������
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; // ������ n�� first�� ����
	listNode *trail = NULL; // ������ trail�� null�� 
	listNode *middle = NULL; // ������ middle�� null��

	while(n != NULL){ // n�� null �� �ƴϸ� �ݺ�
		trail = middle; // trail �� middle�� 
		middle = n; // middle�� n�� 
		n = n->link; // n�� ���� ��� ��
		middle->link = trail; // middle ���� ��忡 trail �� 
	}

	h->first = middle; // first�� middle�� 

	return 0;
}


void printList(headNode* h) { // ����Ʈ ��� �Լ� 
	int i = 0; // ������ ���� ���� i�� 0 ���� 
	listNode* p; // p��� ���� 

	printf("\n---PRINT\n");

	if(h == NULL) { // h�� null �̸�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p�� first�� ���� 

	while(p != NULL) { // p�� null �� �ƴϸ� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; // p�� p���� �� ���� 
		i++; // i+1
	}

	printf("  items = %d\n", i);
}

