  
  





#include "new_node.hpp"

namespace oa{
  namespace ops{
    NodePtr new_node_mat_mult(const NodePtr& u,
                               const NodePtr& v){
      NodePtr np = NodePool::global()->get();
      np->set_type(TYPE_MAT_MULT);
      np->add_input(0, u);
      np->add_input(1, v);
      
      // const NodeDesc &nd = get_node_desc(TYPE_PLUS);

      DataType dt = oa::utils::cast_data_type(u->get_data_type(),
                                              v->get_data_type());

      np->set_depth(u->get_depth(), v->get_depth());
      
      // set data shape
      ArrayPtr A=u->get_data();
      ArrayPtr B=v->get_data();
      Shape s_A=A->shape();
      Shape s_B=B->shape();
      Shape s_C=s_A;
      s_C[1]=s_B[1];
      s_C[2]=max(s_A[2],s_B[2]);
      np->set_shape(s_C);
      // set data other attribute
      np->set_data_type(dt);
      np->set_lbound(u->get_lbound(), v->get_lbound());
      np->set_rbound(u->get_rbound(), v->get_rbound());

      // u & v must in the same grid pos
      //assert(u->get_pos() == v->get_pos());
      if(u->get_pos() != -1)
        np->set_pos(u->get_pos());
      else if(v->get_pos() != -1)
        np->set_pos(v->get_pos());
     
      np->set_pseudo(u->is_pseudo() && v->is_pseudo());
      np->set_bitset(u->get_bitset() | v->get_bitset());

      // split into two fusion kernel when the size of data list is too large
      //int data_list_size = u->get_data_list_size() + v->get_data_list_size();

      //if (data_list_size > 10) {
      //  np->set_lbound({{0,0,0}});
      //  np->set_rbound({{0,0,0}});
      //  u->set_update();
      //  v->set_update();
      //  np->set_data_list_size(1 + 1);
      //} else {
      //  np->set_data_list_size(data_list_size);
      //}

      // np->display();
      return np;
    }

  }
}
