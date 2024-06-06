#include <iostream>
#include <fstream>
#include <vector>
#include <stdbool.h>
#include <cstdlib>
#include "time.h"


void saveMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    std::streampos fileSize = 0;

    int numRows = matrix.size();
    int numCols = (numRows > 0) ? matrix[0].size() : 0;

    for (const auto& row : matrix) {
        file.write((char*)row.data(), sizeof(int) * row.size());
        fileSize += sizeof(int) * row.size();
    }
    file.close();
    std::cout << filename << " saved, total memory: " << fileSize << " bytes, rows: " << numRows << ", columns: " << numCols << std::endl;
}

std::vector<std::vector<int>> loadMatrixFromFile(const std::string& filename, int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    std::ifstream file(filename, std::ios::binary);
    for (auto& row : matrix) {
        file.read((char*)row.data(), sizeof(int) * cols);
    }
    file.close();
    return matrix;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << std::endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> matrixMult(const std::vector<std::vector<int>>& m1, 
                                         const std::vector<std::vector<int>>& m2) {

    int rows1 = m1.size();
    int cols1 = m1[0].size();
    int cols2 = m2[0].size();

    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

void saveResult(const std::vector<std::vector<int>>& matrix, const double& time, const int& r1, const int& c1, const int& c2) {

    std::string filename = "res.txt";
    std::ofstream file(filename);

    double volume = r1 * c1 * c2;

    for (const auto& row : matrix) {
        for (int num : row) {
            file << num << " ";
        }
        file << "\n";
    }

    file << "\n";
    file << "Calculation time: " << time << " seconds." << std::endl;
    file << "Number of multiplication operations: " << volume << std::endl;
    file << "Number of saves to memory: " << volume << std::endl;
    file << "Number of downloads from memory: " << 2 * volume << std::endl;
    file.close();
}

int main() {

    srand(time(nullptr));

    bool SaveToFile = false;
    // Возведение матрицы в степень
    int st = 5;
    // Задание матрицы
    std::vector<int> s = {500, 500};

    std::string m_filename = "matrix.bin";
    std::ifstream iff;
    iff.open("matrix.bin");
    // Если нет матрицы в "matrix.bin", генерируем ее (-5...5)
    if (!iff) {
        std::vector<std::vector<int>> m(s[0], std::vector<int>(s[1]));
        std::vector<std::vector<int>> itog(s[0], std::vector<int>(s[1]));
        for (int i = 0; i < s[0]; i++) {
            for (int j = 0; j < s[1]; j++) {
                m[i][j] = rand()%11 - 5;
            }
        }
        saveMatrixToFile(m, m_filename);
    }
    std::vector<std::vector<int>> m = loadMatrixFromFile(m_filename, s[0], s[1]);
    std::vector<std::vector<int>> itog = m;

    clock_t start;
    start = clock();
    for (int i = 1; i < st; i++) {
        std::cout << i << "/" << st << std::endl;
        //printMatrix(itog);
        std::vector<std::vector<int>> result = matrixMult(itog, m);
        itog = result;
    }

    double time = double(clock() - start) / CLOCKS_PER_SEC;
    saveResult(itog, time, s[0], s[1], s[1]);

    //printMatrix(m);
    //printMatrix(itog);

    std::cout << std::endl << "Calculation time: " << time << " seconds." << std::endl;
    std::cout << "Number of multiplication operations: " << 4*s[0]*s[1]*s[1]*2 << std::endl;

    return 0;
}
