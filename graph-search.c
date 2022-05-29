//linked list 형태로 그래프 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10 //그래프의 최대 vertex 수는 10

typedef struct node //그래프의 정점 노드 정의
{
    int data; //정수형 data(vertex의 숫자)
    struct node* link; //node를 가리키는 link
} node;

typedef struct head //정점의 리스트 구조체 정의
{
    int size; //리스트의 현재 크기
    node* nodelist[MAX_SIZE]; //리스트 최대 노드 수로 정의
} head;

void InitializeGraph(head** h); //그래프를 초기화하는 함수
void freeGraph(head* h); //그래프에 할당된 동적 메모리를 free 시키는 함수
void insert_Vertex(head* h, int key); //key 값을 가진 vertex를 삽입하는 함수
void insert_Edge(head* h, int key, int key2); //key, key2를 가진 vertex들을 이어주는 간선을 삽입하는 함수
void DFS(head* h); //깊이 우선 탐색을 하고 그 순서대로 vertex를 출력하는 함수(edge가 두 개 이상이면 작은 숫자부터 탐색)
void BFS(head* h); //너비 우선 탐색을 하고 그 순서대로 vertex를 출력하는 함수(edge가 두 개 이상이면 작은 숫자부터 탐색)
void printGraph(head* h); //graph를 출력하는 함수
int main()
{
    int key, key2;
    char command;
    head* head = NULL;

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
    if(*h!=NULL) //그래프가 비어있지 않으면
    {
        //free
    }
    *h = (head*)malloc(sizeof(head)); //head에 메모리 동적할당
    (*h)->size = 0; //리스트의 크기 0으로 초기화
    for(int i=0; i<MAX_SIZE; i++) //리스트의 모든 값을 null로 초기화
    {
        (*h)->nodelist[i] = NULL;
    }
}
void freeGraph(head* h)
{

}
void insert_Vertex(head* h, int key)
{
    if(h->size+1 > MAX_SIZE) //현재 그래프의 정점의 수+1이 Max-size 보다 클 때
    {
        printf("graph is full\n");
        return;
    }
    if(key >= MAX_SIZE) //key 값이 정점의 가장 큰 값보다 크거나 같을 때
    {
        printf("해당 key 값이 그래프 사이즈보다 큽니다.\n");
        return;
    }
    node* vertex = (node*)malloc(sizeof(node)); //노드 동적할당
    vertex->data = key; //key 값 할당
    vertex->link = NULL; //link는 NULL로 초기화
    if(h->nodelist[key] != NULL) //key값의 노드가 이미 존재한다면
    {
        printf("해당 key를 가진 정점이 이미 존재합니다.\n");
        free(vertex);
        return;
    }
    h->nodelist[key] = vertex; //nodelist의 key 자리에 vertex 할당
    h->size++; //size 증가
}
void insert_Edge(head* h, int key, int key2)
{
    if(h->nodelist[key] == NULL || h->nodelist[key2] == NULL)
    //key 값에 해당하는 vertex가 존재하지 않을 때
    {
        printf("해당 key를 가진 vertex가 존재하지 않습니다.\n");
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
            printf("%d의 인접 노드 : ", h->nodelist[i]->data);
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