#include "math.h"
#include "stdlib.h"
#include "stdio.h"
typedef int oa_int3[3];
#define min(a,b) ((a)<(b))?(a):(b)
#define BLOCK_NUM 32
#define calc_id2(i,j,k,S0,S1) ((k)*(S0)*(S1)+(j)*(S0)+(i))

extern "C" {
void kernel_1801689973333984248(void** &list, int o) {
  //o = 1;//temp wangdong
  oa_int3* oa_int3_p = (oa_int3*)(list[3]);



  double *list_0;  list_0 = (double *) list[0];
  double *list_1;  list_1 = (double *) list[1];
  double *list_2;  list_2 = (double *) list[2];

  const oa_int3 &lbound = oa_int3_p[3];
  const oa_int3 &rbound = oa_int3_p[4];
  const oa_int3 &sp = oa_int3_p[5];

  const int S0_0 = oa_int3_p[0][0];    const int S0_1 = oa_int3_p[0][1];
  const int S1_0 = oa_int3_p[1][0];    const int S1_1 = oa_int3_p[1][1];
  const int S2_0 = oa_int3_p[2][0];    const int S2_1 = oa_int3_p[2][1];
  int ist=o ;   int ied=o + sp[0] ;
  int jst=o ;   int jed=o + sp[1] ;
  int kst=o ;   int ked=o + sp[2] ;

  /*for (int kk = kst; kk< ked+BLOCK_NUM; kk += BLOCK_NUM)*/{
    //int kend=min(kk+BLOCK_NUM,ked);
    /*for (int jj = jst; jj< jed+BLOCK_NUM; jj += BLOCK_NUM)*/{
      //int jend=min(jj+BLOCK_NUM,jed);
      /*for (int ii = ist; ii< ied+BLOCK_NUM; ii += BLOCK_NUM)*/{
        //int iend=min(ii+BLOCK_NUM,ied);
        for (int k = kst; k < ked; k++) {
          for (int j = jst; j < jed; j++) {
            #pragma simd
            #pragma clang loop vectorize(assume_safety)
            #pragma clang loop interleave(enable)
            #pragma clang loop vectorize_width(8) interleave_count(1)
            for (int i = ist; i < ied ;i++){
              list_2[calc_id2(i,j,k,S2_0,S2_1)] = 1.0*((list_0[calc_id2(1+i,j,k,S0_0,S0_1)])-(list_0[calc_id2(i,j,k,S0_0,S0_1)]))/list_1[calc_id2(i,j,o,S1_0,S1_1)];
            }
          }
        }
      }
    }
  }
  return ;
}}

