//  conversion_test.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/conversion.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <cstring>

namespace be = boost::endian;
using std::cout;
using std::endl;
using boost::int8_t;
using boost::uint8_t;
using boost::int16_t;
using boost::uint16_t;
using boost::int32_t;
using boost::uint32_t;
using boost::int64_t;
using boost::uint64_t;

namespace
{

  //  values for tests

  void native_value(int8_t& x) {x = static_cast<int8_t>(0xF0U);}
  void native_value(uint8_t& x) {x = static_cast<uint8_t>(0xF0U);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int8_t& x) {x = static_cast<int8_t>(0xF0U);}
  void big_value(uint8_t& x) {x = static_cast<uint8_t>(0xF0U);}
  void little_value(int8_t& x) {x = static_cast<int8_t>(0xF0U);}
  void little_value(uint8_t& x) {x = static_cast<uint8_t>(0xF0U);}
# else
  void big_value(int8_t& x) {x = static_cast<int8_t>(0xF0U);}
  void big_value(uint8_t& x) {x = static_cast<uint8_t>(0xF0U);}
  void little_value(int8_t& x) {x = static_cast<int8_t>(0xF0U);}
  void little_value(uint8_t& x) {x = static_cast<uint8_t>(0xF0U);}
# endif

  void native_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void native_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void big_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
  void little_value(int16_t& x) {x = static_cast<int16_t>(0x02F1U);}
  void little_value(uint16_t& x) {x = static_cast<uint16_t>(0x02F1U);}
# else
  void big_value(int16_t& x) {x = static_cast<int16_t>(0x02F1U);}
  void big_value(uint16_t& x) {x = static_cast<uint16_t>(0x02F1U);}
  void little_value(int16_t& x) {x = static_cast<int16_t>(0xF102U);}
  void little_value(uint16_t& x) {x = static_cast<uint16_t>(0xF102U);}
# endif

  void native_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void native_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void big_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
  void little_value(int32_t& x) {x = static_cast<int32_t>(0x0413E2F1UL);}
  void little_value(uint32_t& x) {x = static_cast<uint32_t>(0x0413E2F1UL);}
# else
  void big_value(int32_t& x) {x = static_cast<int32_t>(0x0413E2F1UL);}
  void big_value(uint32_t& x) {x = static_cast<uint32_t>(0x0413E2F1UL);}
  void little_value(int32_t& x) {x = static_cast<int32_t>(0xF1E21304UL);}
  void little_value(uint32_t& x) {x = static_cast<uint32_t>(0xF1E21304UL);}
# endif

  void native_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void native_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
# ifdef BOOST_BIG_ENDIAN
  void big_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void big_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
  void little_value(int64_t& x) {x = static_cast<int64_t>(0x01122344C4D3E2F1ULL);}
  void little_value(uint64_t& x) {x = static_cast<uint64_t>(0x01122344C4D3E2F1ULL);}
# else
  void big_value(int64_t& x) {x = static_cast<int64_t>(0x01122344C4D3E2F1ULL);}
  void big_value(uint64_t& x) {x = static_cast<uint64_t>(0x01122344C4D3E2F1ULL);}
  void little_value(int64_t& x) {x = static_cast<int64_t>(0xF1E2D3C444231201ULL);}
  void little_value(uint64_t& x) {x = static_cast<uint64_t>(0xF1E2D3C444231201ULL);}
# endif

  const float float_value = -1.234F;
  const double double_value = -1.234567;

  void native_value(float& x) {std::memcpy(&x, &float_value, sizeof(float));}
  void native_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
# ifdef BOOST_BIG_ENDIAN
  void big_value(float& x) {memcpy(&x, &float_value, sizeof(float));}
  void big_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
  void little_value(float& x)
  {
    memcpy(&x, &float_value, sizeof(float));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(float));
  }
  void little_value(double& x)
  {
    memcpy(&x, &double_value, sizeof(double));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(double));
  }
# else
  void big_value(float& x)
  {
    memcpy(&x, &float_value, sizeof(float));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(float));
  }
  void big_value(double& x)
  {
    memcpy(&x, &double_value, sizeof(double));
    std::reverse(reinterpret_cast<char*>(&x),
      reinterpret_cast<char*>(&x)+sizeof(double));
  }
  void little_value(float& x) {memcpy(&x, &float_value, sizeof(float));}
  void little_value(double& x) {memcpy(&x, &double_value, sizeof(double));}
# endif

  template <class T>
  void test()
  {
    T native;
    T big;
    T little;
    native_value(native);
    big_value(big);
    little_value(little);

    //  validate the values used by the tests below

# ifdef BOOST_BIG_ENDIAN
    BOOST_TEST_EQ(native, big);
    BOOST_TEST_EQ(be::detail::std_reverse_endianness(native), little);
# else
    BOOST_TEST_EQ(be::detail::std_reverse_endianness(native), big);
    BOOST_TEST_EQ(native, little);
# endif

    //  value-by-value tests

    //  unconditional reverse
    BOOST_TEST_EQ(be::reverse_endianness(big), little);
    BOOST_TEST_EQ(be::reverse_endianness(little), big);

    //  conditional reverse
    BOOST_TEST_EQ(be::native_to_big(native), big);
    BOOST_TEST_EQ(be::native_to_little(native), little);
    BOOST_TEST_EQ(be::big_to_native(big), native);
    BOOST_TEST_EQ(be::little_to_native(little), native);

    //  generic conditional reverse
    BOOST_TEST_EQ((be::conditional_reverse<be::order::big, be::order::big>(big)), big);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::little,
      be::order::little>(little)), little);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::native,
      be::order::native>(native)), native);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::big,
      be::order::little>(big)), little);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::big,
      be::order::native>(big)), native);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::little,
      be::order::big>(little)), big);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::little,
      be::order::native>(little)), native);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::native,
      be::order::big>(native)), big);
    BOOST_TEST_EQ((be::conditional_reverse<be::order::native,
      be::order::little>(native)), little);

    //  runtime conditional reverse
    BOOST_TEST_EQ((be::runtime_conditional_reverse(big, be::order::big, be::order::big)),
      big);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(little, be::order::little,
      be::order::little)), little);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(native, be::order::native,
      be::order::native)), native);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(big, be::order::big,
      be::order::little)), little);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(big, be::order::big,
      be::order::native)), native);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(little, be::order::little,
      be::order::big)), big);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(little, be::order::little,
      be::order::native)), native);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(native, be::order::native,
      be::order::big)), big);
    BOOST_TEST_EQ((be::runtime_conditional_reverse(native, be::order::native,
      be::order::little)), little);

    //  modify-in-place tests

    T x;

    //  unconditional reverse
    x = big; be::reverse_endianness_in_place(x); BOOST_TEST_EQ(x, little);
    x = little; be::reverse_endianness_in_place(x); BOOST_TEST_EQ(x, big);

    //  conditional reverse
    x = native; be::native_to_big_in_place(x); BOOST_TEST_EQ(x, big);
    x = native; be::native_to_little_in_place(x);  BOOST_TEST_EQ(x, little);
    x = big; be::big_to_native_in_place(x);  BOOST_TEST_EQ(x, native);
    x = little; be::little_to_native_in_place(x); BOOST_TEST_EQ(x, native);

    //  generic conditional reverse
    x = big; be::conditional_reverse_in_place<be::order::big, be::order::big>(x);
      BOOST_TEST_EQ(x, big);
    x = little; be::conditional_reverse_in_place<be::order::little, be::order::little>(x);
      BOOST_TEST_EQ(x, little);
    x = native; be::conditional_reverse_in_place<be::order::native, be::order::native>(x);
      BOOST_TEST_EQ(x, native);
    x = big; be::conditional_reverse_in_place<be::order::big, be::order::little>(x);
      BOOST_TEST_EQ(x, little);
    x = big; be::conditional_reverse_in_place<be::order::big, be::order::native>(x);
      BOOST_TEST_EQ(x, native);
    x = little; be::conditional_reverse_in_place<be::order::little, be::order::big>(x);
      BOOST_TEST_EQ(x, big);
    x = little; be::conditional_reverse_in_place<be::order::little, be::order::native>(x);
      BOOST_TEST_EQ(x, native);
      x = native; be::conditional_reverse_in_place<be::order::native, be::order::big>(x);
      BOOST_TEST_EQ(x, big);
    x = native; be::conditional_reverse_in_place<be::order::native, be::order::little>(x);
      BOOST_TEST_EQ(x, little);

    //  runtime conditional reverse
    x = big;
      be::runtime_conditional_reverse_in_place(x, be::order::big, be::order::big);
      BOOST_TEST_EQ(x, big);
    x = little;
      be::runtime_conditional_reverse_in_place(x, be::order::little, be::order::little);
      BOOST_TEST_EQ(x, little);
    x = native;
      be::runtime_conditional_reverse_in_place(x, be::order::native, be::order::native);
      BOOST_TEST_EQ(x, native);
    x = big;
      be::runtime_conditional_reverse_in_place(x, be::order::big, be::order::little);
      BOOST_TEST_EQ(x, little);
    x = big;
      be::runtime_conditional_reverse_in_place(x, be::order::big, be::order::native);
      BOOST_TEST_EQ(x, native);
    x = little;
      be::runtime_conditional_reverse_in_place(x, be::order::little, be::order::big); 
      BOOST_TEST_EQ(x, big);
    x = little;
      be::runtime_conditional_reverse_in_place(x, be::order::little, be::order::native); 
      BOOST_TEST_EQ(x, native);
    x = native;
      be::runtime_conditional_reverse_in_place(x, be::order::native, be::order::big); 
      BOOST_TEST_EQ(x, big);
    x = native;
      be::runtime_conditional_reverse_in_place(x, be::order::native, be::order::little); 
      BOOST_TEST_EQ(x, little);

  }
}  // unnamed namespace

//--------------------------------------------------------------------------------------//

   //  User-defined type 
  
  namespace user
  {
    struct UDT
    {
      int64_t member1;
      int64_t member2;
      int64_t member3;
    };

    UDT reverse_endianness(const UDT& udt) BOOST_NOEXCEPT
    {
      UDT tmp;
      tmp.member1 = boost::endian::reverse_endianness(udt.member1);
      tmp.member2 = boost::endian::reverse_endianness(udt.member2);
      tmp.member3 = boost::endian::reverse_endianness(udt.member3);
      return tmp;
    }

    void reverse_endianness_in_place(UDT& udt) BOOST_NOEXCEPT
    {
      boost::endian::reverse_endianness_in_place(udt.member1);
      boost::endian::reverse_endianness_in_place(udt.member2);
      boost::endian::reverse_endianness_in_place(udt.member3);
    }

  }  // namespace user

//--------------------------------------------------------------------------------------//

int cpp_main(int, char * [])
{
  cout << "byte swap intrinsics: " BOOST_ENDIAN_INTRINSIC_MSG << endl;
  
  //std::cerr << std::hex;

  cout << "int8_t" << endl;
  test<int8_t>();
  cout << "uint8_t" << endl;
  test<uint8_t>();

  cout << "int16_t" << endl;
  test<int16_t>();
  cout << "uint16_t" << endl;
  test<uint16_t>();

  cout << "int32_t" << endl;
  test<int32_t>();
  cout << "uint32_t" << endl;
  test<uint32_t>();

  cout << "int64_t" << endl;
  test<int64_t>();
  cout << "uint64_t" << endl;
  test<uint64_t>();

  cout << "float" << endl;
  test<float>();
  cout << "double" << endl;
  test<double>();

  cout << "UDT" << endl;
  user::UDT udt;
  int64_t big;
  int64_t little;
  int64_t native;
  big_value(big);
  little_value(little);
  native_value(native);

  udt.member1 = big;
  udt.member2 = little;
  udt.member3 = native;
  be::conditional_reverse_in_place<be::order::big, be::order::little>(udt);
  BOOST_TEST_EQ(udt.member1, be::reverse_endianness(big));
  BOOST_TEST_EQ(udt.member2, be::reverse_endianness(little));
  BOOST_TEST_EQ(udt.member3, be::reverse_endianness(native));

  udt.member1 = big;
  udt.member2 = little;
  udt.member3 = native;
  be::conditional_reverse_in_place<be::order::big, be::order::big>(udt);
  BOOST_TEST_EQ(udt.member1, big);
  BOOST_TEST_EQ(udt.member2, little);
  BOOST_TEST_EQ(udt.member3, native);

  return ::boost::report_errors();
}

#include <boost/endian/detail/disable_warnings_pop.hpp>