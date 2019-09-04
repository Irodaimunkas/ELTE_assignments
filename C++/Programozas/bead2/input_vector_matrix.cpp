#include <iostream>
#include <vector>
#include <limits>
#include "input_vector_matrix.h"

void input_vector_matrix(int &i_in, int &j_in, std::vector< std::vector<int> > &vec){

    int i_max, j_max;
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Towns' number: ";
        std::cin >> i_max;
    }while(i_max < 0 || std::cin.fail());
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Bird species' number: ";
        std::cin >> j_max;
    }while(j_max < 0 || std::cin.fail());
    i_in = i_max;
    j_in = j_max;
    vec.resize(i_max);
        for(int i = 0; i < i_max; i++){
            vec[i].resize(j_max);
            for(int j = 0; j < j_max; j++){
                do{
                    if(std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << i + 1 << ". town's " << j + 1 << ". bird species' number: ";
                    std::cin >> vec[i][j];
                }while(vec[i][j] < 0 || std::cin.fail());
            }
        }
}

