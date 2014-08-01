/**
 * =====================================================================================
 *
 *       @file  graph.h
 *
 *		 @brief 课程设计景区系统-图 头文件
 *
 *       @version  1.0
 *       @date  2013年12月17日 09时21分23秒
 *
 *       @author:  Tang Qiuyuan, tangqyuan@gmail.com
 *
 * =====================================================================================
 */

#ifndef  _GRAPH_QUEUE_PLACE
#define  _GRAPH_QUEUE_PLACE

/**
 * @def 景区景点数最大值*/
#define MAXVEX 30
/**
 * @def 初始化数据*/
#define INFINITY 65535

typedef struct queuenode		///<队列节点
{
	int placenode;
	struct queuenode *next;
}nodequeue;

typedef struct				  ///<队列封装队头和队尾
{
	nodequeue *front;
	nodequeue *rear;
}queue;

typedef struct edgenode			///<边结点
{
	int adjvex;					///<邻结点域，存储该顶点对应的下标
	int weight;					///<存储权值
	struct edgenode *next;      ///<指向下一个邻接点
}edgenode;

typedef struct vertexnode		///<顶点接点
{
	char data[20];				///<景点名称
	char information[100];		///<景点信息
	edgenode *firstedge;		///<指向边表头指针
}vertexnode, adjvexlist[MAXVEX + 1];   

typedef struct
{
	adjvexlist  adjlist;
	int numvertexes;			///<顶点数
	int numedges;				///<边数
}graphadjlist;

typedef int pathmatirx[MAXVEX][MAXVEX]; ///<floyd算法：记录路径长度
typedef int shortpath[MAXVEX][MAXVEX];  ///<floyd算法：记录走过的景点,即对应顶点的最小路径的前驱矩阵

struct close							///<prime算法：辅助数组。adjvex：顶点；lowcost：权值
{
	char adjvex[20];
	int lowcost;
};

///初始化队列
queue *initqueue();	
///进队列
void inqueue(queue *q, const int placenode); 
///判断队列是否为空
int emptyqueue(queue *q);				
///出队列
int outqueue(queue *q, int *placenode); 
///创建旅游景点无向带权图的邻接表，顶点数组的下表从1开始
void createadjgraph(graphadjlist *graph);
///打印出景点的地图信息
int output_graph(const graphadjlist *graph);
///景点的查询，输入一个景点名称，显示出与它相关的景点信息
void search_placenode(const graphadjlist *graph);
///利用深度优先搜索算法
void deep_first_search(const graphadjlist *graph, int i, int visited[], int n);
///利用深搜，遍历图
void traver_graph(const graphadjlist *graph);
///将图的信息存入文件中
void save_file_graph(const graphadjlist *graph);
///将地图从文件中读出
graphadjlist *read_file_graph(void);
///floyd算法：求每对顶点之间的最短路径
int  shortestpath_floyd(graphadjlist graph, pathmatirx *path, shortpath *darray);
///调用floyd算法，求每对顶点之间的最短路径
int  get_between_places(graphadjlist graph);
///找到景点start在图中的下标
int locatevertex(graphadjlist graph, char *start);
///在prime算法中closedge数组中，找到lowcost值最小的一个
int minium(struct close closedege[], int count);
///采用prime算法求得最短连通线路
void minispantree_prime(graphadjlist graph);
///判断一个景点是否存在
int search_judge(const graphadjlist *graph, char placename[]);
///利用广度优先搜索，找到景点1到景点2之间一条中转次数最少的线路
int broad_first_search(graphadjlist graph);
///打印出中转次数最少的路径
void print_path(graphadjlist graph, int pre[], int n, char startname[], char endname[]);
///添加新线路
int addnewpath(graphadjlist *graph);
///利用二级指针删除边表中的结点
void delete_node(edgenode **pphead, int i);
///撤销线路
int deleteoldpath(graphadjlist *graph);
///删除景点
int deleteoldplace(graphadjlist *graph);
///得到目前图中第一空闲的顶点集中的下标
int getlocate(graphadjlist graph);
///添加新景点
int addnewplace(graphadjlist *graph);
//给出任意两景点之间的所有简单路径
int find_path(graphadjlist graph, int start, int end, int length, int path[], int visited[]);
//调用find_path函数，得到任意两点之间的所有简单路径
int find_all_path(graphadjlist graph);
#endif








