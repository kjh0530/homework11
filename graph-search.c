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

void InitializeGraph(head* h); //그래프를 초기화하는 함수
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
			InitializeGraph(head);
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
			printf("Your Edge = ");
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

void InitializeGraph(head* h) 
{
    if(h!=NULL) //그래프가 비어있지 않으면
    {
        //free
    }
    h = (head*)malloc(sizeof(head)); //head에 메모리 동적할당
    h->size = 0; //리스트의 크기 0으로 초기화
    for(int i=0; i<MAX_SIZE; i++) //리스트의 모든 값을 null로 초기화
    {
        h->nodelist[i] = NULL;
    }
}
void freeGraph(head* h)
{

}
void insert_Vertex(head* h, int key)
{

}
void insert_Edge(head* h, int key, int key2)
{

}
void DFS(head* h)
{

}
void BFS(head* h)
{

}
void printGraph(head* h)
{

}