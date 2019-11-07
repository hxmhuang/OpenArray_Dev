
#include "../MPI.hpp"
#include "../Array.hpp"
#include "../Grid.hpp"
#include <iostream>
extern "C"{
  void c_grid_init (char* ch, const ArrayPtr*& A,
          const ArrayPtr*& B, const ArrayPtr*& C){
    Grid::global()->init_grid(*ch, *A, *B, *C);
  }

  void c_grid_bind(ArrayPtr*& A, int pos){
    ENSURE_VALID_PTR_MSG(A,
            "can not bind grid to array(array pointer is null)");
    (*A)->set_pos(pos);
  }
  
  void c_get_grid_type(char* grid_type){
   //char* g_type; 
   *grid_type = Grid::global()->get_grid_type();
   //*grid_type = *g_type;
   //return grid_type;
   } 
}
