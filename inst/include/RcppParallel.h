
#ifndef __RCPP_PARALLEL__
#define __RCPP_PARALLEL__

// TinyThread implementation
#include "RcppParallel/TinyThread.h"

// Use TBB only where it's known to compile and work correctly
#ifndef RCPP_PARALLEL_USE_TBB
#if defined(__APPLE__) || defined(__gnu_linux__)
  #define RCPP_PARALLEL_USE_TBB 1
  #include "RcppParallel/TBB.h"
#else
  #define RCPP_PARALLEL_USE_TBB 0
#endif
#endif

#include "RcppParallel/RVector.h"
#include "RcppParallel/RMatrix.h"

namespace RcppParallel {

inline void parallelFor(std::size_t begin, std::size_t end, 
                        Worker& worker, std::size_t grainSize = 1) {
                           
#if RCPP_PARALLEL_USE_TBB
   tbbParallelFor(begin, end, worker, grainSize);
#else
   ttParallelFor(begin, end, worker, grainSize);
#endif

}

template <typename Reducer>
inline void parallelReduce(std::size_t begin, std::size_t end, 
                           Reducer& reducer, std::size_t grainSize = 1) {
                              
#if RCPP_PARALLEL_USE_TBB
   tbbParallelReduce(begin, end, reducer, grainSize);
#else
   ttParallelReduce(begin, end, reducer, grainSize);
#endif

}

} // namespace RcppParallel

#endif // __RCPP_PARALLEL__
