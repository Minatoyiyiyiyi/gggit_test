#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"


using namespace std;

extern CGraph m_Graph;

// ��ȡ������Ϣ
void ReadVexs(CGraph &m_Graph)
{
    ifstream vexFile("Vex.txt");
    if (!vexFile)
    {
        cerr << "�޷����ļ� Vex.txt" << endl;
        return;
    }
    char num[2];
    char name[20];
    char desc[1024];
    Vex sVex;

    // ���ж�ȡVex.txt�е�����
    vexFile.getline(num, 2); // ����һ�е����ݶ�������
    cout << "������Ŀ��" << atoi(num) << endl;
    cout << "-----����-----" << endl;
    while (vexFile.getline(num, 2))
    {
        sVex.num = atoi(num);
        vexFile.getline(name, 20);
        strcpy(sVex.name, name);
        vexFile.getline(desc, 1024);
        strcpy(sVex.desc, desc);
        // ��������Ϣ���
        m_Graph.InsertVex(sVex);
        cout << sVex.num << "-" << sVex.name <<endl;//<< "-" << sVex.desc << endl;
    }
    cout << "------------" << endl;
    vexFile.close();
}

// ��ȡ��·��Ϣ
void ReadEdges(CGraph &m_Graph)
{
    ifstream edgeFile("Edge.txt");
    if (!edgeFile)
    {
        cerr << "�޷����ļ� Edge.txt" << endl;
        return;
    }

    int edgeCount;
    edgeFile >> edgeCount; // ��ȡ�߸���
    edgeFile.ignore(); // ���Ի��з�
    Edge sEdge;
    cout << "��·��Ϣ�� " << endl;
    for (int i = 0; i < edgeCount; ++i)
    {
        string line;
        // ��ȡ��·��Ϣ
        getline(edgeFile, line);
        // ������·��Ϣ
        sscanf(line.c_str(), "%d\t%d\t%d", &sEdge.vex1, &sEdge.vex2, &sEdge.weight);
        m_Graph.InsertEdge(sEdge);
        cout << "<v" << sEdge.vex1 << ",v" << sEdge.vex2 <<"> " << sEdge.weight << endl;
    }

    edgeFile.close();
}

// ����ͼ
void CreateGraph()
{
    m_Graph.Init();
    ReadVexs(m_Graph);
    ReadEdges(m_Graph);

}

void GetSpotInfo() 
{
    for (int i = 0; i < m_Graph.Get_m_nVexNum(); i++)
    {
        Vex sVex = m_Graph.GetVex(i);
        cout << i << "-" << sVex.name << endl;
    }

    cout << "====================" << endl;

    // ��ʾ�û����ݱ�Ž��в�ѯ
    cout << "\n��������Ҫ��ѯ�ľ����ţ�";
    int num;
    cin >> num;
    if (num < 0 || num >= m_Graph.Get_m_nVexNum())
    {
        cout << "��Ч�ľ����ţ�" << endl;
        return;
    }

    Vex sVex = m_Graph.GetVex(num);
    cout << "�������ƣ�" << sVex.name << endl;
    cout << "������ܣ�" << sVex.desc << endl;
    
    Edge edges[20]; // ���������20����
    int count = m_Graph.FindEdge(num, edges);

    cout << "���ھ��㼰���룺" << endl;
    for (int i = 0; i < count; ++i)
    {
        Vex adjacentVex = m_Graph.GetVex(edges[i].vex2);
        cout << "������ " << adjacentVex.name << " �ľ����� " << edges[i].weight << " ����" << endl;
    }
}

void TravelPath()
{
    cout << "��������Ҫ��������ʼ���ţ�";
    int startNum;
    cin >> startNum;
    if (startNum < 0 || startNum >= m_Graph.Get_m_nVexNum())
    {
        cout << "������ı������" << endl;
        return;
    }
    PathList pList = new Path;
    PathList pHead = pList;
    DFSTraverse(startNum, pList);
    cout << endl;

    // ����������
    cout << "����·��Ϊ��" << endl;
    int i = 1;
    pList = pHead;
    while (pList->next != NULL)
    {
        Vex vex = m_Graph.GetVex(pList->vexs[0]);
        cout << "·��" << i++ << ":" << vex.name;
        for (int j = 1; j < m_Graph.Get_m_nVexNum(); j++)
        {
            vex = m_Graph.GetVex(pList->vexs[j]);
            cout << "->" << vex.name;
        }
        cout << endl;
        pList = pList->next;
    }
    cout << endl;

    delete pList;
    pList = NULL;
    pHead = NULL;
}

void FindShortPath(void)
{
    //������������ı��
    int start, end;
    cout << "���������ı��:" << endl;
    cin >> start;
    cout << "�������յ�ı�ţ�" << endl;
    cin >> end;
    //�������·��
    Edge edge[20];
    for (int i = 0; i < 20; i++)
    {
        // ��ʼ������Ϣ����
        edge->vex1 = -1;
        edge->vex2 = -1;
        edge->weight = -1;
    }
    int index = FindShortPath(start, end, edge);
    int length = 0; // ���·���ܳ���
    Vex sVex = m_Graph.GetVex(edge[0].vex1);

    // �õ����·������̾���
    cout << "\n���·��Ϊ��" << sVex.name;

    for (int i = 0; i < index; i++)
    {
        sVex = m_Graph.GetVex(edge[i].vex2);
        cout << "->" << sVex.name;
        length += edge[i].weight;
    }

    cout << endl;
    cout << "��̾���Ϊ:" << length << "��" << endl;
}

void DesignPath(void)
{
    cout << "��������������֮�������·";

    Edge aPath[20];

    FindMinTree(aPath); // ������С��

    int nAllLength = 0;

    for (int i = 0; i < m_Graph.Get_m_nVexNum() - 1; i++)
    {
        Vex nVex1 = m_Graph.GetVex(aPath[i].vex1);
        Vex nVex2 = m_Graph.GetVex(aPath[i].vex2);

        cout << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << endl;
        nAllLength += aPath[i].weight;
    }
    cout << "�����·���ܳ����ǣ�" << nAllLength << "m" << endl;
}