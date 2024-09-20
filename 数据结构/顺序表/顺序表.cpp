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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef struct{  //˳���˳��ṹ���Ķ���
      ElemType * elem;
      int length;
      int listsize;
     }SqList;
typedef struct{  //���Ա�ļ������Ͷ���
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
	int i_num = 9;//���ڲ��������Ա� 
	int op = 1;//�˵� 
	while(op){
		system("cls");	//���� 
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
		printf("    ��ѡ����Ĳ���[0-22]:\n");
		scanf("%d",&op);
		switch(op){
			case 1://1�ǳ�ʼ�����Ա� 
				if(InitList(Lists.elem[i_num].L) == OK) {
					printf("������Ҫ��������Ա������\n");
					scanf("%s",Lists.elem[i_num].name);
					printf("���Ա����ɹ�\n"); 
				}
				else {
					printf("���Ա��Ѿ�����\n"); 
					printf("���Ա���ʧ��\n");
				}
				getchar();getchar();
				break; 
			case 2://2���������Ա�
				if(Lists.elem[i_num].L.elem == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				} 
				if(DestroyList(Lists.elem[i_num].L) == OK){
					printf("���Ա����ٳɹ�\n"); 
					Lists.length --; //���Ա���Ŀ��һ 
				}
				else printf("���Ա�����ʧ��\n");
				getchar(); getchar();
				break; 
			case 3://3��������Ա�
				if(Lists.elem[i_num].L.elem == NULL){
        			printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		} 
         		if(ClearList(Lists.elem[i_num].L) == OK)
         			printf("���Ա���ճɹ�\n"); 
				else printf("���Ա����ʧ��\n");
				getchar(); getchar();
				break;
			case 4://4���ж����Ա��Ƿ�Ϊ��
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		} 
         		if(ListEmpty(Lists.elem[i_num].L) == TRUE){
         			printf("���Ա�Ϊ��\n"); 
				}
				else printf("���Ա��ǿձ�\n");
				getchar(); getchar();
				break;
			case 5://5�ǵõ����Ա��� 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("���Ա��Ϊ %d\n",ListLength(Lists.elem[i_num].L));
         		getchar(); getchar();
         		break;
         	case 6://6�ǵõ�ĳ��Ԫ��
			 	if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("������ҪȡԪ�ص�λ��:\n");
				scanf("%d",&i);
				if(GetElem(Lists.elem[i_num].L,i,&e) == OK)
					printf("��%d��λ��Ԫ����:%d\n",i,e);
				else 
					printf("����λ�ô���\n");
				getchar(); getchar();
				break;
			case 7://7��ȷ��Ԫ��λ��
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("����������Ԫ�ص�ֵ��\n");
				scanf("%d",&e);
				if(i = LocateElem(Lists.elem[i_num].L,e)){
					printf("%dԪ��λ�ڵ�%d��λ��\n",e,i);
				} 
				else printf("%dԪ�������Ա��в�����\n",e);
				getchar(); getchar();
				break;
			case 8://8����ǰ���ڵ�
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("����������Ԫ�أ�\n");
				scanf("%d",&e);
				val = PriorElem(Lists.elem[i_num].L,e,&pre);
				if(val == OK)
		 			printf("��ǰ��Ԫ��Ϊ��%d\n",pre);
		 		else if(val == OVERFLOW)
		 			printf("������ǰ��Ԫ�أ�\n");
		 		else  printf("˳�����û�и�Ԫ�أ�\n");
		 		getchar();getchar();
		 		break;
		 	case 9://9�������Ԫ�� 
		 		if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("����������Ԫ�أ�\n");
				scanf("%d",&e);
				val = NextElem(Lists.elem[i_num].L,e,&next);
				if(val == OK) 
					printf("%d�ĺ��Ԫ���ǣ�%d",e,next);
				else if(val == FALSE)
					printf("��Ԫ�ز����ں��Ԫ��");
				else 
					printf("���Ա���û�и�Ԫ��");
				getchar(); getchar();
				break;
			case 10://10�ǲ���Ԫ��
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("��������Ҫ�����Ԫ��:\n");
         		scanf("%d",&e);
         		printf("��������Ҫ����Ԫ�ص�λ��:\n");
				scanf("%d",&i);
				val = ListInsert(Lists.elem[i_num].L,i,e);
				if(val == OK)
					printf("�������ݳɹ�\n");
				else 
					printf("����Ԫ��ʧ�ܣ�\n");
				getchar(); getchar();
				break;
			case 11://11��ɾ��Ԫ�� 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
				printf("��������Ҫɾ����Ԫ�ص�λ�ã�\n");
				scanf("%d", &i);
				val = ListDelete(Lists.elem[i_num].L,i,&e);
				if(val == OK){
					printf("ɾ����Ԫ���ǣ�%d\n",e);
					printf("ɾ���ɹ���\n");
				}
				else 
					printf("ɾ��ʧ��\n");
				getchar(); getchar();
				break;
			case 12://12�Ǳ������Ա�
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		if(Lists.elem[i_num].L.length == 0)
         			printf("���Ա��ǿձ�û������Ԫ��\n");
				else if(ListTraverse(Lists.elem[i_num].L) == OK)
					printf("���Ա�����ɹ�\n");
				else 
					printf("���Ա����ʧ��\n");
				getchar(); getchar();
				break;
			case 13://13�Ǳ����ļ�
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		printf("���������뱣����ļ�����\n");
         		scanf("%s",FileName);
         		//strcpy(FileName,"aaa"); 
				val = SaveList(Lists.elem[i_num].L, FileName);
				if(val == OK) 
					printf("�ļ�����ɹ�\n�ļ�����%s\n",FileName);
				else 
					printf("����ʧ��");
				getchar(); getchar();
				break;
			case 14://14�Ǽ����ļ�
				printf("������Ҫ���ص��ļ�����\n");
				scanf("%s",FileName);
				val = LoadList(Lists.elem[i_num].L, FileName); 
				if(val == OK) 
					printf("�ļ����سɹ�\n");
				else 
					printf("�ļ�����ʧ��\n");
				getchar(); getchar();
				break;
			case 15://15�������Ա������������Ա�
				printf("������Ҫ��������Ա������\n");
				scanf("%s",ListName); 
				val = AddList(Lists,ListName);
				if(val == OK)	
					printf("���Ա�%s�ɹ��������Ա���\n",ListName);
				else 
					printf("���Ա������Ѿ�����Ϊ%s�����Ա�\n���Ա����ʧ��\n",ListName);
				getchar(); getchar();
				break;
			case 16://16�Ǵ����Ա�����ɾ�����Ա�
				printf("������Ҫɾ�����Ա������\n");
				scanf("%s",ListName);
				val = RemoveList(Lists,ListName);
				if(val == OK)
					printf("���Ա�%sɾ���ɹ�\n",ListName);
				else
					printf("���Ա����в�����%s���Ա�",ListName);
				getchar(); getchar();
				break;
			case 17://17�������Ա����в������Ա�
				printf("������Ҫ���ҵ����Ա�����ƣ�\n");
				scanf("%s",ListName);
				val = LocateList(Lists,ListName);
				if(!val)
					printf("���Ա����в�����%s���Ա�\n",ListName);
				else
					printf("%s���Ա�λ�����Ա����е�%d��λ��\n",ListName,val);
				getchar(); getchar();
				break;
			case 18://19�Ƕ����Ա����� 
				if(Lists.elem[i_num].L.elem == NULL){
             		printf("���Ա�����!\n");
             		getchar(); getchar();
             		break;
         		}
         		SortList(Lists.elem[i_num].L);
         		printf("����ɹ�\n");
         		getchar(); getchar();
         		break;
			case 0://0���˳��˵�
				printf("�˳��ɹ�\n");
				printf("ʹ����죡��"); 
				break; 
		}
	}
		return 0;
}



/***************************************************************
*�������ƣ�IntiaList
*�������ܣ�����һ���յ����Ա�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�����ڣ���������ǹ���һ���յ����Ա������Ա��Ѿ����ڣ�����INFEASIBLE
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1) 
****************************************************************/
status InitList(SqList& L)
//���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem != NULL) return INFEASIBLE;//���Ա�Ϊ��
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//����ռ� 
    if(!L.elem) exit(OVERFLOW);//�ռ䲻�㣬����ʧ��
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
/***************************************************************
*�������ƣ�SortList
*�������ܣ������Ա��Ԫ�ؽ������� 
*�������������Ա�L
*ע�ͣ���ʼ�����������Ա�L���� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n2) 
****************************************************************/
/***************************************************************
*�������ƣ�cmp
*�������ܣ������Ƚ�
*������������������  
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(1) 
****************************************************************/
status cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

status SortList(SqList& L){
	if(L.elem == NULL) return INFEASIBLE;
	qsort(L.elem,L.length,sizeof(int),cmp);//����С�����˳�� 
	return OK; 
}

/***************************************************************
*�������ƣ�DestoryList
*�������ܣ��������Ա�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L.elem) { //�����Ա��Ѿ���ʼ�����������ٲ���
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else return INFEASIBLE; //�����Ա�δ��ʼ��������INFEASIBLE
}


/***************************************************************
*�������ƣ�ClearList
*�������ܣ����˳���
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem == NULL)  return INFEASIBLE;//�����Ա����ڣ����� INFEASIBLE
    L.length = 0;//������Ա� 
    return OK;
}


/***************************************************************
*�������ƣ�ListEmpty
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    
    if(L.elem == NULL) return INFEASIBLE;//���Ա����� 
    else if(L.length == 0) return TRUE;//���Ա���ڣ�Ϊ�� 
    else return FALSE;//���Ա���ڣ���Ϊ�� 

}


/***************************************************************
*�������ƣ�ListLength
*�������ܣ������Ա�ı�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L.elem == NULL) return INFEASIBLE;//���Ա����� 
    else return L.length;//���Ա���ڣ����س��� 
}


/***************************************************************
*�������ƣ�GetElem
*�������ܣ��õ�ĳһ��Ԫ�ص�ֵ
*��������:���Ա�L����ȡԪ�ص�λ�ã��洢Ԫ�ص�e 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status GetElem(SqList L,int i,ElemType *e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem == NULL) return INFEASIBLE;//���Ա����� 
    if(i<1 || i>L.length) return ERROR;//i<1��i>���Ա��ȶ����Ϸ� 
    *e = L.elem[i-1];//��i��Ԫ�ظ�ֵ��e 
    return OK;
}


/***************************************************************
*�������ƣ�LocateElem
*�������ܣ�����Ԫ��
*�������������Ա�L��������Ԫ��e 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L�е�1����e��� 
       ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
*����ֵ���ͣ�int����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
int LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    if(L.elem == NULL) return INFEASIBLE;//���Ա����ڣ����� INFEASIBLE
    int flag = 0,loc = 0;//flag��ʾ��e��ȵ�����Ԫ���Ƿ���ڣ�loc��¼��ȵ�һ����e���Ԫ�ص�λ�� 
    for(int i = 0; i < L.length; i++){
        if(e == L.elem[i]) {
            loc = i;
            flag = 1;
            break; 
        }
    }
    if(flag) return loc+1;//����yue���Ԫ�� 
    else return ERROR;//��������e��ȵ�Ԫ�� 
}


/***************************************************************
*�������ƣ�PriorElem
*�������ܣ���Ԫ�ص�ǰ��
*�������������Ա�L,������e���洢e��ǰ��pre 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������e��L������Ԫ�أ��Ҳ��ǵ�һ����
       ����pre��������ǰ������������OK���������ʧ�ܣ���������ERROR��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status PriorElem(SqList L,ElemType e,ElemType *pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem == NULL) return INFEASIBLE;
    if(e == L.elem[0]) return OVERFLOW;
    int flag = 0;//flag��¼�Ƿ��ҵ�e��ǰ�� 
    for(int i = 1; i < L.length; i++){
        if(L.elem[i] == e) {//�ҵ�e��e��ǰ����ֵ��pre������ѭ�� 
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
*�������ƣ�NextElem
*�������ܣ����̽ڵ�
*�������������Ա�L��������Ԫ��e���洢e�ĺ��Ԫ�صı���next 
*�����������ʼ���������Ա�L�Ѵ��ڣ������������e��L������Ԫ�أ��Ҳ������һ����
           ����next�������ĺ��,��������OK���������ʧ�ܣ�����ERROR��
*����ֵ���ͣ�status����
ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status NextElem(SqList L,ElemType e,ElemType *next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
*�������ƣ�ListInsert
*�������ܣ�����Ԫ��
*�������������Ա�L��������λ��i��������Ԫ��e 
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
*      �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{

    if(L.elem == NULL) return INFEASIBLE;//���Ա����ڣ����� INFEASIBLE
    if(i<1 || i>L.length+1) return ERROR;//����λ�ò��Ϸ������� ERROR
    if(L.length >= L.listsize) {//���Ա�ռ䲻�㣬�������Ŀռ� 
        int *newbase =(int *)realloc(L.elem,(L.listsize + LISTINCREMENT)*sizeof(int));
	    if(!newbase) exit(OVERFLOW); //�ռ䲻�㣬�˳� OVERFLOW
        L.elem = newbase;
	    L.listsize += LISTINCREMENT;
    }
    int j;
    if(L.length == 0) L.elem[0] = e;//����ձ��ڵ�һ��λ�ò��� 
    else {//���ǿձ���Ԫ�غ��ƣ�����e 
        for(j = L.length-1; j >= i-1; j--){
            L.elem[j+1] = L.elem[j];
        }
        L.elem[j+1] = e;
    }
    L.length ++;//���Ա���+1 
    return OK;//����ɹ� 

}

/***************************************************************
*�������ƣ�ListDelete
*�������ܣ�ɾ��Ԫ��
*�������������Ա�L,��ɾ��λ�ã��洢��ɾ��Ԫ��e 
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
*      ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListDelete(SqList &L,int i,ElemType *e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{

    if(L.elem == NULL) return INFEASIBLE;//�����Ա��ǿձ����� INFEASIBLE
    if(i<1 || i > L.length) return ERROR;//ɾ��Ԫ��λ�ò��Ϸ�������ERROR 
    *e = L.elem[i-1];//��Ҫɾ��Ԫ�ظ�ֵ��e 
    for(int j = i; j < L.length; j++){//�ƶ�Ԫ�� 
        L.elem[j-1] = L.elem[j];
    }
    L.length --;//���Ա���-1 
    return OK;//�ɹ�ɾ�� 

}

/***************************************************************
*�������ƣ�ListTrabverse
*�������ܣ�����˳���
*�������������Ա�L 
*ע�ͣ����˳����ֵ
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListTraverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
   
    if(L.elem == NULL) return INFEASIBLE; //���Ա����ڣ�����INFEASIBLE
    for(int i = 0; i < L.length; i++)  //���� ��� 
        printf("%d ",L.elem[i]);
    return OK;//�ɹ����� 
}

/***************************************************************
*�������ƣ�SaveList
*�������ܣ��������Ա�
*���������� ���Ա�L,�ַ����� FileName 
*ע�ͣ������Ա��浽�ļ��У�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�O(n) 
****************************************************************/
status  SaveList(SqList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
*�������ƣ�LoadList
*�������ܣ������ļ�
*�������������Ա�L,�ַ�����FileName 
*ע�ͣ������ļ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
****************************************************************/
status  LoadList(SqList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
*�������ƣ�AddList
*�������ܣ�Lists������һ������ΪListName�Ŀ����Ա�
*�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: 
****************************************************************/
status AddList(LISTS &Lists,char ListName[])
// ��Lists������һ������ΪListName�Ŀ����Ա�
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
*�������ƣ�RemoveList
*�������ܣ�Lists��ɾ��һ������ΪListName�Ŀ����Ա�
/�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:
****************************************************************/

status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
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
*�������ƣ�LocateList
*�������ܣ�Lists�в���һ������ΪListName�Ŀ����Ա�
*�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:
****************************************************************/
status LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    for (int i = 0; i < Lists.length; ++i){
        if (my_strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

