// pp2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SortTestClass.h"
#include "AbstractSorter.h"
#include "LinearMergeSorter.h"
#include "LinearShellSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"
#include "SortRunner.h"

using namespace std;


int main(int argc, char *argv[])
{
    SortTest();

    //string str = argv[0];
    //str = argv[1];
    //ifstream file(argv[1]);
    //SortRunner<int>::Sort(file);

    return 0;
}

