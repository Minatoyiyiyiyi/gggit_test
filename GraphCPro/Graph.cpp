#include"Graph.h"

extern CGraph m_Graph;

void CGraph::Init()
{
    // 初始化顶点数目为0
    m_nVexNum = 0;

    // 初始化邻接矩阵，所有权值初始化为0
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            m_aAdjMatrix[i][j] = 0;
        }
    }
}


bool CGraph::InsertVex(Vex sVex)
{
    if (m_nVexNum == MAX_VERTEX_NUM)
    {
        //顶点已满
        return false;
    }
    m_aVexs[m_nVexNum++] = sVex; //插入顶点信息
    return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
    if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
        {
            // 下标越界
            return false;
        }
        // 插入边的信息
    m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
    m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
    return true;
}

Vex CGraph::GetVex(int v) 
{
    return m_aVexs[v];
}

int CGraph::Get_m_nVexNum()
{
    return m_nVexNum;
}

int CGraph::Get_m_aAdjMatrix(int a, int b)
{
    return m_aAdjMatrix[a][b];
}

int CGraph::FindEdge(int v, Edge aEdge[])
{
    int k = 0;
    for (int i = 0; i < m_nVexNum; ++i)
    {
        if (m_aAdjMatrix[v][i] != 0) // 如果有边连接
        {
            aEdge[k].vex1 = v;      // 起点
            aEdge[k].vex2 = i;      // 终点
            aEdge[k].weight = m_aAdjMatrix[v][i]; // 权值
            k++;
        }
    }
    return k; // 返回边的条数
}

void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList)
{

    bVisited[nVex] = true;
    pList->vexs[nIndex++] = nVex;

    int num = 0; // 被访问过的节点数
    for (int i = 0; i < m_Graph.Get_m_nVexNum(); i++)
    {
        if (bVisited[i])
        { // 如果当前i节点被访问过，则num++
            num++;
        }
    }
    if (num == m_Graph.Get_m_nVexNum())
    { // 如果所有节点都被访问过
        // 保存一条路径
        pList->next = new Path;
        for (int i = 0; i < m_Graph.Get_m_nVexNum(); i++)
        {
            pList->next->vexs[i] = pList->vexs[i];
        }
        pList = pList->next;
        pList->next = NULL;
    }else
    {
        for (int w = 0; w < m_Graph.Get_m_nVexNum(); w++)
        { // 搜索v的所有邻接点
            if (m_Graph.Get_m_aAdjMatrix(nVex,w) > 0 && !bVisited[w])
            {									  // 如果w是nVex的邻接点并未被访问
                DFS(w, bVisited, nIndex, pList); // 递归调用DFS
                bVisited[w] = false;			  // 改为未访问
                nIndex--;						  // 索引值减1
            }
        }
    }
}

void DFSTraverse(int nVex, PathList& pList)
{
    int nIndex = 0;
    bool bVisited[20] = { false };
    DFS(nVex, bVisited, nIndex, pList);
}

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
    //初始化最短路径
    int nShortPath[20][20]; // 最短路径，行表示终点，列表示从起点到终点的最短路径的每一步
    int nShortDistance[20]; // 保存从起点到任一顶点的最短距离
    bool aVisited[20];		// 判断某点是否已在最短路径中
    int v;					// 每一次找到的可以加入集合的顶点

    for (v = 0; v < m_Graph.Get_m_nVexNum(); v++)
    {
        aVisited[v] = false;

        if (m_Graph.Get_m_aAdjMatrix(nVexStart,v) != 0)
        {
            // 如果顶点v和nVexStart相连，则最短距离设置为两顶点间的距离
            nShortDistance[v] = m_Graph.Get_m_aAdjMatrix(nVexStart,v);
        }
        else
        {
            // 如果不相连，则最短距离设置为最大值
            nShortDistance[v] = 0x7FFFFFFF;
        }

        nShortPath[v][0] = nVexStart; // 起始点为nVexStart
        // 初始化最短路径
        for (int w = 1; w < m_Graph.Get_m_nVexNum(); w++)
        {
            nShortPath[v][w] = -1;
        }
    }

    // 初始化，将nVexStart顶点加入到集合中
    aVisited[nVexStart] = true;

    int min; // 暂存路径的最小值
    for (int i = 1; i < m_Graph.Get_m_nVexNum(); i++)
    {
        min = 0x7FFFFFFF;
        bool bAdd = false; // 判断是否还有顶点可以加入集合

        for (int w = 0; w < m_Graph.Get_m_nVexNum(); w++)
        {
            if (!aVisited[w] && nShortDistance[w] < min)
            {
                v = w;					 // w顶点距离nVexStart顶点最近
                min = nShortDistance[w]; // w到nVexStart的最短距离为min
                bAdd = true;
            }
        }
        // 如果没有顶点可以加入到集合，则跳出循环
        if (!bAdd)
        {
            break;
        }

        aVisited[v] = true;	  // 将w顶点加入到集合
        nShortPath[v][i] = v; // 每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v

        for (int w = 0; w < m_Graph.Get_m_nVexNum(); w++)
        {
            // 将w作为中间点计算nVexStart到所有顶点的最短距离
            if (!aVisited[w] && (min + m_Graph.Get_m_aAdjMatrix(v,w) < nShortDistance[w]) && (m_Graph.Get_m_aAdjMatrix(v, w) > 0))
            {
                // 如果有新的最短距离,则更新最短路径及距离
                nShortDistance[w] = min + m_Graph.Get_m_aAdjMatrix(v, w);
                for (int i = 0; i < m_Graph.Get_m_nVexNum(); i++)
                {
                    // 如果通过w到达顶点i的距离比较短，则将w的最短路径赋值给i
                    nShortPath[w][i] = nShortPath[v][i];
                }
            }
        }
    }

    int nIndex = 0;
    int nVex1 = nVexStart;

    // 将最短路径保存到边的结构体数组中
    for (int i = 1; i < m_Graph.Get_m_nVexNum(); i++)
    {
        if (nShortPath[nVexEnd][i] != -1)
        {
            aPath[nIndex].vex1 = nVex1;
            aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
            aPath[nIndex].weight = m_Graph.Get_m_aAdjMatrix(nVex1,aPath[nIndex].vex2);
            nVex1 = nShortPath[nVexEnd][i];
            nIndex++;
        }
    }
    return nIndex;
}

void FindMinTree(Edge aPath[])
{
    bool aVisited[20] = { false }; // 判断某顶点是否在最小生成树中
    aVisited[0] = true;			 // 从0号顶点开始，加入到集合中
    int min;
    int nVex1, nVex2;

    for (int k = 0; k < m_Graph.Get_m_nVexNum() - 1; k++)
    {
        min = 0X7FFFFFFF;

        for (int i = 0; i < m_Graph.Get_m_nVexNum(); i++)
        {
            // 从集合中取一个顶点
            if (aVisited[i])
            {
                for (int j = 0; j < m_Graph.Get_m_nVexNum(); j++)
                {
                    // 从不在集合的顶点中取出一个顶点
                    if (!aVisited[j])
                    {
                        if ((m_Graph.Get_m_aAdjMatrix(i,j) < min) && (m_Graph.Get_m_aAdjMatrix(i,j) != 0))
                        {
                            nVex1 = i;
                            nVex2 = j;
                            // 找出最短边
                            min = m_Graph.Get_m_aAdjMatrix(i,j);
                        }
                    }
                }
            }
        }

        // 保存最短边的两个顶点
        aPath[k].vex1 = nVex1;
        aPath[k].vex2 = nVex2;
        aPath[k].weight = m_Graph.Get_m_aAdjMatrix(nVex1,nVex2);

        // 将两个顶点加入集合
        aVisited[nVex1] = true;
        aVisited[nVex2] = true;
    }
}