#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <chrono>
#pragma warning(disable : 4996)

using namespace std;
using namespace std::chrono;

struct Task
{
    int machine;
    int time;
};

int main()
{
    int type;
    cout<<"to pierwsze wpisz 1"<<endl;
    cout<<"tailard wpisz 2"<<endl;
    cin>>type;
    int jobs, machines;
    cin >> jobs >> machines;
    int gen_num = jobs * machines;
    int pop = 100;
    int iter = 1000;
    int best, best_gen;
    float mutation = 0.2;
    float crossover = 0.8;
    int mutation_index[5];
    srand(time(NULL));
    struct Task** operations = new struct Task*[jobs];
    struct Task task;

    if (type == 1)
    {
        for (int i = 0; i < jobs; i++)
        {
            operations[i] = new struct Task[machines];
            for (int j = 0; j < machines; j++)
            {
                cin >> task.machine;
                cin >> task.time;
                operations[i][j] = task;
            }
        }
    }
    else
    {
        int** imachine = new int*[jobs];
        int** itime = new int*[jobs];
        for (int i = 0; i < jobs; i++)
        {
            itime[i] = new int[machines];
            for (int j = 0; j < machines; j++)
            {
                cin >> itime[i][j];
                //cout << itime[i][j] << "\t";


            }
        }
        for (int i = 0; i < jobs; i++)
        {
            imachine[i] = new int [machines];
            for (int j = 0; j < machines; j++)
            {
                cin >> imachine[i][j];
                //cout << imachine[i][j] << "\t";

            }
        }

        for (int i = 0; i < jobs; i++)
        {
            operations[i] = new struct Task[machines];
            for (int j = 0; j < machines; j++)
            {
                cout << imachine[i][j]-1 << " "<< itime[i][j]<<" ";

                task.machine = imachine[i][j]-1;
                task.time = itime[i][j];
                operations[i][j] = task;
            }
            cout<<endl;
        }
    }
    //////////////////////////////////////////
    int** population = new int* [pop];
    int** crossed = new int*[pop];
    int** selected = new int* [pop];

    int* fitness = new int [pop];
    int* fitness_pop = new int [pop];
    int* machines_time = new int [machines];
    int* jobs_time = new int [jobs];
    //cout<<"Printing generated pop"<<endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i <pop; i++)
    {
        population[i] = new int[gen_num];
        crossed[i] = new int[gen_num];
        selected[i] = new int[gen_num];
        int *temp = new int [gen_num];
        int random_index;
        for (int z = 0; z < gen_num; z++)
        {
            temp[z]=1;
        }
        for (int j = 0; j<gen_num; j++)
        {
            while(true)
            {
                random_index = rand()%gen_num;
                if(temp[random_index])
                {
                    population[i][j]=random_index;
                    temp[random_index]=0;
                    break;
                }
            }
        }

        for (int j = 0; j<gen_num; j++)
        {
            population[i][j] = population[i][j]%jobs;
            //cout<<population[i][j];

        }
        //cout<<endl;
        delete[] temp;
    }
    for (int a = 0; a < iter; a++)
    {
        int slicer_a, slicer_b;
        for (int i  = 0; 2*i< pop; i++)
        {
            slicer_a = rand()%gen_num;
            slicer_b = rand()%gen_num;
            if (slicer_a > slicer_b)
                swap(slicer_a, slicer_b);
            if(crossover > float(rand()%100/100))
            {
                for (int j = 0; j<gen_num; j++)
                {
                    if(j>= slicer_a && j<=slicer_b)
                    {
                        crossed[i*2][j]=population[i*2+1][j];
                        crossed[i*2+1][j]=population[i*2][j];
                    }
                    else
                    {
                        crossed[i*2][j]=population[i*2][j];
                        crossed[i*2+1][j]=population[i*2+1][j];
                    }

                }

            }
            else
                for (int j = 0; j<gen_num; j++)
                {
                    crossed[i*2][j]=population[i*2][j];
                    crossed[i*2+1][j]=population[i*2+1][j];
                }

        }
        /*cout<<"Printing crossed pop"<<endl;
        for(int i=0; i<pop; i++)
        {
            for (int j = 0; j<gen_num; j++)
            {
                cout<<crossed[i][j];
            }
            cout<<endl;

        }*/
        for(int i=0; i<pop; i++)
        {
            int* occurance = new int [jobs];
            for (int j = 0; j<jobs; j++)
            {
                occurance[j]=0;
            }
            for (int j =0; j<gen_num; j++)
            {
                occurance[crossed[i][j]]++;
            }
            bool fixed = false;
            while(!fixed)
            {
                int over = -1;
                int below = -1;
                for (int j =0; j<jobs; j++)
                {
                    if (occurance[j] > machines)
                    {
                        over = j;
                    }
                    else if (occurance[j] < machines)
                    {
                        below = j;
                    }
                    if(over!=-1 && below!=-1)
                    {
                        int left = slicer_a;
                        bool swapped_over = false;
                        while(!(swapped_over))
                        {
                            if (crossed[i][left] == over)
                            {
                                swapped_over = true;
                                crossed[i][left] =  below;
                                occurance[over]--;
                                occurance[below]++;
                            }
                            left++;
                        }
                        break;
                    }
                }
                if(over == -1 && below == -1)
                {
                    delete[] occurance;
                    break;
                }

            }
        }
        /*cout<<"Printing repaired pop"<<endl;
        for(int i=0; i<pop; i++)
        {
            for (int j = 0; j<gen_num; j++)
            {
                cout<<crossed[i][j];
            }
            cout<<endl;
        }*/
        for(int i =0; i <pop; i++)
        {
            if (mutation>=float(rand()%100/100))
            {

                for (int j = 0; j<*(&mutation_index+1)-mutation_index; j++)
                {
                    mutation_index[j]=rand()%gen_num;
                }

                for (int j = 0; j<*(&mutation_index+1)-mutation_index-1; j++)
                {
                    swap(crossed[i][mutation_index[j]],crossed[i][mutation_index[j+1]]);
                }
            }

        }
        /*cout<<"Printing mutated pop"<<endl;
        for(int i=0; i<pop; i++)
        {
            for (int j = 0; j<gen_num; j++)
            {
                cout<<crossed[i][j];
            }
            cout<<endl;

        }*/

        for(int i=0; i<pop; i++)
        {
            queue<Task> *first = new queue<Task>[jobs];
            for(int i=0; i<jobs; i++)
            {
                for(int j=0; j<machines; j++)
                {
                    first[i].push(operations[i][j]);
                }
            }
            int m;
            int t;
            Task tmp;
            for(int j = 0; j<machines; j++)
                machines_time[j] = 0;
            for(int j = 0; j<jobs; j++)
                jobs_time[j] = 0;
            for (int j = 0; j<gen_num; j++)
            {
                m = first[crossed[i][j]].front().machine;
                t = first[crossed[i][j]].front().time;
                tmp = first[crossed[i][j]].front();
                first[crossed[i][j]].push(tmp);
                first[crossed[i][j]].pop();
                int start;

                if(machines_time[m] > jobs_time[crossed[i][j]])
                    start = machines_time[m];
                else
                    start = jobs_time[crossed[i][j]];
                int endd = start + t;
                machines_time[m] = endd;
                jobs_time[crossed[i][j]] = endd;

            }
            int max_time = 0;
            for(int j=0; j<machines; j++)
            {
                if(machines_time[j]>max_time)
                    max_time = machines_time[j];
            }
            fitness[i]= max_time;
            delete[] first;
            /*cout<<fitness[i]<<" ";
            for(int j = 0; j<gen_num; j++)
                cout<<crossed[i][j];
            cout<<endl;*/
        }
        for(int i=0; i<pop; i++)
        {
            queue<Task> *first = new queue<Task>[jobs];
            for(int i=0; i<jobs; i++)
            {
                for(int j=0; j<machines; j++)
                {
                    first[i].push(operations[i][j]);
                }
            }
            int m;
            int t;
            Task tmp;
            for(int j = 0; j<machines; j++)
                machines_time[j] = 0;
            for(int j = 0; j<jobs; j++)
                jobs_time[j] = 0;
            for (int j = 0; j<gen_num; j++)
            {
                m = first[population[i][j]].front().machine;
                t = first[population[i][j]].front().time;
                tmp = first[population[i][j]].front();
                first[population[i][j]].push(tmp);
                first[population[i][j]].pop();
                int start;

                if(machines_time[m] > jobs_time[population[i][j]])
                    start = machines_time[m];
                else
                    start = jobs_time[population[i][j]];
                int endd = start + t;
                machines_time[m] = endd;
                jobs_time[population[i][j]] = endd;

            }
            int max_time = 0;
            for(int j=0; j<machines; j++)
            {
                if(machines_time[j]>max_time)
                    max_time = machines_time[j];
            }
            fitness_pop[i]= max_time;
            delete[] first;
            /*cout<<fitness_pop[i]<<" ";
            for(int j = 0; j<gen_num; j++)
                cout<<population[i][j];
            cout<<endl;*/
        }
        /*cout<<"Printing fitness score"<<endl;
        for(int z = 0; z<pop; z++)
            cout<<fitness[z]<< " "<<fitness_pop[z]<< " ";
        cout<<endl;*/
        for (int j = 0; 2*j<pop; j++)
        {
            int min_fitness = 2147483647;
            int min_index;
            for(int z = 0; z<pop; z++)
            {
                if(fitness[z]<min_fitness)
                {
                    min_fitness = fitness[z];
                    min_index = z;
                    if(j==0)
                    {
                        best_gen = z;
                        best=fitness[z];
                    }
                }
            }
            //cout<<"notfrompop " <<min_fitness<< " "<<min_index<<" ";
            for(int z = 0; z<gen_num; z++)
            {
                selected[j][z]= crossed[min_index][z];
                //cout<<selected[j][z];
            }
            fitness[min_index] = 2147483647;
            //cout<<endl;
        }
        for (int j = pop/2; j<pop; j++)
        {
            int min_fitness = 2147483647;
            int min_index;
            for(int z = 0; z<pop; z++)
            {
                if(fitness_pop[z]<min_fitness)
                {
                    min_fitness = fitness_pop[z];
                    min_index = z;
                    if(fitness_pop[z] < best)
                    {
                        best = fitness_pop[z];
                        best_gen = z;
                    }

                }
            }
            fitness_pop[min_index] = 2147483647;
            //cout<<"frompop " <<min_fitness<< " "<<min_index<<" ";
            for(int z = 0; z<gen_num; z++)
            {
                selected[j][z]= population[min_index][z];
                //cout<<selected[j][z];
            }
            //cout<<endl;
        }
        for (int z = 0; z<pop; z++)
        {
            for(int j = 0; j<gen_num; j++)
            {
                population[z][j] = selected[z][j];
            }
        }
        cout<<"loop done"<<a<<endl;
    }

    queue<Task> *first = new queue<Task>[jobs];
    for(int i=0; i<jobs; i++)
    {
        for(int j=0; j<machines; j++)
        {
            first[i].push(operations[i][j]);
        }
    }
    int m;
    int t;
    for(int j = 0; j<machines; j++)
        machines_time[j] = 0;
    for(int j = 0; j<jobs; j++)
        jobs_time[j] = 0;
    for (int j = 0; j<gen_num; j++)
    {
        m = first[population[best_gen][j]].front().machine;
        t = first[population[best_gen][j]].front().time;
        first[population[best_gen][j]].pop();
        int start;

        if(machines_time[m] > jobs_time[population[best_gen][j]])
            start = machines_time[m];
        else
            start = jobs_time[population[best_gen][j]];
        int endd = start + t;
        machines_time[m] = endd;
        jobs_time[population[best_gen][j]] = endd;

    }
    int max_time = 0;
    for(int j=0; j<machines; j++)
    {
        if(machines_time[j]>max_time)
            max_time = machines_time[j];
    }
    auto stop = high_resolution_clock::now();
    cout<<"MAKESPAN "<<max_time<<endl;
    for(int j = 0; j<gen_num; j++)
        cout<<population[best_gen][j]<<" ";
    cout<<endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    return 0;
}

