#include "AP-Flow.h"
// Yo isnt this the last name of that dude from Breaking Bad??
#include <emmintrin.h>

void APFlow::CalcFlow()
{

    /*
    // From da notes 

    int i, j, v, f;

    for (i = 0; i < N*N; i++) Flow[i] = Adj[i];

    for (v = 0; v < N; ++v) 
    {
        for (i = 0; i < N; ++i) 
        {
            for (j = 0; j < N; ++j) 
            {
                // f is the flow from i to j through v
                f = (Flow[i * N + v] < Flow[v * N + j]) ? Flow[i * N + v] : Flow[v * N + j];
                if (f > Flow[i * N + j]) Flow[i * N + j] = f;
            }   
        }
    }
    */


    int i, j, v, f;

    // Copied from above
    for (i = 0; i < N * N; ++i) Flow[i] = Adj[i];

    for (v = 0; v < N; ++v) 
    {
        for(i = 0; i < N; ++i)
        {
            // Integer broadcast
            __m128i fl_iv = _mm_set1_epi8((unsigned char) Flow[i * N + v]);

            // So the logic below is identical to the inner loop above
            for(j = 0; j < N; j += 128 / (8 * sizeof(char)))
            {
                __m128i fl_ij = _mm_load_si128((const __m128i*)(&Flow[i * N + j]));
                __m128i fl_vj = _mm_load_si128((const __m128i*)(&Flow[v * N + j]));

                // Store smaller of two
                fl_vj = _mm_min_epu8(fl_vj, fl_iv);
                // Store larger of two
                fl_ij = _mm_max_epu8(fl_ij, fl_vj);

                // store where it belongs, just like above
                _mm_store_si128((__m128i*)(&Flow[i * N + j]), fl_ij);
            }
        }
    }
}