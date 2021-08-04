#include"graph.h"
#include<stack>
#include<iostream>



///     Construct a [vertices][vertices] table filled with 0s
/// in matrix.
matrix_graph::matrix_graph(const int& vertices){
    if(vertices<0){
        size = 1;
        matrix.resize(1);
        matrix[0].resize(1,0);
        return;
    }

    size = vertices;
    matrix.resize(vertices);

    for(int i=0;i<vertices;++i){
        matrix[i].resize(vertices,0);
    }
}


/// Add edge from node A to node B with a default cost of 1.
void matrix_graph::edge(const int& a, const int& b){
    if(a-1<0||a-1>=size||b-1<0||b-1>=size){
        printf("Error: (%d,%d) are out of bounds.\n",a,b);
        return;
    }

    matrix[a-1][b-1]=1;
}


/// Add edge from node A to node B with a cost.
void matrix_graph::edge(const int& a, const int& b,const int& cost){
    if(a-1<0||a-1>=size||b-1<0||b-1>=size){
        printf("Error: (%d,%d) are out of bounds.",a,b);
        return;
    }

    matrix[a-1][b-1]=cost;
}


/// Add an edge between A and B with a default cost of 1.
void matrix_graph::dedge(const int& a, const int& b){
    edge(a,b);
    edge(b,a);
}


/// Add an edge between A and B with a cost.
void matrix_graph::dedge(const int& a, const int& b,const int& cost){
    edge(a,b,cost);
    edge(b,a,cost);
}


/// Print the adjacency matrix.
void matrix_graph::printMatrix() const{
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
        printf("\n");

}


/// Print the graph as an adjacency list.
void matrix_graph::printAdjList() const{
    for(int i=0;i<size;++i){
        int p = i+1;
        printf("[%d]-> { ", p);
        for(int j=0;j<size;++j){
            if(matrix[i][j]){
                int p=j+1;
                if(matrix[i][j]!=1){
                    printf("%d[%d] ",p,matrix[i][j]);
                }
                else
                    printf("%d ", p);
            }
        }
        printf("}\n");
    }
    printf("\n");
}


/// Return the number of connected components using DFS.
int matrix_graph::connectedComponents(){
    int comp_counter = 0;
    int elem_counter = 0;
    std::vector<bool> visited(size,0);
    while(elem_counter<size){
        int start=0;
        for(int i = 0;i<size;++i){
            if(!visited[i]){ start = i;++comp_counter; break;}
        }

        std::stack<int> st;
        st.push(start);
        while(!st.empty()){
            int s = st.top();
            st.pop();
            if(!visited[s]){
                visited[s]=true;
                ++elem_counter;
            }
            for(int i=0;i<size;++i){
                if(matrix[s][i]==true){
                    if(!visited[i])
                        st.push(i);
                }
            }
        }
    }

    return comp_counter;
}


///     Check whether the graph is directional by checking
/// whether the adjacency matrix is symmetrical.
bool matrix_graph::isDirectional(){
    for(int i = 0;i<size;++i){
        for(int j=i;j<size;++j){
            if(matrix[i][j]!=matrix[j][i])
                return true;
        }
    }
    return false;
}


/// Experimental function.
void matrix_graph::printConnComp() const{
    std::vector<int> visited(size,0);

    int elem_counter = 0;
    int comp_counter = 0;
    int conn_comp_idx = 1;

    while(elem_counter<size){
        int start = 0;
        for(int i=0;i<size;++i){
            if(visited[i]==0){
                start = i;
                break;
            }
        }

        std::stack<int> st;
        st.push(start);
        while(!st.empty()){
            int s = st.top();
            st.pop();
            if(!visited[s]){
                visited[s]=conn_comp_idx;
                ++elem_counter;
            }

            for(int i=0;i<size;++i){
                if(matrix[s][i]==1){
                    if(!visited[i])
                        st.push(i);
                }
            }
        }

        ++conn_comp_idx;
    }

    for(int i=0;i<size;++i)
        std::cout<<visited[i]<<" ";
    std::cout<<"\n";
}


/// Check if there are cycles in the graph.
bool matrix_graph::isAcyclic(){
    if(!this->isDirectional())
        return false;

    std::vector<bool> visited(size,0);
    int elem_cnt=0;

    while(elem_cnt<size){
        int start=0;
        for(int i=0;i<size;++i)
            if(visited[i]==0){start = i; break;}

        std::stack<int> st;
        st.push(start);
        while(!st.empty()){
            int top;
            top = st.top();
            st.pop();

            if(!visited[top]){
                visited[top]=true;
                ++elem_cnt;
            }

            for(int i =0;i<size;++i)
                if(matrix[top][i]==1){
                    if(!visited[i])
                        st.push(i);
                    else
                        for(int j=0;j<size;++j)
                            if(matrix[i][j]==true&&visited[j])
                                return false;

                }
        }

    }
    return true;
}

bool matrix_graph::isDAG(){
    if( this->isDirectional() &&
        this->isAcyclic())
        return true;
    return false;
}


int matrix_graph::h(int start_x, int start_y, int goal_x, int goal_y){
    int dx = abs(start_x - goal_x);
    int dy = abs(start_y - goal_y);
    int minimum = dx>dy?dy:dx;
    return dx+dy - minimum;
}


/// Return path from st to gl in the graph.
std::vector<int> matrix_graph::dijkstra(const int& st,const int& gl){
    int start = st-1;
    int goal = gl-1;
    /*if( start<0||start>=size  || goal<0 || goal>=size  ){
        printf("ERROR: Dijkstra IVALID GOALS\n");
        printf("Size: %d\n",size);
        printf("Start: %d\n",st);
        printf("End: %d\n",gl);
    }*/

    std::vector<int> dist(size,100000000);
    std::vector<int> prev(size,-1);
    std::vector<int> Q(size);
    for(int i=0;i<size;++i)Q[i]=i;
    dist[start]=0;

    while(!Q.empty()){
        int min=100000001;
        int min_node=0;
        int min_idx=0;

        for(int i = 0;i<Q.size();++i){
            if(dist[Q[i]]<min){
                min = dist[Q[i]];
                min_node = Q[i];
                min_idx = i;
            }
        }
        if(Q[min_idx]==goal)break;
        Q.erase(Q.begin()+min_idx);

        for(int i=0;i<size;++i){
            if(matrix[min_node][i]!=0){
                bool found =0;
                for(int j=0;j<Q.size();++j)
                    if(Q[j]==i)found = true;

                if(found){
                    int alt = dist[min_node]+matrix[min_node][i];
                    if(alt<dist[i]){
                        dist[i]= alt;
                        prev[i]= min_node;
                    }
                }
            }
        }
    }
    std::vector<int> result;
    result.push_back(gl);
    //printf("Path from %d to %d :\n   [%d]",st,gl,gl);
    int i=goal;
    while(prev[i]!=start){
        if(i<0){printf("no path"); break;}
        int a= prev[i]+1;
        result.push_back(a);
        //printf("<-[%d]",a);
        i=prev[i];

    }
    //printf("<-[%d]\n",st);
    result.push_back(st);
    return result;
}


/// Return path from st to gl in the graph.
std::vector<int> matrix_graph::aStar(const int& st,const int& gl, const std::vector<std::vector <short int>>& coords){
    int start = st-1;
    int goal = gl-1;
    /*if( start<0||start>=size  || goal<0 || goal>=size  ){
        printf("ERROR: Dijkstra IVALID GOALS\n");
        printf("Size: %d\n",size);
        printf("Start: %d\n",st);
        printf("End: %d\n",gl);
    }*/

    std::vector<int> dist(size,100000000);
    std::vector<int> prev(size,-1);
    std::vector<int> Q(size);
    for(int i=0;i<size;++i)Q[i]=i;
    dist[start]=0;

    while(!Q.empty()){
        int min=100000001;
        int min_node=0;
        int min_idx=0;

        for(int i = 0;i<Q.size();++i){
            if(dist[Q[i]]<min){
                min = dist[Q[i]];
                min_node = Q[i];
                min_idx = i;
            }
        }
        if(Q[min_idx]==goal)break;
        Q.erase(Q.begin()+min_idx);

        for(int i=0;i<size;++i){
            if(matrix[min_node][i]!=0){
                bool found = false;
                for(int j=0;j<Q.size();++j)
                    if(Q[j]==i)found = true;

                if(found){

                    int alt = dist[min_node]+matrix[min_node][i] +
                              h(coords[i][0],coords[i][1],coords[goal][0],coords[goal][1]);
                    if(alt<dist[i]){
                        dist[i]= alt;
                        prev[i]= min_node;
                    }
                }
            }
        }
    }
    std::vector<int> result;
    result.push_back(gl);
    //printf("Path from %d to %d :\n   [%d]",st,gl,gl);
    int i=goal;
    while(prev[i]!=start){
        if(i<0){printf("no path"); break;}
        int a= prev[i]+1;
        result.push_back(a);
        //printf("<-[%d]",a);
        i=prev[i];

    }
    //printf("<-[%d]\n",st);
    result.push_back(st);
    return result;
}
