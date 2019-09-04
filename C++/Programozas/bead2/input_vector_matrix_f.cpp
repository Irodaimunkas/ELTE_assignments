#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "input_vector_matrix_f.h"

void input_vector_matrix_f(int &i_in, int &j_in, std::vector< std::vector<int> > &vec, std::string file){

    std::ifstream f(file.c_str());
    if(f.fail()){
        std::cout << "Cannot find input file!\n";
        exit(1);
    }
    int i_max, j_max;
    f >> i_max >> j_max;
    i_in = i_max;
    j_in = j_max;
    vec.resize(i_max);
        for(int i = 0; i < i_max; i++){
            vec[i].resize(j_max);
            for(int j = 0; j < j_max; j++){
                f >> vec[i][j];
            }
        }

    std::cout << "Test file's data (rows = towns, columns = bird species): \n";
    for(int i = 0; i < i_max; i++){
        for(int j = 0; j < j_max; j++){
            std::cout << vec[i][j] << " ";
        }
        std::cout << "\n";
    }
}
