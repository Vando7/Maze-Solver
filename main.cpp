/**
 *  Written by Ivan Mihaylov
 *  Compiler: GNU GCC
 */

#include <iostream>
#include "graph.h"
#include<fstream>



///    Take an existing grid with 1's and 0's
/// and a graph that already has as many edges, as
/// there are in the grid.
///    If there are two adjacent 1's in the grid,
/// then they are connected in the graph.
void gridToGraph(
    std::vector<std::vector<std::vector<short int> > >& grid,
    matrix_graph& solution,
    const int& xres,
    const int& yres)
{
    for(int i=0;i<yres;++i){
        for(int j=0;j<xres;++j){
            if(grid[i][j][0]!=0){
                bool b_up,b_down,b_left,b_right;
                b_up=b_down=b_right=b_left=false;
                int curr = grid[i][j][1];

                /// It costs 1 move diagonally once.
                int cost=1;

                if(i>0){
                    b_up=true;
                    if(grid[i-1][j][0]!=0)
                        solution.dedge(curr,grid[i-1][j][1]);
                }
                if(j>0){
                    b_left=true;
                    if(grid[i][j-1][0]!=0)
                        solution.dedge(curr,grid[i][j-1][1]);
                }
                if(i<yres-1){
                    b_down=true;
                    if(grid[i+1][j][0]!=0)
                        solution.dedge(curr,grid[i+1][j][1]);
                }
                if(j<xres-1){
                    b_right=true;
                    if(grid[i][j+1][0]!=0)
                        solution.dedge(curr,grid[i][j+1][1]);
                }
                /// Top right.
                if(b_right&&b_up){
                    if(grid[i-1][j+1][0]!=0)
                        solution.dedge(curr,grid[i-1][j+1][1],cost);
                }
                /// Top left.
                if(b_up&&b_left){
                    if(grid[i-1][j-1][0]!=0)
                        solution.dedge(curr,grid[i-1][j-1][1],cost);
                }
                /// Bottom left.
                if(b_down&&b_left){
                    if(grid[i+1][j-1][0]!=0)
                        solution.dedge(curr,grid[i+1][j-1][1],cost);
                }
                /// Bottom right.
                if(b_down&&b_right){
                    if(grid[i+1][j+1][0]!=0)
                        solution.dedge(curr,grid[i+1][j+1][1],cost);
                }
            }
        }
    }
}



void gridToGraph(
    std::vector<std::vector<std::vector<short int> > >& grid,
    matrix_graph& solution)
{
    gridToGraph(grid,solution,grid[0].size(),grid.size());
}



int main(int argc, char** argv){

    if(argc!=2){
        printf("Error: Invalid input.\n");
        printf("Input format: [Maze.exe \"..\\file.ppm\"] with the quotes.\n");
        return 6;
    }

    std::ifstream file;

    file.open(argv[1]);
    if(!file.is_open()){
        std::cout<<argv[1]<<"\n";
        printf("Error opening file.\n");
        return 2;
    }

    char buffer[10];
    file.getline(buffer,10,'\n');

    /// Read number of columns.
    int xres;
    file>>xres;
    /// Read number of rows.
    int yres;
    file>>yres;
    /// Read the maximum RGB value.
    int maxVal;
    file>>maxVal;

    /// Start point coordinates and white square index.
    int startX, startY, startIdx;
    startX=startY=startIdx=-1;

    /// End point coordinates and white square index.
    int endX  , endY  , endIdx;
    endX=endY=endIdx=-1;


    ///     Declare grid and initialize yres row in it. This grid
    /// will represent the maze.
    ///     Vertex index will be a 2 by (vertex_counter) array which
    /// will save the coordinates of every white square of the table.
    /// That way each white square has its own unique ID which means
    /// that we can easily transition from graph to grid and from grid
    /// to graph. i.e. :
    ///     if
    ///         vertex_index[10] = { 2, 3 }
    ///     then
    ///         grid[2][3][0] = 1  // as in (2,3) is a white pixel
    ///     and
    ///         grid[2][3][1] = 10 // as in (2,3) has an index of 10
    std::vector< std::vector< std::vector<short int> > > grid(yres);
    std::vector< std::vector< short int > >   vertex_index(1);
    int vertex_counter = 0;

    /// Read file
    for(int i=0;i<yres;++i){
        grid[i].resize(yres);

        for(int j=0;j<xres;++j){
            ///     Each set of 3 consecutive rows in the
            /// rest of the file represent an RGB code.
            grid[i][j].resize(2,0);
            int R,G,B;
            file>>R;
            file>>G;
            file>>B;

            /// If square isn't black.
            if((R+G+B)!=0){
                /// Add vertex.
                vertex_index.resize(vertex_index.size()+1);
                vertex_index[vertex_counter].resize(2);
                vertex_index[vertex_counter][0]=i;
                vertex_index[vertex_counter][1]=j;

                /// Write to grid.
                grid[i][j].resize(2,0);
                grid[i][j][0]=1;
                grid[i][j][1]=vertex_counter+1;
                ++vertex_counter;

                /// If square is green.
                if(G==255&&B==0){
                    startX=j;
                    startY=i;
                    startIdx = vertex_counter;
                }

                /// If square is blue.
                if(B==255&&G==0){
                    endX=j;
                    endY=i;
                    endIdx = vertex_counter;
                }
            }
        }
    }



    if(startIdx==-1||endIdx==-1){
        if(startIdx==-1)
            printf("No start point found. It has to be in pure green.\n");
        if(endIdx==-1)
            printf("No end point found. It has to be in pure blue.\n");

        return 1;
    }



    printf("\nFile is a %d by %d maze with %d white squares.\n",yres,xres,vertex_counter);
    printf("Attempting to find path from (%d,%d) to (%d,%d) . . .  \n",startY,startX,endY,endX);



    matrix_graph solution(vertex_counter);
    gridToGraph(grid,solution);

    std::vector<int> a = solution.dijkstra(startIdx,endIdx);

    printf("Successfully found path with a length of %d. Writing to result.ppm\n",a.size());


    /// Write the returned path into the grid.
    /// This is where the Graph -> Grid part comes in.
    /// The path is represented by 3's because 3 is a
    /// lucky number.
    for(int i=0;i<a.size();++i){
        int row = vertex_index[a[i]-1][0];
        int col = vertex_index[a[i]-1][1];
        grid[row][col][0]=3;
    }

    std::ofstream file2("result.ppm");
    file2<<"P3\n"<<xres<<" "<<yres<<"\n225\n";

    for(int i=0;i<yres;++i){
        for(int j=0;j<xres;++j){
            /// Paint the start in Green and the end in Blue.
            if(i==startY&&j==startX){
                file2<<000<<"\n";
                file2<<255<<"\n";
                file2<<000<<"\n";
            }
            else if(i==endY&&j==endX){
                file2<<000<<"\n";
                file2<<000<<"\n";
                file2<<255<<"\n";
            }

            else {
                /// 3 -> RED
                /// 1 -> WHITE
                /// 0 -> BLACK
                if(grid[i][j][0]==3){
                    file2<<255<<"\n";
                    file2<<000<<"\n";
                    file2<<000<<"\n";
                }
                if(grid[i][j][0]==1){
                    file2<<255<<"\n";
                    file2<<255<<"\n";
                    file2<<225<<"\n";
                }
                if(grid[i][j][0]==0){
                    file2<<000<<"\n";
                    file2<<000<<"\n";
                    file2<<000<<"\n";

                }
            }
        }
    }

    printf("Done.\n");
    file2.close();
    return 0;
}
