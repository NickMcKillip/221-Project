//
//  main.cpp
//
//
//  Created by Nick Mckillip on 8/1/17.
//  Copyright © 2017 Nick Mckillip. All rights reserved.
//

#include <iostream>
#include "maze.h"
#include <queue>
#include <algorithm>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;

//Uses a bfs

vector<int> shortestPath(mazeVec m)
{
    bool visited[m.maze.size()];
    for (int i = 0; i < m.maze.size(); ++i) //inititalized visited for each vertex to false
        visited[i] = false;
    queue<int> q; vector<int> parent(m.maze.size(),-1);//store the parent so that the path can be traced
    int curr = 0; visited[curr] = true;q.push(curr); list<int>::iterator i;
    while(!q.empty()) //go until exit is found
    {
        curr = q.front(); q.pop();
        for(i = m.maze.at(curr).adj.begin(); i!=m.maze.at(curr).adj.end(); ++i) //check all of the adjacency's
        {
            if(!visited[*i])
            {
                visited[*i] = true; parent[*i] = curr;
                q.push(m.maze.at(*i).pos);
            }
        }
    }
    vector<int> path;
    int c = m.maze.size()-1; path.push_back(c);
    while(c!=0) //backtrack to find the full
    {
        c = parent[c];
        path.push_back(c);
    }
    reverse(path.begin(), path.end());
    return path;
}



void printPath(vector<int> path, int size)   //prints out the path as text
{   cout << "Length of path: " << path.size() -1 << endl;
    vector<char> output(size);
    for (int i = 0; i < size; ++i)
        output.at(i) = 'x';
    for (int i = 0; i< path.size(); i++)
        output.at(path.at(i)) = 'o';
    for (int i = 0; i < (sqrt(size)); ++ i)
    {
        for (int j = 0; j < sqrt(size); j++)
            cout << output.at(sqrt(size)*i + j) << " ";
        cout << endl;
    }
}


int main() {
    try{
        bool cont = true;
        while (cont == true)
        {
            cout << "Input the name of the file you would like to read" << endl;
            string filename;
            cin >> filename;
            ifstream inf(filename);
            if(!inf)
                cerr << "File not found, restart the program and ensure you enter a locatable filename." << endl;
            mazeVec m;
            int num;
            inf >> num;
            int count = 0;
            while (count < num){  //construct maze from input
                int n; int e; int s ; int w;
                inf >> n >> e >> s >> w;
                m.insert(n,e,s,w,count,num);
                count ++;
            }
            
            vector<int> path = shortestPath(m);
            int choice = 1; //initialized to 1 so the while loop will be entered
            while (choice != 0)
            {
                cout << "Enter 1 to: – Print the adjacency list for a given graph." << endl
                << "Enter 2 to: – Display the entry exit path and show the length of the entry-exit path" << endl
                << "Enter 3 to: – Print out all vertices (room numbers) on the entry-exit path" << endl
                << "Or enter 0 to quit" << endl;
                cin >> choice;
                switch(choice){
                    case 1:
                        for(int i = 0; i < m.maze.size(); ++ i)
                            cout << m.maze.at(i) << endl;
                        break;
                    case 2:
                        printPath(path, m.maze.size());
                        break;
                        
                    case 3:
                        for(int i = 0; i < path.size(); ++ i)
                            cout << path.at(i) << " ";
                        cout << endl;
                        break;
                }
            }
            string o_name;
            cout << "Would you like to save the file? Enter 0 to skip file output. Otherwise enter the file name" << endl;
            cin >> o_name;
            if (o_name != "0")
            {
                ofstream ost(o_name);
                ost << m.maze.size() << endl;
                for (int i = 0; i < m.maze.size(); ++ i)
                {
                    ost << m.maze.at(i).n << " " << m.maze.at(i).e << " " << m.maze.at(i).s << " " << m.maze.at(i).w << endl;
                }
            }
            
            cout << "Would you like to load another file. Enter 1 for yes or 0 for no" << endl;
            cin >> cont;
        }
    }
    catch (const char* exception)
    {
        cerr << "Error: " << exception << endl;
    }
}













    
    
    
