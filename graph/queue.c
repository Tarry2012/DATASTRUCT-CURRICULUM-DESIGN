/**
 * =====================================================================================
 *
 *			@file  queue.c
 *
 *			@brief 队列操作 
 *
 *			@version  1.0
 *			@data  2013年12月17日 09时01分21秒
 *       
 *			@author:  Tang Qiuyuan, tangqyuan@gmail.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


///初始化队列
queue *initqueue()
{
	queue *q;
	nodequeue *p;

	q = (queue *)malloc(sizeof(queue));
	p = (nodequeue *)malloc(sizeof(nodequeue));
	p->next = NULL;
	q->front = q->rear = p;
	return q;
}


///进队
void inqueue(queue *q, const int placenode)
{
	nodequeue *p;
	p = (nodequeue *)malloc(sizeof(nodequeue));
	p->placenode = placenode;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}


///判队是否为空
int emptyqueue(queue *q)
{
	if (q->front == q->rear) return 1;
	else return 0;
}


///出队
int outqueue(queue *q, int *placenode)
{
	nodequeue *p;
	if (emptyqueue(q) == 1)
	{
		printf("队空\n");
		return -1;
	}
	else 
	{
		p = q->front->next;
		q->front->next = p->next;
		*placenode = p->placenode;
		free(p);
		if (q->front->next == NULL)
		  q->rear = q->front;
		return 0;
	}
}





















