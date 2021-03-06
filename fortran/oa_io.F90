module oa_io
  use oa_type
  use iso_c_binding

  interface
     subroutine c_save(A, file, var) &
          bind(C, name="c_save") 
       use iso_c_binding
       type(c_ptr)  :: A
       character(kind=c_char) :: file, var
     end subroutine
  end interface

  interface
     subroutine c_load(A, file, var) &
          bind(C, name="c_load") 
       use iso_c_binding
       type(c_ptr)  :: A
       character(kind=c_char) :: file, var
     end subroutine
  end interface
  
contains

  subroutine save(A, file, var)
    implicit none
    type(array) :: A
    character(len=*) :: file, var

    call c_save(A%ptr, &
         string_f2c(file), string_f2c(var))
  end subroutine 

  function load(file, var) result(A)
    implicit none
    type(array) :: A
    character(len=*) :: file, var

    call c_load(A%ptr, &
         string_f2c(file), string_f2c(var))

    call set_rvalue(A)
  end function
  
end module
