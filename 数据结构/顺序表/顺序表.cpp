#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MAX_num 10
typedef int status;
typedef int ElemType; //数据元素类型定义
typedef struct{  //顺序表（顺序结构）的定义
      ElemType * elem;
      int length;
      int listsize;
     }SqList;
typedef struct{  //线性表的集合类型定义
    struct { 
		char name[30];
        SqList L;    
    } elem[10]; 
    int length;
}LISTS;
LISTS Lists;

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}


void my_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
status InitList(SqList& L); 
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType *e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType *pre);
status NextElem(SqList L,ElemType e,ElemType *next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType *e); 
status ListTraverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
status cmp (const void * a, const void * b); 
status SortList(SqList& L);
int main(){
	char FileName[30],ListName[30];
	int e, pre, next, i, val, summ;
	e = pre = next = -1;
	int i_num = 9;//正在操作的线性表 
	int op = 1;//菜单 
	while(op){
		system("cls");	//清屏 
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList          9. NextElem\n");
		printf("    	  2. DestroyList       10. ListInsert\n");
		printf("    	  3. ClearList         11. ListDelete\n");
		printf("    	  4. ListEmpty         12. ListTraverse\n");
		printf("    	  5. ListLength        13. SaveList\n");
		printf("    	  6. GetElem           14. LoadList\n");
		printf("    	  7. LocateElem        15. AddListt\n");
		printf("    	  8. PriorElem         16. RemoveList\n");
		printf("    	  18. ChooseLis        17. LocateList\n");
		printf("    	  19. SortLis          0.  Exit\n");	
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0-22]:\n");
		scanf("%d",&op);
		switch(op){
			case 1://1是初始化线性表 
				if(InitList(Lists.elem[i_num].L) == OK) {
					printf("请输入要保存的线性表的名称\n");
					scanf("%s",Lists.elem[i_num].name);
					printf("线性表创建成功\n"); 
				}
				else {
					printf("线性表已经存在\n"); 
					printf("线性表创建失败\n");
				}
				getchar();getchar();
				break; 
			case 2://2是销毁线性表
				if(Lists.elem[i_num].L.elem == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				} 
				if(DestroyList(Lists.elem[i_num].L) == OK){
					printf("线性表销毁成功\n"); 
					Lists.length --; //线性表数目减一 
				}
				else printf("线性表销毁失败\n");
				getchar(); getchar();
				break; 
			case 3://3是清空线性表
				if(Lists.elem[i_num].L.elem == NULL){
        			printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		} 
         		if(ClearList(Lists.elem[i_num].L) == OK)
         			printf("线性表清空成功\n"); 
				else printf("线性表清空失败\n");
				getchar(); getchar();
				break;
			case 4://4是判断线性表是否为空
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		} 
         		if(ListEmpty(Lists.elem[i_num].L) == TRUE){
         			printf("线性表为空\n"); 
				}
				else printf("线性表不是空表\n");
				getchar(); getchar();
				break;
			case 5://5是得到线性表长度 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("线性表表长为 %d\n",ListLength(Lists.elem[i_num].L));
         		getchar(); getchar();
         		break;
         	case 6://6是得到某个元素
			 	if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("请输入要取元素的位置:\n");
				scanf("%d",&i);
				if(GetElem(Lists.elem[i_num].L,i,&e) == OK)
					printf("第%d个位置元素是:%d\n",i,e);
				else 
					printf("输入位置错误\n");
				getchar(); getchar();
				break;
			case 7://7是确定元素位置
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("请输入数据元素的值：\n");
				scanf("%d",&e);
				if(i = LocateElem(Lists.elem[i_num].L,e)){
					printf("%d元素位于第%d个位置\n",e,i);
				} 
				else printf("%d元素在线性表中不存在\n",e);
				getchar(); getchar();
				break;
			case 8://8是求前驱节点
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("请输入数据元素：\n");
				scanf("%d",&e);
				val = PriorElem(Lists.elem[i_num].L,e,&pre);
				if(val == OK)
		 			printf("其前驱元素为：%d\n",pre);
		 		else if(val == OVERFLOW)
		 			printf("不存在前驱元素！\n");
		 		else  printf("顺序表中没有该元素！\n");
		 		getchar();getchar();
		 		break;
		 	case 9://9是求后置元素 
		 		if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("请输入数据元素：\n");
				scanf("%d",&e);
				val = NextElem(Lists.elem[i_num].L,e,&next);
				if(val == OK) 
					printf("%d的后继元素是：%d",e,next);
				else if(val == FALSE)
					printf("该元素不存在后继元素");
				else 
					printf("线性表中没有该元素");
				getchar(); getchar();
				break;
			case 10://10是插入元素
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("请输入您要插入的元素:\n");
         		scanf("%d",&e);
         		printf("请输入您要插入元素的位置:\n");
				scanf("%d",&i);
				val = ListInsert(Lists.elem[i_num].L,i,e);
				if(val == OK)
					printf("插入数据成功\n");
				else 
					printf("插入元素失败：\n");
				getchar(); getchar();
				break;
			case 11://11是删除元素 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("请输入您要删除的元素的位置：\n");
				scanf("%d", &i);
				val = ListDelete(Lists.elem[i_num].L,i,&e);
				if(val == OK){
					printf("删除的元素是：%d\n",e);
					printf("删除成功！\n");
				}
				else 
					printf("删除失败\n");
				getchar(); getchar();
				break;
			case 12://12是遍历线性表
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		if(Lists.elem[i_num].L.length == 0)
         			printf("线性表是空表，没有数据元素\n");
				else if(ListTraverse(Lists.elem[i_num].L) == OK)
					printf("线性表遍历成功\n");
				else 
					printf("线性表遍历失败\n");
				getchar(); getchar();
				break;
			case 13://13是保存文件
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("请输入您想保存的文件名：\n");
         		scanf("%s",FileName);
         		//strcpy(FileName,"aaa"); 
				val = SaveList(Lists.elem[i_num].L, FileName);
				if(val == OK) 
					printf("文件保存成功\n文件名是%s\n",FileName);
				else 
					printf("保存失败");
				getchar(); getchar();
				break;
			case 14://14是加载文件
				printf("请输入要加载的文件名：\n");
				scanf("%s",FileName);
				val = LoadList(Lists.elem[i_num].L, FileName); 
				if(val == OK) 
					printf("文件加载成功\n");
				else 
					printf("文件加载失败\n");
				getchar(); getchar();
				break;
			case 15://15是在线性表集合中增添线性表
				printf("请输入要加入的线性表的名称\n");
				scanf("%s",ListName); 
				val = AddList(Lists,ListName);
				if(val == OK)	
					printf("线性表%s成功加入线性表集合\n",ListName);
				else 
					printf("线性表集合中已经有名为%s的线性表\n线性表加入失败\n",ListName);
				getchar(); getchar();
				break;
			case 16://16是从线性表集合中删除线性表
				printf("请输入要删除线性表的名称\n");
				scanf("%s",ListName);
				val = RemoveList(Lists,ListName);
				if(val == OK)
					printf("线性表%s删除成功\n",ListName);
				else
					printf("线性表集合中不存在%s线性表",ListName);
				getchar(); getchar();
				break;
			case 17://17是在线性表集合中查找线性表
				printf("请输入要查找的线性表的名称：\n");
				scanf("%s",ListName);
				val = LocateList(Lists,ListName);
				if(!val)
					printf("线性表集合中不存在%s线性表\n",ListName);
				else
					printf("%s线性表位于线性表集合中第%d个位置\n",ListName,val);
				getchar(); getchar();
				break;
			case 18://19是对线性表排序 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("线性表不存在!\n");
             		getchar(); getchar();
             		break;
         		}
         		SortList(Lists.elem[i_num].L);
         		printf("排序成功\n");
         		getchar(); getchar();
         		break;
			case 0://0是退出菜单
				printf("退出成功\n");
				printf("使用愉快！！"); 
				break; 
		}
	}
		return 0;
}



/***************************************************************
*函数名称：IntiaList
*函数功能：构造一个空的线性表
*函数参数：线性表L 
*注释：初始条件是线性表L不存在；操作结果是构造一个空的线性表。若线性表已经存在，返回INFEASIBLE
*返回值类型：status类型
*时间复杂度：O(1) 
****************************************************************/
status InitList(SqList& L)
//线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L.elem != NULL) return INFEASIBLE;//线性表不为空
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//申请空间 
    if(!L.elem) exit(OVERFLOW);//空间不足，创建失败
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
/***************************************************************
*函数名称：SortList
*函数功能：对线性表的元素进行排序 
*函数参数：线性表L
*注释：初始条件是有线性表L存在 
*返回值类型：status类型
*时间复杂度:O(n2) 
****************************************************************/
/***************************************************************
*函数名称：cmp
*函数功能：辅助比较
*函数参数：两个变量  
*返回值类型：status类型
*时间复杂度:O(1) 
****************************************************************/
status cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

status SortList(SqList& L){
	if(L.elem == NULL) return INFEASIBLE;
	qsort(L.elem,L.length,sizeof(int),cmp);//按从小到大的顺序 
	return OK; 
}

/***************************************************************
*函数名称：DestoryList
*函数功能：销毁线性表
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是销毁线性表L
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L.elem) { //若线性表已经初始化，进行销毁操作
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else return INFEASIBLE; //若线性表未初始化，返回INFEASIBLE
}


/***************************************************************
*函数名称：ClearList
*函数功能：清空顺序表
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是将L重置为空表。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L.elem == NULL)  return INFEASIBLE;//若线性表不存在，返回 INFEASIBLE
    L.length = 0;//清空线性表 
    return OK;
}


/***************************************************************
*函数名称：ListEmpty
*函数功能：判断线性表是否为空
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    
    if(L.elem == NULL) return INFEASIBLE;//线性表不存在 
    else if(L.length == 0) return TRUE;//线性表存在，为空 
    else return FALSE;//线性表存在，不为空 

}


/***************************************************************
*函数名称：ListLength
*函数功能：求线性表的表长
*函数参数：线性表L 
*注释：初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L.elem == NULL) return INFEASIBLE;//线性表不存在 
    else return L.length;//线性表存在，返回长度 
}


/***************************************************************
*函数名称：GetElem
*函数功能：得到某一个元素的值
*函数参数:线性表L，获取元素的位置，存储元素的e 
*注释：初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status GetElem(SqList L,int i,ElemType *e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem == NULL) return INFEASIBLE;//线性表不存在 
    if(i<1 || i>L.length) return ERROR;//i<1或i>线性表长度都不合法 
    *e = L.elem[i-1];//第i个元素赋值给e 
    return OK;
}


/***************************************************************
*函数名称：LocateElem
*函数功能：查找元素
*函数参数：线性表L，带查找元素e 
*注释：初始条件是线性表已存在；操作结果是返回L中第1个与e相等 
       的数据元素的位序，若这样的数据元素不存在，则返回值为0。
*返回值类型：int类型
*时间复杂度：O(n)
****************************************************************/
int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    if(L.elem == NULL) return INFEASIBLE;//线性表不存在，返回 INFEASIBLE
    int flag = 0,loc = 0;//flag表示与e相等的数据元素是否存在，loc记录相等第一个与e相等元素的位置 
    for(int i = 0; i < L.length; i++){
        if(e == L.elem[i]) {
            loc = i;
            flag = 1;
            break; 
        }
    }
    if(flag) return loc+1;//存在yue相等元素 
    else return ERROR;//不存在与e相等的元素 
}


/***************************************************************
*函数名称：PriorElem
*函数功能：求元素的前驱
*函数参数：线性表L,待查找e，存储e的前驱pre 
*注释：初始条件是线性表L已存在；操作结果是若e是L的数据元素，且不是第一个，
       则用pre返回它的前驱，函数返回OK，否则操作失败，函数返回ERROR。
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status PriorElem(SqList L,ElemType e,ElemType *pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem == NULL) return INFEASIBLE;
    if(e == L.elem[0]) return OVERFLOW;
    int flag = 0;//flag记录是否找到e的前驱 
    for(int i = 1; i < L.length; i++){
        if(L.elem[i] == e) {//找到e，e的前驱赋值给pre，跳出循环 
            *pre = L.elem[i-1];
            flag = 1;
            break;
        }
        else continue; 
    }
    if(flag) return OK;
    else return ERROR;
}

/***************************************************************
*函数名称：NextElem
*函数功能：求后继节点
*函数参数：线性表L，所查找元素e，存储e的后继元素的变量next 
*输入输出：初始条件是线性表L已存在；操作结果是若e是L的数据元素，且不是最后一个，
           则用next返回它的后继,函数返回OK，否则操作失败，返回ERROR。
*返回值类型：status类型
时间复杂度：O(n) 
****************************************************************/
status NextElem(SqList L,ElemType e,ElemType *next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if(L.elem == NULL) return INFEASIBLE;
    int flag = 0;
    for(int i = 0; i < L.length-1; i++){
        if(L.elem[i] == e){
            *next = L.elem[i+1];
            flag = 1; 
            break;
        }
    }
    if(flag) return OK;
    else if(e == L.elem[L.length-1]) return FALSE;
    else return -1;

}

/***************************************************************
*函数名称：ListInsert
*函数功能：插入元素
*函数参数：线性表L，待插入位置i，待插入元素e 
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)+1；
*      操作结果是在L的第i个位置之前插入新的数据元素e
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if(L.elem == NULL) return INFEASIBLE;//线性表不存在，返回 INFEASIBLE
    if(i<1 || i>L.length+1) return ERROR;//插入位置不合法，返回 ERROR
    if(L.length >= L.listsize) {//线性表空间不足，申请更大的空间 
        int *newbase =(int *)realloc(L.elem,(L.listsize + LISTINCREMENT)*sizeof(int));
	    if(!newbase) exit(OVERFLOW); //空间不足，退出 OVERFLOW
        L.elem = newbase;
	    L.listsize += LISTINCREMENT;
    }
    int j;
    if(L.length == 0) L.elem[0] = e;//如果空表，在第一个位置插入 
    else {//不是空表，将元素后移，插入e 
        for(j = L.length-1; j >= i-1; j--){
            L.elem[j+1] = L.elem[j];
        }
        L.elem[j+1] = e;
    }
    L.length ++;//线性表长度+1 
    return OK;//插入成功 

}

/***************************************************************
*函数名称：ListDelete
*函数功能：删除元素
*函数参数：线性表L,待删除位置，存储待删除元素e 
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；
*      操作结果：删除L的第i个数据元素，用e返回其值。
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListDelete(SqList &L,int i,ElemType *e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if(L.elem == NULL) return INFEASIBLE;//若线性表是空表，返回 INFEASIBLE
    if(i<1 || i > L.length) return ERROR;//删除元素位置不合法，返回ERROR 
    *e = L.elem[i-1];//将要删除元素赋值给e 
    for(int j = i; j < L.length; j++){//移动元素 
        L.elem[j-1] = L.elem[j];
    }
    L.length --;//线性表长度-1 
    return OK;//成功删除 

}

/***************************************************************
*函数名称：ListTrabverse
*函数功能：遍历顺序表
*函数参数：线性表L 
*注释：输出顺序表的值
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
   
    if(L.elem == NULL) return INFEASIBLE; //线性表不存在，返回INFEASIBLE
    for(int i = 0; i < L.length; i++)  //遍历 输出 
        printf("%d ",L.elem[i]);
    return OK;//成功遍历 
}

/***************************************************************
*函数名称：SaveList
*函数功能：保存线性表
*函数参数： 线性表L,字符数组 FileName 
*注释：将线性表保存到文件中，
*返回值类型：status类型
*时间复杂度O(n) 
****************************************************************/
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (!L.elem) return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    ElemType *p = L.elem, *q = L.elem + L.length;
    //fprintf(fp, "%d\n", L.length);
    for (; p < q; ++p)
        fprintf(fp, "%d ", *p);
    fprintf(fp, "0");
    fclose(fp);
    return OK;

}

/***************************************************************
*函数名称：LoadList
*函数功能：加载文件
*函数参数：线性表L,字符数组FileName 
*注释：加载文件
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
   
    if(!L.elem)
    {
FILE *fp = fopen(FileName, "r");
    L.length = 0;
    L.listsize = 100;
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    ElemType q;
    fscanf(fp, "%d", &q);
    while (q){
        L.elem[L.length++] = q;
        fscanf(fp, "%d", &q);
    }
    fclose(fp);
    return OK;
    }
    else return INFEASIBLE;
}

/***************************************************************
*函数名称：AddList
*函数功能：Lists中增加一个名称为ListName的空线性表
*函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度: 
****************************************************************/
status AddList(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的空线性表
{
    if (Lists.length == 10) return ERROR;
    int i=0;
    for(;ListName[i]!='\0';i++){
        Lists.elem[Lists.length].name[i]=ListName[i];
    }
    Lists.elem[Lists.length].name[i]='\0';
    Lists.elem[Lists.length].L.elem=NULL;
    InitList(Lists.elem[Lists.length].L);
    ++Lists.length;
    return OK;
}

/***************************************************************
*函数名称：RemoveList
*函数功能：Lists中删除一个名称为ListName的空线性表
/函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度:
****************************************************************/

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{

    for (int i = 0; i < Lists.length; ++i) {
    if (my_strcmp(Lists.elem[i].name, ListName) == 0) {
        for (int j = i + 1; j < Lists.length; ++j) {
            my_strcpy(Lists.elem[j - 1].name, Lists.elem[j].name);
            Lists.elem[j - 1].L = Lists.elem[j].L;
        }
        Lists.length--;
        return OK;
    }
}
return ERROR;
}

/***************************************************************
*函数名称：LocateList
*函数功能：Lists中查找一个名称为ListName的空线性表
*函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度:
****************************************************************/
status LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; ++i){
        if (my_strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

