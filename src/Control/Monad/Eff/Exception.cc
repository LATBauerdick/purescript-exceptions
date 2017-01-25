///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Exception.cc
// Copyright   :  (c) Andy Arvanitis 2016
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// Exception FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#include <iostream>
#include "PureScript/PureScript.hh"

namespace Control_Monad_Eff_Exception {
  using namespace PureScript;

  // foreign import stackImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Error
  //   -> Maybe String
  //
  auto stackImpl(const any&, const any& nothing, const any&) -> any {
    std::cerr << "stackImpl: stack traces not available" << std::endl;
    return nothing;
  }

  // foreign import throwException
  //   :: forall a eff
  //    . Error
  //   -> Eff (err :: EXCEPTION | eff) a
  //
  auto throwException(const any& e) -> any {
    return [=]() -> any {
      throw cast<runtime_error>(e);
    };
  }

  // foreign import catchException
  //   :: forall a eff
  //    . (Error -> Eff eff a)
  //   -> Eff (err :: EXCEPTION | eff) a
  //   -> Eff eff a
  //
  auto catchException(const any& c, const any& t) -> any {
    return [=]() -> any {
      try {
        return t();
      } catch (std::runtime_error& e) {
        return c(make_managed<runtime_error>(e));
      } catch (std::exception& e) {
        return c(make_managed<runtime_error>(e.what()));
      }
    };
  }

}
