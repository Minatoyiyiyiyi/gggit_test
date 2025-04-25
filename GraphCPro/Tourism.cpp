#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"


using namespace std;

extern CGraph m_Graph;

// 读取景点信息
void ReadVexs(CGraph &m_Graph)
{
    ifstream vexFile("Vex.txt");
    if (!vexFile)
    {
        cerr << "无法打开文件 Vex.txt" << endl;
        return;
    }
    char num[2];
    char name[20];
    char desc[1024];
    Vex sVex;

    // 逐行读取Vex.txt中的数据
    vexFile.getline(num, 2); // 将第一行的数据读出丢掉
    cout << "顶点数目：" << atoi(num) << endl;
    cout << "-----顶点-----" << endl;
    while (vexFile.getline(num, 2))
    {
        sVex.num = atoi(num);
        vexFile.getline(name, 20);
        strcpy(sVex.name, name);
        vexFile.getline(desc, 1024);
        strcpy(sVex.desc, desc);
        // 将顶点信息输出
        m_Graph.InsertVex(sVex);
        cout << sVex.num << "-" << sVex.name <<endl;//<< "-" << sVex.desc << endl;
    }
    cout << "------------" << endl;
    vexFile.close();
}

// 读取道路信息
void ReadEdges(CGraph &m_Graph)
{
    ifstream edgeFile("Edge.txt");
    if (!edgeFile)
    {
        cerr << "无法打开文件 Edge.txt" << endl;
        return;
    }

    int edgeCount;
    edgeFile >> edgeCount; // 读取边个数
    edgeFile.ignore(); // 忽略换行符
    Edge sEdge;
    cout << "道路信息： " << endl;
    for (int i = 0; i < edgeCount; ++i)
    {
        string line;
        // 读取道路信息
        getline(edgeFile, line);
        // 解析道路信息
        sscanf(line.c_str(), "%d\t%d\t%d", &sEdge.vex1, &sEdge.vex2, &sEdge.weight);
        m_Graph.InsertEdge(sEdge);
        cout << "<v" << sEdge.vex1 << ",v" << sEdge.vex2 <<"> " << sEdge.weight << endl;
    }

    edgeFile.close();
}

// 创建图
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

    // 提示用户根据编号进行查询
    cout << "\n请输入想要查询的景点编号：";
    int num;
    cin >> num;
    if (num < 0 || num >= m_Graph.Get_m_nVexNum())
    {
        cout << "无效的景点编号！" << endl;
        return;
    }

    Vex sVex = m_Graph.GetVex(num);
    cout << "景点名称：" << sVex.name << endl;
    cout << "景点介绍：" << sVex.desc << endl;
    
    Edge edges[20]; // 假设最多有20条边
    int count = m_Graph.FindEdge(num, edges);

    cout << "相邻景点及距离：" << endl;
    for (int i = 0; i < count; ++i)
    {
        Vex adjacentVex = m_Graph.GetVex(edges[i].vex2);
        cout << "到景点 " << adjacentVex.name << " 的距离是 " << edges[i].weight << " 公里" << endl;
    }
}

void TravelPath()
{
    cout << "请输入想要导航的起始点编号：";
    int startNum;
    cin >> startNum;
    if (startNum < 0 || startNum >= m_Graph.Get_m_nVexNum())
    {
        cout << "您输入的编号有误！" << endl;
        return;
    }
    PathList pList = new Path;
    PathList pHead = pList;
    DFSTraverse(startNum, pList);
    cout << endl;

    // 输出遍历结果
    cout << "导航路线为：" << endl;
    int i = 1;
    pList = pHead;
    while (pList->next != NULL)
    {
        Vex vex = m_Graph.GetVex(pList->vexs[0]);
        cout << "路线" << i++ << ":" << vex.name;
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
    //输入两个景点的编号
    int start, end;
    cout << "请输入起点的编号:" << endl;
    cin >> start;
    cout << "请输入终点的编号：" << endl;
    cin >> end;
    //搜索最短路径
    Edge edge[20];
    for (int i = 0; i < 20; i++)
    {
        // 初始化边信息数组
        edge->vex1 = -1;
        edge->vex2 = -1;
        edge->weight = -1;
    }
    int index = FindShortPath(start, end, edge);
    int length = 0; // 最短路径总长度
    Vex sVex = m_Graph.GetVex(edge[0].vex1);

    // 得到最短路径和最短距离
    cout << "\n最短路径为：" << sVex.name;

    for (int i = 0; i < index; i++)
    {
        sVex = m_Graph.GetVex(edge[i].vex2);
        cout << "->" << sVex.name;
        length += edge[i].weight;
    }

    cout << endl;
    cout << "最短距离为:" << length << "米" << endl;
}

void DesignPath(void)
{
    cout << "在以下两个景点之间铺设电路";

    Edge aPath[20];

    FindMinTree(aPath); // 构建最小树

    int nAllLength = 0;

    for (int i = 0; i < m_Graph.Get_m_nVexNum() - 1; i++)
    {
        Vex nVex1 = m_Graph.GetVex(aPath[i].vex1);
        Vex nVex2 = m_Graph.GetVex(aPath[i].vex2);

        cout << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << endl;
        nAllLength += aPath[i].weight;
    }
    cout << "铺设电路的总长度是：" << nAllLength << "m" << endl;
}