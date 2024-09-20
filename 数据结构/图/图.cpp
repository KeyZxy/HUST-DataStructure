#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_NAME_LENGTH 20
#define MAX_GRAPH_NUM 10
#define MAX_KEY 100
typedef int status;
typedef int KeyType;
//5 ���Ա� 8 ���� 7 ������ 6 ����ͼ -1 null
//5 6 5 7 6 7 7 8 -1 -1
// ͼ�����Ͷ���
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
// �������Ͷ���
typedef struct
{
    KeyType key;
    char others[20];
} VertexType;
// �������Ͷ���
typedef struct ArcNode
{
    int adjvex;              // ����λ�ñ��
    struct ArcNode *nextarc; // ��һ������ָ��
} ArcNode;
// ͷ��㼰���������Ͷ���
typedef struct VNode
{
    VertexType data;   // ������Ϣ
    ArcNode *firstarc; // ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
// �ڽӱ�����Ͷ���
typedef struct
{
    AdjList vertices;   // ͷ�������
    int vexnum, arcnum; // ������������
    GraphKind kind;     // ͼ������
} ALGraph;
typedef int ElemType;   //ջ�Ķ���
typedef struct stack
{
    ElemType elem[MAX_VERTEX_NUM];
    int p;
} stack; //ջ�Ķ���
typedef struct{  //����ͼ�Ĺ������
    struct { char name[30]; //����ͼ���� 
     		ALGraph G;	
    } elem[10]; //�������ͼ�ļ��� 
    int length; //����ͼ���ϵĳ��� 
    int listsize; //����ͼ���Ϸ���Ŀռ� 
}LISTS; 
status find(VertexType V[],int key,int n);
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);       // ����ͼ                         // ���ҹؼ���
status DestroyGraph(ALGraph &G);
status PutVex(ALGraph &G,KeyType u,VertexType value);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);                         // ��ȡͼ
void visit(VertexType v);                                              // ���ʺ���
int LocateVex(ALGraph G, KeyType u);                                   // ��λ����
status PutVex(ALGraph &G, KeyType u, VertexType value);                // �޸Ķ���
int FirstAdjVex(ALGraph G, KeyType u);                                 // ��һ���ڽӶ���
int NextAdjVex(ALGraph G, KeyType v, KeyType w);                       // ��һ���ڽӶ���
status InsertVex(ALGraph &G, VertexType v);                            // ���붥��
status DeleteVex(ALGraph &G, KeyType v);                               // ɾ������
status InsertArc(ALGraph &G, KeyType v, KeyType w);                    // ���뻡
status DeleteArc(ALGraph &G, KeyType v, KeyType w);                    // ɾ����
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));             // �����������
void DFS(ALGraph G, int v, bool visited[], void (*visit)(VertexType)); // �������������������
status BFSTraverse(ALGraph &G, void (*visit)(VertexType)); 
status AddGraph(LISTS &Lists,char ListName[]);
status RemoveGraph(LISTS &Lists,char ListName[]);
int LocateGraph(LISTS Lists,char ListName[]);   
void SecondaryTable(ALGraph &G,int op);
int main(){
    int i,j,op=1;
    char Name[30]={'\0'},FileName[30]={'\0'};
    KeyType u,w;
    ALGraph G;
    VertexType value;
    LISTS Lists;
    G.vexnum=G.arcnum=0;
    G.kind=UDG;   
    value.key=0;
    value.others[0]='\0';   
    Lists.length=0;
	Lists.listsize=10;
	for(j=0;j<10;j++)
	{
		Lists.elem[j].G.arcnum=Lists.elem[j].G.vexnum=0;
		Lists.elem[j].G.kind=UDG;
	}//��ʼ�� 
	while(op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiGraph     -2.SingleGraph\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     ��ѡ�����ڵĲ˵��㼶��\n");
        printf("     -1�����˵�ʵ�ֶ�����ͼ����-2����ʱ������ͼ����������\n");
		scanf("%d",&op);
		if(op==-1)
		{
			while(op)
			{
                system("cls");	printf("\n\n");
                printf("            Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------\n");
                printf("         15.AddGraph        16.RemoveGraph      17.LocateGraph\n");
                printf("         18.SecondaryTable\n");
                printf("    	 0. Exit\n");
                printf("---------------------------------------------------------------------\n");
                for(i=0;i<5;i++)
                {
                    if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t����ͼ%d��δ����            \t����ͼ%d��δ����",i+1,i+6);
                    else if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum!=0)
                        printf("\t����ͼ%d��δ����            \t����ͼ%d��%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].G.vexnum!=0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t����ͼ%d��%s                \t����ͼ%d��δ����",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t����ͼ%d��%s                \t����ͼ%d��%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("     ��ѡ����Ĳ���[0��15~18]:");
				scanf("%d",&op);
				switch(op){
                    case 15:
                        printf("���������ӵ�����ͼ���ƣ�");
                        scanf("%s",Name);
                        j=AddGraph(Lists,Name);
                        if(j==OK)
                            printf("����ͼ��ӳɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                        else if(j==OVERFLOW)
                            printf("����ͼ���ʧ�ܣ�����ͼ����������\n");
                        else if(j==ERROR)
                            printf("��������ͼʧ�ܣ�����ͼΪ�ջ������������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 16:
                        printf("�������ɾ��������ͼ���ƣ�");
						scanf("%s",Name);
						j=RemoveGraph(Lists,Name);
						if(j==OK)
							printf("����ͼɾ���ɹ���\n");
						else if(j==ERROR)
							printf("����ͼɾ��ʧ�ܣ��������޴�����ͼ��\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 17:
                        printf("����������ҵ�����ͼ���ƣ�");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							printf("������ͼλ�ڼ����е� %d λ��\n",j);
						else
							printf("����ͼ����ʧ�ܣ��������޴�����ͼ��\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 18:
                        printf("�����������������ͼ���ƣ�");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].G,op);
						else
						{
							getchar();
							printf("����ͼ�������ڼ����У����ܽ��뵥����ͼ������\n");
                            printf("---���������---\n");
							getchar();
							break;
						}
						break;
					case 0:
						break;
                }//end of switch
            }//end of while
        }//end of if
        if(op==-2)
        {
            while(op){
                system("cls");
                printf("\n\n");
                printf("                Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("    	  1. CreateGraph        7. InsertVex            13. SaveGraph\n");
                printf("    	  2. DestroyGraph       8. DeleteVex            14. LoadGraph\n");
                printf("    	  3. LocateVex          9. InsertArc            15. ShowGraph\n");
                printf("    	  4. PutVex             10. DeleteArc\n");
                printf("    	  5. FirstAdjVex        11. DFSTraverse\n");
                printf("    	  6. NextAdjVex         12. BFSTraverse\n");
                printf("    	  0. Exit\n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("     ��ѡ����Ĳ���[0~15]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        VertexType V[30];
                        KeyType VR[100][2];
                        printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
                        do {
                            scanf("%d%s",&V[i].key,V[i].others);
                        } while(V[i++].key!=-1);
                        i=0;
                        printf("������ͼ�����л������루-1��-1����ֹ��\n");
                        do {
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        } while(VR[i++][0]!=-1);
                        j=CreateGraph(G,V,VR);
                        if(j==OK)
                            printf("��������ͼ�ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                        else if(j==ERROR)
                            printf("��������ͼʧ�ܣ�����ͼ�����������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyGraph(G);
                        if(j==OK)
                            printf("��������ͼ�ɹ���\n");
                        else
                            printf("��������ͼʧ�ܣ�����ͼ�����ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 3:
                        printf("����������Ҷ���ؼ��֣�");
                        scanf("%d",&u);
                        j=LocateVex(G,u);
                        if(j==INFEASIBLE)
                            printf("�ؼ���Ϊ %d ���㲻���ڣ�����ʧ�ܣ�\n",u);
                        else
                            printf("���Ҷ���ɹ����ؼ���Ϊ %d �Ķ������ڽӱ������йؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 4:
                        printf("��������Ҫ���¸�ֵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        printf("�������¸�ֵ�Ķ���ؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=PutVex(G,u,value);
                        if(j==OK)
                            printf("��ֵ�ɹ���\n");
                        else if(j==ERROR)
                            printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ������ͼ�йؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 5:
                        printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        j=FirstAdjVex(G,u);
                        if(j==OVERFLOW)
                            printf("��ȡʧ�ܣ��ö������ڽӶ��㣡\n");
                        else if(j==INFEASIBLE)
                            printf("��ȡʧ�ܣ�����ͼ���޴˶��㣡\n");
                        else
                            printf("��ȡ�ɹ����ؼ���Ϊ %d �Ķ���ĵ�һ�ڽӶ���ؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 6:
                        printf("��������Ҫ��ȡ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&w);
                        j=NextAdjVex(G,u,w);
                        if(j==ERROR)
                            printf("��ȡʧ�ܣ�w����һ�ڽӶ��㣡\n");
                        else if(j==INFEASIBLE)
                            printf("��ȡʧ�ܣ�v��������ͼ�У�\n");
                        else
                            printf("��ȡ�ɹ�������v���ڽӶ��������w����һ�ڽӶ���Ĺؼ��ֺ��ַ���Ϊ %d %s ��\n",G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 7:
                        printf("��������붥��Ĺؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertVex(G,value);
                        if(j==OK)
                            printf("���붥��ɹ���\n");
                        else if(j==OVERFLOW)
                            printf("���붥��ʧ�ܣ����㼯������\n");
                        else if(j==ERROR)
                            printf("���붥��ʧ�ܣ��²��붥��Ĺؼ��������ж���ؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 8:
                        printf("������ɾ������Ĺؼ��֣�");
                        scanf("%d",&u);
                        j=DeleteVex(G,u);
                        if(j==OK)
                            printf("ɾ������ɹ���\n");
                        else
                            printf("ɾ������ʧ�ܣ�����ͼΪ�ջ��޴˶��㣡\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 9:
                        printf("����������뻡���������㣺");
                        scanf("%d%d",&u,&w);
                        j=InsertArc(G,u,w);
                        if(j==OK)
                            printf("���뻡�ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("���뻡ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                        else if(j==ERROR)
                            printf("���뻡ʧ�ܣ�����Ļ��Ѵ��ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 10:
                        printf("�������ɾ�������������㣺");
                        scanf("%d%d",&u,&w);
                        j=DeleteArc(G,u,w);
                        if(j==OK)
                            printf("ɾ�����ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("ɾ����ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                        else if(j==ERROR)
                            printf("ɾ����ʧ�ܣ���ɾ���Ļ������ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 11:
                        j=DFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n�����������ͼ�ɹ���\n");
                        else
                            printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 12:
                        j=BFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n�����������ͼ�ɹ���\n");
                        else
                            printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 13:
                        printf("������������ļ����ƣ�");
                        scanf("%s",FileName);
                        j=SaveGraph(G,FileName);
                        if(j==OK)
                            printf("����ͼ�浵�ɹ���\n");
                        else if(j==ERROR)
                            printf("����/���ļ�ʧ�ܣ�\n");
                        else
                            printf("����ͼ�浵ʧ�ܣ�����ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 14:
                        printf("������������ļ����ƣ�");
                        scanf("%s",FileName);
                        j=LoadGraph(G,FileName);
                        if(j==OK)
                            printf("����ͼ�����ɹ���\n");
                        else if(j==ERROR)
                            printf("���ļ�ʧ�ܣ�\n");
                        else
                            printf("����ͼ����ʧ�ܣ�����ͼ�Ѵ��ڣ�������ʹԭ����ͼ������ʧȥ��\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 15:
                        for(j=0;j<G.vexnum;j++)
                        {
                            ArcNode *p=G.vertices[j].firstarc;
                            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
                            while (p)
                            {
                                printf(" %d",p->adjvex);
                                p=p->nextarc;
                            }
                            printf("\n");
                        }
                        getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}
status find(VertexType V[],int key,int n)
{
    for(int i=0;i<n;i++)
    {
        if(V[i].key==key) return OK;
    }
    return ERROR;
}
//ջ�ĺ���
void iniStack(stack &S)
//�ú�����ʼ��ջS
{
    S.p = 0;
}
int isEmptyStack(stack &S)
//�ж��ǲ��ǿ�ջ�����򷵻�1�������򷵻�0
{
    if (S.p)
        return 0;
    else
        return 1;
}
int push(stack &S, ElemType e)
//�ú�����Ԫ�ؽ�ջ���ɹ��򷵻�1��ʧ�ܷ���0
{
    if (S.p == MAX_VERTEX_NUM - 1)
        return OVERFLOW;
    else
    {
        S.elem[++S.p] = e;
    }
    return OK;
}
ElemType pop(stack &S)
//�ú�����Ԫ�س�ջ�����س�ջ��Ԫ��ֵ
{
    if (S.p == 0)
        return ERROR;
    else
        return S.elem[S.p--];
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
int vnum=0,anum=0;
for(int i=0;V[i].key!=-1;i++)
    {
        vnum++;
        for(int j=i+1;V[j].key!=-1;j++)
        {
            if(V[i].key==V[j].key) 
            return ERROR; 
        }
    }
    if(vnum<=0||vnum>MAX_VERTEX_NUM) return ERROR;
    for(int i=0;VR[i][0]!=-1;i++)
    {
        anum++;
        if(find(V,VR[i][0],vnum)==ERROR||find(V,VR[i][1],vnum)==ERROR)
            return ERROR; 
    }
    G.vexnum=vnum;
    G.arcnum=anum;    
    G.kind=UDG;
for(int i=0;i<vnum;i++){
    G.vertices[i].data=V[i];
    G.vertices[i].firstarc=NULL;
}
for(int k=0;k<G.arcnum;k++){
    int i,j;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==VR[k][0])break;
    }
    for(j=0;j<G.vexnum;j++){
        if(G.vertices[j].data.key==VR[k][1])break;
}
ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
p->adjvex=j;
p->nextarc=G.vertices[i].firstarc;
G.vertices[i].firstarc=p;
ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode));
q->adjvex=i;
q->nextarc=G.vertices[j].firstarc;
G.vertices[j].firstarc=q;
}
return OK;
    /********** End **********/
}
status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
int i;
ArcNode *p,*q;
for(i=0;i<G.vexnum;i++){
    p=G.vertices[i].firstarc;
    while(p){
        q=p->nextarc;
        free(p);
        p=q;
    }
}
G.vexnum=0;
G.arcnum=0;
return OK;
    /********** End **********/
}
int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
int i;
for(i=0;i<G.vexnum;i++){
    if(u==G.vertices[i].data.key)
    return i;
}
return -1;
    /********** End **********/
}
status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
int i=LocateVex(G,u);
if(i==-1)return ERROR;
int j;
for(j=0;j<G.vexnum;j++){
    if(G.vertices[j].data.key==value.key)return ERROR;
}
G.vertices[i].data=value;
return OK;
    /********** End **********/
}
int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
ArcNode *p;
int v1=LocateVex(G,u);
if(v1==-1)return -1;
p=G.vertices[v1].firstarc;
if(p)return p->adjvex;
return -1;

    /********** End **********/
}
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v��ӦG��һ������,w��Ӧv���ڽӶ��㣻��������Ƿ���v�ģ������w����һ���ڽӶ����λ�����w�����һ���ڽӶ��㣬��v��w��Ӧ���㲻���ڣ��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
ArcNode *p;
int v1=LocateVex(G,v);
int w1=LocateVex(G,w);
if(v1==-1||w1==-1)return -1;
p=G.vertices[v1].firstarc;
while(p&&p->adjvex!=w1){
    p=p->nextarc;
}
if(!p)return -1;
if(!p->nextarc)return -1;
return p->nextarc->adjvex;

    /********** End **********/
}
status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
if(G.vexnum==MAX_VERTEX_NUM)return ERROR;
for(int i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==v.key) return ERROR;
    }
G.vertices[G.vexnum].data=v;
G.vertices[G.vexnum].firstarc=NULL;
G.vexnum++;
return OK;

    /********** End **********/
}
status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
if(G.vexnum == 1)
    {
        return ERROR;
    }
int i, j;
    ArcNode *p, *q;
    j = LocateVex(G, v);
    if (j == -1)
        return ERROR;
    p = G.vertices[j].firstarc;
    while (p)
    {
        q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--;
    }
    G.vexnum--;
    for (i = j; i < G.vexnum; i++)
        G.vertices[i] = G.vertices[i + 1];
    
    for (i = 0; i < G.vexnum; i++)
    {
        p = G.vertices[i].firstarc;
        while (p)
        {
            if (p->adjvex == j)
            {
                if (p == G.vertices[i].firstarc)
                {
                    G.vertices[i].firstarc = p->nextarc;
                    free(p);
                    p = G.vertices[i].firstarc;
                }
                else
                {
                    q->nextarc = p->nextarc;
                    free(p);
                    p = q->nextarc;
                }
            }
            else
            {
                if (p->adjvex > j)
                    p->adjvex--; 
                q = p;
                p = p->nextarc;
            }
        }
    }
    return OK;

    /********** End **********/
}
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
ArcNode *p,*q,*temp;
int i,j;
i=LocateVex(G,v);
j=LocateVex(G,w);
if(i==-1||j==-1)return ERROR;
G.arcnum++;
temp=G.vertices[i].firstarc;
    while(temp!=NULL) 
    {
        if(temp->adjvex==j)
            return ERROR;
        temp=temp->nextarc;
    }
p=(ArcNode*)malloc(sizeof(ArcNode));
p->adjvex=j;
p->nextarc = G.vertices[i].firstarc;
G.vertices[i].firstarc = p;
q = (ArcNode*)malloc(sizeof(ArcNode));
q->adjvex = i;
q->nextarc = G.vertices[j].firstarc;
G.vertices[j].firstarc = q;
	
    return OK;


    /********** End **********/
}
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
ArcNode *p, *q;
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	return ERROR;
	p = G.vertices[i].firstarc;
	while(p && p->adjvex != j)
	{
		q = p;
		p = p->nextarc;
	}
	if(p && p->adjvex == j)
	{
		if(p == G.vertices[i].firstarc)
		G.vertices[i].firstarc = p->nextarc;
		else
		q->nextarc = p->nextarc;
		free(p);
		G.arcnum--;
	}
	p = G.vertices[j].firstarc;
	while(p && p->adjvex != i)
	{
		q = p;
		p = p->nextarc;
	}
	if(p && p->adjvex == i)
	{
		if(p == G.vertices[j].firstarc)
		G.vertices[j].firstarc=p->nextarc;
		else
		q->nextarc=p->nextarc;
		free(p);
	}
	return OK;

    /********** End **********/
}
void DFS(ALGraph G, int v, bool visited[], void (*visit)(VertexType)) {
    visited[v] = true; // ��Ƕ���vΪ�ѷ���
    
    // ���ʶ���v
    (*visit)(G.vertices[v].data);
    
    // ��������v�������ڽӵ�
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex, visited, visit); // �ݹ����δ�����ʹ����ڽӵ�
        }
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
 bool visited[MAX_VERTEX_NUM] = {false}; // ������飬���ڼ�¼�����Ƿ񱻷��ʹ�
    
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited, visit); // ��δ�����ʵĶ�����������������
        }
    }
    
    return OK;

    /********** End **********/
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
  bool visited[MAX_VERTEX_NUM] = {false}; // ������飬���ڼ�¼�����Ƿ񱻷��ʹ�
    int queue[MAX_VERTEX_NUM]; // ���У����ڴ洢�����ʵĶ���
    int front = 0, rear = 0; // ���е�ǰ�˺ͺ��ָ��
    
    // ��ÿ�����㿪ʼ���й����������
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            // ��ʼ������
            queue[rear++] = v; // ����ʼ�������
            visited[v] = true; // �����ʼ����Ϊ�ѷ���
            
            while (front != rear) { // �����в�Ϊ��ʱѭ��
                int u = queue[front++]; // ����һ������
                (*visit)(G.vertices[u].data); // ���ʸö���
                
                // ������ǰ����������ڽӵ�
                ArcNode *p = G.vertices[u].firstarc;
                while (p != NULL) {
                    int w = p->adjvex;
                    if (!visited[w]) { // ����ڽӵ�δ�����ʹ�
                        queue[rear++] = w; // ���ڽӵ����
                        visited[w] = true; // ����ڽӵ�Ϊ�ѷ���
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    
    return OK;
    /********** End **********/
}
//�˵�����ѡ�� 13 ����ͼ�浵
status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    FILE *fp;
    if(!G.vexnum)
        return INFEASIBLE;
    if (!(fp = fopen(FileName, "wb")))
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    { //д��ÿһ������
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        { //˳��д��ö����ÿһ���ڽӵ��λ��
            fprintf(fp, "%d ", p->adjvex);
        }
        fprintf(fp, "%d ", -1); //�ڽӵ��β��д��-1
    }
    fprintf(fp, "%d %s ", -1, "nil"); //�����β��д��-1
    fclose(fp);
    return OK;
}

//�˵�����ѡ�� 14 ����ͼ����
status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
//����������ջ�����ݽṹ�����������
{
    if (G.vexnum > 0)
        return  INFEASIBLE;
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")))
        return ERROR;
    G.vexnum = G.arcnum = 0;
    KeyType key;          //�洢���ļ��ж�ȡ����keyֵ����ʱ����
    int ConnectVerLocate; //�洢��ȡ�Ķ����ڽӵ��λ�õ���ʱ����
    char others[20];      //�洢��ȡ�Ķ����data��others��������ʱ����
    stack S;              //����ջ
    iniStack(S);
    fscanf(fp, "%d ", &key);
    fscanf(fp, "%s ", others);
    for (int i = 0; key != -1 && G.vexnum < MAX_VERTEX_NUM; i++)
    { //��������
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        fscanf(fp, "%d ", &ConnectVerLocate);
        for (; ConnectVerLocate != -1;)
        { //����������ڽӱ�
            //ͨ����ջ��ջ��˳���ã�ȷ����ȡ�󶥵��ڽӱ�˳����ԭͼ��ͬ
            push(S, ConnectVerLocate);
            fscanf(fp, "%d ", &ConnectVerLocate);
        }
        for (ArcNode *p; !isEmptyStack(S);)
        {                              //ջ��Ϊ��ʱѭ��
            ConnectVerLocate = pop(S); //��ջ
            //���ڽӱ�ͷ�������ڽӵ���
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = ConnectVerLocate;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
            G.arcnum++; //ͼ�ı�������
        }
        G.vexnum++;                        //ͼ�Ķ���������
        fscanf(fp, "%d %s", &key, others); //��ȡ��һ����
    }
    G.arcnum/=2;
    fclose(fp);
    return OK;
}
//�˵�����ѡ�� 15 ������ͼ����֮��������ͼ 
status AddGraph(LISTS &Lists,char ListName[])
// ��Lists������һ������ΪListName������ͼ��
{
    if(Lists.length<Lists.listsize)
    {
    	int i,flag=0;
    	for(i=0;i<Lists.length;i++)
			if(!strcmp(Lists.elem[i].name,ListName))
			{
				flag=1;
				break;
			}				
		if(!flag)
		{
			strcpy(Lists.elem[Lists.length].name,ListName);
            VertexType V[30];   //����ͼΪ��ʱ�൱��ͼ�����ڣ�����ͼʱ����ͼ������Ԫ��
            KeyType VR[100][2];
            int i=0,j;
            printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            printf("������ͼ�����л������루-1��-1����ֹ��\n");
            do {
                scanf("%d%d",&VR[i][0],&VR[i][1]);
            } while(VR[i++][0]!=-1);
			j=CreateGraph(Lists.elem[Lists.length].G,V,VR);
            if(j==ERROR)
                return ERROR;
			Lists.length++;
			return OK;
		}
	    else
			return INFEASIBLE;	
	}
	else
		return OVERFLOW;
} 

//�˵�����ѡ�� 16 ������ͼ����֮ɾ������ͼ 
status RemoveGraph(LISTS &Lists,char ListName[])
// ��Lists��ɾ��һ������ΪListName������ͼ�� 
{
    int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{
			flag=1;
			break;
		}	
	}
	if(flag)
	{
        DestroyGraph(Lists.elem[i].G);
        for(;i<Lists.length-1;i++)
			Lists.elem[i]=Lists.elem[i+1];
        if(i!=Lists.length-1)
            DestroyGraph(Lists.elem[Lists.length-1].G);
        Lists.elem[Lists.length-1].G.vexnum=Lists.elem[Lists.length-1].G.arcnum=0;
        Lists.elem[Lists.length-1].name[0]='\0';
		Lists.length--;
		return OK;
	}
	else
		return ERROR;
} 

//�˵�����ѡ�� 17 ������ͼ����֮��������ͼ 
int LocateGraph(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName������ͼ�����ҳɹ������߼���ţ����򷵻�ERROR�� 
{
	int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{
			flag=1;
			break;
		}
	}
	if(!flag||!Lists.length)
		return ERROR;
	else
		return i+1;
}

//��������������ͼ����
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

//������������������˵�
void SecondaryTable(ALGraph &G,int op)
{
    int i,j;
    char Name[30]={'\0'},FileName[30]={'\0'};
    KeyType u,w;
    VertexType value;
    while(op){
        system("cls");
        printf("\n\n");
        printf("                Menu for Linear Table On Sequence Structure \n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("    	  1. CreateGraph        7. InsertVex            13. SaveGraph\n");
        printf("    	  2. DestroyGraph       8. DeleteVex            14. LoadGraph\n");
        printf("    	  3. LocateVex          9. InsertArc            15. ShowGraph\n");
        printf("    	  4. PutVex             10. DeleteArc\n");
        printf("    	  5. FirstAdjVex        11. DFSTraverse\n");
        printf("    	  6. NextAdjVex         12. BFSTraverse\n");
        printf("    	  0. Exit\n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("     ��ѡ����Ĳ���[0~15]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                VertexType V[30];
                KeyType VR[100][2];
                printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                printf("������ͼ�����л������루-1��-1����ֹ��\n");
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                j=CreateGraph(G,V,VR);
                if(j==OK)
                    printf("��������ͼ�ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                else if(j==ERROR)
                    printf("��������ͼʧ�ܣ�����ͼ�����������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 2:
                j=DestroyGraph(G);
                if(j==OK)
                    printf("��������ͼ�ɹ���\n");
                else
                    printf("��������ͼʧ�ܣ�����ͼ�����ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 3:
                printf("����������Ҷ���ؼ��֣�");
                scanf("%d",&u);
                j=LocateVex(G,u);
                if(j==INFEASIBLE)
                    printf("�ؼ���Ϊ %d ���㲻���ڣ�����ʧ�ܣ�\n",u);
                else
                    printf("���Ҷ���ɹ����ؼ���Ϊ %d �Ķ������ڽӱ������йؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 4:
                printf("��������Ҫ���¸�ֵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                printf("�������¸�ֵ�Ķ���ؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=PutVex(G,u,value);
                if(j==OK)
                    printf("��ֵ�ɹ���\n");
                else if(j==ERROR)
                    printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ������ͼ�йؼ����ظ���\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 5:
                printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                j=FirstAdjVex(G,u);
                if(j==OVERFLOW)
                    printf("��ȡʧ�ܣ��ö������ڽӶ��㣡\n");
                else if(j==INFEASIBLE)
                    printf("��ȡʧ�ܣ�����ͼ���޴˶��㣡\n");
                else
                    printf("��ȡ�ɹ����ؼ���Ϊ %d �Ķ���ĵ�һ�ڽӶ���ؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 6:
                printf("��������Ҫ��ȡ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&w);
                j=NextAdjVex(G,u,w);
                if(j==ERROR)
                    printf("��ȡʧ�ܣ�w����һ�ڽӶ��㣡\n");
                else if(j==INFEASIBLE)
                    printf("��ȡʧ�ܣ�v��������ͼ�У�\n");
                else
                    printf("��ȡ�ɹ�������v���ڽӶ��������w����һ�ڽӶ����λ��Ϊ %d %s ��\n",G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 7:
                printf("��������붥��Ĺؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=InsertVex(G,value);
                if(j==OK)
                    printf("���붥��ɹ���\n");
                else if(j==OVERFLOW)
                    printf("���붥��ʧ�ܣ����㼯������\n");
                else if(j==ERROR)
                    printf("���붥��ʧ�ܣ��²��붥��Ĺؼ��������ж���ؼ����ظ���\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 8:
                printf("������ɾ������Ĺؼ��֣�");
                scanf("%d",&u);
                j=DeleteVex(G,u);
                if(j==OK)
                    printf("ɾ������ɹ���\n");
                else
                    printf("ɾ������ʧ�ܣ�����ͼΪ�ջ��޴˶��㣡\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 9:
                printf("����������뻡���������㣺");
                scanf("%d%d",&u,&w);
                j=InsertArc(G,u,w);
                if(j==OK)
                    printf("���뻡�ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("���뻡ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                else if(j==ERROR)
                    printf("���뻡ʧ�ܣ�����Ļ��Ѵ��ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 10:
                printf("�������ɾ�������������㣺");
                scanf("%d%d",&u,&w);
                j=DeleteArc(G,u,w);
                if(j==OK)
                    printf("ɾ�����ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("ɾ����ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                else if(j==ERROR)
                    printf("ɾ����ʧ�ܣ���ɾ���Ļ������ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 11:
                j=DFSTraverse(G,visit);
                if(j==OK)
                    printf("\n�����������ͼ�ɹ���\n");
                else
                    printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 12:
                j=BFSTraverse(G,visit);
                if(j==OK)
                    printf("\n�����������ͼ�ɹ���\n");
                else
                    printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 13:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=SaveGraph(G,FileName);
                if(j==OK)
                    printf("����ͼ�浵�ɹ���\n");
                else if(j==ERROR)
                    printf("����/���ļ�ʧ�ܣ�\n");
                else
                    printf("����ͼ�浵ʧ�ܣ�����ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 14:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=LoadGraph(G,FileName);
                if(j==OK)
                    printf("����ͼ�����ɹ���\n");
                else if(j==ERROR)
                    printf("���ļ�ʧ�ܣ�\n");
                else
                    printf("����ͼ����ʧ�ܣ�����ͼ�Ѵ��ڣ�������ʹԭ����ͼ������ʧȥ��\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 15:
                for(j=0;j<G.vexnum;j++)
                {
                    ArcNode *p=G.vertices[j].firstarc;
                    printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d",p->adjvex);
                        p=p->nextarc;
                    }
                    printf("\n");
                }
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}