#include <iostream>
#include <vector>
#include <ctime>

#include "Sort.h"
#include "Participant.h"

using namespace std;

int main()
{
    srand(time(0));

    const int N = 10;

    vector<int> values(N);
    int* ptrs[N];

    for (int i = 0; i < N; i++)
    {
        values[i] = rand() % 100;
        ptrs[i] = &values[i];
    }

    cout << "Original:\n";
    for (int i = 0; i < N; i++)
        cout << *ptrs[i] << " ";

    cout << "\n\n";

   
    int* ptrs_shell[N];
    int* ptrs_quick[N];
    int* ptrs_insert[N];

    for (int i = 0; i < N; i++)
    {
        ptrs_shell[i] = ptrs[i];
        ptrs_quick[i] = ptrs[i];
        ptrs_insert[i] = ptrs[i];
    }

    long comp_shell = Sort<int>::shellSort(ptrs_shell, N);

    cout << "Shell Sort:\n";
    for (int i = 0; i < N; i++)
        cout << *ptrs_shell[i] << " ";
    cout << "\nComp: " << comp_shell << "\n\n";

    long comp_quick = Sort<int>::quickSort(ptrs_quick, 0, N - 1);

    cout << "Quick Sort:\n";
    for (int i = 0; i < N; i++)
        cout << *ptrs_quick[i] << " ";
    cout << "\nComp: " << comp_quick << "\n\n";

    long comp_insert = Sort<int>::insertionSort(ptrs_insert, N);

    cout << "Insertion Sort:\n";
    for (int i = 0; i < N; i++)
        cout << *ptrs_insert[i] << " ";
    cout << "\nComp: " << comp_insert << endl;

    
    const int M = 5;

    vector<Participant> people(M);
    Participant* pptr[M];

    for (int i = 0; i < M; i++)
        pptr[i] = &people[i];

    cout << "\nParticipants:\n";
    Participant::printHeader();

    for (int i = 0; i < M; i++)
        cout << *pptr[i] << endl;

    Sort<Participant>::insertionSort(pptr, M);

    cout << "\nSorted Participants:\n";
    Participant::printHeader();

    for (int i = 0; i < M; i++)
        cout << *pptr[i] << endl;

    return 0;
}