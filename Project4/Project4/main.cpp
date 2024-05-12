#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <queue>

#if(MSVC)
addcompileoptions("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
addcompileoptions("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#endif()

int** create_graph(int* rows)
{
    int arr_index = 0;
    int line;
    std::ifstream in("input2.txt");
    if (!in.is_open())
    {
        printf("File is not opened");
        return nullptr;
    }

    in >> *rows;
    int columns = *rows;
    int** two_dimensional_array = new int* [*rows];
    for (size_t i = 0; i < *rows; i++)
    {
        two_dimensional_array[i] = new int[columns] {};
        for (size_t j = 0; j < columns; j++)
        {
            in >> line;
            two_dimensional_array[i][j] = line;
            if (in.eof() && j < columns - 1)
            {
                printf("Reading has finished at i = %d, j = %d\n", i, j);
            }
        }
    }
    in.close();
    /*while (!(in >> line).eof())
    {
        lines[arr_index++] = line;
    }
    lines[arr_index++] = line;
    in.close();*/
    return two_dimensional_array;
}

void print_graph(int** two_dim_arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << two_dim_arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void delete_graph(int** two_dim_arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] two_dim_arr[i];
    }
    delete[] two_dim_arr;
}

void dfs_deep(int** graph, int vertex_index, bool*& visited, int v)
{
    printf("%d ", vertex_index + 1);
    visited[vertex_index] = true;

    for (size_t i = 0; i < v; i++)
    {
        if (graph[vertex_index][i] == true && visited[i] == false)
        {
            dfs_deep(graph, i, visited, v);
        }
    }
}

void dfs_deep(int** graph, int v)
{
    bool* visited = new bool[v] {};
    for (size_t i = 0; i < v; i++)
    {
        if (visited[i] == false)
        {
            dfs_deep(graph, i, visited, v);
        }
    }
    delete[] visited;
}

void bfs(int** graph, int vertex_index, bool*& visited, int v)
{
    printf("%d ", vertex_index + 1);
    visited[vertex_index] = true;
    std::queue<int> queue;
    for (size_t i = 0; i < v; i++)
    {
        if (graph[vertex_index][i] == true && visited[i] == false)
        {
            queue.push(i);
        }
    }

    while (!queue.empty())
    {
        int index = queue.front();
        queue.pop();
        if (visited[index] == true)
        {
            continue;
        }
        printf("%d ", index + 1);
        visited[index] = true;
        for (size_t i = 0; i < v; i++)
        {
            if (graph[index][i] == true && visited[i] == false)
            {
                queue.push(i);
            }
        }
    }
}

void bfs(int** graph, int v)
{
    bool* visited = new bool[v] {};
    for (size_t i = 0; i < v; i++)
    {
        if (visited[i] == false)
        {
            bfs(graph, i, visited, v);
        }
    }
    delete[] visited;
}

bool dfs_is_cyclic(int** graph, int vertex_index, bool*& visited, int prev_vertex, int v)
{
    visited[vertex_index] = true;
    for (size_t i = 0; i < v; i++)
    {
        if (graph[vertex_index][i] == true && visited[i] == false)
        {
            if (dfs_is_cyclic(graph, i, visited, vertex_index, v))
            {
                return true;
            }
        }
        else if (graph[vertex_index][i] == true && visited[i] == true && i != prev_vertex && i != vertex_index)
        {
            return true;
        }
    }
    return false;
}

void is_cyclic(int** graph, int v)
{
    bool* visited = new bool[v] {};
    int prev_vertex = 0;
    for (size_t i = 0; i < v; i++)
    {
        if (visited[i] == false)
        {
            prev_vertex = i;
            if (dfs_is_cyclic(graph, i, visited, prev_vertex, v))
            {
                printf("There is a cycle");
                return;
            }
        }
    }
    delete[] visited;
    printf("No cycles");
}

//cids - массив; cid - номер для различия одних компонентов связности от других(number to define a cycle from others)
void dfs_find_components(int** graph, int vertex_index, int *&cids, int cid, int v)
{
    cids[vertex_index] = cid;
    for (size_t i = 0; i < v; i++)
    {
        if (graph[vertex_index][i] == true && cids[i] == 0)
        {
            dfs_find_components(graph, i, cids, cid, v);
        }
    }
}
    
void find_components(int** graph, int v)
{
    int* cids = new int[v]{};
    int cid = 1;
    for (size_t i = 0; i < v; i++)
    {
        if (cids[i] == 0)
        {
            dfs_find_components(graph, i, cids, cid, v);
            cid++;
        }
    }
    //printf("Result:\n");
    for (size_t i = 0; i < v; i++)
    {
        printf("%d - %d\n", (i + 1), cids[i]);
    }

    //How many different components
    printf("Количество компонентов связности в графе: %d", cid - 1);
    delete[] cids;
}
            

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");
    int rows = 0;
    int** graph = create_graph(&rows);
    if (graph == NULL)
    {
        printf("Error creating the graph");
        return 1;
    }
    printf("Принадлежность вершин компонентам связности:\n");
    find_components(graph, rows);
    delete_graph(graph, rows);
    return 0;
}