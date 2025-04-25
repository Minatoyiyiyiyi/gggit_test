#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

CGraph m_Graph;

int main()
{
	int bRunning = 1;
	int choice;
	while (bRunning)
	{
		//输出界面
		cout << " = = = = 景区信息管理系统 = = = = " << endl;
		cout << "1.创建景区景点图 "<< endl;
		cout << "2.查询景点信息 "<< endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入1-5的选项:" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			CreateGraph();
			break;
		case 2:
			GetSpotInfo();
			break;
		case 3:
			TravelPath();
			break;
		case 4:
			FindShortPath();
			break;
		case 5:
			DesignPath();
			break;
		case 0:break;
		default:break;
		}
	}
	return 0;
}