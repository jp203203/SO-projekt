#ifndef PEA_PROJEKT2_GENETICALGORITHM_H
#define PEA_PROJEKT2_GENETICALGORITHM_H

#include <vector>
#include <set>
#include <unordered_set>
#include <random>
#include <queue>
#include "Timer.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm();
    std::pair<int, std::vector<float>> findGeneticSolution(int** cost_matrix, int problem_size,
                                                         int population_size, int stop_criterion, float mutation_rate,
                                                         float crossover_rate, int mutation_method,
                                                         int crossover_method, int time_interval);

    struct Chromosome{
        std::vector<int> sequence;
        int cost;
        float fitness_value;

        explicit Chromosome(std::vector<int>& sequence, GeneticAlgorithm& ga) {
            this -> sequence = sequence;
            cost = ga.calculateCost(sequence);
            fitness_value = float(10) / float(cost);
        };

    };




private:
    Timer timer;

    int crossover_method;
    int mutation_method;
    int** cost_matrix;
    int problem_size;
    float mutation_rate;
    float crossover_rate;
    int population_size;

    std::mt19937 gen;

    int calculateCost(const std::vector<int>& sequence);
    float calculateDiversity(const std::vector<Chromosome>& generation);
    std::vector<int> OXCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    std::vector<int> SCXCrossover(const vector<int> &parent1, const vector<int> &parent2);
    void mutateSwap(std::vector<int>& sequence);
    std::vector<int> mutateInsert(const std::vector<int>& sequence);
    void mutateShuffle(std::vector<int>& sequence);
    std::pair<std::vector<int>, std::vector<int>> selectionTournament(const std::vector<Chromosome>& generation);
    std::vector<Chromosome> initialGeneration();
    std::vector<Chromosome> newGeneration(std::vector<Chromosome>& old_generation);
    void mutatePopulation(std::vector<Chromosome>& generation);
    float costAverage(const vector<Chromosome> &generation);

    class GenerationSort {
    public:
        GenerationSort();
        void sort(int population_size, std::vector<GeneticAlgorithm::Chromosome>& generation);

    private:
        int population_size;

        void buildHeap(std::vector<Chromosome>& generation);
        void fixHeapDown(std::vector<Chromosome>& generation, int parent, int size);
    };

    GenerationSort gen_sort;
};


#endif //PEA_PROJEKT2_GENETICALGORITHM_H
