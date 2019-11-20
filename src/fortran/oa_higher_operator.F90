module oa_higher_operator

use oa_type

	interface curl
       module procedure curl_array_array_array
    end interface curl 
	
		
	interface adv
      module procedure adv_uv_three
      module procedure adv_uv_two
      module procedure adv_qt
    end interface adv 
	
	interface hdif
       module procedure hdif_uv_three_two
	   module procedure hdif_v_three
	   module procedure hdif_q
	   module procedure hdif_t
    end interface hdif 

contains

function divergence(U,V,W) result(A)
   type(array)::U,V,W,A
   A = DXB(U)+DYB(V)+DZB(W)
end function

subroutine grad(A,BX,BY,BZ)
  type(array)::A,BX,BY,BZ
  BX=DXB(A)
  BY=DYB(A)
  BZ=DZB(A)
end subroutine

subroutine curl_array_array_array(U,V,W,curli,curlj,curlk)
    implicit none
	  
    type(array),intent(in):: U
    type(array),intent(in):: V
    type(array),intent(in):: W
	type(array),intent(inout):: curli,curlj,curlk

	curli = DYF(W)- DZF(V)
	curlj = DZF(U)- DXF(W)
	curlk = DXF(V)- DYF(U)
	  
end subroutine

function adv_uv_three (F,dt,res_v1,res_v2) result(res_node)
	implicit none
	type(array) :: F,dt,res_v1,res_v2
	type(array) :: res_node
	integer :: F_pos
		
	call get_array_pos(F,F_pos)
	if (F_pos == 1) then
		res_node = DXF(AYB(AXB(dt)*res_v1)*AXB(F))+DYB(AYF(AYB(dt)*F)*AYF(F))-DZF(AYB(res_v2)*AZB(F))
	else if (F_pos == 2) then
		res_node = DXB(AXF(AXB(dt) * F) * AXF(F))+ DYF(AXB(AYB(dt) * res_v1) * AYB(F))-DZF(AXB(res_v2) * AZB(F))
	else
		write(*,*)"Error：The Function is reload to only supports pos 1 or 2 Array in three dimension , if you want manage the Array of other value,please change the argument of value!"
		stop
	endif
	end function

function adv_uv_two (F,dt,res_v1) result(res_node)
	implicit none
	type(array) :: F,dt,res_v1
	type(array) :: res_node
	integer :: F_pos

	call get_array_pos(F,F_pos)

	if (F_pos == 1) then
		res_node = DXF(AYB(AXB(dt)*res_v1)*AXB(F))+DYB(AYF(AYB(dt)*F)*AYF(F))
	else if (F_pos == 2) then
		res_node = DXB(AXF(AXB(dt)*F) * AXF(F))+ DYF(AXB(AYB(dt)*res_v1) * AYB(F))
	else
		write(*,*)"Error：The Function is reload to only supports pos 1 or 2 Array in three dimension , if you want manage the Array of other value,please change the argument of value!"
		stop
	endif
	end function
	
function adv_qt(F,dt,res_v1,res_v2,res_v3) result(res_node)
	implicit none
	type(array) :: F,dt,res_v1,res_v2,res_v3
	type(array) :: res_node
	integer :: F_pos
		
		
	call get_array_pos(F,F_pos)

	if (F_pos == 3) then
		res_node = DXF(AXB(dt)*AXB(F)*res_v1)+DYF(AYB(dt)*AYB(F)*res_v2)-DZF(AZB(F)*res_v3)
	else if (F_pos == 7) then
		res_node = DXF(AXB(F)* AXB(dt)* AZB(res_v1))+DYF(AYB(F)* AYB(dt)* AZB(res_v2))-DZB(AZF(res_v3*F))
	else
		write(*,*)"Error：The Function is reload to only supports pos 3 or 7 Array in three dimension , if you want manage the Array of other value,please change the argument of value!"
		stop
	endif
	end function

function hdif_uv_three_two(F,dt,aam,res_v1,cal_dimension) result(res_node)
	implicit none
	type(array) :: dt,aam,F,res_v1
	type(array) :: res_node
	integer :: cal_dimension,F_pos
	call get_array_pos(F,F_pos)
	
	if (cal_dimension == 3) then
	    res_node = -DXB(2.d0*dt* aam*DXF(F)) - DYF(AYB(AXB(dt)) * AYB(AXB(aam))*(DYB(F) + DXB(res_v1)))
	else if (cal_dimension == 2) then
		if (F_pos == 1) then
			res_node = -DXF(AYB(AXB(dt))*AXB(AYB(aam))*(DYB(res_v1)+DXB(F)))-DYB(2.d0*dt* aam * DYF(F))
		else if (F_pos == 2) then
			res_node = -DXB(2.d0*dt*aam*DXF(F))-DYF(AYB(AXB(dt))*AXB(AYB(aam))*(DYB(F)+ DXB(res_v1)))
		else
			write(*,*)"Error：The Function is reload to only supports pos 1 or 2 Array in three dimension , if you want manage the Array of other value,please change the argument of value!"
			stop
		endif	
	else
		write(*,*)"Error：The Function is reload to only supports dimension 2 or 3 Array in three dimension , if you want manage the Array of other dimension,please change the argument of value!"
		stop
	endif
	end function
	
function hdif_v_three(F,dt,aam,res_v1,dt_3d,cal_dimension) result(res_node)
	implicit none
	type(array) :: dt,aam,F,res_v1,dt_3d
	type(array) :: res_node
	integer :: cal_dimension
		
	res_node = -DXF(AYB(AXB(dt)) * AYB(AXB(aam))*(DYB(res_v1) + DXB(F))) - DYB(dt_3d*aam*2.d0*DYF(F))

	end function
	
function hdif_q(F,h,aam,dum,dvm) result(res_node)
	implicit none
	type(array) :: F,h,aam,dum,dvm
	type(array) :: res_node
		
	res_node = -DXF(AZB(AXB(aam))*AXB(h)*DXB(F)* dum) - DYF(AZB(AYB(aam))*AYB(h)*DYB(F)*dvm)

	end function
	
function hdif_t(F,h,aam,tprni,h_3d,dum,dvm) result(res_node)
	implicit none
	type(array) :: F,h,aam,tprni,h_3d,dum,dvm
	type(array) :: res_node
		
	res_node = -DXF(-AXB(aam)*AXB(h)*tprni*DXB(F)*dum) - DYF(AYB(aam)*AYB(h_3d)*tprni*DYB(F)*dvm)

	end function

end module


