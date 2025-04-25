#pragma once
#define MAX_VERTEX_NUM 20
#include<iostream>

struct Vex//ͼ
{
	int num; // ������
	char name[20]; // ��������
	char desc[1024]; // �������
};

struct Edge//��
{
	int vex1; // �ߵĵ�һ������
	int vex2; // �ߵĵڶ�������
	int weight; // Ȩֵ
};

class CGraph
{
private:
	int m_aAdjMatrix[20][20]; // �ڽӾ���
	Vex m_aVexs[20]; // ������Ϣ����
	int m_nVexNum; // ��ǰͼ�Ķ������
public:
	// ��ʼ��ͼ
	void Init();
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	Vex GetVex(int v);//����ͼ
	int Get_m_nVexNum();//���ص�ǰͼ�Ķ������
	int Get_m_aAdjMatrix(int a, int b);//�����ڽӾ���
	int FindEdge(int v, Edge aEdge[]);
};


typedef struct Path
{
	int vexs[20]; //����һ��·��
	Path* next; //��һ��·��
}*PathList;

void DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList);

void DFSTraverse(int nVex, PathList& pList);

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);

void FindMinTree(Edge aPath[]);