//linked list ���·� �׷��� ����
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10 //�׷����� �ִ� vertex ���� 10

typedef struct graphNode //�׷����� ���� ��� ����
{
    int data; //������ data(vertex�� ����)
    struct graphNode* link; //node�� ����Ű�� link
} graphNode;

typedef struct graphHead //������ ����Ʈ�� ���� ����ü ����
{
    int size; //����Ʈ�� ���� ũ��
    graphNode* nodelist[MAX_SIZE]; //����Ʈ �ִ� ��� ���� ����
} graphHead;

typedef struct GQueue //ť ����ü ����
{
    int queue[MAX_SIZE]; //ť�� ������ ���� ������ �迭
    int front, rear; //ť�� front, rear ������ ����
} GQueue;



void InitializeGraph(graphHead** h); //�׷����� �ʱ�ȭ�ϴ� �Լ�
void freeGraph(graphHead* h); //�׷����� �Ҵ�� ���� �޸𸮸� free ��Ű�� �Լ�
void insert_Vertex(graphHead* h); //key ����ŭ vertex�� �����ϴ� �Լ�
void insert_Edge(graphHead* h, int tail, int head); //tail�� head vertex���� �̾��ִ� ������ �����ϴ� �Լ�
void DFS(graphHead* h, int key); //���� �켱 Ž���� �ϰ� �� ������� vertex�� ����ϴ� �Լ�(edge�� �� �� �̻��̸� ���� ���ں��� Ž��)
void BFS(graphHead* h, int key); //�ʺ� �켱 Ž���� �ϰ� �� ������� vertex�� ����ϴ� �Լ�(edge�� �� �� �̻��̸� ���� ���ں��� Ž��)
void printGraph(graphHead* h); //graph�� ����ϴ� �Լ�
void InitialVisit(); //visit �迭�� �ʱ�ȭ �ϴ� �Լ�
void InitialQueue(GQueue* q); //ť �ʱ�ȭ �ϴ� �Լ�
int is_empty(GQueue *q); //ť ����ֳ� Ȯ���ϴ� �Լ�
int is_full(GQueue *q); //ť�� full���� Ȯ���ϴ� �Լ�
void enqueue(GQueue *q, int key); //ť�� �����ϴ� �Լ�
int dequeue(GQueue *q); //ť���� �����ϰ� ���� �����ϴ� �Լ�

int visit[MAX_SIZE];

int main()
{
    int key, tail, head;
    char command;
    graphHead* gHead = NULL;

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
			InitializeGraph(&gHead);
			break;
		case 'q': case 'Q':
			freeGraph(gHead);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
            for(int i=0; i<key; i++)
            {
                insert_Vertex(gHead);
            }
			break;
		case 'e': case 'E':
			printf("Your tail, head = ");
			scanf("%d %d", &tail, &head);
			insert_Edge(gHead, tail, head);
            insert_Edge(gHead, head, tail);
			break;

		case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            InitialVisit();
			DFS(gHead, key);
			break;
		case 'b': case 'B':
            printf("Your Key = ");
            scanf("%d", &key);
            InitialVisit();
			BFS(gHead, key);
			break;

		case 'p': case 'P':
			printGraph(gHead);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;

    
}

void InitializeGraph(graphHead** h) 
{
    if(*h!=NULL) //�׷����� ������� ������
    {
        //free
    }
    *h = (graphHead*)malloc(sizeof(graphHead)); //head�� �޸� �����Ҵ�
    (*h)->size = 0; //����Ʈ�� ũ�� 0���� �ʱ�ȭ
    for(int i=0; i<MAX_SIZE; i++) //����Ʈ�� ��� ���� null�� �ʱ�ȭ
    {
        (*h)->nodelist[i] = NULL;
    }
}

void freeGraph(graphHead* h)
{
    graphNode* next; //���� ��� ��ũ ������ ����
    for(int i=0; i<h->size; i++) //�迭�� ������ �ݺ�
    {
        graphNode* node = h->nodelist[i]; //��� �Ҵ�
        while(node)//��� ������ �ݺ�
        {
            next = node->link; //���� ��� ����
            free(node); //��� free
            node = next; //���� ���� �̵�
        }
    }
}

void insert_Vertex(graphHead* h)
{
    if(h->size+1 > MAX_SIZE) //���� �׷����� ������ ��+1�� Max-size ���� Ŭ ��
    {
        printf("graph is full\n");
        return;
    }
    h->size++; //size ����
}

void insert_Edge(graphHead* h, int tail, int head)
{
    if(tail >= h->size || head >= h->size)
    //tail�� head ���� �ش��ϴ� vertex�� �������� ���� ��
    {
        printf("�ش� key�� ���� vertex�� �������� �ʽ��ϴ�.\n");
        return;
    }
    graphNode* newnode = (graphNode*)malloc(sizeof(graphNode)); //��� ����
    newnode->data = head; //����� ���� head �Ҵ�
    newnode->link = h->nodelist[tail]; //tail�� �ش��ϴ� ����Ʈ ���ҿ� ����
    h->nodelist[tail] = newnode;
}

void DFS(graphHead* h, int key)
{
    graphNode* w; //������带 �Ҵ��� ����
    visit[key] = 1;
    printf("%d ", key);
    for(w = h->nodelist[key]; w; w = w->link)
    {
        if(visit[w->data] == 0)
        {
            DFS(h, w->data);
        }
    }
    
}

void BFS(graphHead* h, int key)
{
	graphNode *w;
	GQueue q;
	InitialQueue(&q); //ť�� �ʱ�ȭ �Ѵ�. 
	visit[key] = 1;  //visit �迭�� ǥ���Ѵ�.
	printf("%d ", key); //���� ��� ���
	enqueue(&q, key); //���� ��带 q�� �����Ѵ�. 
	while (!is_empty(&q)) 
    {
		key = dequeue(&q);		//ť�� ����� ���� �Ҵ� 
		for (w = h->nodelist[key]; w; w = w->link) //���� ���� Ž��
			if (visit[w->data] = 0) 
            {	// �̹湮 ���� Ž�� 
				visit[w->data] = 1;   // �湮 ǥ��
				printf("%d ", w->data);
				enqueue(&q, w->data);	//������ ť�� ����
			}
	}
}

void printGraph(graphHead* h) //�׷����� �����ϴ� ������ ��������Ʈ�� ����ϴ� �Լ�
{
    graphNode* node;
    for(int i=0; i<h->size; i++)
    {
        graphNode* node = h->nodelist[i];
        printf("%d�� ��������Ʈ : ", i);
        while(node != NULL)
        {
            printf("%d ", node->data);
            node = node->link;
        }
        printf("\n");
    }
}

void InitialVisit() //visit�迭�� �ʱ�ȭ�ϴ� �Լ�
{
    for(int i=0; i<MAX_SIZE; i++)
    {
        visit[i] = 0;
    }
}

void InitialQueue(GQueue* q) //ť�� �ʱ�ȭ�ϴ� �Լ�
{
    q->front = q->rear = 0;
}


int is_empty(GQueue* q) //ť�� ����ִ��� Ȯ���ϴ� �Լ�
{
    if(q->front == q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_full(GQueue* q) //ť�� full���� Ȯ���ϴ� �Լ�
{
    if((q->rear + 1) % MAX_SIZE == q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void enqueue(GQueue* q, int key) //ť�� �����ϴ� �Լ�
{
	if (is_full(q))
		printf("queue is full\n");
	q->rear = (q->rear + 1) % MAX_SIZE; //����ť���� rear�ϳ� ����
	q->queue[q->rear] = key; //������ rear���� key ����
}

int dequeue(GQueue* q) //ť���� �����ϰ� �� ���� �����ϴ� �Լ�
{
	if (is_empty(q))
		printf("queue is empty\n");
	q->front = (q->front + 1) % MAX_SIZE; //����ť���� front�� �ϳ� ����
	return q->queue[q->front];
}