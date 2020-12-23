#include<iostream>
using namespace std;//!bug:cout,cin需用此行
#define MaxVNum 100//最大结点数量!bug:define后不用跟分号
#define MaxSize 100


typedef struct Painter{//实体
    int id;
	char name[20];
	int age;
	char sex[10];
	char city[20];
	int careerAge;
}Painter;

typedef struct PainterNode{//创建链表
    Painter data;
	struct PainterNode *next;
}PainterNode, *LinkList;

int InitList(LinkList &L){//链表初始化
    L=new PainterNode;
	L->next=NULL;
	return 1;
}

int InsertList(LinkList &L, Painter painter){//1.实现添加操作
    PainterNode *p, *s;
	p=L;
	while(p->next)
		p=p->next;//将全部信息便利

	s=new PainterNode;
	s->data=painter;
	s->next=NULL;

	p->next=s;
	return 1;
}

int DeleteList(LinkList &L, int id){//2.实现删除操作（根据id删除）
	PainterNode *p;//p为id所在节点的前驱节点指针
	p=L;
	while(p->next){
		if(p->next->data.id==id)
			break;
		p=p->next;
	}
    
	if(p->next!=NULL)
	    p->next=p->next->next;
	else{
	    cout<<"要删除的结点不存在！";
		return 0;
	}
}

void EditList(LinkList &L, int id){//3.修改painter信息（根据Id）
    Painter painter;
	PainterNode *p;
    p=L->next;
	while(p){
		if(p->data.id==id){ 
			DeleteList(L,id);
            cout<<"***请重新输入信息***"<<endl;
			cout<<"请输入id：";
			cin>>painter.id;
			cout<<"请输入姓名：";
			cin>>painter.name;
			cout<<"请输入年龄：";
			cin>>painter.age;
			cout<<"请输入性别：";
			cin>>painter.sex;
			cout<<"请输入所在城市：";
			cin>>painter.city;
			cout<<"请输入从事年限：";
			cin>>painter.careerAge;
			InsertList(L, painter);//！！bug:同一个函数中不能调用类型不同（一个void一个int就出bug）的函数
		}else
            cout<<"请输入正确的id号！";
		p=p->next;
	}

}

void LocateListId(LinkList L, int id){//4.查询painter的信息（根据id查询）
	PainterNode *p;
	p=L->next;
	while(p){
		if(p->data.id==id){
			cout<<"id："<<p->data.id<<endl;
			cout<<"姓名："<<p->data.name<<endl;
			cout<<"年龄："<<p->data.age<<endl;
			cout<<"性别："<<p->data.sex<<endl;
			cout<<"所在城市："<<p->data.city<<endl;
			cout<<"从事年限："<<p->data.careerAge<<endl;
		}else{
			cout<<"查询不到您输入的id！";
		}
		p=p->next;
	}
}

int GetListNum(LinkList L){//5.统计painter的个数
	int num=0;
	PainterNode *p;
	p=L;
	while(p->next){
		num++;	
		p=p->next;
	}
	return num;
}

void DisplayList(LinkList L){//6.实现输出列表操作
    PainterNode *p;
	p=L->next;
	while(p){
	    cout<<"id:"<<p->data.id<<endl;
		cout<<"姓名"<<p->data.name<<endl;
		cout<<"年龄："<<p->data.age<<endl;
		cout<<"性别："<<p->data.sex<<endl;
		cout<<"所在城市："<<p->data.city<<endl;
		cout<<"从事年限："<<p->data.careerAge<<endl;
		p=p->next;
	}
}
//------
void DisplayMenu(){
	cout<<"painter信息管理系统功能菜单"<<endl;
	cout<<"1.增加painter"<<endl;
	cout<<"2.删除painter"<<endl;
	cout<<"3.修改painter"<<endl;
	cout<<"4.查询painter信息"<<endl;
	cout<<"5.统计painter个数"<<endl;
	cout<<"6.输出painter列表"<<endl;
	cout<<"7.退出"<<endl;							
}
//----------------------------------以上为painter功能

void DisplayChoose(){
	cout<<"请选择您要打开的painter功能："<<endl;
    cout<<"1.painter管理系统功能菜单"<<endl;
	cout<<"2.painter图结构数据处理程序"<<endl;
}

void InputPainter(Painter &painter){
    cout<<"请输入id：";
	cin>>painter.id;
	cout<<"请输入姓名：";
	cin>>painter.name;
	cout<<"请输入年龄：";
	cin>>painter.age;
	cout<<"请输入性别：";
	cin>>painter.sex;
	cout<<"请输入所在城市：";
	cin>>painter.city;
	cout<<"请输入从事年限：";
	cin>>painter.careerAge;
}

//---------------------------------以下为painter图
void DisplayTu(){
	cout<<"paintee图结构数据处理程序"<<endl;
	cout<<"1.创建painter图"<<endl;
	cout<<"2.按照深度遍历方式打印所有painter"<<endl;
	cout<<"3.按照广度遍历方式打印所有painter"<<endl;
	cout<<"4.退出"<<endl;
}
//------
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
	Painter data;
	ArcNode *firstarc;
}VNode,AdjList[MaxVNum];

typedef struct ALGraph{
	AdjList vertices;
	int vexnum,arcnum;
}ALGraph;
  
int LocateGraph(ALGraph G, int id){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.id==id)
			break;
	if(i==G.vexnum)
		i=-1;
	return i;
}

void CreateUDG(ALGraph &G){//1.创建painter图
	int i,j,k;
	int id;
    ArcNode *s;
	cout<<"请输入顶点数的总数：";
	cin>>G.vexnum;
	cout<<"请输入边数的总数：";
	cin>>G.arcnum;

	for(k=0;k<G.vexnum;k++){
		InputPainter(G.vertices[k].data);
        G.vertices[k].firstarc=NULL;
	}

    for(k=0;k<G.arcnum;k++){
		cout<<"请输入当前边的一个painter的id：";
		cin>>id;
		i=LocateGraph(G,id);

		cout<<"请输入当前边的另一个painter的id：";
		cin>>id;
		j=LocateGraph(G,id);

		//为[i]新增指向j的边界点，挂到链表，头插法
        s=new ArcNode;
		s->adjvex=j;
		s->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=s;
		//为[j]新增指向i的边界点，挂到链表，头插法
		s=new ArcNode;
		s->adjvex=i;
		s->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=s;
	}

}

typedef struct SqStack{//创建栈!bug:typedef的函数就不要加()
	int *base;
	int *top;
	int stacksize;
}SqStack;

int InitStack(SqStack &S){//栈的初始化
	S.base=new int[MaxSize];
	if(!S.base)
		return -1;
	S.top=S.base;
	S.stacksize=MaxSize;
	return 1;
}

int EmptyStack(SqStack S){//判断栈空否
    if(S.top==S.base)
		return 1;
	else 
		return 0;
}

int Push(SqStack &S, int e){//压栈
	if(S.top-MaxSize==S.base)
		return 0;
	else{
		*(S.top)=e;
		S.top++;
		return 1;
	}
}

int Pop(SqStack &S, int &e){//出栈
    if(S.base==S.top)
		return 0;
	else{
		S.top--;
		e=*(S.top);
	    return 1;
	}
}

void DisplayPainter(Painter p){
	cout<<"id:"<<p.id<<endl;
	cout<<"姓名："<<p.name<<endl;
	cout<<"年龄："<<p.age<<endl;
	cout<<"性别："<<p.sex<<endl;
	cout<<"所在城市："<<p.city<<endl;
	cout<<"从事年限："<<p.careerAge<<endl;
}

void DepthTraverseGraph(ALGraph G){//2.深度遍历所有的painter
    int id,v,i;
	SqStack S;
	ArcNode *p;
	int visited[MaxVNum];
	cout<<"请输入初始点的id:";
	cin>>id;
	v=LocateGraph(G, id);
	for(i=0;i<G.vexnum;i++)
		visited[i]=0;
	InitStack(S);
	visited[v]=1;
	Push(S, v);
	while(!EmptyStack(S)){//若栈不空
		Pop(S, v);
        DisplayPainter(G.vertices[v].data);
		p=G.vertices[v].firstarc;
		while(p){
			if(visited[p->adjvex]==0){
				Push(S, p->adjvex);
			    visited[p->adjvex]=1;
			}
			p=p->nextarc;
		}
	}
	i=0;
}	

typedef struct Queue{//队列的存贮结构
    int *base;
	int front,rear;
}SeQueue;

int InitQueue(SeQueue &Q){
    Q.base=new int[MaxSize];
	if(!Q.base)
		return 0;
	Q.front=0;
	Q.rear=0;//头尾指针都为0，对列为空
	return 1;
}

int EmptyQueue(SeQueue &q){ //判断是否为空列
	if(q.rear==q.front)
		return 1;
	return 0;
}

int EnQueue(SeQueue &Q,int e){//入队
	if((Q.rear+1)%MaxSize==Q.front)
		return 0;
	Q.base[Q.rear]=e;//新元素加在队尾
	Q.rear=(Q.rear+1)%MaxSize;//队尾指针+1
	return 1;
}

int DeQueue(SeQueue &Q,int &e)
{//出队
	if(Q.front==Q.rear)
		return 0;
	e=Q.base[Q.front];//新元素插入队尾
	Q.front=(Q.front+1)%MaxSize;//队尾指针+1
	return 1;
}

void BFS(ALGraph G){//3.广度优先遍历方式打印painter
    int visited[MaxVNum];
	ArcNode *p;
	int i,v,id;
    Queue Q;
	cout<<"请输入初始点的id:";
	cin>>id;
	v=LocateGraph(G, id);
    for(i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    InitQueue(Q);  //初始化队列 
   	visited[v]=1;
	EnQueue(Q, v);
	while(!EmptyQueue(Q)){//若栈不空
		DeQueue(Q, v);
        DisplayPainter(G.vertices[v].data);
		p=G.vertices[v].firstarc;
		while(p){
			if(visited[p->adjvex]==0){
				EnQueue(Q, p->adjvex);
			    visited[p->adjvex]=1;
			}
			p=p->nextarc;
		}
	}
}

int main(){
	int choose;

	int id;
	int choice;
	int num;
    Painter painter;
	LinkList L;
	InitList(L);//为链表结点的数据封装

	ALGraph G;//为图的结构封装
    
    while(1){//先进行1及分类
		DisplayChoose();
		cout<<"输出选项：";
		cin>>choose;
		if(choose==1){//2及分类
			DisplayMenu();
			cout<<"输入选项：";
			cin>>choice;
			switch(choice){
			   case 1:
				   InputPainter(painter);
				   InsertList(L,painter);
				   break;
			   case 2:
				   cout<<"要删除节点的id是:";
				   cin>>id;
				   DeleteList(L, id);
				   break;
			   case 3:
				   cout<<"要修改的结点id是：";
				   cin>>id;
				   EditList(L, id);
				   break;
			   case 4:
				   cout<<"要查找结点的id是：";
				   cin>>id;
				   LocateListId(L, id);
				   break;
			   case 5:
				   num=GetListNum(L);
				   cout<<num;
				   break;
			   case 6:
				   DisplayList(L);
				   break;
			   case 7:
				   return 0;
				   break;
			   default:
				 cout<<"您输入的号码不正确！"<<endl;
			}
		}else if(choose==2){//2及分类
             DisplayTu();
		   	 cout<<"输入选项：";
	      	 cin>>choice;
			 switch(choice){
			   case 1:
				   CreateUDG(G);
				   break;
			   case 2:
				   DepthTraverseGraph(G);
				   break;
			   case 3:
				   BFS(G);
				   break;
			   case 4:
				   return 0;
				   break;
			   default:
				   cout<<"您输入的号码不正确！"<<endl;
			}
		}else
			cout<<"您输入的号码不正确！"<<endl;
	}
	return 0;
}