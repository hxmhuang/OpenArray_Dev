#include "c_simple_type.hpp"
#include "../modules/basic/c_new_node_simple.cpp"
#include "../modules/operator/c_simple_node.cpp"

extern "C"{

  void adv_uv_three_pos_one(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1,ArrayPtr* &res_v2,int *res_id){
		
		int F_id1,F_id2,F_id3,F_id4,dt_id1,dt_id2,res_v1_id1,res_v2_id;
		int axb1_id,multi1_id,ayb1_id,axb2_id,multi2_id,dxf1_id;
		int ayb2_id,multi3_id,ayf1_id,ayf2_id,multi4_id,dyb1_id;
		int ayb3_id,azb1_id,dzf1_id,multi5_id;
		int plus1_id;
		
		//#######First u item
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb1_id,&dt_id1);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_mult_simple(&multi1_id,&axb1_id,&res_v1_id1);
		
		c_new_node_ayb_simple(&ayb1_id,&multi1_id);
		
		c_new_node_array_simple(F,&F_id1);
		c_new_node_axb_simple(&axb2_id,&F_id1);
		
		c_new_node_mult_simple(&multi2_id, &ayb1_id, &axb2_id);
		
		c_new_node_dxf_simple(&dxf1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb2_id,&dt_id2);
		
		c_new_node_array_simple(F, &F_id2);
		c_new_node_mult_simple(&multi3_id,&ayb2_id,&F_id2);
		
		c_new_node_ayf_simple(&ayf1_id,&multi3_id);
		
		c_new_node_array_simple(F,&F_id3);
		c_new_node_ayf_simple(&ayf2_id,&F_id3);
		
		c_new_node_mult_simple(&multi4_id, &ayf1_id, &ayf2_id);
		
		c_new_node_dyb_simple(&dyb1_id, &multi4_id);
				
		//#######third w item
		c_new_node_array_simple(res_v2,&res_v2_id);
		c_new_node_ayb_simple(&ayb3_id,&res_v2_id);
		
		c_new_node_array_simple(F, &F_id4);
		c_new_node_azb_simple(&azb1_id,&F_id4);
		
		c_new_node_mult_simple(&multi5_id, &ayb3_id, &azb1_id);
		
		c_new_node_dzf_simple(&dzf1_id, &multi5_id);
		
		//#########sum
		c_new_node_plus_simple(&plus1_id,&dxf1_id,&dyb1_id);
		c_new_node_minus_simple(res_id,&plus1_id,&dzf1_id);

  }
  
    void adv_uv_three_pos_two(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1,ArrayPtr* &res_v2,int *res_id){
		
		int F_id1,F_id2,F_id3,F_id4,dt_id1,dt_id2,res_v1_id1,res_v2_id;
		int axb1_id,multi1_id,axf1_id,axf2_id,multi2_id,dxb1_id;
		int ayb1_id,multi3_id,axb2_id,ayb2_id,multi4_id,dyf1_id;
		int axb3_id,azb1_id,multi5_id,dzf1_id;
		int plus1_id;
		
		//#######First u item
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb1_id,&dt_id1);
		
		c_new_node_array_simple(F, &F_id1);
		c_new_node_mult_simple(&multi1_id,&axb1_id,&F_id1);
		
		c_new_node_axf_simple(&axf1_id,&multi1_id);
		
		c_new_node_array_simple(F,&F_id2);
		c_new_node_axf_simple(&axf2_id,&F_id2);
		
		c_new_node_mult_simple(&multi2_id, &axf1_id, &axf2_id);
		
		c_new_node_dxb_simple(&dxb1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb1_id,&dt_id2);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_mult_simple(&multi3_id,&ayb1_id,&res_v1_id1);
		
		c_new_node_axb_simple(&axb2_id,&multi3_id);
		
		c_new_node_array_simple(F,&F_id3);
		c_new_node_ayb_simple(&ayb2_id,&F_id3);
		
		c_new_node_mult_simple(&multi4_id, &axb2_id, &ayb2_id);

		c_new_node_dyf_simple(&dyf1_id, &multi4_id);
				
		//#######third w item
		c_new_node_array_simple(res_v2,&res_v2_id);
		c_new_node_axb_simple(&axb3_id,&res_v2_id);
		
		c_new_node_array_simple(F, &F_id4);
		c_new_node_azb_simple(&azb1_id,&F_id4);
		
		c_new_node_mult_simple(&multi5_id, &axb3_id, &azb1_id);
		
		c_new_node_dzf_simple(&dzf1_id, &multi5_id);
		
		//#########sum
		c_new_node_plus_simple(&plus1_id,&dxb1_id,&dyf1_id);
		c_new_node_minus_simple(res_id,&plus1_id,&dzf1_id);
  }
  
    void adv_uv_two_pos_one(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1,int *res_id){
		
		int F_id1,F_id2,F_id3,dt_id1,dt_id2,res_v1_id1,res_v2_id;
		int axb1_id,multi1_id,ayb1_id,axb2_id,multi2_id,dxf1_id;
		int ayb2_id,multi3_id,ayf1_id,ayf2_id,multi4_id,dyb1_id;
		
		//#######First u item
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb1_id,&dt_id1);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_mult_simple(&multi1_id,&axb1_id,&res_v1_id1);
		
		c_new_node_ayb_simple(&ayb1_id,&multi1_id);
		
		c_new_node_array_simple(F,&F_id1);
		c_new_node_axb_simple(&axb2_id,&F_id1);
		
		c_new_node_mult_simple(&multi2_id, &ayb1_id, &axb2_id);
		
		c_new_node_dxf_simple(&dxf1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb2_id,&dt_id2);
		
		c_new_node_array_simple(F, &F_id2);
		c_new_node_mult_simple(&multi3_id,&ayb2_id,&F_id2);
		
		c_new_node_ayf_simple(&ayf1_id,&multi3_id);
		
		c_new_node_array_simple(F,&F_id3);
		c_new_node_ayf_simple(&ayf2_id,&F_id3);
		
		c_new_node_mult_simple(&multi4_id, &ayf1_id, &ayf2_id);
		
		c_new_node_dyb_simple(&dyb1_id, &multi4_id);
		
		//#########sum
		c_new_node_plus_simple(res_id,&dxf1_id,&dyb1_id);
  }
  
      void adv_uv_two_pos_two(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1 ,int *res_id){
		
		int F_id1,F_id2,F_id3,dt_id1,dt_id2,res_v1_id1,res_v2_id;
		int axb1_id,multi1_id,axf1_id,axf2_id,multi2_id,dxb1_id;
		int ayb1_id,multi3_id,axb2_id,ayb2_id,multi4_id,dyf1_id;

		//#######First u item
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb1_id,&dt_id1);
		
		c_new_node_array_simple(F, &F_id1);
		c_new_node_mult_simple(&multi1_id,&axb1_id,&F_id1);
		
		c_new_node_axf_simple(&axf1_id,&multi1_id);
		
		c_new_node_array_simple(F,&F_id2);
		c_new_node_axf_simple(&axf2_id,&F_id2);
		
		c_new_node_mult_simple(&multi2_id, &axf1_id, &axf2_id);
		
		c_new_node_dxb_simple(&dxb1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb1_id,&dt_id2);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_mult_simple(&multi3_id,&ayb1_id,&res_v1_id1);
		
		c_new_node_axb_simple(&axb2_id,&multi3_id);
		
		c_new_node_array_simple(F,&F_id3);
		c_new_node_ayb_simple(&ayb2_id,&F_id3);
		
		c_new_node_mult_simple(&multi4_id, &axb2_id, &ayb2_id);

		c_new_node_dyf_simple(&dyf1_id, &multi4_id);

		
		//#########sum
		c_new_node_plus_simple(res_id,&dxb1_id,&dyf1_id);

  }

    void adv_qt_pos_third(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1,ArrayPtr* &res_v2,ArrayPtr* &res_v3,int *res_id){
		
		int F_id1,F_id2,F_id3,dt_id1,dt_id2,res_v1_id1,res_v2_id,res_v3_id;
		int axb1_id,axb2_id,multi1_id,multi2_id,dxf1_id;
		int ayb1_id,ayb2_id,multi3_id,multi4_id,dyf1_id;
		int azb1_id,multi5_id,dzf1_id;
		int plus1_id;
		
		//#######First u item
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb1_id,&dt_id1);
		
		c_new_node_array_simple(F,&F_id1);
		c_new_node_axb_simple(&axb2_id,&F_id1);
	
		c_new_node_mult_simple(&multi1_id,&axb1_id,&axb2_id);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_mult_simple(&multi2_id,&multi1_id,&res_v1_id1);

		c_new_node_dxf_simple(&dxf1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb1_id,&dt_id2);
		
		c_new_node_array_simple(F, &F_id2);
		c_new_node_ayb_simple(&ayb2_id,&F_id2);
		
		c_new_node_mult_simple(&multi3_id,&ayb1_id,&ayb2_id);
		
		c_new_node_array_simple(res_v2, &res_v2_id);
		c_new_node_mult_simple(&multi4_id,&multi3_id,&res_v2_id);
		
		c_new_node_dyf_simple(&dyf1_id, &multi4_id);
				
		//#######third w item
		c_new_node_array_simple(F,&F_id3);
		c_new_node_azb_simple(&azb1_id,&F_id3);
		
		c_new_node_array_simple(res_v3, &res_v3_id);
		c_new_node_mult_simple(&multi5_id,&azb1_id,&res_v3_id);

		c_new_node_dzf_simple(&dzf1_id, &multi5_id);
		
		//#########sum
		c_new_node_plus_simple(&plus1_id,&dxf1_id,&dyf1_id);
		c_new_node_minus_simple(res_id,&plus1_id,&dzf1_id);

  }
  
      void adv_qt_pos_seven(ArrayPtr* &F, ArrayPtr* &dt, ArrayPtr* &res_v1,ArrayPtr* &res_v2,ArrayPtr* &res_v3,int *res_id){
		
		int F_id1,F_id2,F_id3,dt_id1,dt_id2,res_v1_id1,res_v2_id,res_v3_id;
		int axb1_id,axb2_id,multi1_id,azb1_id,multi2_id,dxf1_id;
		int ayb1_id,ayb2_id,multi3_id,azb2_id,multi4_id,dyf1_id;
		int multi5_id,azf1_id,dzb1_id;
		int plus1_id;
		
		//#######First u item

		
		c_new_node_array_simple(F,&F_id1);
		c_new_node_axb_simple(&axb1_id,&F_id1);
		
		c_new_node_array_simple(dt,&dt_id1);
		c_new_node_axb_simple(&axb2_id,&dt_id1);
	
		c_new_node_mult_simple(&multi1_id,&axb1_id,&axb2_id);
		
		c_new_node_array_simple(res_v1, &res_v1_id1);
		c_new_node_azb_simple(&azb1_id,&res_v1_id1);
		
		c_new_node_mult_simple(&multi2_id,&multi1_id,&azb1_id);

		c_new_node_dxf_simple(&dxf1_id, &multi2_id);
		
		//#######second v item
		c_new_node_array_simple(F, &F_id2);
		c_new_node_ayb_simple(&ayb1_id,&F_id2);
		
		c_new_node_array_simple(dt,&dt_id2);
		c_new_node_ayb_simple(&ayb2_id,&dt_id2);
	
		c_new_node_mult_simple(&multi3_id,&ayb1_id,&ayb2_id);
		
		c_new_node_array_simple(res_v2, &res_v2_id);
		c_new_node_azb_simple(&azb2_id,&res_v2_id);
		
		c_new_node_mult_simple(&multi4_id,&multi3_id,&azb2_id);

		c_new_node_dyf_simple(&dyf1_id, &multi4_id);
				
		//#######third w item
		
		c_new_node_array_simple(res_v3,&res_v3_id);
		c_new_node_array_simple(F,&F_id3);
		c_new_node_mult_simple(&multi5_id,&res_v3_id,&F_id3);
		
		c_new_node_azf_simple(&azf1_id,&multi5_id);
		c_new_node_dzb_simple(&dzb1_id,&azf1_id);

		//#########sum
		c_new_node_plus_simple(&plus1_id,&dxf1_id,&dyf1_id);
		c_new_node_minus_simple(res_id,&plus1_id,&dzb1_id);

  }
}
