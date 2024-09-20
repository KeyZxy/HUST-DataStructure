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
//5 线性表 8 集合 7 二叉树 6 无向图 -1 null
//5 6 5 7 6 7 7 8 -1 -1
// 图的类型定义
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
// 顶点类型定义
typedef struct
{
    KeyType key;
    char others[20];
} VertexType;
// 表结点类型定义
typedef struct ArcNode
{
    int adjvex;              // 顶点位置编号
    struct ArcNode *nextarc; // 下一个表结点指针
} ArcNode;
// 头结点及其数组类型定义
typedef struct VNode
{
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
// 邻接表的类型定义
typedef struct
{
    AdjList vertices;   // 头结点数组
    int vexnum, arcnum; // 顶点数、弧数
    GraphKind kind;     // 图的类型
} ALGraph;
typedef int ElemType;   //栈的定义
typedef struct stack
{
    ElemType elem[MAX_VERTEX_NUM];
    int p;
} stack; //栈的定义
typedef struct{  //无向图的管理表定义
    struct { char name[30]; //无向图名称 
     		ALGraph G;	
    } elem[10]; //存放无向图的集合 
    int length; //无向图集合的长度 
    int listsize; //无向图集合分配的空间 
}LISTS; 
status find(VertexType V[],int key,int n);
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);       // 创建图                         // 查找关键字
status DestroyGraph(ALGraph &G);
status PutVex(ALGraph &G,KeyType u,VertexType value);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);                         // 读取图
void visit(VertexType v);                                              // 访问函数
int LocateVex(ALGraph G, KeyType u);                                   // 定位顶点
status PutVex(ALGraph &G, KeyType u, VertexType value);                // 修改顶点
int FirstAdjVex(ALGraph G, KeyType u);                                 // 第一个邻接顶点
int NextAdjVex(ALGraph G, KeyType v, KeyType w);                       // 下一个邻接顶点
status InsertVex(ALGraph &G, VertexType v);                            // 插入顶点
status DeleteVex(ALGraph &G, KeyType v);                               // 删除顶点
status InsertArc(ALGraph &G, KeyType v, KeyType w);                    // 插入弧
status DeleteArc(ALGraph &G, KeyType v, KeyType w);                    // 删除弧
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));             // 深度优先搜索
void DFS(ALGraph G, int v, bool visited[], void (*visit)(VertexType)); // 深度优先搜索辅助函数
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
	}//初始化 
	while(op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiGraph     -2.SingleGraph\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     请选择所在的菜单层级：\n");
        printf("     -1：主菜单实现多无向图管理，-2：临时单无向图基本操作。\n");
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
                        printf("\t无向图%d：未创建            \t无向图%d：未创建",i+1,i+6);
                    else if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum!=0)
                        printf("\t无向图%d：未创建            \t无向图%d：%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].G.vexnum!=0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t无向图%d：%s                \t无向图%d：未创建",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t无向图%d：%s                \t无向图%d：%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("     请选择你的操作[0或15~18]:");
				scanf("%d",&op);
				switch(op){
                    case 15:
                        printf("请输入待添加的无向图名称：");
                        scanf("%s",Name);
                        j=AddGraph(Lists,Name);
                        if(j==OK)
                            printf("无向图添加成功！\n");
                        else if(j==INFEASIBLE)
                            printf("无向图添加失败，该无向图已存在！\n");
                        else if(j==OVERFLOW)
                            printf("无向图添加失败，无向图集合已满！\n");
                        else if(j==ERROR)
                            printf("创建无向图失败，无向图为空或数据输入错误！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 16:
                        printf("请输入待删除的无向图名称：");
						scanf("%s",Name);
						j=RemoveGraph(Lists,Name);
						if(j==OK)
							printf("无向图删除成功！\n");
						else if(j==ERROR)
							printf("无向图删除失败，集合中无此无向图！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 17:
                        printf("请输入待查找的无向图名称：");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							printf("该无向图位于集合中第 %d 位！\n",j);
						else
							printf("无向图查找失败，集合中无此无向图！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 18:
                        printf("请输入待操作的无向图名称：");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].G,op);
						else
						{
							getchar();
							printf("无向图不存在于集合中，不能进入单无向图操作！\n");
                            printf("---任意键继续---\n");
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
                printf("     请选择你的操作[0~15]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        VertexType V[30];
                        KeyType VR[100][2];
                        printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
                        do {
                            scanf("%d%s",&V[i].key,V[i].others);
                        } while(V[i++].key!=-1);
                        i=0;
                        printf("请输入图中所有弧，输入（-1，-1）终止：\n");
                        do {
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        } while(VR[i++][0]!=-1);
                        j=CreateGraph(G,V,VR);
                        if(j==OK)
                            printf("创建无向图成功！\n");
                        else if(j==INFEASIBLE)
                            printf("无向图添加失败，该无向图已存在！\n");
                        else if(j==ERROR)
                            printf("创建无向图失败，无向图数据输入错误！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyGraph(G);
                        if(j==OK)
                            printf("销毁无向图成功！\n");
                        else
                            printf("销毁无向图失败，无向图不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 3:
                        printf("请输入待查找顶点关键字：");
                        scanf("%d",&u);
                        j=LocateVex(G,u);
                        if(j==INFEASIBLE)
                            printf("关键字为 %d 顶点不存在，查找失败！\n",u);
                        else
                            printf("查找顶点成功，关键字为 %d 的顶点在邻接表数组中关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 4:
                        printf("请输入需要重新赋值的顶点的关键字：");
                        scanf("%d",&u);
                        printf("请输入新赋值的顶点关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=PutVex(G,u,value);
                        if(j==OK)
                            printf("赋值成功！\n");
                        else if(j==ERROR)
                            printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后无向图中关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 5:
                        printf("请输入需要获取第一邻接点的顶点的关键字：");
                        scanf("%d",&u);
                        j=FirstAdjVex(G,u);
                        if(j==OVERFLOW)
                            printf("获取失败，该顶点无邻接顶点！\n");
                        else if(j==INFEASIBLE)
                            printf("获取失败，无向图中无此顶点！\n");
                        else
                            printf("获取成功，关键字为 %d 的顶点的第一邻接顶点关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 6:
                        printf("请输入需要获取邻接点的顶点的关键字：");
                        scanf("%d",&u);
                        printf("请输入需要获取下一邻接点的顶点的关键字：");
                        scanf("%d",&w);
                        j=NextAdjVex(G,u,w);
                        if(j==ERROR)
                            printf("获取失败，w无下一邻接顶点！\n");
                        else if(j==INFEASIBLE)
                            printf("获取失败，v不在无向图中！\n");
                        else
                            printf("获取成功，顶点v的邻接顶点相对于w的下一邻接顶点的关键字和字符串为 %d %s ！\n",G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 7:
                        printf("请输入插入顶点的关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertVex(G,value);
                        if(j==OK)
                            printf("插入顶点成功！\n");
                        else if(j==OVERFLOW)
                            printf("插入顶点失败，顶点集已满！\n");
                        else if(j==ERROR)
                            printf("插入顶点失败，新插入顶点的关键字与已有顶点关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 8:
                        printf("请输入删除顶点的关键字：");
                        scanf("%d",&u);
                        j=DeleteVex(G,u);
                        if(j==OK)
                            printf("删除顶点成功！\n");
                        else
                            printf("删除顶点失败，无向图为空或无此顶点！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 9:
                        printf("请输入待插入弧的两个顶点：");
                        scanf("%d%d",&u,&w);
                        j=InsertArc(G,u,w);
                        if(j==OK)
                            printf("插入弧成功！\n");
                        else if(j==INFEASIBLE)
                            printf("插入弧失败，输入的弧顶点不存在于图中！\n");
                        else if(j==ERROR)
                            printf("插入弧失败，插入的弧已存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 10:
                        printf("请输入待删除弧的两个顶点：");
                        scanf("%d%d",&u,&w);
                        j=DeleteArc(G,u,w);
                        if(j==OK)
                            printf("删除弧成功！\n");
                        else if(j==INFEASIBLE)
                            printf("删除弧失败，输入的弧顶点不存在于图中！\n");
                        else if(j==ERROR)
                            printf("删除弧失败，待删除的弧不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 11:
                        j=DFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n深度搜索无向图成功！\n");
                        else
                            printf("\n搜索图失败，图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 12:
                        j=BFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n广度搜索无向图成功！\n");
                        else
                            printf("\n搜索图失败，图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 13:
                        printf("请输入待操作文件名称：");
                        scanf("%s",FileName);
                        j=SaveGraph(G,FileName);
                        if(j==OK)
                            printf("无向图存档成功！\n");
                        else if(j==ERROR)
                            printf("创建/打开文件失败！\n");
                        else
                            printf("无向图存档失败，无向图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 14:
                        printf("请输入待操作文件名称：");
                        scanf("%s",FileName);
                        j=LoadGraph(G,FileName);
                        if(j==OK)
                            printf("无向图读档成功！\n");
                        else if(j==ERROR)
                            printf("打开文件失败！\n");
                        else
                            printf("无向图读档失败，无向图已存在，读档会使原无向图中数据失去！\n");
                        getchar();
                        printf("---任意键继续---\n");
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
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}
status find(VertexType V[],int key,int n)
{
    for(int i=0;i<n;i++)
    {
        if(V[i].key==key) return OK;
    }
    return ERROR;
}
//栈的函数
void iniStack(stack &S)
//该函数初始化栈S
{
    S.p = 0;
}
int isEmptyStack(stack &S)
//判断是不是空栈，是则返回1，不是则返回0
{
    if (S.p)
        return 0;
    else
        return 1;
}
int push(stack &S, ElemType e)
//该函数将元素进栈，成功则返回1，失败返回0
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
//该函数将元素出栈，返回出栈的元素值
{
    if (S.p == 0)
        return ERROR;
    else
        return S.elem[S.p--];
}

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
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
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
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
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
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
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
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
    visited[v] = true; // 标记顶点v为已访问
    
    // 访问顶点v
    (*visit)(G.vertices[v].data);
    
    // 遍历顶点v的所有邻接点
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex, visited, visit); // 递归访问未被访问过的邻接点
        }
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
 bool visited[MAX_VERTEX_NUM] = {false}; // 标记数组，用于记录顶点是否被访问过
    
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited, visit); // 对未被访问的顶点进行深度优先搜索
        }
    }
    
    return OK;

    /********** End **********/
}
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
  bool visited[MAX_VERTEX_NUM] = {false}; // 标记数组，用于记录顶点是否被访问过
    int queue[MAX_VERTEX_NUM]; // 队列，用于存储待访问的顶点
    int front = 0, rear = 0; // 队列的前端和后端指针
    
    // 从每个顶点开始进行广度优先搜索
    for (int v = 0; v < G.vexnum; v++) {
        if (!visited[v]) {
            // 初始化队列
            queue[rear++] = v; // 将起始顶点入队
            visited[v] = true; // 标记起始顶点为已访问
            
            while (front != rear) { // 当队列不为空时循环
                int u = queue[front++]; // 出队一个顶点
                (*visit)(G.vertices[u].data); // 访问该顶点
                
                // 遍历当前顶点的所有邻接点
                ArcNode *p = G.vertices[u].firstarc;
                while (p != NULL) {
                    int w = p->adjvex;
                    if (!visited[w]) { // 如果邻接点未被访问过
                        queue[rear++] = w; // 将邻接点入队
                        visited[w] = true; // 标记邻接点为已访问
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    
    return OK;
    /********** End **********/
}
//菜单功能选择 13 无向图存档
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    if(!G.vexnum)
        return INFEASIBLE;
    if (!(fp = fopen(FileName, "wb")))
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    { //写入每一个顶点
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        { //顺序写入该顶点的每一个邻接点的位置
            fprintf(fp, "%d ", p->adjvex);
        }
        fprintf(fp, "%d ", -1); //邻接点结尾处写上-1
    }
    fprintf(fp, "%d %s ", -1, "nil"); //顶点结尾处写上-1
    fclose(fp);
    return OK;
}

//菜单功能选择 14 无向图读档
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
//本函数调用栈的数据结构及其操作函数
{
    if (G.vexnum > 0)
        return  INFEASIBLE;
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")))
        return ERROR;
    G.vexnum = G.arcnum = 0;
    KeyType key;          //存储从文件中读取顶点key值的临时变量
    int ConnectVerLocate; //存储读取的顶点邻接点的位置的临时变量
    char others[20];      //存储读取的顶点的data中others分量的临时变量
    stack S;              //定义栈
    iniStack(S);
    fscanf(fp, "%d ", &key);
    fscanf(fp, "%s ", others);
    for (int i = 0; key != -1 && G.vexnum < MAX_VERTEX_NUM; i++)
    { //创建顶点
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        fscanf(fp, "%d ", &ConnectVerLocate);
        for (; ConnectVerLocate != -1;)
        { //建立顶点的邻接表
            //通过入栈出栈把顺序倒置，确保读取后顶点邻接表顺序与原图相同
            push(S, ConnectVerLocate);
            fscanf(fp, "%d ", &ConnectVerLocate);
        }
        for (ArcNode *p; !isEmptyStack(S);)
        {                              //栈不为空时循环
            ConnectVerLocate = pop(S); //出栈
            //从邻接表头部插入邻接点结点
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = ConnectVerLocate;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
            G.arcnum++; //图的边数自增
        }
        G.vexnum++;                        //图的顶点数自增
        fscanf(fp, "%d %s", &key, others); //读取下一顶点
    }
    G.arcnum/=2;
    fclose(fp);
    return OK;
}
//菜单功能选择 15 多无向图管理之增加无向图 
status AddGraph(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的无向图。
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
            VertexType V[30];   //由于图为空时相当于图不存在，增加图时即向图中输入元素
            KeyType VR[100][2];
            int i=0,j;
            printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            printf("请输入图中所有弧，输入（-1，-1）终止：\n");
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

//菜单功能选择 16 多无向图管理之删除无向图 
status RemoveGraph(LISTS &Lists,char ListName[])
// 在Lists中删除一个名称为ListName的无向图。 
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

//菜单功能选择 17 多无向图管理之查找无向图 
int LocateGraph(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的无向图，查找成功返回逻辑序号，否则返回ERROR。 
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

//辅助函数：访问图顶点
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

//辅助函数：进入二级菜单
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
        printf("     请选择你的操作[0~15]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                VertexType V[30];
                KeyType VR[100][2];
                printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                printf("请输入图中所有弧，输入（-1，-1）终止：\n");
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                j=CreateGraph(G,V,VR);
                if(j==OK)
                    printf("创建无向图成功！\n");
                else if(j==INFEASIBLE)
                    printf("无向图添加失败，该无向图已存在！\n");
                else if(j==ERROR)
                    printf("创建无向图失败，无向图数据输入错误！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 2:
                j=DestroyGraph(G);
                if(j==OK)
                    printf("销毁无向图成功！\n");
                else
                    printf("销毁无向图失败，无向图不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 3:
                printf("请输入待查找顶点关键字：");
                scanf("%d",&u);
                j=LocateVex(G,u);
                if(j==INFEASIBLE)
                    printf("关键字为 %d 顶点不存在，查找失败！\n",u);
                else
                    printf("查找顶点成功，关键字为 %d 的顶点在邻接表数组中关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 4:
                printf("请输入需要重新赋值的顶点的关键字：");
                scanf("%d",&u);
                printf("请输入新赋值的顶点关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=PutVex(G,u,value);
                if(j==OK)
                    printf("赋值成功！\n");
                else if(j==ERROR)
                    printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后无向图中关键字重复！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 5:
                printf("请输入需要获取第一邻接点的顶点的关键字：");
                scanf("%d",&u);
                j=FirstAdjVex(G,u);
                if(j==OVERFLOW)
                    printf("获取失败，该顶点无邻接顶点！\n");
                else if(j==INFEASIBLE)
                    printf("获取失败，无向图中无此顶点！\n");
                else
                    printf("获取成功，关键字为 %d 的顶点的第一邻接顶点关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 6:
                printf("请输入需要获取邻接点的顶点的关键字：");
                scanf("%d",&u);
                printf("请输入需要获取下一邻接点的顶点的关键字：");
                scanf("%d",&w);
                j=NextAdjVex(G,u,w);
                if(j==ERROR)
                    printf("获取失败，w无下一邻接顶点！\n");
                else if(j==INFEASIBLE)
                    printf("获取失败，v不在无向图中！\n");
                else
                    printf("获取成功，顶点v的邻接顶点相对于w的下一邻接顶点的位序为 %d %s ！\n",G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 7:
                printf("请输入插入顶点的关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=InsertVex(G,value);
                if(j==OK)
                    printf("插入顶点成功！\n");
                else if(j==OVERFLOW)
                    printf("插入顶点失败，顶点集已满！\n");
                else if(j==ERROR)
                    printf("插入顶点失败，新插入顶点的关键字与已有顶点关键字重复！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 8:
                printf("请输入删除顶点的关键字：");
                scanf("%d",&u);
                j=DeleteVex(G,u);
                if(j==OK)
                    printf("删除顶点成功！\n");
                else
                    printf("删除顶点失败，无向图为空或无此顶点！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 9:
                printf("请输入待插入弧的两个顶点：");
                scanf("%d%d",&u,&w);
                j=InsertArc(G,u,w);
                if(j==OK)
                    printf("插入弧成功！\n");
                else if(j==INFEASIBLE)
                    printf("插入弧失败，输入的弧顶点不存在于图中！\n");
                else if(j==ERROR)
                    printf("插入弧失败，插入的弧已存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 10:
                printf("请输入待删除弧的两个顶点：");
                scanf("%d%d",&u,&w);
                j=DeleteArc(G,u,w);
                if(j==OK)
                    printf("删除弧成功！\n");
                else if(j==INFEASIBLE)
                    printf("删除弧失败，输入的弧顶点不存在于图中！\n");
                else if(j==ERROR)
                    printf("删除弧失败，待删除的弧不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 11:
                j=DFSTraverse(G,visit);
                if(j==OK)
                    printf("\n深度搜索无向图成功！\n");
                else
                    printf("\n搜索图失败，图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 12:
                j=BFSTraverse(G,visit);
                if(j==OK)
                    printf("\n广度搜索无向图成功！\n");
                else
                    printf("\n搜索图失败，图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 13:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=SaveGraph(G,FileName);
                if(j==OK)
                    printf("无向图存档成功！\n");
                else if(j==ERROR)
                    printf("创建/打开文件失败！\n");
                else
                    printf("无向图存档失败，无向图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 14:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=LoadGraph(G,FileName);
                if(j==OK)
                    printf("无向图读档成功！\n");
                else if(j==ERROR)
                    printf("打开文件失败！\n");
                else
                    printf("无向图读档失败，无向图已存在，读档会使原无向图中数据失去！\n");
                getchar();
                printf("---任意键继续---\n");
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
                printf("---任意键继续---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}