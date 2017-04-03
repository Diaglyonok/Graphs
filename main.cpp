#include <iostream>
#include <list>
#include <queue>
#include <time.h>
#include <random>
#include <windows.h>

using namespace std;
/*
 * Class Declaration
 */
class Graph
{
    protected:
        int V;
        list<int> *adj;
    public:
        Graph(int V)
        {
            this->V = V;
            adj = new list<int> [V];
        }

        ~Graph()
        {
            adj = NULL;
            V = 0;
        }

        void addEdge(int v, int w){adj[v].push_back(w);};
        Graph BFS(int s, int visited[]);
        void printGraph();
        void generateGraph();

        int detectTreeRoot(int visited[]);
        Graph buildTree(int visited[]);
        void buildForest();
};



/*
 *  A recursive method to print BFS starting from s
 */
Graph Graph::BFS(int s, int visited[])
{
    Graph tree(V);

    list<int> q;
    list<int>::iterator i;
    visited[s] = 1;
    q.push_back(s);
    while (!q.empty())
    {
        s = q.front();
        q.pop_front();
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {

                visited[*i] = 1;
                q.push_back(*i);
                tree.addEdge(s, *i);
            }

        }
    }

    return tree;
}



/*
 *  methid detect root of the tree
 */
int Graph::detectTreeRoot(int visited[])
{
    list<int>::iterator k;
    int minX = V;
    int iterX = 0;
    int power[V];
    for (int i = 0; i<V; i++)
        power[i] = 0;

    for (int i = 0; i<V; i++)
    {
        for (k = adj[i].begin(); k != adj[i].end(); ++k)
        {
            power[*k]++;

        }
    }

    for (int i = 0; i < V; i++)
    {
        if (minX > power[i] && !visited[i])
        {
            minX = power[i];
            iterX = i;
        }
    }
    cout << endl;
    cout << "Tree root is: " << iterX << endl;
    cout << endl;
    return iterX;
}



/*
 *  Printing graph on the srcreen
 */
void Graph::printGraph()
{
    list<int>::iterator i;
    int foundConnection = 0;
    cout << "Connections (Descendant: Ancestors) :" << endl;
    for (int k = 0; k<V; k++){
        if (!adj[k].empty()){
            cout << k << ":";
            foundConnection++;
        }
        for (i = adj[k].begin(); i != adj[k].end(); ++i)
            {
                if (i != adj[k].begin())
                    cout << ", ";
                    cout << *i;
            }
        if (!adj[k].empty())
            cout << endl;

        //if (foundEmpty == V-1)

    }
    if (foundConnection == 0)
    cout << "No connections" << endl;
}



/*
 * Check if Graph is Connected
 */
bool isAllVisitedTrue(int visited[], int V)
{
    for (int i = 0; i<V; i++)
    {
        if (!visited[i]  /*i!=V-1*/)
            return false;
    }
    return true;
}



/*
 *  Method, that bulds
 */
void Graph::buildForest()
{
    int visited[V];
    int treeCount = 0;
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    do
    {
        Graph tree(V);
        cout << endl;
        cout << "______________________________________________________________________"<< endl;
        cout << "Tree " << treeCount+1 << endl;
        (tree = this->buildTree(visited)).printGraph();
        treeCount ++;
    }
    while(!isAllVisitedTrue(visited, V));

}



Graph Graph::buildTree(int visited[])
{
    int root = detectTreeRoot(visited);

    Graph tree(V);

    tree = BFS(root, visited);

    return tree;
}

void Graph::generateGraph()
{
    time_t t;
    int a1, a2, a3;
    srand((unsigned) time(&t));
    int a[V][V];
    int i,j;
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++){
            a1 = rand() % 2;
            a2 = rand() % 2;
            a3 = rand() % 2;
            if (a1 == 1 && a2 == 1 && a3 == 1)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
        {
            if (a[i][j] == 1)
                this->addEdge(i, j);
        }
}
/*
 * Main Contains Menu
 */


int main()
{
    int chose;

    do{
        cout << endl;
        cout << "Enter:"  << endl;
        cout << "1. If you want to generate random graph"  << endl;
        cout << "2. If you want to see demo graph"  << endl;
        cout << "3. If you want to enter your graph"  << endl;
        cout << "0. Exit"  << endl;
        do{
            cout << ">"; cin >> chose;
            if (chose < 0 || chose > 3)
                cout << "You entered wrong number, enter again" << endl;
        }while (chose < 0 || chose > 3);

        switch (chose)
        {

            case 1:{
                int edges;
                cout << "Enter number of edges" << endl;
                do{
                    cout << ">"; cin >> edges;
                    if (edges < 2)
                        cout << "You entered wrong number, enter again" << endl;
                }while (edges < 2);

                cout << endl;
                cout << "Generated graph: " << endl;

                Graph g1(edges);

                g1.generateGraph();
                g1.printGraph();
                g1.buildForest();

                system("pause");
                system("cls");
            }

            break;

            case 2:{
                cout << endl;
                cout << "Demo Graph: " << endl;
                Graph g2(13);

                g2.addEdge(0, 4);
                g2.addEdge(0, 7);
                g2.addEdge(1, 12);
                g2.addEdge(1, 6);
                g2.addEdge(4, 8);
                g2.addEdge(4, 9);
                g2.addEdge(5, 9);
                g2.addEdge(8, 11);
                g2.addEdge(9, 10);
                g2.addEdge(2, 5);
                g2.addEdge(2, 7);
                g2.addEdge(3, 7);

                g2.printGraph();
                g2.buildForest();

                system("pause");
                system("cls");
            }
            break;

            case 3:{
                bool isEnd = false;
                int descendant, ancestor, edges, connectionCount=0;
                char answer;

                cout << "Enter number of edges" << endl;
                do{
                    cout << ">"; cin >> edges;
                    if (edges < 2)
                        cout << "You entered wrong number, enter again" << endl;
                }while (edges < 2);

                Graph g3(edges);

                do{

                    cout << "Enter Descendant[" << connectionCount << "] :" << endl;
                    do{
                        cout << ">"; cin >> descendant;
                        if (descendant < 0 || descendant >= edges)
                            cout << "You entered wrong descendant, enter again" << endl;
                    }while (descendant < 0 || descendant >= edges);


                    cout << "Enter Ancestor[" << connectionCount << "] :" << endl;
                    do{
                        cout << ">"; cin >> ancestor;
                        if (ancestor < 0 || ancestor >= edges)
                            cout << "You entered wrong ancestor, enter again" << endl;
                    }while (ancestor < 0 || ancestor >= edges);

                    g3.addEdge(descendant, ancestor);
                    connectionCount++;

                    cout << endl << "Continue? (Y/N)" << endl;
                    do{
                        cout << ">"; cin >> answer;
                        if (answer == 'Y' || answer == 'y')
                            isEnd = false;
                        if (answer == 'N' || answer == 'n')
                            isEnd = true;

                        if (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
                            cout << "You entered wrong answer, enter again" << endl;

                    }while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n');


                }while (!isEnd);

                cout <<  endl;
                cout << "Entered graph: " << endl;
                g3.printGraph();
                g3.buildForest();

                system("pause");
                system("cls");
            }
            break;

            default:
                break;
        }
    }while (chose != 0);
    /*Graph g1(10);
    g1.addEdge(0, 4);
    g1.addEdge(1, 3);
    g1.addEdge(1, 2);
    g1.addEdge(1, 5);
    g1.addEdge(2, 5);
    g1.addEdge(2, 4);
    g1.addEdge(3, 6);
    g1.addEdge(4, 6);
    g1.addEdge(4, 8);
    g1.addEdge(5, 7);
    g1.printGraph();

    g1.buildForest();*/

    return 0;
}
