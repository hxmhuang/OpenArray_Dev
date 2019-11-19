#include "config.h"
module oa_mat_mult
  use iso_c_binding
  use oa_type
  interface mat_mult
     module procedure mat_mult_node_node
     module procedure mat_mult_array_node
     module procedure mat_mult_node_array
     module procedure mat_mult_array_array
  end interface mat_mult
contains
  
  function mat_mult_node_node(A, B) result(res)
    implicit none
    type(node) :: A, B
    type(node) :: res
 
    call c_new_node_mat_mult_simple(res%id, A%id, B%id)    
 
 !   call set_rvalue(res)
 !   call try_destroy(A)
 !   call try_destroy(B)
  end function
 !
  function mat_mult_array_node(A, B) result(res)
    implicit none
    type(array) :: A
    type(node) :: B
    type(node) :: res
    integer :: id
 !
    call c_new_node_array_simple(A%ptr, id)
    call c_new_node_mat_mult_simple(res%id, id, B%id)    
 
 !   call set_rvalue(res)
 !   call try_destroy(A)
 !   call try_destroy(B)
 !   call destroy(NA)
  end function
 
  function mat_mult_node_array(A, B) result(res)
    implicit none
    type(node) :: A
    type(array) :: B
    type(node) :: res
    integer :: id1
 !
    call c_new_node_array_simple(B%ptr, id1)
    call c_new_node_mat_mult_simple(res%id, A%id, id1)    
 !
 !   call set_rvalue(res)
 !   call try_destroy(A)
 !   call try_destroy(B)
 !   call destroy(NB)
  end function
 !
  function mat_mult_array_array(A, B) result(res)
    implicit none
    type(array) :: A
    type(array) :: B
    type(node) :: res
    integer :: id_a,id_b
 !
    call c_new_node_array_simple(A%ptr, id_a)
    call c_new_node_array_simple(B%ptr, id_b)
    call c_new_node_mat_mult_simple(res%id, id_a, id_b)
 !   call c_new_node_op2(res%ptr, TYPE_MAT_MULT, NA%ptr, ND%ptr)    
 !
 !   call set_rvalue(res)
 !   call try_destroy(A)
 !   call try_destroy(B)
 !   call destroy(NA)
 !   call destroy(ND)
  end function
end module
