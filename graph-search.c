//linked list 형태로 그래프 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10 //그래프의 최대 vertex 수는 10

typedef struct graphNode //그래프의 정점 노드 정의
{
    int data; //정수형 data(vertex의 숫자)
    struct graphNode* link; //node를 가리키는 link
} graphNode;

typedef struct graphHead //정점의 리스트를 가진 구조체 정의
{
    int size; //리스트의 현재 크기
    graphNode* nodelist[MAX_SIZE]; //리스트 최대 노드 수로 정의
} graphHead;

typedef struct GQueue //큐 구조체 정의
{
    int queue[MAX_SIZE]; //큐에 들어오는 값을 저장할 배열
    int front, rear; //큐의 front, rear 저장할 변수
} GQueue;



void InitializeGraph(graphHead** h); //그래프를 초기화하는 함수
void freeGraph(graphHead* h); //그래프에 할당된 동적 메모리를 free 시키는 함수
void insert_Vertex(graphHead* h); //key 값만큼 vertex를 삽입하는 함수
void insert_Edge(graphHead* h, int tail, int head); //tail과 head vertex들을 이어주는 간선을 삽입하는 함수
void DFS(graphHead* h, int key); //깊이 우선 탐색을 하고 그 순서대로 vertex를 출력하는 함수(edge가 두 개 이상이면 작은 숫자부터 탐색)
void BFS(graphHead* h, int key); //너비 우선 탐색을 하고 그 순서대로 vertex를 출력하는 함수(edge가 두 개 이상이면 작은 숫자부터 탐색)
void printGraph(graphHead* h); //graph를 출력하는 함수
void InitialVisit(); //visit 배열을 초기화 하는 함수
void InitialQueue(GQueue* q); //큐 초기화 하는 함수
int is_empty(GQueue *q); //큐 비어있나 확인하는 함수
int is_full(GQueue *q); //큐가 full인지 확인하는 함수
void enqueue(GQueue *q, int key); //큐에 삽입하는 함수
int dequeue(GQueue *q); //큐에서 삭제하고 값을 리턴하는 함수

int visit[MAX_SIZE];

int main()
{
    int key, tail, head;
    char command;
    graphHead* gHead = NULL;

	printf("[----- 김주훈 2020039027 -----]\n\n"); //이름 학번 출력

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
    if(*h!=NULL) //그래프가 비어있지 않으면
    {
        //free
    }
    *h = (graphHead*)malloc(sizeof(graphHead)); //head에 메모리 동적할당
    (*h)->size = 0; //리스트의 크기 0으로 초기화
    for(int i=0; i<MAX_SIZE; i++) //리스트의 모든 값을 null로 초기화
    {
        (*h)->nodelist[i] = NULL;
    }
}

void freeGraph(graphHead* h)
{
    graphNode* next; //다음 노드 링크 저장할 변수
    for(int i=0; i<h->size; i++) //배열의 끝까지 반복
    {
        graphNode* node = h->nodelist[i]; //노드 할당
        while(node)//노드 끝까지 반복
        {
            next = node->link; //다음 노드 저장
            free(node); //노드 free
            node = next; //다음 노드로 이동
        }
    }
}

void insert_Vertex(graphHead* h)
{
    if(h->size+1 > MAX_SIZE) //현재 그래프의 정점의 수+1이 Max-size 보다 클 때
    {
        printf("graph is full\n");
        return;
    }
    h->size++; //size 증가
}

void insert_Edge(graphHead* h, int tail, int head)
{
    if(tail >= h->size || head >= h->size)
    //tail과 head 값에 해당하는 vertex가 존재하지 않을 때
    {
        printf("해당 key를 가진 vertex가 존재하지 않습니다.\n");
        return;
    }
    graphNode* newnode = (graphNode*)malloc(sizeof(graphNode)); //노드 생성
    newnode->data = head; //노드의 값에 head 할당
    newnode->link = h->nodelist[tail]; //tail에 해당하는 리스트 원소에 연결
    h->nodelist[tail] = newnode;
}

void DFS(graphHead* h, int key)
{
    graphNode* w; //인접노드를 할당할 변수
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
	InitialQueue(&q); //큐를 초기화 한다. 
	visit[key] = 1;  //visit 배열에 표시한다.
	printf("%d ", key); //현재 노드 출력
	enqueue(&q, key); //시작 노드를 q에 저장한다. 
	while (!is_empty(&q)) 
    {
		key = dequeue(&q);		//큐에 저장된 정점 할당 
		for (w = h->nodelist[key]; w; w = w->link) //인접 정점 탐색
			if (visit[w->data] = 0) 
            {	// 미방문 정점 탐색 
				visit[w->data] = 1;   // 방문 표시
				printf("%d ", w->data);
				enqueue(&q, w->data);	//정점을 큐에 삽입
			}
	}
}

void printGraph(graphHead* h) //그래프의 존재하는 노드들의 인접리스트를 출력하는 함수
{
    graphNode* node;
    for(int i=0; i<h->size; i++)
    {
        graphNode* node = h->nodelist[i];
        printf("%d의 인접리스트 : ", i);
        while(node != NULL)
        {
            printf("%d ", node->data);
            node = node->link;
        }
        printf("\n");
    }
}

void InitialVisit() //visit배열을 초기화하는 함수
{
    for(int i=0; i<MAX_SIZE; i++)
    {
        visit[i] = 0;
    }
}

void InitialQueue(GQueue* q) //큐를 초기화하는 함수
{
    q->front = q->rear = 0;
}


int is_empty(GQueue* q) //큐가 비어있는지 확인하는 함수
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

int is_full(GQueue* q) //큐가 full인지 확인하는 함수
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


void enqueue(GQueue* q, int key) //큐에 삽입하는 함수
{
	if (is_full(q))
		printf("queue is full\n");
	q->rear = (q->rear + 1) % MAX_SIZE; //원형큐에서 rear하나 증가
	q->queue[q->rear] = key; //증가한 rear값에 key 넣음
}

int dequeue(GQueue* q) //큐에서 삭제하고 그 값을 리턴하는 함수
{
	if (is_empty(q))
		printf("queue is empty\n");
	q->front = (q->front + 1) % MAX_SIZE; //원형큐에서 front를 하나 증가
	return q->queue[q->front];
}