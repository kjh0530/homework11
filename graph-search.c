//linked list ���·� �׷��� ����
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10 //�׷����� �ִ� vertex ���� 10

typedef struct node //�׷����� ���� ��� ����
{
    int data; //������ data(vertex�� ����)
    struct node* link; //node�� ����Ű�� link
} node;

typedef struct head //������ ����Ʈ ����ü ����
{
    int size; //����Ʈ�� ���� ũ��
    node* nodelist[MAX_SIZE]; //����Ʈ �ִ� ��� ���� ����
} head;

void InitializeGraph(head** h); //�׷����� �ʱ�ȭ�ϴ� �Լ�
void freeGraph(head* h); //�׷����� �Ҵ�� ���� �޸𸮸� free ��Ű�� �Լ�
void insert_Vertex(head* h, int key); //key ���� ���� vertex�� �����ϴ� �Լ�
void insert_Edge(head* h, int key, int key2); //key, key2�� ���� vertex���� �̾��ִ� ������ �����ϴ� �Լ�
void DFS(head* h); //���� �켱 Ž���� �ϰ� �� ������� vertex�� ����ϴ� �Լ�(edge�� �� �� �̻��̸� ���� ���ں��� Ž��)
void BFS(head* h); //�ʺ� �켱 Ž���� �ϰ� �� ������� vertex�� ����ϴ� �Լ�(edge�� �� �� �̻��̸� ���� ���ں��� Ž��)
void printGraph(head* h); //graph�� ����ϴ� �Լ�
int main()
{
    int key, key2;
    char command;
    head* head = NULL;

	printf("[----- ������ 2020039027 -----]\n\n"); //�̸� �й� ���

	do{
		printf("\n\n");
        printf("--------------------------------------------------------------\n");
        printf("\t\t\tGraph Searches\t\t\t\n");
        printf("--------------------------------------------------------------\n");
        printf(" Initialize Graph       = z \n");
        printf(" Insert Vertex          = v \t Insert Edge            = e\n");
        printf(" Depth First Search     = d \t Breath First Searchh   = b\n");
        printf(" Print Graph            = p \t Quit                   = q\n");
        printf("--------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			InitializeGraph(&head);
			break;
		case 'q': case 'Q':
			freeGraph(head);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insert_Vertex(head, key);
			break;
		case 'e': case 'E':
			printf("Your tail, head = ");
			scanf("%d %d", &key, &key2);
			insert_Edge(head, key, key2);
			break;

		case 'd': case 'D':
			DFS(head);
			break;
		case 'b': case 'B':
			BFS(head);
			break;

		case 'p': case 'P':
			printGraph(head);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;

    
}

void InitializeGraph(head** h) 
{
    if(*h!=NULL) //�׷����� ������� ������
    {
        //free
    }
    *h = (head*)malloc(sizeof(head)); //head�� �޸� �����Ҵ�
    (*h)->size = 0; //����Ʈ�� ũ�� 0���� �ʱ�ȭ
    for(int i=0; i<MAX_SIZE; i++) //����Ʈ�� ��� ���� null�� �ʱ�ȭ
    {
        (*h)->nodelist[i] = NULL;
    }
}
void freeGraph(head* h)
{

}
void insert_Vertex(head* h, int key)
{
    if(h->size+1 > MAX_SIZE) //���� �׷����� ������ ��+1�� Max-size ���� Ŭ ��
    {
        printf("graph is full\n");
        return;
    }
    if(key >= MAX_SIZE) //key ���� ������ ���� ū ������ ũ�ų� ���� ��
    {
        printf("�ش� key ���� �׷��� ������� Ů�ϴ�.\n");
        return;
    }
    node* vertex = (node*)malloc(sizeof(node)); //��� �����Ҵ�
    vertex->data = key; //key �� �Ҵ�
    vertex->link = NULL; //link�� NULL�� �ʱ�ȭ
    if(h->nodelist[key] != NULL) //key���� ��尡 �̹� �����Ѵٸ�
    {
        printf("�ش� key�� ���� ������ �̹� �����մϴ�.\n");
        free(vertex);
        return;
    }
    h->nodelist[key] = vertex; //nodelist�� key �ڸ��� vertex �Ҵ�
    h->size++; //size ����
}
void insert_Edge(head* h, int key, int key2)
{
    if(h->nodelist[key] == NULL || h->nodelist[key2] == NULL)
    //key ���� �ش��ϴ� vertex�� �������� ���� ��
    {
        printf("�ش� key�� ���� vertex�� �������� �ʽ��ϴ�.\n");
        return;
    }
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = key2;
    newnode->link = NULL;
    node* temp = h->nodelist[key];
    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = newnode;

    node* newnode2 = (node*)malloc(sizeof(node));
    newnode2->data = key;
    newnode2->link = NULL;
    temp = h->nodelist[key2];
    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = newnode2;
}
void DFS(head* h)
{

}
void BFS(head* h)
{

}
void printGraph(head* h)
{

    for(int i=0; i<MAX_SIZE; i++)
    {
        if(h->nodelist[i] != NULL)
        {
            printf("%d�� ���� ��� : ", h->nodelist[i]->data);
            node* temp = h->nodelist[i]->link;
            while(temp != NULL)
            {
                printf("%d ", temp->data);
                temp = temp->link;
            }
            printf("\n");
        }
    }
}