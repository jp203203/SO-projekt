#include <algorithm>
#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(){
    timer = Timer();
    gen_sort = GenerationSort();

    cost_matrix = nullptr;
    problem_size = 0;
    mutation_rate = 0;
    crossover_rate = 0;
    population_size = 0;
    crossover_method = 0;
    mutation_method = 0;

    random_device rand;
    gen = mt19937(rand());
}

//funkcja obliczająca koszt chromosomu (cyklu)
int GeneticAlgorithm::calculateCost(const vector<int>& sequence) {
    int cost = 0;
    for(int i = 0; i < problem_size; i++) {
        cost += cost_matrix[sequence[i]][sequence[(i + 1) % problem_size]];
    }

    return cost;
}

//obliczanie różnorodności generacji
float GeneticAlgorithm::calculateDiversity(const std::vector<Chromosome> &generation) {
    set<vector<int>> unique_sequences;
    for(const Chromosome& chromosome : generation) {
        unique_sequences.insert(chromosome.sequence);
    }

    return (float)(unique_sequences.size()) / population_size;
}

//funkcja wyznaczająca potomka na podstawie krzyżowania OX
vector<int> GeneticAlgorithm::OXCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    uniform_int_distribution random_number(0, problem_size);
    int a = random_number(gen);
    int b = random_number(gen);
    while(b == a) {
        b = random_number(gen);
    }

    vector<int> offspring(problem_size, -1);
    for(int i = min(a, b); i < max(a, b); i++) {
        offspring[i] = parent1[i];
    }

    int p1_iterator = max(a, b);
    int p2_iterator = max(a, b);

    while(p1_iterator < problem_size + min(a, b)) {
        bool in_segment = false;
        for(int i = min(a, b); i < max(a, b); i++) {
            if(parent2[p2_iterator % problem_size] == parent1[i]) {
                in_segment = true;
                break;
            }
        }
        if(in_segment) {
            p2_iterator++;
            continue;
        } else {
            offspring[p1_iterator % problem_size] = parent2[p2_iterator % problem_size];
            p2_iterator++;
            p1_iterator++;
        }
    }

    return offspring;
}

//funkcja wyznaczająca potomka na podstawie krzyżowania SCX
vector<int> GeneticAlgorithm::SCXCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    vector<int> offspring;
    offspring.reserve(problem_size);
    unordered_set<int> used_cities;

    int current_city = parent1[0];
    offspring.push_back(current_city);
    used_cities.insert(current_city);

    while(offspring.size() < problem_size) {
        int p1_next_city = -1;
        int p2_next_city = -1;

        for(int i = 0; i < problem_size; i++) {
            if(current_city == parent1[i]) {
                p1_next_city = parent1[(i + 1) % problem_size];
            }
            if(current_city == parent2[i]) {
                p2_next_city = parent2[(i + 1) % problem_size];
            }
        }

        int min_cost = INT_MAX;
        int next_city = -1;
        if(used_cities.find(p1_next_city) == used_cities.end() && cost_matrix[current_city][p1_next_city] < min_cost) {
            next_city = p1_next_city;
            min_cost = cost_matrix[current_city][p1_next_city];
        }
        if(used_cities.find(p2_next_city) == used_cities.end() && cost_matrix[current_city][p2_next_city] < min_cost) {
            next_city = p2_next_city;
        }
        if(used_cities.find(p1_next_city) != used_cities.end() && used_cities.find(p2_next_city) != used_cities.end()) {
            for(int i = 0; i < problem_size; i++) {
                if(used_cities.find(i) == used_cities.end()) {
                    next_city = i;
                    break;
                }
            }
        }

        offspring.push_back(next_city);
        used_cities.insert(next_city);
        current_city = next_city;
    }

    return offspring;
}

//mutacja potomka poprzez zamianę dwóch losowych elementów
void GeneticAlgorithm::mutateSwap(vector<int>& sequence) {
    uniform_int_distribution random_number(0, problem_size - 1);
    int a = random_number(gen);
    int b = random_number(gen);
    while(a == b) {
        b = random_number(gen);
    }

    swap(sequence[a], sequence[b]);
}

//mutacja potomka poprzez odwrócenie kolejności odcinka w cyklu
vector<int> GeneticAlgorithm::mutateInsert(const vector<int>& sequence) {
    vector<int> new_sequence(problem_size, -1);

    uniform_int_distribution random_number(0, problem_size - 1);
    int a = random_number(gen);
    int b = random_number(gen);
    while(b == a || b == a - 1) {
        b = random_number(gen);
    }

    int j = 0;
    for(int i = 0; i < problem_size; i++) {
        if(i == a) {
            continue;
        }
        new_sequence[j] = sequence[i];
        j++;
        if(i == b) {
            new_sequence[j] = sequence[a];
            j++;
        }
    }

    return new_sequence;
}

//mutacja przez losowe przestawianie elementów w odcinku
void GeneticAlgorithm::mutateShuffle(vector<int>& sequence) {
    uniform_int_distribution random_number(0, problem_size - 1);
    int a = random_number(gen);
    int b = random_number(gen);
    while(abs(a - b) < 0.25 * problem_size) {
        a = random_number(gen);
        b = random_number(gen);
    }

    if(a > b) swap(a, b);

    shuffle(sequence.begin() + a, sequence.begin() + b, gen);
}

//turniej selekcji rodziców kolejnych cykli/sekwencji
pair<vector<int>, vector<int>> GeneticAlgorithm::selectionTournament(const vector<Chromosome>& generation) {
    uniform_int_distribution random_number(0, population_size - 1);
    uniform_real_distribution<> probability_roll(0, 1);

    set<int> unique_indices;
    while(unique_indices.size() < 4) {
        unique_indices.insert(random_number(gen));
    }

    vector<Chromosome> parent_candidates;
    for(int index : unique_indices) {
        parent_candidates.emplace_back(generation[index]);
    }

    gen_sort.sort(4, parent_candidates);

    if(probability_roll(gen) < 0.65) {
        return {parent_candidates[0].sequence, parent_candidates[1].sequence};
    } else {
        return {parent_candidates[1].sequence, parent_candidates[2].sequence};
    }

}

//inicjalizacja początkowej generacji
vector<GeneticAlgorithm::Chromosome> GeneticAlgorithm::initialGeneration() {
    vector<Chromosome> generation;
    generation.reserve(population_size);

    for(int i = 0; i < population_size; i++) {
        vector<int> sequence(problem_size, 0);
        for(int j = 0; j < problem_size; j++) {
            sequence[j] = j;
        }

        shuffle(sequence.begin(), sequence.end(), gen);
        generation.emplace_back(sequence, *this);
    }

    gen_sort.sort(population_size, generation);
    return generation;
}

//inicjalizacja nowej generacji
vector<GeneticAlgorithm::Chromosome> GeneticAlgorithm::newGeneration(vector<Chromosome>& old_generation) {
    uniform_real_distribution<> probability_roll(0, 1);

    vector<Chromosome> new_generation;
    new_generation.reserve(population_size);

    int old_gen_index = 0;
    new_generation.push_back(old_generation[old_gen_index++]);
    int gen_size = 1;

    for(int i = 0; i < population_size / 2; i++) {
        if(probability_roll(gen) <= crossover_rate) {
            auto parents = selectionTournament(old_generation);
            auto parent1 = parents.first;
            auto parent2 = parents.second;

            vector<int> child1, child2;
            if(crossover_method == 1) {
                child1 = OXCrossover(parent1, parent2);
                child2 = OXCrossover(parent2, parent1);
            } else if(crossover_method == 2) {
                child1 = SCXCrossover(parent1, parent2);
                child2 = SCXCrossover(parent2, parent1);
            }

            if(probability_roll(gen) <= mutation_rate) {
                if(mutation_method == 1) {
                    mutateSwap(child1);
                } else if(mutation_method == 2) {
                    child1 = mutateInsert(child1);
                }
            }
            if(probability_roll(gen) <= mutation_rate) {
                if(mutation_method == 1) {
                    mutateSwap(child2);
                } else if(mutation_method == 2) {
                    child2 = mutateInsert(child2);
                }
            }

            new_generation.emplace_back(child1, *this);
            gen_size++;
            if(gen_size == population_size) break;
            new_generation.emplace_back(child2, *this);
            gen_size ++;
            if(gen_size == population_size) break;
        }
    }

    for(; gen_size < population_size; gen_size++) {
        new_generation.push_back(old_generation[old_gen_index++]);
    }

    gen_sort.sort(population_size, new_generation);
    return new_generation;
}

//restart populacji - zachowane jest 20% najlepszych członków poprzedniej generacji
void GeneticAlgorithm::mutatePopulation(std::vector<Chromosome>& generation) {
    int elite_size = 0.3 * population_size;
    for(int i = elite_size; i < population_size; i++) {
        mutateShuffle(generation[i].sequence);
        generation[i].cost = calculateCost(generation[i].sequence);
    }

    gen_sort.sort(population_size, generation);
}

//obliczenie średniej kosztów z populacji
float GeneticAlgorithm::costAverage(const vector<Chromosome>& generation) {
    float average = 0;
    for(int i = 0; i < population_size; i++) {
        average += (float)generation[i].cost;
    }
    average /= population_size;

    return average;
}

//główna funkcja algorytmu
pair<int, vector<float>> GeneticAlgorithm::findGeneticSolution(int** cost_matrix, int problem_size,
                                                             int population_size, int stop_criterion,
                                                             float mutation_rate, float crossover_rate,
                                                             int mutation_method, int crossover_method,
                                                             int time_interval) {
    this -> cost_matrix = cost_matrix;
    this -> problem_size = problem_size;
    this -> population_size = population_size;
    this -> mutation_rate = mutation_rate;
    this -> crossover_rate = crossover_rate;
    this -> mutation_method = mutation_method;
    this -> crossover_method = crossover_method;
    int next_measure = time_interval;

    vector<float> cost_evolution;

    auto current_generation = initialGeneration();
    int best_cost = current_generation[0].cost;
    cost_evolution.push_back(costAverage(current_generation));

    timer.start();

    while(true) {
        timer.stop();
        if(timer.getTime() >= next_measure) {
            float average = costAverage(current_generation);
            cost_evolution.push_back(average);
            next_measure += time_interval;
        }

        if(timer.getTime() >= stop_criterion) {
            break;
        }

        float diversity = calculateDiversity(current_generation);
        if(diversity < 0.2) {
            mutatePopulation(current_generation);
        } else {
            current_generation = newGeneration(current_generation);
        }

        if(current_generation[0].cost < best_cost) best_cost = current_generation[0].cost;
    }

    return {best_cost, cost_evolution};
}


GeneticAlgorithm::GenerationSort::GenerationSort() {
    population_size = 0;
}


void GeneticAlgorithm::GenerationSort::buildHeap(std::vector<GeneticAlgorithm::Chromosome>& generation) {
    int parent = (population_size - 2) / 2;
    while(parent >= 0) {
        fixHeapDown(generation, parent, population_size);
        parent--;
    }
}


void GeneticAlgorithm::GenerationSort::fixHeapDown(std::vector<GeneticAlgorithm::Chromosome>& generation, int parent, int size) {
    int smallest = parent;
    int l_child = parent * 2 + 1;
    int r_child = l_child + 1;

    if(l_child < size && generation[l_child].fitness_value < generation[smallest].fitness_value) {
        smallest = l_child;
    }
    if(r_child < size && generation[r_child].fitness_value < generation[smallest].fitness_value) {
        smallest = r_child;
    }

    if(smallest != parent) {
        std::swap(generation[parent], generation[smallest]);
        fixHeapDown(generation, smallest, size);
    }
}


void GeneticAlgorithm::GenerationSort::sort(int size, std::vector<GeneticAlgorithm::Chromosome>& generation) {
    population_size = size;
    buildHeap(generation);

    size--;
    while(size > 0) {
        std::swap(generation[0], generation[size]);
        fixHeapDown(generation, 0, size);
        size--;
    }
}