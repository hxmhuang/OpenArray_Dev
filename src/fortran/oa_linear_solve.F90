module oa_linear_solve
		use oa_type
		use petscsys
		use oa_pvariable
contains
function linear_equations_solve(A, B,numperow) result(X)

		!####################################################################
		!Note:Petsc index is start from 0, but fortran index is start from 1!
		!####################################################################
		
		implicit none
		!-------------decare and set variables-----------
		integer,optional :: numperow
		integer :: Ai,Aj,Ai_global,Aj_global,ierr,p_numperow,Az
		integer :: Bi,Bi_global,Bj,Bz
		integer :: Xi,Xi_global,Xj,Xz
		integer :: numperrow
		
		type(array) :: A,B,X
		integer :: A_ind(3),A_ind_global(6),A_xs,A_ys
		integer :: B_ind(3),B_ind_global(6),B_xs
		integer :: X_ind(3),X_ind_global(6),X_xs
		real(kind=8),allocatable :: res_raw(:)
		real(kind=8),pointer :: pA(:,:,:),pB(:,:,:),pX(:,:,:)
		integer,allocatable :: ix(:)
		

		if(present(numperow))then
			p_numperow=numperow
		else
			p_numperow=p_N
		endif
		
		!--------------get A and B data buffer------------
		call get_local_buffer(pA,A)
		call get_local_buffer(pB,B)

		!--------------Check array shapes-------------
		
		A_ind = shape(A)
		A_ind_global = get_box_corners(A)
		B_ind = shape(B)
		B_ind_global = get_box_corners(B)
		
		if ((A_ind(1).ne.B_ind(1)).OR.(A_ind(1).ne.A_ind(2)))then
			write(*,*)"Error：A is not a square matrix or the first dimension length of B is not equal with the first(second) dimension length of A!"
			call MPI_Abort(MPI_COMM_WORLD,99,ierr)
		endif 
		!---------------------------petsc init-----------------------------
		call PetscInitialize(PETSC_NULL_CHARACTER,ierr)
		call MPI_Comm_rank(MPI_COMM_WORLD,p_rank,ierr)
		call MPI_Comm_size(MPI_COMM_WORLD,p_size,ierr)
		PETSC_COMM_WORLD=MPI_COMM_WORLD
		p_N=A_ind(1)
		!--------------------------create X------------------------------------
		X = zeros(p_N,1,1,sw=1,dt=2)
		call get_local_buffer(pX,X)
		X_ind = shape(X)
		X_ind_global = get_box_corners(X)
		!---------------------------Create p_A ------------------------------
		call MatCreate(PETSC_COMM_WORLD,p_A,ierr)
		call MatSetSizes(p_A,PETSC_DECIDE,PETSC_DECIDE,p_N,p_N,ierr)
		call MatSetFromOptions(p_A,ierr)
		if (p_size>1) then 
			call MatMPIAIJSetPreallocation(p_A,p_numperow,&
				PETSC_NULL_INTEGER,p_numperow,PETSC_NULL_INTEGER,ierr)
		else
			call MatSeqAIJSetPreallocation(p_A,p_numperow,&
				PETSC_NULL_INTEGER,ierr)
		endif
		!--------------------------Create p_B and p_x ix p_from p_to p_x_all-----------------------------
		call VecCreate(PETSC_COMM_WORLD,p_b,ierr)
		call VecSetSizes(p_b,PETSC_DECIDE,p_N,ierr)
		call VecSetFromOptions(p_b,ierr)
		call VecDuplicate(p_b,p_x,ierr)
		allocate(ix(0:p_N-1))
		allocate(res_raw(0:p_N-1))
		do p_i=0,p_N-1
			call VecSetValues(p_x,1,p_i,p_default_vec_value,INSERT_VALUES,ierr)
			ix(p_i)=p_i
			res_raw(p_i)=p_i
		end do

		call VecCreateSeq(PETSC_COMM_SELF,p_N,p_x_all,ierr)
		call ISCreateGeneral(PETSC_COMM_WORLD,p_N,ix,PETSC_COPY_VALUES,p_from,ierr)
		call ISCreateGeneral(PETSC_COMM_WORLD,p_N,ix,PETSC_COPY_VALUES,p_to,ierr)
		!--------------------------pass by A buffer to p_a---------------
		A_xs=A_ind_global(1);A_ys=A_ind_global(3);Az = 1+default_stencil_width

		do Ai=1,A_ind(1)
			do Aj=1,A_ind(2)
				if (pA(Aj+default_stencil_width,Ai+default_stencil_width,Az)>0) then
					p_aprA=pA(Aj+default_stencil_width,Ai+default_stencil_width,Az)
					
					if ((Ai+default_stencil_width==Aj+default_stencil_width).AND.(p_aprA == 0)) then
						write(*,*)"Error：Matrix A is a singular matrix , cant solve result,please check your Matrix A first!"
						call MPI_Abort(MPI_COMM_WORLD,99,ierr)
					endif
					Ai_global=Ai+A_xs-1
					Aj_global=Aj+A_ys-1
					call MatSetValues(p_A,1,Aj_global,1,Ai_global,p_aprA,INSERT_VALUES,ierr)
				endif
			end do
		end do
		call MatAssemblyBegin(p_A,MAT_FINAL_ASSEMBLY,ierr)
		call MatAssemblyEnd(p_A,MAT_FINAL_ASSEMBLY,ierr)
		!--------------------------pass by B buffer to p_b---------------		
		B_xs=B_ind_global(1);Bj=1+default_stencil_width;Bz=1+default_stencil_width
		do Bi=1,B_ind(1)
				p_aprb=pB(Bi+default_stencil_width,Bj,Bz)
				Bi_global=Bi+B_xs-1
				call VecSetValues(p_b,1,Bi_global,p_aprb,INSERT_VALUES,ierr)
		end do
		call VecAssemblyBegin(p_b,ierr)
		call VecAssemblyEnd(p_b,ierr)
		
		!--------------------------Create KSP solver ------------------------------
		call KSPCreate(PETSC_COMM_WORLD,p_ksp,ierr)
		call KSPSetOperators(p_ksp,p_A,p_A,ierr)
		call KSPSetInitialGuessNonzero(p_ksp,PETSC_TRUE,ierr)
		call KSPSetTolerances(p_ksp,tol,PETSC_DEFAULT_REAL,PETSC_DEFAULT_REAL,200,ierr)
		call KSPSetFromOptions(p_ksp,ierr)
		call KSPSolve(p_ksp,p_b,p_x,ierr)
		!--------------------------pass p_x value to a serial vector p_x_all and res_raw
		call VecScatterCreate(p_x,p_from,p_x_all,p_to,p_ctx,ierr)
		call VecScatterBegin(p_ctx,p_x,p_x_all,INSERT_VALUES,SCATTER_FORWARD,ierr)
		call VecScatterEnd(p_ctx,p_x,p_x_all,INSERT_VALUES,SCATTER_FORWARD,ierr)
		call VecGetValues(p_x_all,p_N,ix,res_raw,ierr)
		!--------------------------pass res_raw value to pX
		X_xs=X_ind_global(1);Xj=1+default_stencil_width;Xz=1+default_stencil_width
		do Xi=1,X_ind(1)
			pX(Xi+default_stencil_width,Xj,Xz)=res_raw(Xi-1) 
		end do
		deallocate(ix)
		deallocate(res_raw)
		call VecScatterDestroy(p_ctx,ierr)
		call VecDestroy(p_b,ierr)
		call VecDestroy(p_x,ierr)
		call MatDestroy(p_A,ierr)
		call KSPDestroy(p_ksp,ierr)

    end function	
	
end module	
		