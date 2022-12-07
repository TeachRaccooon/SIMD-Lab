#include "AP-Flow.h"
#include <emmintrin.h>

void APFlow::CalcFlow()
{

    int i, j, v, f;

    /*
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


    uint8_t *Flow_ptr = Flow;
    int i, j, v, f;


    for(i = 0; i < N; ++i)
    {
        Flow_ptr[i * N + i] = 0xff;
    }

    for (v = 0; v < N; ++v) 
    {
        for(i = 0; i < N; ++i)
        {
            unsigned char fl_iv = Flow[i * N + v];

            __m128i m_fl_iv;
            m_fl_iv = _mm_set1_epi8(fl_iv);

            for(j = 0; j < N; j += 128 / (8 * sizeof(char)))
            {
                __m128i m_fl_ij, m_fl_vj;
                m_fl_ij = _mm_load_si128((const __m128i*)(Flow_ptr + (i * N + j)));
                m_fl_vj = _mm_load_si128((const __m128i*)(Flow_ptr + (v * N + j)));

                // Store smaller of two
                m_fl_vj = _mm_min_epu8(m_fl_vj, m_fl_iv);
                // Store larger of two
                m_fl_ij = _mm_max_epu8(m_fl_ij, m_fl_vj);

                _mm_store_si128((__m128i*)(Flow_ptr + (i * N + j)), m_fl_ij);
            }
        }
    }

}