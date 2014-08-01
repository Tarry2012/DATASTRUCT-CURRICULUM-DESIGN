/**
 * =====================================================================================
 *
 *			@file  main.c
 *
 *			@brief 主页面 
 *
 *			@version 1.0
 *			@data  2013年12月17日 20时57分30秒
 *      
 *			@author:  Tang Qiuyuan, tangqyuan@gmail.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


///创建图
void create(graphadjlist *graph)
{
	createadjgraph(graph);
	///保存图
	save_file_graph(graph);
}


///添加线路
void addpath(graphadjlist *graph)
{
	addnewpath(graph);
	///保存图
	save_file_graph(graph);
}


///删除线路
void deletepath(graphadjlist *graph)
{
	deleteoldpath(graph);
	///保存图
	save_file_graph(graph);
}


///删除景点
void deleteplace(graphadjlist *graph)
{
	deleteoldplace(graph);
	///保存图
	save_file_graph(graph);
}


///添加景点
void addplace(graphadjlist *graph)
{
	addnewplace(graph);
	///保存图
	save_file_graph(graph);
}


///主页面
int  choice(void)
{
	graphadjlist *graph;
	graph = (graphadjlist *)malloc(sizeof(graphadjlist));
	///读取图
	graph = read_file_graph();

	system("clear");
	int choice;
	do 
	{
		printf("\n\n***********************景区导游系统******************************");
		printf("\n\t1.显示景点及其介绍；");
		printf("\n\t2.查询景点；");
		printf("\n\t3.查询从一个景点到另外一个景点中转次数最少的线路；");
		printf("\n\t4.查询从某个景点到另外一个景点的最短路径；");
		printf("\n\t5.查询从某个景点出发的最短连通路线；");
		printf("\n\t6.查询某两个景点之间的所有简单路径；");
		printf("\n\t7.重建景区地图；");
		printf("\n\t8.添加新线路；");
		printf("\n\t9.撤销线路；");
		printf("\n\t10.删除景点; ");
		printf("\n\t11.添加新景点;");
		printf("\n\t0.退出系统:\n");
		printf("*****************************************************************\n");
		scanf("%d", &choice);
		switch (choice)
		{
			///显示景点
			case 1: system("clear");
					output_graph(graph);
					break;
			///查询景点
			case 2:	system("clear");
					search_placenode(graph);
					break;
			///中转次数最少
			case 3: system("clear");
					broad_first_search(*graph);
					break;
			///最短路径
			case 4: system("clear");
					get_between_places(*graph);
					 break;
			///最短连通路线
			case 5: system("clear");
					 minispantree_prime(*graph);
					 break;
			///简单路径
			case 6:  system("clear");
					 find_all_path(*graph);
					 break;
			///重建图
			case 7:  system("clear");
					 create(graph);
					 break;
			///添加线路
			case 8:  system("clear");
					 addpath(graph);
					 break;
			///删除线路
			case 9:  system("clear");
					 deletepath(graph);
					 break;
			///删除景点
			case 10: system("clear");
					 deleteplace(graph);
					 break;
			///添加景点
			case 11:
					 system("clear");
					 addplace(graph);
					 break;
			///退出系统
			case 0:  system("clear");
					 printf("$已退出系统$\n");
					 return 0;
		    ///其他选项
			default :
					 system("clear");
					 printf("$该选项不存在，请重新输入！$\n");
					 break;
		}
	}while (1);
}


int main(int argc, char *argv[])
{
	choice();

	return 0;
}

