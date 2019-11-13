/*
 * Init.cpp:
 *
=======================================================*/

#include "mpi.h"
#include "MPI.hpp"
#include "Init.hpp"
#include "Partition.hpp"
#ifdef __HAVE_CUDA__
  #include "CUDA.hpp"
#endif

namespace oa{
  // init the MPI, init Partition default information
  void init(int comm, Shape procs_shape,
          int argc, char** argv){
    oa::MPI::global()->init(comm, argc, argv);
    /*************************** 注册系统信号，截获出错时内存堆栈信息 *********************************/
    signal(SIGINT, [](int signum) {
        //Received a signal, abnormally exited
        oa_log::global()->handle_segv(signum);
        OA_LOG_FATAL<<"......Received a signal SIGINT, abnormally exited......";
        exit(208);
    });
    signal(SIGSEGV, [](int signum) {
        oa_log::global()->handle_segv(signum);
        OA_LOG_FATAL<<"......Received a signal SIGSEGV, abnormally exited......";
        exit(208);
    });
    signal(SIGTERM, [](int signum) {
        oa_log::global()->handle_segv(signum);
        OA_LOG_FATAL<<"......Received a signal SIGTERM, abnormally exited......";
        exit(208);
    });
    signal(SIGABRT, [](int signum) {
        oa_log::global()->handle_segv(signum);
        OA_LOG_FATAL<<"......Received a signal SIGABRT, abnormally exited......";
        exit(208);
    });
    /*********************************************************************************************/
    oa_log::global()->initLog();
    OA_LOG_INFO<<"log init success!";
    #ifdef __HAVE_CUDA__
      std:cout<<"Init gpu envirionment\n";
      MPI_Comm c_comm = MPI_Comm_f2c(comm); 
      oa::gpu::initialize_gpu(c_comm);
    #endif
    
    Partition::set_default_procs_shape(procs_shape);
    Partition::set_default_stencil_width(1);
  }

  // finalize the MPI
  void finalize(){
    oa::MPI::global()->finalize();
  }
}
