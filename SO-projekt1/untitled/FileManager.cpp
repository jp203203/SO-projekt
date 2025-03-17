#include <fstream>
#include <iostream>
#include "FileManager.h"
#include "ArrayManager.h"

ArrayManager am;

FileManager::FileManager(ArrayManager arrayManager) {
    am = arrayManager;
}

int* FileManager::readArray(std::string filepath){
    std::ifstream file(filepath+".txt");

    if(!file.is_open())
    {
        std::cerr<<"Nie mozna otworzyc pliku!"<<std::endl;
        return nullptr;
    }

    int size = 0;
    std::string line;
    while(getline(file, line))
    {
        size++;
    }

    file.clear();
    file.seekg(0, std::ios::beg);

    int * array = new int[size];

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

int FileManager::getArrSize(std::string filepath){
    std::ifstream file(filepath+".txt");

    if(!file.is_open())
    {
        std::cerr<<"Nie mozna otworzyc pliku!"<<std::endl;
        return 0;
    }

    int size = 0;
    std::string line;
    while(getline(file, line))
    {
        size++;
    }

    return size;
}

void FileManager::saveArray(int* array, int size, bool isSorted){
    if(isSorted)
    {
        std::cout<<"Zapis posortowanej tablicy"<<std::endl;
    } else
    {
        std::cout<<"Zapis wygenerowanej tablicy"<<std::endl;
    }

    std::string filepath;
    std::cout<<"Wybierz nazwe/sciezke dla pliku"<<std::endl;
    std::cin>>filepath;

    std::ifstream checkFile(filepath+".txt");
    if(checkFile.good() && !isSorted)
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

    for(int i = 0; i < size; ++i)
    {
        file<<array[i]<<"\n";
    }

    file.close();
    std::cout<<"Zapisano tablice do pliku"<<std::endl;
}

void FileManager::saveTimes(double time, int index, std::string filepath){

    std::ofstream file(filepath, std::ios_base::app);
    if(!file.is_open()){
        std::cerr<<"Nie można otworzyć pliku!"<<std::endl;
        return;
    }

    file<<index<<";"<<time<<std::endl;
}
