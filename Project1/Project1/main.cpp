#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>

/*#if(MSVC)
addcompileoptions("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
addcompileoptions("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#endif()*/

void copy_graph(char** two_dim_arr_source, char** two_dim_arr_target, const int rows, const int columns)
{
    for (int i = 0; i < rows; i++)
    {
        std::copy_n(two_dim_arr_source[i], columns, two_dim_arr_target[i]);
    }
}

int** create_graph(int rows, int cols)
{
    int** two_dimensional_array = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        two_dimensional_array[i] = new int[cols];
    }

    return two_dimensional_array;
}

void init_graph(char** two_dim_arr, int** coordiantes, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int rows = coordiantes[i][0];
        int cols = coordiantes[i][1];
        two_dim_arr[rows][cols] = '*';
    }
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

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");
    int rows = 7;
    int columns = rows;

    int arr_index = 0;
    std::string line;
    std::string* lines = new std::string[rows];
    std::ifstream read_file("input.txt");
    while (std::getline(read_file, line)) {
        //rows = line;
        std::stringstream in(line);
        in >> rows;
        
        for (size_t i = 0; i < rows - 1; i++)
        {
            
            std::getline(in, lines[arr_index++], ' ');
            
        }
        //std::getline(in, lines[arr_index++], '\n');

    }
    read_file.close();
    int** graph = create_graph(rows, columns);
    //init
    delete[] lines;



    delete_graph(graph, rows);
	return 0;
}