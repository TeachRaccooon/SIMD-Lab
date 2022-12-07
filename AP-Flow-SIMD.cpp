#include "AP-Flow.h"

void APFlow::CalcFlow()
{
  int i, j, v, f;

  for (i = 0; i < N*N; i++) Flow[i] = Adj[i];

    for (v = 0; v < N; ++v) 
    {
        for (i = 0; i < N; ++i) 
        {
            for (j = 0; j < N; ++j) 
            {
                /* f is the flow from i to j through v */
                f = (Flow[i * N + v] < Flow[v * N + j]) ? Flow[i * N + v] : Flow[v * N + j];
                if (f > Flow[i * N + j]) Flow[i * N + j] = f;
            }   
        }
    }
}