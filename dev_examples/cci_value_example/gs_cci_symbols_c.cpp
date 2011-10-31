// LICENSETEXT
//
//   Copyright (C) 2011 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//
//
// The contents of this file are subject to the licensing terms specified
// in the file LICENSE. Please consult this file for restrictions and
// limitations that may apply.
// 
// ENDLICENSETEXT

#include "gs_cci_symbols_c.h"
#include "test_datatype_without_parameter_implementation.h"

//
// This makes sure the symbols for supported parameter types are available in the library!
//

namespace cci { namespace cnf {

#define CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS_T_TM(PTYPE, MUTABILITY_TYPE) \
  template  cci::cnf::cci_param_impl_if<PTYPE, MUTABILITY_TYPE>*  create_cci_param (cci::cnf::cci_param<PTYPE, MUTABILITY_TYPE> *owner_par, const char* nam,                   const bool is_top_level_name, cci_cnf_broker_if* broker_accessor); \
  template  cci::cnf::cci_param_impl_if<PTYPE, MUTABILITY_TYPE>*  create_cci_param (cci::cnf::cci_param<PTYPE, MUTABILITY_TYPE> *owner_par, const char* nam, const PTYPE& val, const bool is_top_level_name, cci_cnf_broker_if* broker_accessor); \
  template  cci::cnf::cci_param_impl_if<PTYPE, MUTABILITY_TYPE>*  create_cci_param (cci::cnf::cci_param<PTYPE, MUTABILITY_TYPE> *owner_par, const char* nam, const char* val,  const bool is_top_level_name, cci_cnf_broker_if* broker_accessor); \
  template                                                  void  init_cci_param   (cci::cnf::cci_param<PTYPE, MUTABILITY_TYPE> *owner_par); \
  template                                                  void  destroy_cci_param(cci::cnf::cci_param<PTYPE, MUTABILITY_TYPE>* param    );

#define CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS(PTYPE) \
  CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS_T_TM(PTYPE, cci::cnf::mutable_parameter) \
  CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS_T_TM(PTYPE, cci::cnf::immutable_parameter) \
  CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS_T_TM(PTYPE, cci::cnf::elaboration_time_parameter) \
  CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS_T_TM(PTYPE, cci::cnf::other_parameter)

  CCI_IMPL_CREATE_SYMBOLS_FOR_FUNCTIONS(test_datatype_without_parameter_implementation)

} } // end namespace


std::istream& operator >>(std::istream &is,test_datatype_without_parameter_implementation &obj)
{
  is>>obj.strVal;
  return is;
}
std::ostream& operator <<(std::ostream &os,const test_datatype_without_parameter_implementation &obj)
{
  os<<obj.strVal;
  return os;
}

// The following code enables the new data type parameter to work with cci_values !!!!
#ifdef ENABLE_CCI_VALUE_SUPPORT_FOR_TEST_DATATYPE

__OPEN_NAMESPACE_EXAMPLE_PARAM_IMPLEMENTATION__

/// Helper class template specialization: to make cci_values work
template<cci::cnf::param_mutable_type TM>
struct cci_value_helper<test_datatype_without_parameter_implementation, TM> {
  typedef test_datatype_without_parameter_implementation my_type;
  static void from_value(const cci::cnf::cci_value& val, gs_cci_param<my_type, TM>& param) {
    test_datatype_without_parameter_implementation d;
    switch (val.type() ) {
      case cci::cnf::partype_string:
        d.strVal = val.get_string();
        param.set(d);
        break;
      default:
        cci::cnf::cci_report_handler::cci_value_failure("Set cci value called with not supported value type.");
    }
  }
  
  static cci::cnf::cci_value to_value(gs_cci_param<my_type, TM>& param) {
    test_datatype_without_parameter_implementation d;
    std::string s = param.get().strVal;
    cci::cnf::cci_value val(s);
    return val;    
  }
};

__CLOSE_NAMESPACE_EXAMPLE_PARAM_IMPLEMENTATION__

#endif
// end if ENABLE_CCI_VALUE_SUPPORT_FOR_TEST_DATATYPE