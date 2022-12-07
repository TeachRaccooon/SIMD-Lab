#include "AP-Flow.h"
#include <emmintrin.h>

void APFlow::CalcFlow()
{


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


   memcpy(APFlow::Flow, APFlow::Adj, APFlow::N*APFlow::N);
   /* abbreviated flow and N */
   uint8_t *lflow = APFlow::Flow;
   int lN = APFlow::N;



   int i, j, k;

   for(i = 0; i < lN; i++)
   {
      lflow[i*N + i] = 0xff;
   }

   for(k = 0; k < lN; k++)
   {
      for(i = 0; i < lN; i++)
      {
         unsigned char lflow_ik = lflow[i*lN + k];
         __m128i m_flow_ik;
         m_flow_ik = _mm_set1_epi8(lflow_ik);
         for(j = 0; j < lN; j+=128/(8*sizeof(char)))
         {
            __m128i m_flow_ij, m_flow_kj;
            m_flow_ij = _mm_load_si128((const __m128i*)(lflow + (i*lN + j)));
            m_flow_kj = _mm_load_si128((const __m128i*)(lflow + (k*lN + j)));

            /* store in m_flow_kj the lesser between it and m_flow_ik */
            m_flow_kj = _mm_min_epu8(m_flow_kj, m_flow_ik);
            /* store in m_flow_ij the larger between it and m_flow_kj */
            m_flow_ij = _mm_max_epu8(m_flow_ij, m_flow_kj);

            _mm_store_si128((__m128i*)(lflow + (i*N + j)), m_flow_ij);
         }
      }
   }

}