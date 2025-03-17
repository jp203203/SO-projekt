#include <fstream>
#include <iostream>
#include <iomanip>
#include "FileManager.h"
#include "ArrayManager.h"

template <typename T>
FileManager<T>::FileManager() {}

template <typename T>
T* FileManager<T>::readArray(std::string filepath){
    std::ifstream file(filepath+".txt");

    if(!file.is_open())
    {
        std::cerr<<"Nie mozna otworzyc pliku!"<<std::endl;
        return nullptr;
    }

    int size;
    file >> size;

    T* array = new T[size];

    for(int i = 0; i < size; ++i)
    {
        if(!(file >> array[i]))
        {
            std::cerr<<"Blad odczytu z pliku!"<<std::endl;
            delete[] array;
            return nullptr;
        }
    }

    file.close();
    return array;
}

template <typename T>
int FileManager<T>::getArrSize(std::string filepath){
    std::ifstream file(filepath+".txt");

    if(!file.is_open())
    {
        std::cerr<<"Nie mozna otworzyc pliku!"<<std::endl;
        return 0;
    }

    int size;
    file >> size;

    return size;
}

template <typename T>
void FileManager<T>::saveArray(T* array, int size){

    std::cout<<"Zapis tablicy\n";

    std::string filepath;
    std::cout<<"Wybierz nazwe/sciezke dla pliku"<<std::endl;
    std::cin>>filepath;

    std::ifstream checkFile(filepath+".txt");
    if(checkFile.good())
    {
        std::cerr<<"Podany plik już istnieje!"<<std::endl;
        return;
    }

    std::ofstream file(filepath+".txt");
    if(!file.is_open())
    {
        std::cerr<<"Nie można otworzyć pliku!"<<std::endl;
        return;
    }

    file << size << "\n";

    for(int i = 0; i < size; ++i)
    {
        file << array[i] << "\n";
    }

    file.close();
    std::cout<<"Zapisano tablice do pliku"<<std::endl;
}

template <typename T>
void FileManager<T>::saveTimes(double time, int index, std::string filepath){

    std::ofstream file(filepath, std::ios_base::app);
    if(!file.is_open()){
        std::cerr<<"Nie można otworzyć pliku!"<<std::endl;
        return;
    }

    std::cout<<std::fixed<<std::showpoint<<std::setprecision(5);
    file<<index<<";"<<time<<std::endl;
}

template class FileManager<int>;
template class FileManager<float>;