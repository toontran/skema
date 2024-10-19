#pragma once
#include <KokkosSparse.hpp>
#include <Kokkos_Core.hpp>
#include <Kokkos_Macros.hpp>
#include <Kokkos_Random.hpp>
#include <cstddef>
#include "Skema_AlgParams.hpp"
#include "Skema_Common.hpp"
#include "Skema_Utils.hpp"

namespace Skema {
template <typename MatrixType>
class ISVD {
 public:
  ISVD(const AlgParams&);
  ~ISVD(){};

  /* Public methods */
  void solve(const MatrixType&);

 protected:
  const AlgParams algParams;

  /* Compute U = A*V*Sigma^{-1} */
  KOKKOS_INLINE_FUNCTION
  void U(matrix_type& U,
         const MatrixType& A,
         const vector_type& S,
         const matrix_type V,
         const ordinal_type rank,
         const AlgParams& algParams) {
    const size_type nrow{static_cast<size_type>(algParams.matrix_m)};
    const size_type ncol{static_cast<size_type>(algParams.matrix_n)};
    range_type rlargest = std::make_pair<size_type, size_type>(0, rank);

    matrix_type Vr(V, Kokkos::ALL(), rlargest);
    matrix_type Av("Av", nrow, rank);

    Impl::mm('N', 'N', 1.0, A, Vr, 0.0, Av);

    for (auto r = rlargest.first; r < rlargest.second; ++r) {
      auto avr = Kokkos::subview(Av, Kokkos::ALL(), r);
      auto ur = Kokkos::subview(U, Kokkos::ALL, r);
      auto s = S(r);
      KokkosBlas::scal(ur, (1.0 / s), avr);
    }

    matrix_type Atu("Atu", ncol, rank);
    Impl::mm('T', 'N', 1.0, A, U, 0.0, Atu);
  }

  KOKKOS_INLINE_FUNCTION
  void distribute(const vector_type& svals, const matrix_type& vvecs) {
    size_type k{static_cast<size_type>(svals.size())};
    Kokkos::parallel_for(
        k, KOKKOS_LAMBDA(const int ii) {
          scalar_type sval{svals(ii)};
          for (auto jj = 0; jj < vvecs.extent(1); ++jj) {
            vvecs(ii, jj) *= sval;
          }
        });
  };

  KOKKOS_INLINE_FUNCTION
  void normalize(const vector_type& svals, const matrix_type& vvecs) {
    size_type k{static_cast<size_type>(svals.size())};
    Kokkos::parallel_for(
        k, KOKKOS_LAMBDA(const int ii) {
          scalar_type sval{svals(ii)};
          for (auto jj = 0; jj < vvecs.extent(1); ++jj) {
            vvecs(ii, jj) *= (1.0 / sval);
          }
        });
  };

  struct {
    scalar_type time_svd{0.0};
    scalar_type time_update{0.0};
  } stats;
};

template class ISVD<matrix_type>;
template class ISVD<crs_matrix_type>;

template <typename MatrixType>
void isvd(const MatrixType&, const AlgParams&);
}  // namespace Skema