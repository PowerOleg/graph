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

int** create_graph(int* rows)
{
    int arr_index = 0;
    int line;
    std::ifstream in("input.txt");
    if (!in.is_open())
    {
        printf("The file is not opened");
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
                printf("The reading has finished at i = %d, j = %d\n", i, j);
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
    print_graph(graph, rows, rows);
    



    delete_graph(graph, rows);
	return 0;
}