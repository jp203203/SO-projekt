#ifndef AIZO_PROJEKT2_SETS_H
#define AIZO_PROJEKT2_SETS_H


class Sets {
private:
    int* parent;
    int* rank;
    int no_of_vertexes;

public:
    Sets(int no_of_vertexes);
    ~Sets();

    int findSet(int u);
    void mergeSets(int u, int v);
};


#endif //AIZO_PROJEKT2_SETS_H
