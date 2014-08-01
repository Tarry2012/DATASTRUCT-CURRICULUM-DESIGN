///////////////////////////////////////////////////////////////////////////////////////////
///
///
///       @File interestplaces.c
///
///       @brief 数据结构课程设计 图  
///
///       @Version 1.0
///       @data  2013年12月15日 14时53分18秒
///       
///       
///
///       @Author  Tang Qiuyuan, tangqyuan@gmail.com
///         
/// 
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


/**
 * @fn 创建旅游景点无向带权图的邻接表，顶点数组的下标从1开始.
 * 
 * @param 景点图的邻接表. 
 */
void createadjgraph(graphadjlist *graph)		
{
	int i,j,k;
	int m = 0;
	int n = 0;
	unsigned roadweight;						///<权值
	edgenode *edge;

	graph->numvertexes = 0;
	graph->numedges = 0;
	for (i = 1; i <= MAXVEX; i++)
	{
		strcpy(graph->adjlist[i].data, "#");
		strcpy(graph->adjlist[i].information, "#");
		graph->adjlist[i].firstedge = NULL;
	}

	printf("输入景点数和道路数：\n");						///<输入图的顶点数和边数
	scanf("%d%d", &graph->numvertexes, &graph->numedges);

	for (i = 1; i <= graph->numvertexes; i++)				///<输入图的顶点信息
	{
		printf("输入景点%d名称:\n", i);
		scanf("%s", graph->adjlist[i].data);
		printf("输入景点%d信息介绍:\n", i);
		scanf("%s", graph->adjlist[i].information);
		graph->adjlist[i].firstedge = NULL;
	}
	m = graph->numedges;
	n = graph->numvertexes;
	for (k = 1; k <= m; k++)				///<创建边集
	{
		do
		{
			printf("请正确输人道路%d上的两个景点序号(i, j):  ", k);
			scanf("%d%d", &i, &j);
		}while(i > m || j > m);
		printf("输入路径长度:\n");
		scanf("%d", &roadweight);

		edge = (edgenode *)malloc(sizeof(edgenode));	///<向内存申请空间，生成边结点
		///i结点与j结点相连，所以i结点邻接点域存入j
		edge->adjvex = j;						
		///边上的权值存入边结点weight中
		edge->weight = roadweight;
		///用头插入建立顶点i的邻接边链
		edge->next = graph->adjlist[i].firstedge;
		graph ->adjlist[i].firstedge = edge;

		///向内存申请空间，生成边结点
		edge = (edgenode *)malloc(sizeof(edgenode));
		///j结点与i结点相连，所以j结点邻接点存入j
		edge->adjvex = i;
		///边上的权值存入边结点weight中
		edge->weight = roadweight;
		///用头插法建立顶点j的邻接边链
		edge->next = graph->adjlist[j].firstedge;
		graph->adjlist[j].firstedge = edge;
	}
	graph->numedges = m;
	graph->numvertexes = n;
}


/** @fn 打印出景点的地图信息.
 *
 *  @param 景点图的邻接表.
 *
 *  @return 如果景区内没有景点，返回-1.否则返回0.
 */
int output_graph(const graphadjlist *graph)
{
	int i = 0;
	int count = 1;						///<输出时给景点标号
	edgenode *edge;
	int verxnum = graph->numvertexes;

	///先判断该景区有没有景点
	if (graph->numvertexes <= 0)
	{
		printf("$该景区没有景点！\n");
		return -1;
	}
	
	printf("\t$景区的景点有：\n");
	///显示一个景点，景点介绍及它与周围景点的联系
	for (i = 1; i <= MAXVEX; i++)
	{
		if (strcmp(graph->adjlist[i].data, "#"))
		{
			edge = graph->adjlist[i].firstedge;
			///输出景点的信息
			printf("%d.景点名称：%s 景点介绍：%s\n", count,graph->adjlist[i].data, graph->adjlist[i].information);
			count++;
			if (edge == NULL)
			{
				printf("%s$周围没有相邻的景点\n", graph->adjlist[i].data);
			}
			else printf("$周围的景点有：");
			while (edge)
			{
				printf("%s ", graph->adjlist[edge->adjvex].data);
				edge = edge->next;
			}
		printf("\n\n");
		}
	}
	return 0;
	
}


/**
 * @fn 景点的查询。输入一个景点名称，显示出与它相关的景点信息.
 *
 * @param 景区地图邻接表.
 */
void search_placenode(const graphadjlist *graph)
{
	char placename[20];
	int i = 0;
	int flag = 0;
	int numverx = MAXVEX;
	edgenode *edge;

	printf("$请输入要查询的景点名称：\n");
	scanf("%s", placename);
	///利用顶点景点存于顺序表的结构，根据下标查找
	for (i = 1; i <= numverx; i++)
	{
		///找到后，输出景点的信息
		if (!strcmp(placename, graph->adjlist[i].data))
		{
			printf("景点名称：%s 景点介绍:%s\n", graph->adjlist[i].data, graph->adjlist[i].information);
			edge = graph->adjlist[i].firstedge;
			while (edge)
			{
				printf("与景点%s 相聚%d米；", graph->adjlist[edge->adjvex].data, edge->weight);
				edge = edge->next;
			}
			///设标志，如果找到了景点，则将flag置为1
			flag = 1;
		}
	}
	printf("\n");

	///flag值为0，说明景点不存在
	if (flag == 0)
	{
		printf("$该景点不存在!\n");
	}
}



/** 
 * @fn 利用深度优先搜索算法.
 *
 * @param graph为景区的地图邻接表，i 为开始搜索的景点下标， visited记录访问过的景点，n是visited数组的大小.
 */
void deep_first_search(const graphadjlist *graph, int i, int visited[], int n)
{
	edgenode *edge;
	///visited数组用来记录该景点是否被访问过，访问过置为1
	visited[i] = 1;
	///访问结点
	printf("%s ", graph->adjlist[i].data);
	edge = graph->adjlist[i].firstedge;
	///深搜，访问它的邻接
	while (edge)
	{
		///在访问邻接点前，判断该景点是否被访问过
		if (!visited[edge->adjvex])
		{
			deep_first_search(graph, edge->adjvex, visited, n);
		}
		edge = edge->next;
	}

}


/**
 * @fn 利用深搜，遍历图.
 *
 * @param 景点的图.
 */
void traver_graph(const graphadjlist *graph)
{
	int numverx = graph->numvertexes;
	int visited[numverx + 1];		///<记录访问过的景点
	int v = 0;
	int count = 1;

	printf("该景区的景点有：\n");
	///初始化visited数组，将其全部置为0
	for (v = 1; v <= numverx; v++)
	{
		visited[v] = 0;
	}
	///一个景点一个景点的遍历一遍
	for (v = 1; v <= numverx; v++)
	{
		///如果该景点没有遍历过，利用深搜遍历
		if (!visited[v])
		{
			deep_first_search(graph, v, visited, numverx);
		}
	}
}


/**
 * @fn 将图的信息存入文件中.
 *
 * @param 景点区的图邻接表.
 */
void save_file_graph(const graphadjlist *graph)
{
	FILE *fp;
	edgenode *edge;
	char ch = '@';
	int i = 0;

	///打开文件
	fp = fopen("saveplace.txt", "wt");
	if (fp == NULL)
	{
		printf("can not open!\n");
	}

	///先将景点图的景点数和道路数按格式存入文件
	fprintf(fp, "%d %d\n", graph->numvertexes, graph->numedges);
	///分别存入各个景点的信息（景点名称，介绍，邻接点）
	for (i = 1; i <= graph->numvertexes; i++)
	{
		edge = graph->adjlist[i].firstedge;
		///将景点的名称，介绍存入文件
		fprintf(fp, "%s %s ", graph->adjlist[i].data, graph->adjlist[i].information);
		while (edge)
		{
			///将它的邻接点存入文件
			fprintf(fp, "%d %d ", edge->adjvex, edge->weight);
			edge = edge->next;
		}
		///在文件中，区别各个景点的信息，用‘@’作为结束标志
		fprintf(fp, "%c", ch);
	}
	///关闭文件
	fclose(fp);
}


/**
 * @fn 将地图从文件中读出.
 *
 * @return 将函数中创建好的图返回.
 */
graphadjlist *read_file_graph(void)
{
	FILE *fp;
	edgenode *edge;
	graphadjlist *graph;
	int i = 0;
	char ch = '&';

	///打开文件
	fp = fopen("saveplace.txt", "rt");
	if (fp == NULL)
	{
		printf("can not open!\n");
	}
	///申请空间
	graph = (graphadjlist *)malloc(sizeof(graphadjlist));
	//将景点的景点数和道路数从文件中读出
	fscanf(fp, "%d %d\n", &graph->numvertexes, &graph->numedges);
	///将各个景点读出
	for (i = 1; i <= graph->numvertexes; i++)
	{
		///从文件中读出该景点的名称和介绍
		fscanf(fp, "%s %s ", graph->adjlist[i].data, graph->adjlist[i].information);
		graph->adjlist[i].firstedge = NULL;
		do
		{
			///从文件中读出该景点的邻接点信息
			edge = (edgenode *)malloc(sizeof(edgenode));
			fscanf(fp, "%d %d ", &edge->adjvex, &edge->weight);
			edge->next = graph->adjlist[i].firstedge;
			graph ->adjlist[i].firstedge = edge;
			fscanf(fp,"%c", &ch);
			///如果不是‘@’，回退文件指针
			if (ch != '@')
			fseek(fp, -1L, SEEK_CUR);
			///直到读到‘@’为止。一旦读到‘@’，就是下一个景点的信息。
		}while(ch != '@');
	}
	for (i = graph->numvertexes + 1; i <= MAXVEX; i++)
	{
		strcpy(graph->adjlist[i].data, "#");
		strcpy(graph->adjlist[i].information, "#");
		graph->adjlist[i].firstedge = NULL;
	}
	///关闭文件
	fclose(fp);
	///返回读出的地图信息
	return graph;
}


/**
 * @fn floyd算法：每对顶点之间的最短路径.
 *
 * @param graph为景区图 path为记录路径矩阵 darray为图的邻接矩阵.
 *
 * @return 如果出发点或者终点为孤点，则返回-1，否则返回0.
*/
int shortestpath_floyd(graphadjlist graph, pathmatirx *path, shortpath *darray)
{
	int v = 0;
	int w = 0;
	int k = 0;
	int i = 0;
	int count = 0;
	int a_judge = 0;		///<出发点下标
	int b_judge = 0;        ///<终点下标
	edgenode *edge;
	char startplace[20];    ///<出发点名称
	char endplace[20];      ///<终点名称

	///初始化darray矩阵,对角线上元素为0，其余为INFINITY
	for (v = 0; v < graph.numvertexes; ++v)
	{
		for (w = 0; w < graph.numvertexes; ++w)
		{
			(*darray)[v][w] = INFINITY;
			if (v == w)
			{
				(*darray)[v][w] = 0;
			}
			(*path)[v][w] = w;
		}
	}
	///进一步初始化darray矩阵，darray[i][j]记录顶点i-顶点j的权值
	for (v = 1; v <= graph.numvertexes; ++v)
	{
		edge = graph.adjlist[v].firstedge;
		while (edge)
		{
			w = edge->adjvex;
			(*darray)[v - 1][w - 1] = edge->weight;
			edge = edge->next;
		}
	}
	
	for (k = 0; k < graph.numvertexes; ++k)
	{
		for (v = 0; v < graph.numvertexes; ++v)
		{
			for (w = 0; w < graph.numvertexes; ++w)
			{
				if ((*darray)[v][w] > (*darray)[v][k] + (*darray)[k][w])
				  ///如果经过下标为k顶点路径比原来两点间路径更短
				  ///将当前两点间权值设为更小的一个
				{
					(*darray)[v][w] = (*darray)[v][k] + (*darray)[k][w];
					///路径设置经过下标为k的顶点
					(*path)[v][w] = (*path)[v][k]; 
				}
			}
		}
	}
	///输入要查询的线路，输入出发点和终点，寻求两者之间的最短线路	
	do 
	{
		printf("请输入出发点和终点: ");
		scanf("%s%s",startplace, endplace);
		a_judge = locatevertex(graph, startplace);
		b_judge = locatevertex(graph, endplace);
		if ((a_judge == -1)|| (b_judge == -1))
		  printf("出发点或终点不存在\n");
	}while ((a_judge == -1) || (b_judge == -1));

	///判断出发点和终点是否可以到达，不可到达返回0
	if ((graph.adjlist[a_judge].firstedge == NULL) || (graph.adjlist[b_judge].firstedge == NULL))
	{
		printf("终点或者出发点为孤点，无法参观！\n");
		return -1;
	}
	v = a_judge;
	w = b_judge;
	///根据path矩阵，得到线路
	printf("%s-%s 需要走 %d 米", graph.adjlist[v].data , graph.adjlist[w].data , (*darray)[v - 1][w - 1]);
	///获得第一个路径顶点下标
	k = (*path)[v - 1][w - 1];
	///打印出发点
	printf(" 经过的景点 %s", graph.adjlist[v].data);
	///如果路径顶点下标不是终点
	while (k != w - 1)
	{
		///打印路径景点
		printf(" -> %s", graph.adjlist[k + 1].data);
		///获得下一个路径顶点下标
		k = (*path)[k][w - 1];
	}
	///打印终点
	printf(" -> %s\n", graph.adjlist[k + 1].data);
	printf("\n");
	return 0;
}

/**
 * @fn 调用floyd算法，求每对顶点之间的最短路径.
 */
int get_between_places(graphadjlist graph)
{
	int i = 0;

	///定义图的邻接矩阵darray
	shortpath darray;
	///定义路径矩阵path,代表对应顶点的最小路径的前驱
	pathmatirx path;

	///调用floyd算法
	i = shortestpath_floyd(graph, &darray, &path);
	///判断shortestpath_floyd函数的返回值
	if (i == -1)
	  return -1;
	else return 0;
}


/**
 * @fn 找到景点start在图中的下标
 *
 * @param graph为景区邻接表 start为景点名
 *
 * @return 如果能找到该景点则返回该景点名的下标，否则返回-1
 */
int locatevertex(graphadjlist graph, char *start)
{
	int i = 0;
	int flag = 0;		///<标志是否能找到该景点

	for (i = 1; i <= MAXVEX; i++)
	{
		if (!strcmp(graph.adjlist[i].data, start))
		{
			flag = 1;
			///找到返回下标
			return i;
		}
	}
	if (flag == 0)
	{
		///没有找到返回-1.
		//printf("该景点不存在！\n");
		return -1;
	}
}


/**
 * @fn 在prime算法中closedge数组中，找到lowcost值最小一个
 *
 * @param closedge数组和该数组的大小
 *
 * @return 返回lowcost最小的下标
 */
int minium(struct close closedge[], int count)
{
	int i = 0;
	int min = INFINITY;		///<记录最小值
	int minindex = 0;		///<记录最小值的下标

	///寻找lowcost值最小的位置
	for (i = 1; i <= count; i++)
	{
		if (min >= closedge[i].lowcost && closedge[i].lowcost != 0)	
		{
			min = closedge[i].lowcost;
			minindex = i;
		}
	}
	///找到lowcost值最小的后，返回其下标
	return minindex;
}


/**
 * @fn 采用prime算法求得最短连通线路
 */
void minispantree_prime(graphadjlist graph)
{
	edgenode *edge = NULL;
	struct close closedge[MAXVEX];
	int k = 0;
	int i = 0;
	int j = 0;
	int k0 = 0;
	char u0[20] = " ";		 ///<前驱
	char v0[20] = " ";       ///<当前
	char start[20] = " ";    ///<出发点名称
	int count = 0;

	///输入出发点,并验证其正确性
	do
	{
		printf("请输入你的出发点： ");
		scanf("%s", start);
		///判断出发点是否存在，并得到它的下标
		k = locatevertex(graph, start);
		if (k == -1)
		{
			printf("重新输入！\n");
		}
	}while (k == -1);
	
	///将出发点对应的closedge数组中的lowcost值设为0,表示该点被选中过了
	closedge[k].lowcost = 0;
	///将closedge[k].adjvex初始化为出发点
	strcpy(closedge[k].adjvex, start);
	///初始化除出发点之外的closedge数组里的数据
	for (i = 1; i <= graph.numvertexes; i++)
	{
		if (i != k)
		{
			closedge[i].lowcost = INFINITY;
		}
	}
	///继续初始化closedge数组，如果有顶点和出发点有关系，将权值存入对应的lowcost中
	for (i = 1; i <= graph.numvertexes; i++)
	{
		if (i != k)
		{
			strcpy(closedge[i].adjvex, " ");
			edge = graph.adjlist[k].firstedge;
			while (edge)
			{
				if (edge->adjvex == i)
				{
					///权值存入对应的closedge数组中
					closedge[i].lowcost = edge->weight;
					strcpy(closedge[i].adjvex,  graph.adjlist[k].data);
				}
				edge = edge->next;
			}
		}
	}
	strcpy(v0, start);
	for (i = 2; i <= graph.numvertexes; i++)
	{
		///得到closedge数组中lowcost最小的下标
		k0 = minium(closedge, graph.numvertexes);
		strcpy(u0, v0);
		strcpy(v0, graph.adjlist[k0].data);
		///打印出走过的顶点
		printf("%s -> ", u0);
		///将顶点v0放入求得生成树的顶点集中
		closedge[k0].lowcost = 0;
		///当v0加入后，更新closedge数组信息
		for (j = 1; j <= graph.numvertexes; j++)
		{
			edge = graph.adjlist[k0].firstedge;
			while (edge)
			{
				if (edge->adjvex == j)
				  ///一旦发现有更小的权值出现，则替换原有信息
				if (edge->weight < closedge[j].lowcost)
				{
					closedge[j].lowcost = edge->weight;
					strcpy(closedge[j].adjvex, v0);
				}
				edge = edge->next;
			}
		}
	}
	///打印出最后一个顶点
	printf("%s\n", v0);
}


/**
 * @fn 判断一个景点是否存在
 *
 * @return 景点存在返回1，否则返回0；
 */
int search_judge(const graphadjlist *graph, char placename[])
{
	int i = 0;
	int flag = 0;
	int numverx = graph->numvertexes;
	edgenode *edge;

	///利用顶点景点存于顺序表的结构，根据关键字查找
	for (i = 1; i <= numverx; i++)
	{
		if (!strcmp(placename, graph->adjlist[i].data))
		{
			edge = graph->adjlist[i].firstedge;
			while (edge)
			{
				edge = edge->next;
			}
			flag = 1;
			///存在返回1
			return 1;
		}
	}
	printf("\n");

	///flag值为0，说明景点不存在
	if (flag == 0)
	{
		return -1;
	}
}


/**
 * @fn 利用广度优先搜索，找到景点1到景点2之间一条中转次数最少的路线
 *
 * @return 当出发点和终点为孤点时，返回-1，否则返回0；
 */
int  broad_first_search(graphadjlist graph)
{
	char startplace[20];				///<终点
	char endplace[20];					///<出发景点
	int  placenode;						///<当前访问到的景点下标
	int  pre[MAXVEX] = {0};				///<记录前趋结点
	int  visited[MAXVEX] = {0};			///<记录结点是否被访问过
	int i = 0;
	int a_judge = 0;                    ///<终点下标
	int b_judge = 0;					///<出发景点下标
	edgenode *edge;
	queue *que;

	///初始化队列
	que = initqueue();
	///初始化pre[]和visited[]数组，都置为-1
	for (i = 1; i <= MAXVEX; i++)
	{
		pre[i] = -1;
		visited[i] = -1;
	}
	///输入出发点和终点,并验证其正确性
	do 
	{
		printf("请输入出发点和终点: ");
		scanf("%s%s",endplace, startplace);
		a_judge = locatevertex(graph, startplace);
		b_judge = locatevertex(graph, endplace);
		if ((a_judge == -1)|| (b_judge == -1))
		  printf("出发点或终点不存在\n");
	}while ((a_judge == -1) || (b_judge == -1));
	
	if ((graph.adjlist[a_judge].firstedge == NULL) || (graph.adjlist[b_judge].firstedge == NULL))
	{
		printf("起点或者终点为孤点，无法参观！\n");
		return -1;
	}
	///出发点已经访问过，visited置为1
	visited[a_judge] = 1;
	///将出发点入队
	inqueue(que, a_judge);
	///一个一个景点开始
	for (i = 1; i <= graph.numvertexes; i++)
	{
		///如果队不空
		while (!emptyqueue(que))
		{
			///出队
			outqueue(que, &placenode);
			///访问它的第一个邻接点
			edge = graph.adjlist[placenode].firstedge;
			while (edge)
			{
				///即将访问的顶点为-1，访问它
				if (visited[edge->adjvex] != 1)
				{
				///	访问过的顶点置为1
					visited[edge->adjvex] = 1;
					///进队
					inqueue(que, edge->adjvex);
					///出队的结点最为当前的前趋
					pre[edge->adjvex] = placenode;
				}
				///访问下一个邻接点
				edge = edge->next;
			}
		}
	}
	///打印出路径
	print_path(graph, pre, MAXVEX,startplace, endplace);
	return 0;
}


/**
 * @fn 打印出中转次数最少的路径
 *
 * @param graph为景点图 pre为记录每一个访问的对应下标的前趋下标 n为pre数组的大小 
 *        startname为终点，endname为出发点
 */
void print_path(graphadjlist graph, int pre[], int n, char startname[], char endname[])
{
	int i = 0;
	int j = 0;
	int a_judge = 0;		///<终点下标
	int b_judge = 0;		///<起点下标
	int p_judge = 0;        ///<当前走到的景点下标
	int count = 0;			///<用来判断出发点和终点是否可以直达
	char placename[20];     ///<当前走到的景点
	
	///得到终点和出发点的下标
	a_judge = locatevertex(graph, startname);
	b_judge = locatevertex(graph, endname);
	printf("可以考虑的线路:\n");
	///打印出出发点
	printf(" %s ->", endname);
	count++;
	p_judge = b_judge;
	///根据pre数组，求得路径
	strcpy(placename, graph.adjlist[pre[p_judge]].data);
	printf(" %s ", placename);
	count++;
	///判断当前走的景点是否为终点，如果不是继续走下去
	while (strcmp(placename, startname))
	{
		for (i = 0; i <= graph.numvertexes; i++)
		{
			if (!strcmp(graph.adjlist[i].data, placename))
			  p_judge = i;
		}
		strcpy(placename,graph.adjlist[pre[p_judge]].data);
		///打印经过的景点
		printf("-> %s ", placename);
		count++;
	}
	///count等于2表示可以直达
	if (count == 2)
	{
		printf(": 可直接到达\n");
	}
	
}


/**
 * @fn 添加新路线
 */
int addnewpath(graphadjlist *graph)
{
	int a_judge = 0;			///<出发点下标
	int b_judge = 0;			///<终点下标
	int weight  = 0;			///<两者之间的距离
	int a_flag = 0;
	int b_flag = 0;
	char choicejudge = ' ';
	char startplace[20];		///<起点名称
	char endplace[20];          ///<终点名称
	edgenode *edge;

	///输入出发点和终点，并且判断出发点和终点是否存在
	///判断该线路是否存在
	///如果出发点和终点存在，则重新输入
	///如果该线路存在，则重新输入
	do 
	{
		a_flag = 0;
		b_flag = 0;
		printf("请输入终点和起点: ");
		scanf("%s%s", endplace, startplace);
		///得到出发点和终点的下标
		a_judge = locatevertex(*graph, startplace);
		b_judge = locatevertex(*graph, endplace);
		///比较出发点和终点是否相同
		if (!strcmp(startplace, endplace))
		{
			a_flag = 1;
		}
		///判断该线路是否存在
		if ((a_judge != -1) && (b_judge != -1) && (a_flag != 1))
		{
			edge = graph->adjlist[a_judge].firstedge;
			while (edge)
			{
				if (edge->adjvex == b_judge)
				b_flag =1; 
				edge = edge->next;
			}
		}
		if ((a_flag == 1) || (b_flag == 1) || (a_judge == -1) || (b_judge == -1))
		{
			printf("该线路已存在或者出发点或终点输入有误，请查实后再输入\n");
			printf("\t是否返回上一级(是Y): ");
			getchar();
			scanf("%c", &choicejudge);
			if ((choicejudge == 'Y') || (choicejudge == 'y'))
			  return 1;
		}
	}while((a_judge == -1) || (b_judge == -1) ||(a_flag == 1) || (b_flag == 1));

	///输入新线路的距离即权值
	printf("距离： ");
	scanf("%d", &weight);
	///为a_judge的新边结点申请空间
	edge = (edgenode *)malloc(sizeof(edgenode));
	///a_judge的邻接边为b_judge
	edge->adjvex = b_judge;
	///记录权值
	edge->weight = weight;
	///采用头插法，将新边结点加入到a_judge的邻接边中
	edge->next = graph->adjlist[a_judge].firstedge;
	graph->adjlist[a_judge].firstedge = edge;
	
	///为b_judge的新边结点申请空间
	edge = (edgenode *)malloc(sizeof(edgenode));
	///b_judge的新边结点为a_judge
	edge->adjvex = a_judge;
	///记录权值
	edge->weight = weight;
	///采用头插法，将新边结点加入到b_judge的邻接边中
	edge->next = graph->adjlist[b_judge].firstedge;
	graph->adjlist[b_judge].firstedge = edge;
	///更新地图边数
	graph->numedges = graph->numedges + 1;
	return 0;
}


/**
 * @fn 利用二级指针删除边表中的节点
 *
 * @param pphead为要删除邻接边的fistedge指针，i为要删除的邻接边的adjvex值
 *	      用与表明删除的节点
 */
void delete_node(edgenode **pphead, int i)
{
	edgenode **cur = pphead;			///<用二级指针控制指针的值
   	edgenode *edge;
	while(*cur)
	{
		edge = *cur;
		if( edge->adjvex == i )
		{
			*cur = edge->next;			///<cur为待删除结点的next节点
			///释放待删除结点，此时二级指针cur依然存在,指向edge->next
			free(edge);					
		}
		else
			cur = &edge->next;
	}
}


/**
 * @fn 删除线路
 *
 * @param 景区图的邻接表
 *
 * @return 如果景区已经没有线路了，返回-1，否则返回0
 */
int deleteoldpath(graphadjlist *graph)
{
	int a_judge = 0;				///<起点下标
	int b_judge = 0;                ///<终点下标
	int a_flag = 0;					
	int b_flag = 0;    
	char choicejudge = 0;
	char startplace[20];			///<起点名
	char endplace[20];				///<终点名
	edgenode *edge;

	///在删除线路前，先确认该景区有没有线路
	if (graph->numedges <= 0)
	{
		printf("$该景区没有线路可以删除！\n");
		return -1;
	}

	///输入终点和起点，并验证正确性
	///终点和起点是否存在
	///终点和起点是否相同
	///终点和起点之间是否有线路
	do 
	{
		a_flag = 0;
		b_flag = 0;
		printf("请输入终点和起点: ");
		scanf("%s%s",endplace, startplace);
		///得到终点和起点的下标
		a_judge = locatevertex(*graph, startplace);
		b_judge = locatevertex(*graph, endplace);
		///判断终点和起点是否相同
		if (!strcmp(startplace, endplace))
		{
			a_flag = 1;
		}
		///判断该线路是否存在
		if ((a_judge != -1) && (b_judge != -1) && (a_flag != 1))
		{
			edge = graph->adjlist[a_judge].firstedge;
			while (edge)
			{
				if (edge->adjvex == b_judge)
				b_flag = 1; 
				edge = edge->next;
			}
		}
		if ((a_flag == 1) || (b_flag == 0) || (a_judge == -1) || (b_judge == -1))
		{
			printf("$该线路不存在或者出发点或终点输入有误，请查实后再输入\n");
			printf("\t是否返回上一级(是Y): ");
			getchar();
			scanf("%c", &choicejudge);
			if ((choicejudge == 'Y') || (choicejudge == 'y'))
			  return 0;
		}
	}while((a_judge == -1) || (b_judge == -1) ||(a_flag == 1) || (b_flag == 0));

	///删除graph->adjvex[b_judge]中的边结点a_judge
	delete_node(&(graph->adjlist[b_judge].firstedge), a_judge );
	///删除graph->adjvex[a_judge]中的边结点b_judge
	delete_node(&(graph->adjlist[a_judge].firstedge), b_judge );

	///更新图的边数
	graph->numedges = graph->numedges - 1;
	
	return 0;
}


/**
 * @fn 删除景点
 *
 * @param 景区图的邻接表
 *
 * @return 如果景区没有景点可以删除返回-1，否则返回0
 */
int deleteoldplace(graphadjlist *graph)
{
	char placename[20];				///<要删除的景点名
	int a_judge = 0;				///<要删除的景点下标
	char choicejudge = 0;
	edgenode *edge;
	edgenode *flagedge;

	///在删除景点前，先确认该景区有没有景点
	if (graph->numvertexes <= 0)
	{
		printf("该景区没有景点可以删除\n");
		return -1;
	}
	///输入景点名，验证其正确性
	///判断其是否存在
	do 
	{
		printf("请输入要删除的景点：\n");
		scanf("%s", placename);
		a_judge = locatevertex(*graph, placename);
		///如果a_judge为-1，则不存在
		if (a_judge == -1)
		{
			printf("要删除的景点有误，请查实后再输入!\n");
			printf("\t是否返回上一级(是Y): ");
			getchar();
			scanf("%c", &choicejudge);
			if ((choicejudge == 'Y') || (choicejudge == 'y'))
			  return 0;
		}
	}while (a_judge == -1);
	
	edge = graph->adjlist[a_judge].firstedge;
	while (edge)
	{
		///根据要删除景点的邻接景点下标，逐个删除它的邻接点里的边结点
		///即待删除景点A与B邻接,删除B里与A有关的信息
		delete_node(&(graph->adjlist[edge->adjvex].firstedge), a_judge);
		///更新地图的边数
		graph->numedges--;
		edge = edge->next;
	}

	///删除待删除景点的邻接边信息
	edge = graph->adjlist[a_judge].firstedge;
	while (edge)
	{
		flagedge = edge->next;
		free(edge);
		edge = flagedge;
	}
	///将该景点变为初始状态
	strcpy(graph->adjlist[a_judge].data, "#");
	strcpy(graph->adjlist[a_judge].information, "#");
	graph->adjlist[a_judge].firstedge = NULL;
	///更新顶点数
	graph->numvertexes--;
	return 0;
}


/*
 ** @fn 得到目前邻接表中第一个空闲位置的下标

*   @param 景区图的邻接表
*
*   @return 返回邻接表中第一个空闲位置的下标，如果邻接表位置满了，返回-1
*/
int getlocate(graphadjlist graph)
{
	int i = 0;
	
	///循环判断
	for (i = 1; i<= MAXVEX; i++)
	{
		///data域为'#'，则说明该顶点为空，即处于空闲状态
		if(strcmp(graph.adjlist[i].data, "#") == 0)
		{
			return i;
		} 
	}
	return -1;
}


/**
 * @fn 添加新景点
 *
 * @param 景区图的邻接表
 *
 */
int addnewplace(graphadjlist *graph)
{

	char placename[20];		///<新景点的名称
	char connectname[20];   ///<相连景点名称
	char choicejudge;
	int a_judge = 0;		///<添加景点的下标
	int b_judge = 0;		///<与添加景点相连景点的下标
	unsigned weight = 0;    ///<两个景点间的距离
	edgenode *edge;


	///输入要添加的景点名称，进行判断该景点是否存在
	///如果不存在，进行添加
	do
	{
		printf("请输入要添加的景点名称： ");
		scanf("%s", placename);
		a_judge = locatevertex(*graph, placename);
		if (a_judge != -1)
		{
			printf("该景点已存在！\n");
			printf("\t是否返回上一级(是Y): ");
			getchar();
			scanf("%c", &choicejudge);
			if ((choicejudge == 'Y') || (choicejudge == 'y'))
			  return 0;
		}	
	}while (a_judge != -1);

	///判断景点数是否达到上线
	if ((a_judge = getlocate(*graph)) == -1)
	{
		printf("a_judge : %d\n", a_judge);
		printf("景点数已达上线，无法添加");
		return -1;
	}

	///将新景点和景区内已有的景点相连
	do 
	{
		do
		{
			///输入要与新景点相连的景点名称
			printf("请输入与新加结点相连的景点名称: ");
			scanf("%s", connectname);
			///判断该景点是否存在，并得到其下标
			b_judge = locatevertex(*graph, connectname);
			if (b_judge == -1)
			  printf("该景点不存在！\n");
		}while (b_judge == -1);

		///添加景点名称
		strcpy(graph->adjlist[a_judge].data, placename);
		///添加景点描述
		printf("请输入添加的景点描述:\n");
		scanf("%s", graph->adjlist[a_judge].information);

		///输入两者间的距离
		printf("请输入它们之间的距离： ");
		scanf("%d", &weight);
				
	///为graph->adjvex[a_judge]的新边结点申请空间
	edge = (edgenode *)malloc(sizeof(edgenode));
	///a_judge的邻接边为b_judge
	edge->adjvex = b_judge;
	///记录权值
	edge->weight = weight;
	///采用头插法，将新边结点加入到a_judge的邻接边中
	edge->next = graph->adjlist[a_judge].firstedge;
	graph->adjlist[a_judge].firstedge = edge;
	
	///为graph->adjvex[b_judge]的新边结点申请空间
	edge = (edgenode *)malloc(sizeof(edgenode));
	///b_judge的新边结点为a_judge
	edge->adjvex = a_judge;
	///记录权值
	edge->weight = weight;
	///采用头插法，将新边结点加入到b_judge的邻接边中
	edge->next = graph->adjlist[b_judge].firstedge;
	graph->adjlist[b_judge].firstedge = edge;
	///更新地图边数
	graph->numedges = graph->numedges + 1;
	///更新地图顶点数
	graph->numvertexes = graph->numvertexes + 1;
	///是否需要继续添加相邻景点
	printf("是否需要继续添加相邻景点？（是Y）");
	getchar();
	scanf("%c", &choicejudge);
	}while ((choicejudge == 'Y') || choicejudge == 'y');

	return 0;
}


/**
 * @fn 求start到end的所有简单路径
 *
 * @param graph为邻接表 start为开始点的下标，end为终点下表，length为当前start和end经过的点下标
 *        path数组记录路径，visited记录景点是否访问过
 */
int find_path(graphadjlist graph, int start, int end, int length, int path[], int visited[])
{
	///将start加入当前路径中
	path[length] = start;
	visited[start] = 1;
	int num = 0;
	int i = 0;
	edgenode *edge;
	///如果，当前走到的景点和终点相同
	//那么就找到了一条简单路径
	if (start == end)
	{
		printf("\npath:");
		///并且路径存储到了path数组中
		for (i = 0; path[i]; i++)
		{
			///打印输出path数组
			printf(" %s ", graph.adjlist[path[i]].data);
			if (path[i + 1])
			{
				printf("->");
			}
		}
	}
	///如果，当前的景点不是终点
	else
	{///那么从它的邻接边开始继续寻找
		for (edge = graph.adjlist[start].firstedge; edge; edge = edge->next)
		{
			num = edge->adjvex;
			if (!visited[num]) 
			{
				///继续寻找
				find_path(graph, num, end, length + 1, path, visited);
			}
		}
	}
	visited[start] = 0;
	path[length] = 0;				///<回溯

	return 0;
}


/**
 * @fn 给出任意两个景点间的所有简单路径
 */
int find_all_path(graphadjlist graph)
{
	char choicejudge;
	char startplace[20];		///<出发点名称
	char endplace[20];			///<终点名称
	int a_judge = 0;			///<出发点的下标
	int b_judge = 0;            ///<终点的下标
	int flag = 0;
	int i = 0;
	int path[MAXVEX];           ///<记录路径
	int visited[MAXVEX];        ///<记录是否访问过

	///初始化path和visited数组
	for (i = 0; i<= MAXVEX; i++)
	{
		path[i] = 0;
		visited[i] = 0;
	}

	///输入出发点和终点，并验证其正确性
	///出发点和终点是否存在，是否相同
	do
	{
		flag = 0;
		printf("请输入出发点和终点： ");
		scanf("%s%s", startplace, endplace);
		a_judge = locatevertex(graph, startplace);
		b_judge = locatevertex(graph, endplace);
		if (!strcmp(startplace, endplace))
		{
			printf("终点和起点相同，查实后再输入！\n");
			flag = 1;
		}
		if ((a_judge == -1) || (b_judge == -1))
		{
			printf("起点和终点有误，查实后再输入!\n");
			printf("\t是否返回上一级(是Y): ");
			getchar();
			scanf("%c", &choicejudge);
			if ((choicejudge == 'Y') || (choicejudge == 'y'))
			  return 0;
		}
	}while ((flag == 1) || (a_judge == -1) || (b_judge == -1));
	///求从出发点到终点的所有简单路径
	find_path(graph, a_judge, b_judge, 0, path, visited);

	return 0;
}





