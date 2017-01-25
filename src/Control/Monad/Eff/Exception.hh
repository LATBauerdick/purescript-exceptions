///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Exception.hh
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
#ifndef Control_Monad_Eff_Exception_FFI_HH
#define Control_Monad_Eff_Exception_FFI_HH

#include "PureScript/PureScript.hh"

namespace Control_Monad_Eff_Exception {
  using namespace PureScript;

  // foreign import showErrorImpl :: Error -> String
  //
  inline auto showErrorImpl(const any& e) -> string {
    return cast<runtime_error>(e).what();
  }

  // foreign import error :: String -> Error
  //
  inline auto error(const string& e) -> any {
    return make_managed<runtime_error>(e);
  }

  // foreign import message :: Error -> String
  //
  inline auto message(const any& e) -> string {
    return cast<runtime_error>(e).what();
  }

  // foreign import stackImpl
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Error
  //   -> Maybe String
  //
  auto stackImpl(const any&, const any&, const any&) -> any;

  // foreign import throwException
  //   :: forall a eff
  //    . Error
  //   -> Eff (err :: EXCEPTION | eff) a
  //
  auto throwException(const any& e) -> any;

  // foreign import catchException
  //   :: forall a eff
  //    . (Error -> Eff eff a)
  //   -> Eff (err :: EXCEPTION | eff) a
  //   -> Eff eff a
  //
  auto catchException(const any&, const any&) -> any;

}

#endif // Control_Monad_Eff_Exception_FFI_HH
