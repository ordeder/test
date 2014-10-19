#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define N 1000
using namespace std;

int adj[N][N]={0};
int timePro[N][N]={0};
int costPro[N][N]={0};
int n=0,proc=0;
struct Node
{
	int start;
	int exe;
	int end;
	int pro;
	int cost;
}Node;

struct Node myNode[N];
int main()
{
	vector<int> v;
	int totalTime=0,totalCost=0;
	int theirTime=0,theirCost=0;
	ifstream in("..\\yan\\2013.txt");
	ifstream inResult("..\\yan\\result.txt");
	string flag;
	int task,i,j;
	int from,to;
	//cout<<"hh"<<endl;
	in>>flag>>n>>flag>>proc;
	cout<<n<<" "<<proc<<endl;
	//	cout<<n<<" "<<proc<<endl;
	for (i=0;i<n;i++)
	{
		in>>flag>>task;
		in>>flag;
		in>>from>>to;
		while(to!=-1)
		{
			adj[from][to]=1;
			in>>from>>to;
		}
		in>>flag;		
		for (j=0;j<proc;j++)
		{
			in>>timePro[task][j];
		}
		in>>flag;
		for (j=0;j<proc;j++)
		{
			in>>costPro[task][j];
		}
	}	

	inResult>> flag>>flag>>flag>>flag>>flag>>flag;
	for(i=0;i<n;i++)
	{
		inResult>> flag;
		inResult>> myNode[i].start>>myNode[i].exe>>myNode[i].end>>myNode[i].pro>>myNode[i].cost;
	}
	inResult>>flag>>theirTime;
	inResult>>flag>>theirCost;

	//check adj
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j]>0)
			{
				if(myNode[i].end>myNode[j].start)
				{
					cout<<"ERROR adj: "<<i<<"   "<<j<< " "<<myNode[i].end <<endl;
					system("pause");
				}

			}
		}
	}

	for(i=0;i<n;i++)
	{
		
		if(timePro[i][myNode[i].pro-1]!=myNode[i].exe)
		{
			cout<<"ERROR pro:"<< i<<endl;
			system("pause");
		}
		if(costPro[i][myNode[i].pro-1]!=myNode[i].cost)
		{
			cout<<"ERROR cost:"<< i<<endl;
			system("pause");
		}
		/*
		if(timePro[i][myNode[i].pro]!=myNode[i].exe)
		{
			cout<<"ERROR pro:"<< i<<endl;
			system("pause");
		}
		if(costPro[i][myNode[i].pro]!=myNode[i].cost)
		{
			cout<<"ERROR cost:"<< i<<endl;
			system("pause");
		}*/

		if(myNode[i].exe>myNode[i].end-myNode[i].start)
		{
			cout<<"ERROR exe:"<< i<<endl;
			system("pause");
		}
		//totalTime+=myNode[i].exe;
		totalCost+=myNode[i].cost;
	}
	for(i=0;i<proc;i++)
	{
		for(j=0;j<n;j++)
		{
			
			if(myNode[j].pro-1==i)
			{
				for(int k=myNode[j].start;k<myNode[j].end;k++)
				{
					v.push_back(k);
				}
			}
			/*
			if(myNode[j].pro==i)
			{
				for(int k=myNode[j].start;k<myNode[j].end;k++)
				{
					v.push_back(k);
				}
			}*/
		}
		sort(v.begin(),v.end());
		for(j=1;j<v.size();j++)
			if(v.at(j)==v.at(j-1))
			{
				cout<<"ERROR multiple exe pro:"<< i<<" "<<v.at(j)<<endl;
				system("pause");
			}else if(v.at(j)>theirTime)
			{
				cout<<"ERROR reach out totalTime:"<< i<<endl;
				system("pause");
			}
			v.clear();
	}
	if(theirCost<totalCost)
	{
		cout<<"ERROR reach out totalcost"<<endl;
		system("pause");
	}
	cout<<"congratulation!!!"<<endl;
	system("pause");
}