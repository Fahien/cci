// LICENSETEXT
//
//   Copyright (C) 2009-2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
//
//
// The contents of this file are subject to the licensing terms specified
// in the file LICENSE. Please consult this file for restrictions and
// limitations that may apply.
// 
// ENDLICENSETEXT


#include "ParameterOwnerModule.h"
using namespace std;

void show_cci_value_vector(const cci::cnf::cci_value_list& vec) {
  for (std::vector<cci::cnf::cci_value>::const_iterator iter = vec.begin(); iter != vec.end(); iter++) {
    std::cout << iter->get_string() << ", ";
  }
  std::cout << std::endl;
}


void ParameterOwnerModule::main_action() {

  // demonstrate value setting using cci_value
  /*
   int
   unsigned int
   bool
   double
   float
   std::string
   long long
   unsigned char
   signed char
   char
   unsigned short
  */   
  
  cci::cnf::cci_value int_v(-10);
  DEMO_DUMP(name(), "Set and get parameter Owner.int_param - value = " << int_v.get_int());
  int_param.set_value(int_v);
  int inte = int_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << inte << endl);
  
  cci::cnf::cci_value uint_v(10);
  DEMO_DUMP(name(), "Set and get parameter Owner.uint_param - value = " << uint_v.get_int());
  uint_param.set_value(uint_v);
  unsigned int uint = uint_param.get_value().get_int64();
  DEMO_DUMP(name(), "  got " << uint << endl);

  cci::cnf::cci_value bool_v(true);
  DEMO_DUMP(name(), "Set and get parameter Owner.bool_param - value = " << bool_v.get_bool());
  bool_param.set_value(bool_v);
  bool boole = bool_param.get_value().get_bool();
  DEMO_DUMP(name(), "  got " << boole << endl);

  cci::cnf::cci_value dbl_v(10.123);
  DEMO_DUMP(name(), "Set and get parameter Owner.double_param - value = " << dbl_v.get_real());
  double_param.set_value(dbl_v);
  double dbl = double_param.get_value().get_real();
  DEMO_DUMP(name(), "  got " << dbl << endl);
  
  cci::cnf::cci_value flt_v(98.765);
  DEMO_DUMP(name(), "Set and get parameter Owner.float_param - value = " << flt_v.get_real());
  float_param.set_value(flt_v);
  float flt = float_param.get_value().get_real();
  DEMO_DUMP(name(), "  got " << flt << endl);
  
  cci::cnf::cci_value str_v("This is a string");
  DEMO_DUMP(name(), "Set and get parameter Owner.str_param - value = " << str_v.get_string());
  str_param.set_value(str_v);
  std::string stri = str_param.get_value().get_string();
  DEMO_DUMP(name(), "  got \"" << stri << "\"" << endl);
  
  cci::cnf::cci_value ll_v((sc_dt::int64)1000000000000000001ull);
  DEMO_DUMP(name(), "Set and get parameter Owner.ll_param - value = " << ll_v.get_int64());
  ll_param.set_value(ll_v);
  long long ll = ll_param.get_value().get_int64();
  DEMO_DUMP(name(), "  got " << ll << endl);
  
  cci::cnf::cci_value uc_v(70);
  DEMO_DUMP(name(), "Set and get parameter Owner.uchar_param - value = " << (unsigned char) uc_v.get_int());
  uchar_param.set_value(uc_v);
  unsigned char uc = uchar_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << uc << endl);
  
  cci::cnf::cci_value sc_v(71);
  DEMO_DUMP(name(), "Set and get parameter Owner.schar_param - value = " << (signed char) sc_v.get_int());
  schar_param.set_value(sc_v);
  signed char sc = schar_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << sc << endl);
  
  cci::cnf::cci_value c_v(72);
  DEMO_DUMP(name(), "Set and get parameter Owner.char_param - value = " << (char) c_v.get_int());
  char_param.set_value(c_v);
  char c = char_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << c << endl);
  cci::cnf::cci_value c_vs("A");
  DEMO_DUMP(name(), "Set and get parameter Owner.char_param - value = " << c_vs.get_string());
  char_param.set_value(c_vs);
  c = char_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << c << endl);
  
  cci::cnf::cci_value us_v(244);
  DEMO_DUMP(name(), "Set and get parameter Owner.ushort_param - value = " << (unsigned short) us_v.get_int());
  ushort_param.set_value(us_v);
  unsigned short us = ushort_param.get_value().get_int();
  DEMO_DUMP(name(), "  got " << us << endl);
  
  /*
   std::vector<std::string>
   */
  
  cci::cnf::cci_value_list lst_v_lst;
  lst_v_lst.push_back(cci::cnf::cci_value("value1"));
  lst_v_lst.push_back(cci::cnf::cci_value("value2"));
  lst_v_lst.push_back(cci::cnf::cci_value("value3"));
  cci::cnf::cci_value lst_v(lst_v_lst);
  DEMO_DUMP(name(), "Set and get parameter Owner.strvec_param - value = "); show_cci_value_vector(lst_v_lst);
  strvec_param.set_value(lst_v);
  cci::cnf::cci_value v_get = strvec_param.get_value();
  DEMO_DUMP(name(), "  got "); show_cci_value_vector(v_get.get_list());
  std::cout << std::endl;

  /*
   sc_dt::sc_int_base
   sc_dt::sc_uint_base
   sc_dt::sc_signed
   sc_dt::sc_unsigned
   sc_dt::sc_bit
   sc_dt::sc_logic
   sc_core::sc_time
   sc_dt::sc_int<w> w=1...64
   sc_dt::sc_uint<w> w=1...64
   sc_dt::sc_bigint<w> w=1...1024
   sc_dt::sc_biguint<w> w=1...1024
  */
  
  cci::cnf::cci_value scintbv_v(-1000);
  DEMO_DUMP(name(), "Set and get parameter Owner.scintbase_param - value = " << scintbv_v.get_int64());
  scintb_param.set_value(scintbv_v);
  sc_dt::int64 scintb(scintb_param.get_value().get_int64());
  DEMO_DUMP(name(), "  got " << scintb << endl);
  cci::cnf::cci_value scintbv_vs("-111000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scintbase_param - value = " << scintbv_vs.get_string());
  scintb_param.set_value(scintbv_vs);
  scintb = scintb_param.get_value().get_int64();
  DEMO_DUMP(name(), "  got " << scintb << endl);
  
  cci::cnf::cci_value scuintbv_v(1000);
  DEMO_DUMP(name(), "Set and get parameter Owner.scuintbase_param - value = " << (sc_dt::uint64) scuintbv_v.get_int64());
  scuintb_param.set_value(scuintbv_v);
  sc_dt::uint64 scuintb(scuintb_param.get_value().get_int64());
  DEMO_DUMP(name(), "  got " << scuintb << endl);
  cci::cnf::cci_value scuintbv_vs("111000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scuintbase_param - value = " << scuintbv_vs.get_string());
  scuintb_param.set_value(scuintbv_vs);
  scuintb = scuintb_param.get_value().get_int64();
  DEMO_DUMP(name(), "  got " << scuintb << endl);
  
  cci::cnf::cci_value scsigned_v(-3000);
  DEMO_DUMP(name(), "Set and get parameter Owner.scsigned_param - value = " << scsigned_v.get_int64());
  scsigned_param.set_value(scsigned_v);
  std::string scsigned(scsigned_param.get_value().get_string());
  DEMO_DUMP(name(), "  got " << scsigned << endl);
  cci::cnf::cci_value scsigned_vs("-2000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scsigned_param - value = " << scsigned_vs.get_string());
  scsigned_param.set_value(scsigned_vs);
  scsigned = scsigned_param.get_value().get_string();
  DEMO_DUMP(name(), "  got " << scsigned << endl);
  
  cci::cnf::cci_value scunsigned_v(3000);
  DEMO_DUMP(name(), "Set and get parameter Owner.scunsigned_param - value = " << scunsigned_v.get_int64());
  scunsigned_param.set_value(scunsigned_v);
  std::string scunsigned(scunsigned_param.get_value().get_string());
  DEMO_DUMP(name(), "  got " << scunsigned << endl);
  cci::cnf::cci_value scunsigned_vs("2000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scunsigned_param - value = " << scunsigned_vs.get_string());
  scunsigned_param.set_value(scunsigned_vs);
  scunsigned = scunsigned_param.get_value().get_string();
  DEMO_DUMP(name(), "  got " << scunsigned << endl);
  
  // deprecated data type not implemented in prototype
  //cci::cnf::cci_value scbit_v(1);
  //DEMO_DUMP(name(), "Set and get parameter Owner.scbit_param - value = " << scbit_v.get_int());
  //scbit_param.set_value(scbit_v);
  //sc_dt::sc_bit scbit(scbit_param.get_value().get_int());
  //DEMO_DUMP(name(), "  got " << scbit << endl);

  cci::cnf::cci_value sclogic_v(1);
  DEMO_DUMP(name(), "Set and get parameter Owner.sclogic_param - value = " << sclogic_v.get_int());
  sclogic_param.set_value(sclogic_v);
  sc_dt::sc_logic sclogic;
  std::stringstream error;
  //try {
  //  sclogic = sclogic_param.get_value().get_int();
  //} catch(sc_core::sc_report e) {
  //  error << std::endl << name() << ": Caught " << e.what() << std::endl;
  //  try {
      sclogic = sclogic_param.get_value().get_string().at(0);
  //  } catch(sc_core::sc_report e) {
  //    error << std::endl << name() << ": Caught " << e.what();
  //    std::cout << error << std::endl;
  //  }
  //}
  DEMO_DUMP(name(), "  got " << sclogic << endl);
  sclogic_param = sc_dt::Log_X;
  std::cout << "get cci_value X: " << sclogic_param.get_value().get_string() << std::endl;
  cci::cnf::cci_value sclogic_v1("Z");
  std::cout << "set cci_value  Z " << std::endl;
  sclogic_param.set_value(sclogic_v1);
  std::cout << "get cci_value: " << sclogic_param.get_value().get_string() << std::endl << std::endl;
  
  // checks:
  sc_core::sc_time ti1(1, sc_core::SC_FS); std::cout << ti1 << " ";
  sc_core::sc_time ti2(1, sc_core::SC_PS); std::cout << ti2 << " ";
  sc_core::sc_time ti3(1, sc_core::SC_NS); std::cout << ti3 << " ";
  sc_core::sc_time ti4(1, sc_core::SC_US); std::cout << ti4 << " ";
  sc_core::sc_time ti5(1, sc_core::SC_MS); std::cout << ti5 << " ";
  sc_core::sc_time ti6(1, sc_core::SC_SEC); std::cout << ti6 << std::endl;
  // recommended style double (value) + string (unit)
  cci::cnf::cci_value_list sctime_v_lst;
  sctime_v_lst.push_back(cci::cnf::cci_value(10.123));
  sctime_v_lst.push_back(cci::cnf::cci_value("SC_NS"));
  cci::cnf::cci_value sctime_v(sctime_v_lst);
  // alternative style string ???
  //cci::cnf::cci_value sctime_v2("10.123 SC_PS");
  DEMO_DUMP(name(), "Set and get parameter Owner.sctime_param - value = " << sctime_v.get_list().at(0).get_real() << " " << sctime_v.get_list().at(1).get_string() );
  sctime_param.set_value(sctime_v);
  std::cout << "raw from cci_value (real, string): "<< sctime_param.get_value().get_list().at(0).get_real() << " " << sctime_param.get_value().get_list().at(1).get_string() << std::endl;
  sc_core::sc_time sctime(sctime_param.get_value().get_list().at(0).get_real(), string_to_sc_time_unit(sctime_param.get_value().get_list().at(1).get_string()));
  DEMO_DUMP(name(), "  got " << sctime.to_string() << endl);
    
  cci::cnf::cci_value scint_v(-9223372036854775807ll);
  DEMO_DUMP(name(), "Set and get parameter Owner.scint64_param - value = " << scint_v.get_int64());
  scint64_param.set_value(scint_v);
  sc_dt::sc_int<64> scint(scint64_param.get_value().get_int64());
  DEMO_DUMP(name(), "  got " << scint << endl);
  
  cci::cnf::cci_value scuint_v((sc_dt::int64)18446744073709551615ull);
  DEMO_DUMP(name(), "Set and get parameter Owner.scuint64_param - value = " << (sc_dt::uint64) scuint_v.get_int64());
  scuint64_param.set_value(scuint_v);
  sc_dt::sc_uint<64> scuint(scuint64_param.get_value().get_int64());
  DEMO_DUMP(name(), "  got " << scuint << endl);
  
  cci::cnf::cci_value scbigint_v("-170141183460469200000000000000000000000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scbigint128_param - value = " << scbigint_v.get_string());
  scbigint128_param.set_value(scbigint_v);
  sc_dt::sc_bigint<128> scbigint(scbigint128_param.get_value().get_string().c_str());
  DEMO_DUMP(name(), "  got " << scbigint << endl);
  
  cci::cnf::cci_value scbiguint_v("340282366920938463463374607431760000000");
  DEMO_DUMP(name(), "Set and get parameter Owner.scbiguint128_param - value = " << scbiguint_v.get_string());
  scbiguint128_param.set_value(scbiguint_v);
  sc_dt::sc_biguint<128> scbiguint(scbiguint128_param.get_value().get_string().c_str());
  DEMO_DUMP(name(), "  got " << scbiguint << endl);
  
  
  
  cout << endl;
  cout << "-------------------------" << endl;
  
  // demonstrate setting a parameter using a cci value OF WRONG TYPE
  DEMO_DUMP(name(), "Set unsigned integer parameter Owner.uint_param to string value=\"Hello\" using WRONG cci_value type!");
  cci::cnf::cci_value valStr("Hello");
  try {
    uint_param.set_value(valStr);
  } catch(sc_core::sc_report e) {
    switch ( cci::cnf::cci_report_handler::get_param_failure(e) ) {
      case cci::cnf::CCI_VALUE_FAILURE: 
        std::cout << std::endl << name() << ": Caught " << e.what() << std::endl;
        break;
      default:
        // If other error, throw it again
        throw e;
    }
  }
  cout << endl;

  // demonstrate setting a parameter (that does not support cci_values) using a cci value
#ifdef ENABLE_CCI_VALUE_SUPPORT_FOR_TEST_DATATYPE
  DEMO_DUMP(name(), "Set user data type parameter that does not support cci_values using a cci_value (disabled ENABLE_CCI_VALUE_SUPPORT_FOR_TEST_DATATYPE)!");
#else
  DEMO_DUMP(name(), "Set user data type parameter that does support cci_values using a cci_value (enabled ENABLE_CCI_VALUE_SUPPORT_FOR_TEST_DATATYPE)!");
#endif
  try {
    some_param.set_value(valStr);
  } catch(sc_core::sc_report e) {
    switch ( cci::cnf::cci_report_handler::get_param_failure(e) ) {
      case cci::cnf::CCI_VALUE_FAILURE: 
        std::cout << std::endl << name() << ": Caught " << e.what() << std::endl;
        break;
      default:
        // If other error, throw it again
        throw e;
    }
  }
  

}

sc_core::sc_time_unit string_to_sc_time_unit(const std::string& str) {
  std::string stri(str);
  boost::to_upper(stri);
  if      (stri.compare("SC_FS") == 0 || stri.compare("FS") == 0) return sc_core::SC_FS;
  else if (stri.compare("SC_PS") == 0 || stri.compare("PS") == 0) return sc_core::SC_PS;
  else if (stri.compare("SC_NS") == 0 || stri.compare("NS") == 0) return sc_core::SC_NS;
  else if (stri.compare("SC_US") == 0 || stri.compare("US") == 0) return sc_core::SC_US;
  else if (stri.compare("SC_MS") == 0 || stri.compare("MS") == 0) return sc_core::SC_MS;
  else if (stri.compare("SC_SEC") == 0 || stri.compare("SEC") == 0) return sc_core::SC_SEC;
  else std::cout << "Fehler in string_to_sc_time_unit" << std::endl;
  return sc_core::SC_SEC;
}
