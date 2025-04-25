#pragma once
#define MAX_VERTEX_NUM 20
#include<iostream>

struct Vex//图
{
	int num; // 景点编号
	char name[20]; // 景点名字
	char desc[1024]; // 景点介绍
};

struct Edge//边
{
	int vex1; // 边的第一个顶点
	int vex2; // 边的第二个顶点
	int weight; // 权值
};

class CGraph
{
private:
	int m_aAdjMatrix[20][20]; // 邻接矩阵
	Vex m_aVexs[20]; // 顶点信息数组
	int m_nVexNum; // 当前图的顶点个数
public:
	// 初始化图
	void Init();
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	Vex GetVex(int v);//返回图
	int Get_m_nVexNum();//返回当前图的顶点个数
	int Get_m_aAdjMatrix(int a, int b);//返回邻接矩阵
	int FindEdge(int v, Edge aEdge[]);
};


typedef struct Path
{
	int vexs[20]; //保存一条路径
	Path* next; //下一条路径
}*PathList;

void DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList);

void DFSTraverse(int nVex, PathList& pList);

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);

void FindMinTree(Edge aPath[]);