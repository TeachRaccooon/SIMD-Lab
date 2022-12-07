#include "The-Tips.h"



double TheTips::solve(vector <string> Cl, vector <int> probability, int print)
{
    int i, j, v;
    vector < vector <char> > C;
    vector <double> p;
    double x;
    
    C.resize(Cl.size());
    
    /* Change the Y/N's to 1/0's */

    for (i = 0; i < C.size(); i++) 
    {
        C[i].resize(Cl[i].size());
        for (j = 0; j < C.size(); j++) 
        {
            C[i][j] = (Cl[i][j] == 'Y') ? 1 : 0;
        }
        C[i][i] = 1;
    }
  
    /* Print the adjacency matrix before doing Floyd-Warshall */

    if (print) {
        printf("The Adjacency Matrix:\n\n");
        printf("    ");
        for (i = 0; i < C.size(); i++) printf("%X", i&0xf);
        printf("\n");
        printf("   -");
        for (i = 0; i < C.size(); i++) printf("-");
        printf("\n");
        for (i = 0; i < C.size(); i++) 
        {
            printf("%X | ", i&0xf);
            for (j = 0; j < C[i].size(); j++) printf("%d", C[i][j]);
            printf("\n");
        }
        printf("\n");
    }

    for (v = 0; v < C.size(); v++) 
    {
        for (i = 0; i < C.size(); i++) 
        {
            if (C[i][v]) 
            {
                for (j = 0; j < C.size(); j++) 
                {
                    C[i][j] |= C[v][j];
                }
            }
        }
    }
  

    if (print) 
    {
        printf("Probabilities:\n\n");
        for (i = 0; i < probability.size(); i++) printf("%4d", probability[i]);
        printf("\n\n");
        printf("The Floyd-Warshall Matrix:\n\n");
    
        printf("    ");
        for (i = 0; i < C.size(); i++) printf("%X", i&0xf);
        printf("\n");
        printf("   -");
        for (i = 0; i < C.size(); i++) printf("-");
        printf("\n");
        for (i = 0; i < C.size(); i++) 
        {
            printf("%X | ", i&0xf);
            for (j = 0; j < C[i].size(); j++) printf("%d", C[i][j]);
            printf("\n");
        }
        printf("\n");
    }

    /* Calculate the values of p from the probabilities and reachability: */

    p.resize(C.size(), 0);

    for (i = 0; i < C.size(); i++) 
    {
        x = probability[i];
        x /= 100.0;
        for (j = 0; j < C.size(); j++) 
        {
            if (C[i][j]) p[j] += ((1 - p[j]) * x);
        }
    }

    if (print) 
    {
        printf("\nThe Expected Values\n\n");
        for (i = 0; i < C.size(); i++) 
        {
            printf("I: %X    Prob: %7.5lf\n", i, p[i]);
        }
        printf("\n");
    }
    
    /* Calculate the final return value */

    x = 0;
    for (i = 0; i < C.size(); i++) x += p[i];
    
    return x;
}


/*
double TheTips::solve(vector <string> clues, vector <int> probability, int print)
{
    int v, i, j = 0;
    size_t size = clues.size();

    // The Floyd-Warshall Calculation
    for (v = 0; v < size; ++v) 
    {
        for (i = 0; i < size; ++i) 
        {
            if (clues[i][v]) 
            {
                for (j = 0; j < size; ++j) 
                {
                    clues[i][j] |= clues[v][j];
                }
            }
        }
    }

    // Calculate the values of p from the probabilities and reachability:
    probability.resize(size, 0);
    for (i = 0; i < size; ++i) 
    {
        print = probability[i];
        print /= 100.0;
        for (j = 0; j < size; ++j) 
        {   
            if (clues[i][j]) probability[j] += ((1 - probability[j]) * print);
        }
    }

    // Calculate the final return value
    print = 0;
    for (i = 0; i < size; ++i) print += probability[i];
    
    return print;
}
*/