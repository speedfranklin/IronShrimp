//------------------------------------------------------------------------------
//                   Copyright (c) 2003-2015 Codalogic Ltd.
//
// This file forms part of THE SUPPORTING SOFTWARE of Codalogic's LMX W3C
// Schema to C++ code generator product.  It may not be used independent of
// files legitimately generated and used by the LMX product.  See the LMX
// licence agreement for further restrictions on the use of this file.
//
// THIS FILE AND THE SOFTWARE CONTAINED HEREIN IS PROVIDED 'AS IS' AND COMES
// WITH NO WARRANTIES OF ANY KIND.
//
// CODALOGIC LTD SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY ANYONE
// OR ANYTHING DUE TO THE USE OF THIS FILE HOWEVER THEY MAY BE CAUSED.
//
// For more information on the LMX compiler, go to:
//
//     http://www.xml2cpp.com
//
// Also see:
//
//     http://www.codalogic.com
//
// Notes:   is_occurs_ok_is_required - An optional item in a base class my be
//          restricted in a derived class to be required.  Hence when testing
//          is_occurs_ok() on an item we need to specify whether it is
//          required or not even though the type with which it is stored
//          suggests it is optional.
//
// A note on version numbers: We often make builds of the code in response to
//      customer requests.  Such builds may not be formally released as an
//      official build, but are still given a version number.  Hence, in the
//      version history below you will see version numbers that do not
//      directly correspond to formal releases.
//
// Version 7.2:
//      - !C170428_1753: Enhanced s_debug_error to support customized error
//        descriptions for user defined errors.
//
// Version 7.1.4:
//      - !C160721_1012: Removed LMX_PDECL from in front of classes that
//        derive from std::exception to avoid MSVC warning 4275 being
//        generated.
//
// Version 7.1.3:
//      - !C160504_1254: ct_simple_pod_list_single::clear() now marks a list
//        as present.
//
// Version 7.1.2:
//      - !C160420_1332: Fixed c_namespace_context.swap() code.
//      - !C160421_1501: Fixed c_namespace_context.clear() code.
//
// Version 7.1:
//      - !C150217_1231: Included struct lmx::uniq_ptr in order to migrate
//        std::auto_ptr use to C++11.
//
// Version 6.4:
//      - !C130509_1309: c_lmx_exception now derives from std::exception.
//      - !C130509_1312: Added no throw declarations for exception virtual
//        destructors.
//
// Version 6.3:
//      - Updated variable naming convention.
//
// Version 6.2:
//      - !C120411_0908: Made ct_simple_pod_single always marshal a value
//        even if value has not been explicitly set by user.  Moved original
//        version of count() to ct_simple_pod_optional.
//      - !C121019_1950: Changed release( p ) in
//        ct_complex_optional<T>::unset()to Tdeleter::release( p );
//      - !C121119_0851: Qualified push_back( ar_new ) in ct_pod_container
//        with TC::push_back( ar_new ).
//      - !C121120_1245: Added ability for container objects to get relevant
//        bridge object in order to work around over optimisation bugs in
//        gcc4.2.3, 4.3.3 and 4.4.1 etc.
//
// Version 6.1:
//      - !C120312_1122: Rearranged the code in ct_non_pod_container( const
//        Tself & ar_rhs ) so that the try/catch block is no longer required.
//
// Version 6:
//      - C110918_1018
//      - Significant refactoring due to addition of bridge classes.
//
//
// Version: 5.6
//      - !C110507_1734 - Added initialisers for template members.
//
// Version: 5.5
//      - !C110301_1550: Added additional methods to ct_simple_pod_multi and
//        ct_complex_multi so they can they include the same interface methods
//        as single and optional types so they can be readily used when
//        complex content restriction has restricted the number of times an
//        element can occur from multi occurs to be optional or single.
//      - !C110301_1621: Added polymorphic assign to c_complex_multi.
//      - !C110318_1330: Changed some std::vector accessors to use .at() rather
//        than [] so that exceptions would be thrown if users asks for
//        something that is not there.
//
// Version: 5.4.4
//      - !C110110_2117: Reversed order of c_marshalable and
//        ct_grin_or_happy_ptr_deleter< T > in base list of ct_complex_optional.
//
// Version: 5.3
//      - !C100916_1604: ct_complex_single<T> now derives from
//        ct_complex_optional<T> instead of vice versa so that the former can
//        allocate the mandatory object rather than relying on code to do it.
//      - !C100916_1636: Similar to C100916_1604, ct_empty_single also
//        automatically sets itself to present rather than relying on the code
//        generator to do it.
//
// Version: 5.2
//      - !C100902_2046: ct_simple_pod_multi and ct_simple_pod_list_single
//        now create additional members for non-const get() and set() methods.
//
// Version: 5.1.1
//      - !C100825_2018: Added support for insert_XYZ( size_t a_index, T * a_p )
//        methods
//
// Version: 5.0.5
//      - !C100510_1423: Changed name of .isset() methods on classes to
//        .is_value_set() to avoid problems when other code defines an isset()
//        macro (e.g. HP aCC).
//
// Version: 5
//      - Reformatted.
//      - Added LMX Generation 2 (LMXG2) code.
//      - Added == and != to c_empty.
//      - Added == and != to c_any_info.
//
// Version: 4.1.2
//      - Added c_namespace_context and other machinery so that namespace
//        context can be collected by c_any_info.
//      - Added get_local_name() to c_any_info.
//
// Version: 3.10
//      - Moved string_size(), string_swap(), string_eq() and string_empty()
//        to lmxuser.h to solve dependencies when compiling under GCC 4.1.2.
//
// Version: 3.9.2
//      - Added string_size(), string_swap(), string_eq() and string_empty()
//        template functions.
//      - String and binary initialisers moved to lmxuser.h.
//
// Version: 3.8.1
//      - Added c_lmx_exception_with_name exception class.
//
// Version: 3.8
//      - Added ELMX_USER_DEFINED_[1-9] to elmx_error enumeration.  This is
//        primarily intended for passing back user generated errors when
//        processing snippet events.
//      - Added ELMX_OCCURRENCE_ERROR to elmx_error enumeration.
//
// Version: 3.7.5
//      - Added declaration of struct s_known_elements.
//
// Version: 3.7.1
//      - s_debug_error and debug_error moved from lmxparse.h into this file.
//
// Version: 3.6
//      - Added c_empty to allow for multiple empty elements.
//
// Version: 3.4
//      - Added ELMX_UNKNOWN_XSI_TYPE and ELMX_TYPE_NOT_SET
//        error codes.
//
// Version: 3.3
//      - Added QName, from_hex and from_base64 helper functions.
//
// Version: 3.2
//      - Added ELMX_VALUE_DOES_NOT_MATCH_FIXED_CONSTRAINT error constant.
//
// Version: 3.0
//      - Used std:: versions of a number of C utility functions.
//      - Added definition of t_class_identity.
//
// Version: 3.0 (Beta)
//      - Moved xisxxxx() functions to this header file from lmxtypes.h
//      - ELMX_UNDEFINED_ERROR error code added.
//
// Version: 2.11.3
//      - Added virtual destructor to c_lmx_exception to remove GCC 4.x
//        warnings.
//
// Version: 2.11
//      - No changes
//
// Version: 2.10
//      - Unicode handling extended beyond the Basic Multi-lingual Plane
//        to full Unicode range (0x-0x10ffff).
//
// Version: 2.9.2
//      - Added switches for MS VC 2005
//
// Version: 2.9
//      - No changes
//
// Version: 2.8
//      - No changes
//
// Version: 2.7
//      - Moved inittowidestring as an inline function into this file allow
//        control of wide vs. narrow string usage for customers without
//        supporting software source code.
//
// Version: 2.6
//
// Version: 2.5
//
//------------------------------------------------------------------------------


#ifndef LMXINTERNALS_H
#define LMXINTERNALS_H

#if defined( _MSC_VER ) && _MSC_VER > 1000
#pragma once
#pragma warning(disable:4786)
#endif

#if defined( _MSC_VER ) && _MSC_VER >= 1400
#pragma warning (push)
#pragma warning (disable:4996)  // Disable VC8 'safe' warnings
#endif

#ifndef LMXUSER_H
#error lmxinternals.h should now be included via lmxuser.h in order to setup declspec
#endif

#if defined( __BORLANDC__ )
    #pragma warn -8004
    #pragma warn -8012
#endif

#include <cctype>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace lmx {

// Bring std::swap functions into lmx namespace so we can use them without a
// prefix
using std::swap;

// Can't use the following code to do swap because vc10 complains about abiguity
//template< typename T >
//void swap( T & ar_lhs, T & ar_rhs )
//{
//    std::swap( ar_lhs, ar_rhs );    // Use std::swap if LMX doesn't provide a special version
//}

// Enable for backwards compatibility with v5.0 - C100510_1423
#ifdef LMX_USE_ISSET_METHOD
#define is_value_set isset
#endif

//------------------------------------------------------------------------------
//                           C++11 Migration Support
//------------------------------------------------------------------------------

template<typename T>
struct uniq_ptr
{
#if __cplusplus < 201103L
    typedef std::auto_ptr<T> type;
#else
    typedef std::unique_ptr<T> type;
#endif
};

//------------------------------------------------------------------------------
//                             xs:all ordering constants
//------------------------------------------------------------------------------

const size_t k_all_order_not_present = ~static_cast<size_t>( 0 );

//------------------------------------------------------------------------------
//                             Error codes
//------------------------------------------------------------------------------

enum elmx_error_type { EET_FATAL, EET_ERROR, EET_WARNING, EET_NOTE, EET_NONE };

enum elmx_error {
    ELMX_OK,
    ELMX_NO_FILE,
    ELMX_ALL_CARDINALITY_VIOLATION,
    ELMX_ATTRIBUTE_ALREADY_READ,
    ELMX_ATTRIBUTES_IN_ANONYMOUS_COMPOSITOR,
    ELMX_BADLY_FORMED,
    ELMX_BAD_CHAR_ENCODING,
    ELMX_BAD_CHOICE,
    ELMX_BAD_COMMENT,
    ELMX_BAD_DTD,
    ELMX_BAD_ELEMENT_END,
    ELMX_BAD_END_OF_START_TAG,
    ELMX_BAD_END_TAG,
    ELMX_BAD_XML_DECL,
    ELMX_BAD_XML_VERSION,
    ELMX_CHAR_ENCODING_MISMATCH,
    ELMX_ELEMENT_NOT_FOUND,
    ELMX_EXTERNAL_ENTITY,
    ELMX_FRACTION_DIGITS_EXCEEDED,
    ELMX_LENGTH_TOO_LONG,
    ELMX_LENGTH_TOO_SHORT,
    ELMX_MANDATORY_ELEMENT_MISSING,
    ELMX_NO_PATTERN_MATCHED,
    ELMX_NOT_WELL_FORMED,
    ELMX_RECURSIVE_ENTITY_DEFINITION,
    ELMX_REQUIRED_ATTRIBUTES_MISSING,
    ELMX_TOO_MANY_ITEMS,
    ELMX_TOTAL_DIGITS_EXCEEDED,
    ELMX_UNABLE_TO_READ_ATTRIBUTE_VALUE,
    ELMX_UNABLE_TO_READ_ELEMENT_VALUE,
    ELMX_UNEXPECTED_ALL_EVENT,
    ELMX_UNEXPECTED_ELEMENT_EVENT,
    ELMX_UNEXPECTED_EMPTY_ELEMENT,
    ELMX_UNEXPECTED_ENTITY,
    ELMX_UNEXPECTED_EOM,
    ELMX_VALUE_BAD_FORMAT,
    ELMX_VALUE_EXCEEDS_MAX,
    ELMX_VALUE_EXCEEDS_MIN,
    ELMX_VALUE_NOT_ENUMERATED,
    //------------------------
    // Added in V2.1
    ELMX_UNEXPECTED_ATTRIBUTE,
    ELMX_NILLED_ELEMENT_NOT_EMPTY,
    //------------------------
    // Added in V2.7
    ELMX_ENTITY_NOT_FOUND,
    //------------------------
    // Added in V3.0
    ELMX_UNDEFINED_ERROR,   // Used as an initialization value that can be later overwritten with a valid error code
    //------------------------
    // Added in V3.2
    ELMX_VALUE_DOES_NOT_MATCH_FIXED_CONSTRAINT,
    //------------------------
    // Added in V3.4
    ELMX_UNKNOWN_XSI_TYPE,
    ELMX_TYPE_NOT_SET,
    //------------------------
    // Added in V3.8
    ELMX_OCCURRENCE_ERROR,
    //------------------------
    ELMX_LAST_ERROR,

    //------------------------
    // Added in V3.8 - primarily for use by users in snippet event handlers
    ELMX_USER_DEFINED_1 = 1000,
    ELMX_USER_DEFINED_2,
    ELMX_USER_DEFINED_3,
    ELMX_USER_DEFINED_4,
    ELMX_USER_DEFINED_5,
    ELMX_USER_DEFINED_6,
    ELMX_USER_DEFINED_7,
    ELMX_USER_DEFINED_8,
    ELMX_USER_DEFINED_9
};

enum elxp_xml_event
{
    // General events
    EXE_EOM,
    EXE_UNKNOWN,
    EXE_FATAL_ERROR,

    // XML events
    EXE_BADLY_FORMED,
    EXE_START_TAG_END,
    EXE_CDATA,
    EXE_ELEMENT_END,
    EXE_TOKEN,

    EXE_XSI_TYPE,
    EXE_XSI_NIL,
    EXE_XSI_SCHEMALOCATION,
    EXE_XSI_NONAMESPACESCHEMALOCATION,

    EXE_HAS_SKIPPED_UNKNOWN_ELEMENTS,

    EXE_LAST_XML_EVENT
};

enum elmx_whitespace { EXWS_PRESERVE, EXWS_REPLACE, EXWS_COLLAPSE };

//------------------------------------------------------------------------------
//                 Utility functions for initialising constants
//------------------------------------------------------------------------------

// V3.9.2 - String and binary initialisers moved to lmxuser.h

typedef char tc_utf8_buf[6+1];

// V3.3
inline tc_qname make_qname(
                    const std::string & r_qname_in,
                    const std::string & r_namespace_in,
                    const std::string & r_local_name_in )
{
    tc_qname qname;
    make_qname( &qname, r_qname_in, r_namespace_in, r_local_name_in );
    return qname;
}

//------------------------------------------------------------------------------
//                         Error code mapping support
//------------------------------------------------------------------------------

struct s_error_description
{
    elmx_error      code;
    const char *    to_string;
    const char *    p_description;
};

LMX_PDECL const s_error_description * get_error_mapping( elmx_error error_code_in );
LMX_PDECL const char * to_string( elmx_error error_code_in );
LMX_PDECL const char * get_error_description( elmx_error error_code_in );

//------------------------------------------------------------------------------
//                           LMX exception classes
// These are designed to be non-throwing.  Interogate c_xml_reader or
// c_xml_writer within the catch block to find out more information.
//------------------------------------------------------------------------------

class c_lmx_exception : public std::exception     // C130509_1309 // C160721_1012
{
private:
    elmx_error m_error_code;

public:
    c_lmx_exception( elmx_error error_code_in ) : m_error_code( error_code_in ) {}
    virtual ~c_lmx_exception() throw() {}   // v2.11.3 // C130509_1312
    elmx_error get_error() const { return m_error_code; }
    virtual const char * what() const throw()
    {
        return get_error_description( m_error_code );
    }
};

class c_lmx_exception_with_name : public c_lmx_exception  // V3.8.1 // C160721_1012
{
private:
    const char * mp_item_name;

public:
    c_lmx_exception_with_name( elmx_error error_code_in, const char * p_item_name_in ) :
            c_lmx_exception( error_code_in ), mp_item_name( p_item_name_in )
    {}
    virtual ~c_lmx_exception_with_name() throw() {} // C130509_1312
    const char * get_item_name() const { return mp_item_name; }
};

class c_lmx_reader_exception : public c_lmx_exception // C160721_1012
{
private:
    int m_line;

public:
    c_lmx_reader_exception( elmx_error error_code_in, int line_in ) :
            c_lmx_exception( error_code_in ), m_line( line_in )
    {}
    int get_line() const { return m_line; }
};

class c_check_exception : public std::exception
{
private:
    std::string location;
    const char * p_prog_file;
    int prog_line;

public:
    c_check_exception() : p_prog_file( "(not set)" ), prog_line( -1 ) {}
    c_check_exception( const std::string & r_location_in, const char * p_prog_file_in, int prog_line_in )
        : location( r_location_in ), p_prog_file( p_prog_file_in ), prog_line( prog_line_in )
    {}
    // c_check_exception( const c_check_exception & ) = default;
    // c_check_exception & operator = ( const c_check_exception & ) = default;
    virtual ~c_check_exception() throw() {}

    virtual const char * what() const throw() { return "lmx check exception"; }

    void set_location( const std::string & r_location_in ) { location = r_location_in; }
    const std::string & get_location() const { return location; }
    void set_prog_file( const char * p_prog_file_in ) { p_prog_file = p_prog_file_in; }
    const char * get_prog_file() const { return p_prog_file; }
    void set_prog_line( int prog_line_in ) { prog_line = prog_line_in; }
    int get_prog_line() const { return prog_line; }
};

LMX_PDECL extern c_check_exception global_check_exception;

class c_check_tracker
{
private:
    struct c_members {
        c_check_exception * p_exception;
        c_check_tracker * p_tracker_prev;
        const char * p_node_name;
        c_members() : p_exception( 0 ), p_tracker_prev( 0 ), p_node_name( 0 ) {}
    } m;

public:
    c_check_tracker() {}
    c_check_tracker( c_check_exception * p_exception_in ) { m.p_exception = p_exception_in; }
    c_check_tracker( c_check_tracker * p_tracker_prev_in )
        { m.p_tracker_prev = p_tracker_prev_in; }
    c_check_tracker( c_check_tracker * p_tracker_prev_in, const char * p_node_name_in )
        { m.p_tracker_prev = p_tracker_prev_in; m.p_node_name = p_node_name_in; }

    bool set_name( const char * p_node_name_in ) { m.p_node_name = p_node_name_in; return true; }   // Returns true so it can be included in if statement shortcut operators
    bool named_check( bool condition_in, const char * p_node_name_in )
    {
        if( condition_in )
            m.p_node_name = p_node_name_in;
        return condition_in;
    }

    bool report( const char * p_prog_file_in, int prog_line_in )
    {
        std::string location;
        c_check_exception * p_exception = build_location( &location );
        c_check_exception check_exception( location, p_prog_file_in, prog_line_in );
        if( p_exception )
            *p_exception = check_exception;
        global_check_exception = check_exception;
#if LMX_USE_CHECK_EXCEPTIONS == 1
        throw check_exception;
#endif
        return false;
    }

private:
    c_check_exception * build_location( std::string * p_location_out ) const
    {
        c_check_exception * p_exception = m.p_exception;
        if( m.p_tracker_prev )
            p_exception = m.p_tracker_prev->build_location( p_location_out );
        if( m.p_node_name )
            p_location_out->append( "/" ).append( m.p_node_name );
        return p_exception;
    }
};

//------------------------------------------------------------------------------
//                 Reader and writer class forward references
//------------------------------------------------------------------------------

typedef int t_xml_event;
typedef const char * t_class_identity;
struct s_event_map;
struct s_known_elements;    // V3.7.5
struct s_ns_map;    // Added in V2.9.2
class c_xml_reader;
class c_xml_writer;

//------------------------------------------------------------------------------
//                          struct s_debug_error
//  This structure provides a way to capture (un)marshalling error information
//  during code debugging.  It's prime purpose is to help debugging when the
//  convenience methods are being used.  If extended error information is
//  required in Release mode, then the Advanced forms of (un)marshalling should
//  be used.
//------------------------------------------------------------------------------

#if defined( _DEBUG ) && ! defined( LMX_DEBUG_CAPTURE_ERROR )
    #define LMX_DEBUG_CAPTURE_ERROR 1
#endif

struct s_custom_error_description   // Use in an array. Last entry should be { lmx::ELMX_OK, LMXNULL }
{
    elmx_error      code;
    const char *    p_description;
};  // C170428_1753

struct s_debug_error
{
    elmx_error error;
    std::string item_name;
    const char * p_prog_file;
    int prog_line;
    int xml_line;

    LMX_PDECL s_debug_error();
    LMX_PDECL void clear();
    LMX_PDECL void set( elmx_error error_in, const std::string & r_item_name_in,
                const char * p_prog_file_in, int prog_line_in, int xml_line_in = -1 );
    LMX_PDECL const char * get_description() const;
    LMX_PDECL const char * get_description( const s_custom_error_description * p_custom_error_description ) const;  // C170428_1753
    LMX_PDECL std::string to_string() const;
    LMX_PDECL std::string to_string( const s_custom_error_description * p_custom_error_description ) const;  // C170428_1753
    LMX_PDECL std::ostream & to_stream( std::ostream & r_os_in ) const;
    LMX_PDECL std::ostream & to_stream( std::ostream & r_os_in, const s_custom_error_description * p_custom_error_description  ) const;  // C170428_1753
};

LMX_PDECL std::ostream & operator << ( std::ostream & r_os_in, const s_debug_error & r_debug_error_in );

#if defined( LMX_DEBUG_CAPTURE_ERROR ) && LMX_DEBUG_CAPTURE_ERROR == 1
    LMX_PDECL extern s_debug_error debug_error;

    #define MK_LMX_DEBUG_ERROR_PTR( x ) lmx::s_debug_error *x = &lmx::debug_error;
    #define LMX_OUTPUT_DEBUG_ERROR( xstream ) xstream << lmx::debug_error
#else
    #define MK_LMX_DEBUG_ERROR_PTR( x )
    #define LMX_OUTPUT_DEBUG_ERROR( xstream )
#endif

//------------------------------------------------------------------------------
//                          c_custom_error_reporter
//------------------------------------------------------------------------------

class c_custom_error_reporter
{
private:
    const s_debug_error & r_debug_error;
    const s_custom_error_description * p_custom_error_descriptions;

    c_custom_error_reporter & operator = ( const c_custom_error_reporter & );

public:
    c_custom_error_reporter(
            const s_debug_error & r_debug_error_in,
            const s_custom_error_description * p_custom_error_descriptions_in )
        :
        r_debug_error( r_debug_error_in ),
        p_custom_error_descriptions( p_custom_error_descriptions_in )
    {}
    const char * get_description() const
    {
        return r_debug_error.get_description( p_custom_error_descriptions );
    }
    std::string to_string() const
    {
        return r_debug_error.to_string( p_custom_error_descriptions );
    }
    std::ostream & to_stream( std::ostream & r_os_in ) const
    {
        return r_debug_error.to_stream( r_os_in, p_custom_error_descriptions );
    }
};

inline std::ostream & operator << ( std::ostream & r_os_in, const c_custom_error_reporter & r_error_in )
{
    return r_error_in.to_stream( r_os_in );
}

//------------------------------------------------------------------------------
// Older compilers do not support two phase template instantiation.  These
// classes allow us to get around this problem using the arg::grin_ptr technique
// described at: http://www.octopull.demon.co.uk/arglib/TheGrin.html
//------------------------------------------------------------------------------

template< class T >
class ct_grin_ptr_deleter
{
private:
    typedef void (* tpfn_deleter)( T * );
    tpfn_deleter m_pfn_deleter;

public:
    ct_grin_ptr_deleter() : m_pfn_deleter( &deleter ) {}
    void release( T * ap ) { m_pfn_deleter( ap ); }

private:
    static void deleter( T * ap ) { delete ap; }
};

template< class T >
class ct_happy_ptr_deleter
{
public:
    void release( T * ap ) { delete ap; }

};

#if LMX_TWO_PHASE_TEMPLATES_SUPPORTED == 1
    template< class T >
    class ct_grin_or_happy_ptr_deleter : public ct_happy_ptr_deleter< T > {};
#else
    template< class T >
    class ct_grin_or_happy_ptr_deleter : public ct_grin_ptr_deleter< T > {};
#endif

//------------------------------------------------------------------------------
// ct_pod_container, ct_non_pod_container & ct_clonable_container:
// Low level containers
//------------------------------------------------------------------------------

template< typename T, typename TC = std::vector< T > >
class ct_pod_container : public TC
{
public:
    typedef ct_pod_container< T, TC > Tself;
    typedef TC Trawcontainer;

    T & at( size_t index_in )
    {
        #if defined( __GNUC__ ) && __GNUC__ == 2
            return (*this)[ index_in ];
        #else
            return TC::at( index_in );
        #endif
    }
    const T & at( size_t index_in ) const
    {
        #if defined( __GNUC__ ) && __GNUC__ == 2
            return (*this)[ index_in ];
        #else
            return TC::at( index_in );
        #endif
    }
    void insert( size_t index_in, const T & r_new_in )
    {
        if( index_in >= TC::size() )
            TC::push_back( r_new_in );    // C121119_0851
        else
            TC::insert( TC::begin() + index_in, r_new_in );
    }
    void erase( size_t index_in )
    {
        lmx_assert( index_in < TC::size() );
        TC::erase( TC::begin() + index_in );
    }

    Trawcontainer & raw_container() { return *this; }
    const Trawcontainer & raw_container() const { return *this; }
};

template<>
class ct_pod_container< bool > : public ct_pod_container< bool, std::deque< bool > >
{};

template< typename T, typename TC = std::vector< T * >, typename Tdeleter = ct_happy_ptr_deleter< T > >
class ct_non_pod_container : public Tdeleter
{
private:
    TC m_container;

public:
    typedef ct_non_pod_container< T, TC, Tdeleter > Tself;
    typedef typename TC::const_iterator Tconst_iterator;
    typedef typename TC::iterator Titerator;
    typedef TC Trawcontainer;

    ct_non_pod_container()
    {}
    ct_non_pod_container( const Tself & r_rhs_in )    // C120312_1122
    {
        Tself temp;
        for( Tconst_iterator i( r_rhs_in.m_container.begin() ), i_end( r_rhs_in.m_container.end() );
                i != i_end;
                ++i )
        {
            typename uniq_ptr< T >::type lap_new( new T( **i ) );
            temp.push_back( lap_new );
        }
        swap( temp );
    }
    ~ct_non_pod_container()
    {
        clear();
    }
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself temp( r_rhs_in );
        swap( temp );
        return *this;
    }
    void swap( Tself & r_rhs_in )
    {
        m_container.swap( r_rhs_in.m_container );
    }
    Tconst_iterator begin() const
    {
        return m_container.begin();
    }
    Titerator begin()
    {
        return m_container.begin();
    }
    Tconst_iterator end() const
    {
        return m_container.end();
    }
    Titerator end()
    {
        return m_container.end();
    }
    void push_back( T * p_new_in )
    {
        m_container.push_back( p_new_in );
    }
    void push_back( typename uniq_ptr< T >::type & arap_new )
    {
        m_container.push_back( arap_new.get() );
        arap_new.release();
    }
    void push_back( const T & r_new_in )
    {
        typename uniq_ptr< T >::type lap_t( new T( r_new_in ) );
        push_back( lap_t );
    }
    void push_back_w_autop( T * p_new_in )
    {
        typename uniq_ptr< T >::type lap_t( p_new_in );
        push_back( lap_t );
    }
    void insert( size_t index_in, typename uniq_ptr< T >::type & arap_new )
    {
        if( index_in >= size() )
            push_back( arap_new );
        else
        {
            m_container.insert( m_container.begin() + index_in, arap_new.get() );
            arap_new.release();
        }
    }
    void insert( size_t index_in, const T & r_new_in )
    {
        insert_w_autop( index_in, new T( r_new_in ) );
    }
    void insert_w_autop( size_t index_in, T * p_new_in )
    {
        typename uniq_ptr< T >::type lap_t( p_new_in );
        insert( index_in, lap_t );
    }
    T & assign( size_t index_in, T * p_new_in )    // Added to support C110301_1621
    {
        if( index_in >= size() )
        {
            push_back( p_new_in );
            return back();
        }
        else
        {
            if( ! p_new_in )
            {
                T *p_old = m_container[ index_in ];
                m_container[ index_in ] = 0;
                return *p_old;     // Assigning NULL pointer causes object to surrender ownership
            }
            delete m_container[ index_in ];
            m_container[ index_in ] = p_new_in;
        }
        return *(m_container[ index_in ]);
    }
    T & at( size_t index_in )
    {
        #if defined( __GNUC__ ) && __GNUC__ == 2
            return *(m_container[ index_in ]);
        #else
            return *(m_container.at( index_in ));
        #endif
    }
    const T & at( size_t index_in ) const
    {
        #if defined( __GNUC__ ) && __GNUC__ == 2
            return *(m_container[ index_in ]);
        #else
            return *(m_container.at( index_in ));
        #endif
    }
    T & operator [] ( size_t index_in )
    {
        return *(m_container[ index_in ]);
    }
    const T & operator [] ( size_t index_in ) const
    {
        return *(m_container[ index_in ]);
    }
    T & back()
    {
        return *(m_container.back());
    }
    const T & back() const
    {
        return *(m_container.back());
    }
    void erase( size_t index_in )
    {
        lmx_assert( index_in < size() );
        Tdeleter::release( *(m_container.begin() + index_in) );
        m_container.erase( m_container.begin() + index_in );
    }
    void clear()
    {
        for( Titerator i( m_container.begin() ), i_end( m_container.end() ); i != i_end; ++i )
            Tdeleter::release( *i );
        m_container.clear();
    }
    size_t size() const { return m_container.size(); }
    void resize( size_t new_size_in )
    {
        while( m_container.size() < new_size_in )
            push_back_w_autop( new T );
    }
    bool empty() const { return m_container.empty(); }
    bool operator == ( const Tself & r_rhs_in ) const
    {
        if( size() != r_rhs_in.size() )
            return false;
        for( size_t i=0; i<size(); ++i )
            if( (*this)[i] != r_rhs_in[i] )
                return false;
        return true;
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    Trawcontainer & raw_container() { return m_container; }
    const Trawcontainer & raw_container() const { return m_container; }
};

template< typename T, typename TC = std::vector< T * >, typename Tdeleter = ct_grin_or_happy_ptr_deleter< T > >
class ct_clonable_container : public ct_non_pod_container< T, TC, Tdeleter >
{
public:
    typedef ct_clonable_container< T, TC, Tdeleter > Tself;
    typedef ct_non_pod_container< T, TC, Tdeleter > Tbase;

    ct_clonable_container() {}
    ct_clonable_container( const Tself & r_rhs_in ) : ct_non_pod_container< T, TC, Tdeleter >() // Be explicit about not using ct_non_pod_container copy constructor
    {
        for( typename TC::const_iterator i( r_rhs_in.raw_container().begin() ), i_end( r_rhs_in.raw_container().end() ); i != i_end; ++i )
            Tbase::push_back_w_autop( (*i)->clone() );
    }
    void clone( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in );
        Tbase::swap( t );
    }
    Tself & operator = ( const Tself & r_rhs_in )
    {
        clone( r_rhs_in );
        return *this;
    }
};

//------------------------------------------------------------------------------
//                  Classes for representing special schema types
//------------------------------------------------------------------------------

struct s_namesapace_context_item    // v4.1.2
{
    std::string m_ns_prefix;
    std::string ns_uri;
    s_namesapace_context_item( const std::string & r_ns_prefix_in, const std::string & r_ns_uri_in )
        : m_ns_prefix( r_ns_prefix_in ), ns_uri( r_ns_uri_in )
        {}
};

class c_namespace_context   // v4.1.2
{
private:
    typedef std::vector< s_namesapace_context_item > t_container;
    t_container m_container;

public:
    c_namespace_context()
    {
        m_container.reserve( 6 );    // We don't expect many ns to uri mappings so keep it simple
    }
    c_namespace_context( const c_namespace_context & r_rhs_in ) : m_container( r_rhs_in.m_container )
    {}
    c_namespace_context & operator = ( const c_namespace_context & r_rhs_in )
    {
        c_namespace_context( r_rhs_in ).swap( *this );
        return *this;
    }
    void swap( c_namespace_context & r_rhs_in ) { m_container.swap( r_rhs_in.m_container ); }   // C160420_1332
    void add( const std::string &r_ns_prefix_in, const std::string &r_ns_uri_in )
    {
        for( size_t i=0; i<m_container.size(); ++i )
            if( m_container[i].m_ns_prefix == r_ns_prefix_in )
            {
                m_container[i].ns_uri = r_ns_uri_in;
                return;
            }
        m_container.push_back( s_namesapace_context_item( r_ns_prefix_in, r_ns_uri_in ) );
    }
    size_t size() const { return m_container.size(); }
    void clear() { m_container.clear(); }   // C160421_1501
    const std::string & get_ns_prefix( size_t index_in ) const { return m_container[index_in].m_ns_prefix; }
    const std::string & get_ns_uri( size_t index_in ) const { return m_container[index_in].ns_uri; }
};

class c_any_info
{
private:
    std::string m_namespace;
    std::string m_name;
    std::string m_value;
    c_namespace_context m_namespace_context;  // v4.1.2

public:
    c_any_info()
    {
    }
    // c_any_info( const c_any_info< t > & ) = default;
    // For writing during unmarshaling
    c_any_info( const std::string & r_namespace_in,
                const std::string & r_name_in,
                const std::string & r_value_in ) :
        m_namespace( r_namespace_in ),
        m_name( r_name_in ),
        m_value( r_value_in )
    {
    }
    // For user writing xs:anyAttribute
    c_any_info( const std::string & r_name_in,
                const std::string & r_value_in ) :
        m_name( r_name_in ),
        m_value( r_value_in )
    {
    }
    // For user writing xs:any
    c_any_info( const std::string & r_value_in ) :
        m_value( r_value_in )
    {
    }
    // c_any_info & operator = ( const c_any_info & ) = default;
    const std::string & get_namespace() const { return m_namespace; }
    const std::string & get_name() const { return m_name; }
    const std::string & get_value() const { return m_value; }
    std::string get_local_name() const  // v4.1.2
    {
        std::string::size_type colon_pos = m_name.find( ':' );

        if( colon_pos == std::string::npos )
            return m_name;
        return m_name.substr( colon_pos+1, std::string::npos );
    }

    void set_namespace( const std::string & r_namespace_in ) { m_namespace = r_namespace_in; }
    void set_name( const std::string & r_name_in ) { m_name = r_name_in; }
    void set_value( const std::string & r_value_in ) { m_value = r_value_in; }

    const c_namespace_context & get_namespace_context() const { return m_namespace_context; }
    c_namespace_context & get_namespace_context() { return m_namespace_context; }

    bool operator == ( const c_any_info & ) const { return true; }  // v5 - Contents of c_any_info ignored during comparison
    bool operator != ( const c_any_info & ) const { return false; } // v5
};

typedef std::vector< c_any_info * > t_any_info_vector;
typedef ct_non_pod_container< c_any_info > t_any_info_container;

class c_empty
{
public:
    bool operator == ( const c_empty & ) const { return true; }     // v5
    bool operator != ( const c_empty & ) const { return false; }    // v5

public: // C110918_1018: To keep gcc 323 and 423 happy (323 doesn't like to swap empty objects, 423 doesn't like no initialisation)
    c_empty() : dummy( 0 ) {}
    char dummy;
};

//------------------------------------------------------------------------------
//                                LMXG2 Classes
//------------------------------------------------------------------------------

class c_handling_qname {};

class c_handling_ur_type {};

// To allow error free symmetry between ct_non_mixed and ct_mixed classes
static tlmx_unicode_string m_unused_non_mixed_text;

template< typename T >
class ct_non_mixed
{
private:
    T m_value;

public:
    ct_non_mixed() : m_value( T() ) {}        // C110507_1734 - Added initialisers for template members
    ct_non_mixed( const T & r_v_in ) : m_value( r_v_in ) {}
    // ct_non_mixed( const ct_non_mixed & ) = default;
    // ct_non_mixed & operator = ( const ct_non_mixed & ) = default;
    void swap( ct_non_mixed< T > & r_rhs_in ) { lmx::swap( m_value, r_rhs_in.m_value ); }

    bool operator == ( const ct_non_mixed< T > & r_rhs_in ) const { return m_value == r_rhs_in.m_value; }
    bool operator != ( const ct_non_mixed< T > & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    static bool is_in_mixed() { return false; }

    T & ref_value() { return m_value; }
    const T & ref_value() const { return m_value; }
    tlmx_unicode_string & ref_text() { lmx_assert( 0 ); return m_unused_non_mixed_text; }
    const tlmx_unicode_string & ref_text() const { lmx_assert( 0 ); return m_unused_non_mixed_text; }

    // Allow treating object as simply an instance of T if required
    T & operator = ( const T & r_v_in ) { m_value = r_v_in; return m_value; }
    operator T & () { return m_value; }
    operator const T & () const { return m_value; }
};

template< typename T >
class ct_mixed
{
private:
    T m_value;
    tlmx_unicode_string m_text;

public:
    ct_mixed() : m_value( T() ) {}        // C110507_1734 - Added initialisers for template members
    ct_mixed( const T & r_v_in ) : m_value( r_v_in ) {}
    // ct_mixed( const ct_mixed & ) = default;
    // ct_mixed & operator = ( const ct_mixed & ) = default;
    void swap( ct_mixed< T > & r_rhs_in ) { lmx::swap( m_value, r_rhs_in.m_value ); lmx::swap( m_text, r_rhs_in.m_text ); }

    bool operator == ( const ct_mixed< T > & r_rhs_in ) const { return m_value == r_rhs_in.m_value && m_text == r_rhs_in.m_text; }
    bool operator != ( const ct_mixed< T > & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    static bool is_in_mixed() { return true; }

    T & ref_value() { return m_value; }
    const T & ref_value() const { return m_value; }
    tlmx_unicode_string & ref_text() { return m_text; }
    const tlmx_unicode_string & ref_text() const { return m_text; }

    // Allow treating object as simply an instance of T if required
    T & operator = ( const T & r_v_in ) { m_value = r_v_in; return m_value; }
    operator T & () { return m_value; }
    operator const T & () const { return m_value; }
};

template< typename Treader, typename Tcollection, typename Tatomic_type, typename Thandling >
class c_unmarshal_bridge;

template< typename Treader, typename Tcollection, typename Tatomic_type, typename Thandling >
class c_unmarshal_list_bridge;

template< typename Twriter, typename Tcollection, typename Tatomic_type, typename Thandling >
class c_marshal_bridge;

template< typename Twriter, typename Tcollection, typename Tatomic_type, typename Thandling >
class c_marshal_list_bridge;

template< typename Tatomic_type >
class ct_typed_validation_spec;

// For simple POD (Plain Ordinary Data) types such as int, float etc., that
// we can store directly in a std::vector
template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T > >
class ct_simple_pod_single
{
private:
    Twrapper m_value;
    bool m_is_set;

public:
    typedef ct_simple_pod_single< T, Thandling, Twrapper > Tself;
    typedef T t_atomic_type;
    typedef Thandling t_handling;

    ct_simple_pod_single() : m_is_set( false ) {}
    // ct_simple_pod_single( const ct_simple_pod_single< T, Thandling, Twrapper > & ) = default;
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in ); swap( t );
        return *this;
    }
    ~ct_simple_pod_single() {}
    void swap( Tself & r_rhs_in ) { m_value.swap( r_rhs_in.m_value ); std::swap( m_is_set, r_rhs_in.m_is_set ); }

    // User interface methods
    const T & get() const { return m_value.ref_value(); }
    T & get() { return m_value.ref_value(); }
    elmx_error set( const T & r_v_in ) { m_value.ref_value() = r_v_in; m_is_set = true; return ELMX_OK; }
    const tlmx_unicode_string & get_text() const { return m_value.ref_text(); }
    tlmx_unicode_string & get_text() { return m_value.ref_text(); }
    void set_text( const tlmx_unicode_string & r_t_in ) { m_value.ref_text() = r_t_in; m_is_set = true; }
    bool is_value_set() const { return m_is_set; }  // C100510_1423
    void unset() { m_is_set = false; }
    void unset( const T & r_default_in ) { m_value.ref_value() = r_default_in; m_is_set = false; }
    bool is_occurs_ok( bool LMX_UNUSED_PARAM( is_required_in ) ) const { return m_is_set; }  // See note is_occurs_ok_is_required

    bool operator == ( const Tself & r_rhs_in ) const
    {
        return m_is_set == r_rhs_in.m_is_set && (! m_is_set || m_value == r_rhs_in.m_value);
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }

public:
    // For c_xml_reader and c_xml_writer access

    bool is_in_mixed() const { return Twrapper::is_in_mixed(); }

    // Unmarshal interface methods
    bool is_already_unmarshalled() const { return is_value_set(); }
    void mk_new_space() { m_is_set = true; }
    tlmx_unicode_string & get_new_space_text_ref() { return m_value.ref_text(); }
    T & get_new_space_value_ref() { return m_value.ref_value(); }

    // Marshaling interface methods
    size_t count() const { return 1; }      // C120411_0908
    const tlmx_unicode_string & access_text( size_t LMX_UNUSED_PARAM( i ) ) const { return m_value.ref_text(); }
    const T & access_value( size_t LMX_UNUSED_PARAM( i ) ) const { return m_value.ref_value(); }

    template< typename Treader >    // C121120_1245
    c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T > >
class ct_simple_pod_optional : public ct_simple_pod_single< T, Thandling, Twrapper >
{
public:
    typedef ct_simple_pod_optional< T, Thandling, Twrapper > Tself;
    typedef ct_simple_pod_single< T, Thandling, Twrapper > Tbase;  // See http://www.parashift.com/c++-faq-lite/templates.html#faq-35.19
    typedef T t_atomic_type;
    typedef Thandling t_handling;

    // ct_simple_pod_optional() = default;
    // ct_simple_pod_optional( const ct_simple_pod_optional< t > & ) = default;
    // ct_simple_pod_optional< t > & operator = ( const ct_simple_pod_optional< t > & ) = default;
    ~ct_simple_pod_optional() {}

    // Additional user interface methods
    bool is_occurs_ok( bool is_required_in ) const { return is_required_in ? Tbase::is_value_set() : true; }    // See note is_occurs_ok_is_required

    // Marshaling interface methods
    size_t count() const { return Tbase::is_value_set() ? 1 : 0; }  // C120411_0908

    template< typename Treader >    // C121120_1245
    c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T >, typename TC = ct_pod_container< Twrapper > >
class ct_simple_pod_multi
{
private:
    TC m_values;

public:
    typedef ct_simple_pod_multi< T, Thandling, Twrapper, TC > Tself;
    typedef T t_atomic_type;
    typedef Thandling t_handling;
    typedef typename TC::Trawcontainer Tcontainer;

    ct_simple_pod_multi() {}
    // ct_simple_pod_multi( const Tself & ar_rhs ) = default;
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in ); swap( t );
        return *this;
    }
    ~ct_simple_pod_multi() {}
    void swap( Tself & r_rhs_in )
    {
        m_values.swap( r_rhs_in.m_values );
    }

    // User interface methods
    const T & get( size_t index_in ) const       // For read access
    {
        lmx_assert( index_in < m_values.size() );
        return m_values.at( index_in ).ref_value();
    }
    T & get( size_t index_in )                   // For read/write access
    {
        while( m_values.size() <= index_in )       // C100902_2046
            append( T() );
        return m_values[index_in].ref_value();
    }
    const T & get() const       // For read access - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return get( 0 );
    }
    T & get()                // For read/write access - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return get( 0 );
    }
    const T & back( size_t index_in ) const  // For read access
    {
        return m_values.back().ref_value();
    }
    T & back( size_t index_in )              // For read/write access
    {
        return m_values.back().ref_value();
    }
    elmx_error set( size_t index_in, const T & r_value_in )
    {
        while( m_values.size() <= index_in )       // C100902_2046
            append( r_value_in );
        m_values[index_in].ref_value() = r_value_in;
        return ELMX_OK;
    }
    elmx_error set( const T & r_value_in )       // C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return set( 0, r_value_in );
    }
    void append( const T & r_value_in )
    {
        m_values.push_back( r_value_in );
    }
    void insert( size_t index_in, const T & r_value_in )
    {
        m_values.insert( index_in, r_value_in );
    }
    void erase( size_t index_in )
    {
        m_values.erase( index_in );
    }
    void clear() { m_values.clear(); }
    size_t size() const { return m_values.size(); }
    bool empty() const { return m_values.empty(); }
    bool is_value_set() const { return ! empty(); } // C110301_1550 - For when multi occurs is restricted to single or optional
    void unset() { clear(); }   // C110301_1550 - For when multi occurs is restricted to single or optional
    bool is_occurs_ok( size_t min_occurs_in ) const  // For maxOccurs unbounded
    {
        return m_values.size() >= min_occurs_in;
    }
    bool is_occurs_ok( size_t min_occurs_in, size_t max_occurs_in ) const
    {
        return min_occurs_in <= m_values.size() && m_values.size() <= max_occurs_in;
    }
    bool operator == ( const Tself & r_rhs_in ) const
    {
        return m_values == r_rhs_in.m_values;
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    Tcontainer & raw_container() { return m_values.raw_container(); }
    const Tcontainer & raw_container() const { return m_values.raw_container(); }

public:
    // For c_xml_reader and c_xml_writer access

    bool is_in_mixed() const { return Twrapper::is_in_mixed(); }

    // Unmarshal interface methods
    bool is_already_unmarshalled() const { return is_value_set(); }
    void mk_new_space() { m_values.resize( m_values.size() + 1 ); }
    tlmx_unicode_string & get_new_space_text_ref() { return m_values.back().ref_text(); }
    T & get_new_space_value_ref() { return m_values.back().ref_value(); }

    // cit_multi can be multi or list
    // Marshaling interface methods
    size_t count() const { return m_values.size(); }
    const tlmx_unicode_string & access_text( size_t i ) const { return m_values.at(i).ref_text(); }
    const T & access_value( size_t i ) const { return m_values.at(i).ref_value(); }

    template< typename Treader >    // C121120_1245
    c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

template< typename T, typename Thandling = T, typename TC = ct_pod_container< T >, typename Twrapper = ct_non_mixed< TC > >
class ct_simple_pod_list_single
{
protected:
    Twrapper list;
    bool is_present;    // A list may be present but empty and we need to be able to tell the difference

public:
    typedef ct_simple_pod_list_single< T, Thandling, TC, Twrapper > Tself;
    typedef T t_atomic_type;
    typedef Thandling t_handling;
    typedef typename TC::Trawcontainer Tcontainer;

    ct_simple_pod_list_single() : is_present( false ) {}
    // ct_simple_pod_list_single( const Tself & ) = default;
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in ); swap( t );
        return *this;
    }
    ~ct_simple_pod_list_single() {}
    void swap( Tself & r_rhs_in )
    {
        list.swap( r_rhs_in.list );
        std::swap( is_present, r_rhs_in.is_present );
    }

    const T & get( size_t index_in ) const       // For read access
    {
        lmx_assert( index_in < list.ref_value().size() );
        return list.ref_value().at(index_in);
    }
    T & get( size_t index_in )                   // For read/write access
    {
        is_present = true;
        while( list.ref_value().size() <= index_in )     // C100902_2046
            append( T() );
        return list.ref_value()[index_in];
    }
    const T & back( size_t index_in ) const  // For read access
    {
        return list.ref_value().back();
    }
    T & back( size_t index_in )              // For read/write access
    {
        return list.ref_value().back();
    }
    elmx_error set( size_t index_in, const T & r_value_in )
    {
        is_present = true;
        while( list.ref_value().size() <= index_in )     // C100902_2046
            append( r_value_in );
        list.ref_value()[index_in] = r_value_in;
        return ELMX_OK;
    }
    void append( const T & r_value_in )
    {
        list.ref_value().push_back( r_value_in );
        is_present = true;
    }
    void insert( size_t index_in, const T & r_value_in )
    {
        list.ref_value().insert( index_in, r_value_in );
        is_present = true;
    }
    void erase( size_t index_in )
    {
        list.ref_value().erase( index_in );
    }
    void clear() { list.ref_value().clear(); is_present = true; }  // C160504_1254
    size_t size() const { return list.ref_value().size(); }
    bool empty() const { return list.ref_value().empty(); }

    bool is_value_set() const { return is_present; }    // C100510_1423
    void unset() { list.ref_value().clear(); is_present = false; }
    bool is_occurs_ok( bool LMX_UNUSED_PARAM( is_required_in ) ) const { return is_present; }    // See note is_occurs_ok_is_required
    bool is_occurs_ok( size_t min_occurs_in, size_t max_occurs_in ) const
    {
        return min_occurs_in <= size() && size() <= max_occurs_in;
    }
    bool operator == ( const Tself & r_rhs_in ) const
    {
        return is_present == r_rhs_in.is_present && ( ! is_present || list == r_rhs_in.list);
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    Tcontainer & raw_container() { return list.ref_value().raw_container(); }
    const Tcontainer & raw_container() const { return list.ref_value().raw_container(); }

public:
    // For c_xml_reader and c_xml_writer access

    bool is_in_mixed() const { return Twrapper::is_in_mixed(); }

    // Unmarshal interface methods
    bool is_already_unmarshalled() const { return is_value_set(); }
    void start_new_list() { is_present = true; }
    tlmx_unicode_string & get_new_space_text_ref() { return list.ref_text(); }  // Max 1 text item per list
    void mk_new_space() { list.ref_value().resize( list.ref_value().size() + 1 ); }
    T & get_new_space_value_ref() { return list.ref_value().back(); }
    size_t new_list_size() const { return list.ref_value().size(); }

    // Marshaling interface methods
    size_t list_count() const { return 1; }
    const tlmx_unicode_string & access_text( size_t LMX_UNUSED_PARAM( i ) ) const { return list.ref_text(); }
    size_t count( size_t LMX_UNUSED_PARAM( i ) ) const { return list.ref_value().size(); }
    const T & access_value( size_t LMX_UNUSED_PARAM( i ), size_t j ) const { return list.ref_value()[j]; }

    template< typename Treader >    // C121120_1245
    c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_list_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_list_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

template< typename T, typename Thandling = T, typename TC = ct_pod_container< T >, typename Twrapper = ct_non_mixed< TC > >
class ct_simple_pod_list_optional : public ct_simple_pod_list_single< T, Thandling, TC, Twrapper >
{
public:
    typedef ct_simple_pod_list_optional< T, Thandling, TC, Twrapper > Tself;
    typedef ct_simple_pod_list_single< T, Thandling, TC, Twrapper > Tbase;
    typedef T t_atomic_type;
    typedef Thandling t_handling;

    // ct_simple_pod_list_optional() = default;
    // ct_simple_pod_list_optional( const ct_simple_pod_list_single< T, Thandling, TC, Twrapper > & ) = default;
    // ct_simple_pod_list_optional< T, Thandling, Twrapper > & operator = ( const ct_simple_pod_list_single< T, Thandling, TC, Twrapper > & ar_rhs ) = default;

    bool is_occurs_ok( bool is_required_in ) const { return is_required_in ? Tbase::is_present : true; }  // See note is_occurs_ok_is_required

public:
    // For c_xml_reader and c_xml_writer access

    // Unmarshal interface methods
    // using ct_simple_pod_list_single::start_new_list()
    // using ct_simple_pod_list_single::mk_new_space()
    // using ct_simple_pod_list_single::get_new_space_value_ref()

    // Marshaling interface methods
    size_t list_count() const { return Tbase::is_present ? 1 : 0; }
    // using ct_simple_pod_list_single::access_text( size_t i )
    // using ct_simple_pod_list_single::count( size_t i )
    // using ct_simple_pod_list_single::access_value( size_t i, size_t j )

    template< typename Treader >    // C121120_1245
    c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_list_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_list_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< ct_simple_list< T > >, typename TC = ct_non_pod_container< Twrapper > >
class ct_simple_pod_list_multi
{
private:
    TC m_lists;

public:
    typedef ct_simple_pod_list_multi< T, Thandling, Twrapper, TC > Tself;
    typedef T t_atomic_type;
    typedef Thandling t_handling;
    typedef typename TC::Trawcontainer Tcontainer;

    // ct_simple_pod_list_multi() = default;
    // ct_simple_pod_list_multi( const Tself & ) = default;
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in ); swap( t );
        return *this;
    }
    ~ct_simple_pod_list_multi() {}

    void swap( Tself & r_rhs_in )
    {
        m_lists.swap( r_rhs_in.m_lists );
    }

    // User interface methods
    const ct_simple_list< T > & get( size_t index_in ) const // For read access
    {
        lmx_assert( index_in < m_lists.size() );
        return m_lists.at(index_in);
    }
    void append()                                       // For write access
    {
        m_lists.push_back_w_autop( new Twrapper );
    }
    ct_simple_list< T > & back()                    // For write access
     {
        return m_lists.back();
    }
    void insert( size_t index_in )                       // For write access
    {
        m_lists.insert_w_autop( index_in, new Twrapper );
    }
    ct_simple_list< T > & get( size_t index_in ) // For read/write access
    {
        while( m_lists.size() <= index_in )
            m_lists.push_back_w_autop( new Twrapper );
        return m_lists[index_in];
    }
    void erase( size_t index_in )
    {
        m_lists.erase( index_in );
    }
    void clear()
    {
        m_lists.clear();
    }
    ct_simple_list< T > & assign( size_t index_in, const ct_simple_list< T > & r_value_in ) // Deep copy
    {
        return get( index_in ) = r_value_in;
    }
    size_t size() const
    {
        return m_lists.size();
    }
    bool is_occurs_ok( size_t min_occurs_in ) const  // For unbounded upper limit
    {
        return min_occurs_in <= m_lists.size();
    }
    bool is_occurs_ok( size_t min_occurs_in, size_t max_occurs_in ) const
    {
        return min_occurs_in <= m_lists.size() && m_lists.size() <= max_occurs_in;
    }
    bool operator == ( const Tself & r_rhs_in ) const
    {
        return m_lists == r_rhs_in.m_lists;
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }

    Tcontainer & raw_container() { return m_lists.raw_container(); }
    const Tcontainer & raw_container() const { return m_lists.raw_container(); }

public:
    // For c_xml_reader and c_xml_writer access

    bool is_in_mixed() const { return Twrapper::is_in_mixed(); }

    // Unmarshal interface methods
    bool is_already_unmarshalled() const { return ! m_lists.empty(); }
    void start_new_list() { m_lists.push_back_w_autop( new Twrapper ); }
    tlmx_unicode_string & get_new_space_text_ref() { return m_lists.back().ref_text(); }
    void mk_new_space() { m_lists.back().ref_value().grow(); }
    T & get_new_space_value_ref() { return m_lists.back().ref_value().back(); }
    size_t new_list_size() const { return m_lists.back().ref_value().size(); }

    // Marshal interface methods
    size_t list_count() const { return m_lists.size(); }  // Number of lists
    const tlmx_unicode_string & access_text( size_t i ) const { return m_lists[i].ref_text(); }
    size_t count( size_t i ) const { return m_lists[i].ref_value().size(); }      // Number of items in list i
    const T & access_value( size_t i, size_t j ) const { return m_lists[i].ref_value().get( j ); }

    template< typename Treader >    // C121120_1245
    c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling > get_unmarshal_list_bridge( Treader & r_reader_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in )
    {
        return c_unmarshal_list_bridge< Treader, Tself, t_atomic_type, t_handling >( r_reader_in, *this, r_item_spec_in );
    }
    template< typename Twriter >
    c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling > get_marshal_list_bridge( Twriter & r_writer_in, const ct_typed_validation_spec< t_atomic_type > & r_item_spec_in ) const
    {
        return c_marshal_list_bridge< Twriter, Tself, t_atomic_type, t_handling >( r_writer_in, *this, r_item_spec_in );
    }
};

// It's useful to have some additional methods for the empty type
template< class T = c_empty, class Thandler = T, typename Twrapper = ct_non_mixed< T > >
class ct_empty_single : public ct_simple_pod_single< T, Thandler, Twrapper >
{
public:
    ct_empty_single() : ct_simple_pod_single< T, Thandler, Twrapper >() { set(); }  // C100916_1636
    elmx_error set() { return ct_simple_pod_single< T, Thandler, Twrapper >::set( T() ); }
};

template< class T = c_empty, class Thandler = T, typename Twrapper = ct_non_mixed< T > >
class ct_empty_optional : public ct_simple_pod_optional< T, Thandler, Twrapper >
{
public:
    // ct_empty_optional() = default;
    elmx_error set() { return ct_simple_pod_optional< T, Thandler, Twrapper >::set( T() ); }
};

template< class T = c_empty, class Thandler = T, typename Twrapper = ct_non_mixed< T >, typename TC = ct_pod_container< Twrapper > >
class ct_empty_multi : public ct_simple_pod_multi< T, Thandler, Twrapper, TC >
{
public:
    typedef ct_simple_pod_multi< T, Thandler, Twrapper, TC > Tbase;

    // ct_empty_multi() = default;
    elmx_error set( size_t index_in ) { return Tbase::set( index_in, T() ); }
    void append() { Tbase::append( T() ); }
    void insert( size_t index_in ) { Tbase::insert( index_in, T() ); }
};

// For non-POD simple types such as c_big_int etc., that we prefer to store a pointer to in a std::vector.
// The single and optional variants are handled in the same way as the POD types.
template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T > >
class ct_simple_non_pod_single : public ct_simple_pod_single< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T > >
class ct_simple_non_pod_optional : public ct_simple_pod_optional< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< T >, typename TC = ct_non_pod_container< Twrapper > >
class ct_simple_non_pod_multi : public ct_simple_pod_multi< T, Thandling, Twrapper, TC >
{};

template< typename T, typename Thandling = T, typename TC = ct_non_pod_container< T >, typename Twrapper = ct_non_mixed< TC > >
class ct_simple_non_pod_list_single : public ct_simple_pod_list_single< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename TC = ct_non_pod_container< T >, typename Twrapper = ct_non_mixed< TC > >
class ct_simple_non_pod_list_optional : public ct_simple_pod_list_optional< T, Thandling, TC, Twrapper >
{};

// For backwards compatibility reasons, we don't differentiate between POD and non-POD types
// -for multi-list.
template< typename T, typename Thandling = T, typename Twrapper = ct_non_mixed< ct_simple_list< T > >, typename TC = ct_non_pod_container< Twrapper > >
class ct_simple_non_pod_list_multi : public ct_simple_pod_list_multi< T, Thandling, Twrapper, TC >
{};

// For mixed variants (both POD and non-POD mixed types treated as non-POD)
template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_simple_pod_single : public ct_simple_non_pod_single< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_simple_pod_optional : public ct_simple_non_pod_optional< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T >, typename TC = ct_non_pod_container< Twrapper > >
class ct_mixed_simple_pod_multi : public ct_simple_non_pod_multi< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename TC = ct_pod_container< T >, typename Twrapper = ct_mixed< TC > >
class ct_mixed_simple_pod_list_single : public ct_simple_pod_list_single< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename TC = ct_pod_container< T >, typename Twrapper = ct_mixed< TC > >
class ct_mixed_simple_pod_list_optional : public ct_simple_pod_list_optional< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< ct_simple_list< T > >, typename TC = ct_non_pod_container< Twrapper > >
class ct_mixed_simple_pod_list_multi : public ct_simple_pod_list_multi< T, Thandling, Twrapper, TC >
{};

template< class T = c_empty, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_empty_single : public ct_empty_single< T, Thandling, Twrapper >
{};

template< class T = c_empty, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_empty_optional : public ct_empty_optional< T, Thandling, Twrapper >
{};

template< class T = c_empty, typename Thandling = T, typename Twrapper = ct_mixed< T >, typename TC = ct_non_pod_container< Twrapper > >
class ct_mixed_empty_multi : public ct_empty_multi< T, Thandling, Twrapper, TC >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_simple_non_pod_single : public ct_simple_non_pod_single< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T > >
class ct_mixed_simple_non_pod_optional : public ct_simple_non_pod_optional< T, Thandling, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< T >, typename TC = ct_non_pod_container< Twrapper > >
class ct_mixed_simple_non_pod_multi : public ct_simple_non_pod_multi< T, Thandling, Twrapper, TC >
{};

template< typename T, typename Thandling = T, typename TC = ct_non_pod_container< T >, typename Twrapper = ct_mixed< TC > >
class ct_mixed_simple_non_pod_list_single : public ct_simple_non_pod_list_single< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename TC = ct_non_pod_container< T >, typename Twrapper = ct_mixed< TC > >
class ct_mixed_simple_non_pod_list_optional : public ct_simple_non_pod_list_optional< T, Thandling, TC, Twrapper >
{};

template< typename T, typename Thandling = T, typename Twrapper = ct_mixed< ct_simple_list< T > >, typename TC = ct_non_pod_container< Twrapper > >
class ct_mixed_simple_non_pod_list_multi : public ct_simple_non_pod_list_multi< T, Thandling, Twrapper, TC >
{};

// For complex types
template< typename T >  // C100916_1604
class ct_complex_optional : public ct_grin_or_happy_ptr_deleter< T >  // C110110_2117
{
protected:
    T * p;

public:
    typedef ct_complex_optional< T > Tself;
    typedef ct_grin_or_happy_ptr_deleter< T > Tdeleter;

    ct_complex_optional() : p( 0 ) {}
    ct_complex_optional( const Tself & r_rhs_in ) : p( r_rhs_in.p ? r_rhs_in.p->clone() : 0 ) {}
    Tself & operator = ( const Tself & r_rhs_in )
    {
        Tself t( r_rhs_in ); swap( t );
        return *this;
    }
    ~ct_complex_optional() { Tdeleter::release( p ); }
    void swap( Tself & r_rhs_in ) { std::swap( p, r_rhs_in.p ); }
    void clone( Tself & r_rhs_in ) { assign( p->clone() ); }

    // User interface methods
    const T & get() const { lmx_assert( p ); return *p; }   // For read access
    T & get()                                       // For read/write access
    {
        if( ! p )
            p = new T;
        return *p;
    }
    T & assign( const T & r_v_in ) { return (get() = r_v_in); } // Deep copy
    T & assign( T * p_v_in )                                  // Polymorphic assign
    {
        if( ! p_v_in )
        {
            T *p_old = p;
            p = 0;
            return *p_old;     // Assigning NULL pointer causes object to surrender ownership
        }
        Tdeleter::release( p );
        p = p_v_in;
        return *p_v_in;
    }
    bool is_value_set() const { return p != 0; }    // C100510_1423
    void unset() { Tdeleter::release( p ); p = 0; } // C121019_1950
    bool is_occurs_ok( bool is_required_in ) const { return is_required_in ? (p != 0) : true; }    // See note is_occurs_ok_is_required

    bool operator == ( const Tself & r_rhs_in ) const
    {
        return (p == 0) == (r_rhs_in.p == 0) &&
                ( p == 0 || *(p) == *(r_rhs_in.p) );
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }
    bool iseq( const Tself & r_rhs_in ) const
    {
        return (p == 0) == (r_rhs_in.p == 0) && ( p == 0 || p->iseq( r_rhs_in.p ) );
    }
};

template< class T >
class ct_complex_single : public ct_complex_optional< T >   // C100916_1604
{
public:
    typedef ct_complex_single< T > Tself;
    typedef ct_complex_optional< T > Tbase;
    ct_complex_single() { Tbase::p = new T; }   // C100916_1604
    // ct_complex_single( const Tself & ar_rhs ) = default;
    // Tself & operator = ( const Tself & ar_rhs ) = inherit
    ~ct_complex_single() {}

    // Additional user interface methods
    bool is_occurs_ok( bool LMX_UNUSED_PARAM( is_required_in ) ) const { return Tbase::p != 0; }    // See note is_occurs_ok_is_required
};

template< class T >
class ct_complex_multi
{
private:
    ct_clonable_container< T > m_values;

public:
    typedef ct_complex_multi< T > Tself;
    typedef typename ct_clonable_container< T >::Trawcontainer Tcontainer;

    // ct_complex_multi() = default;
    // ct_complex_multi( const Tself & ar_rhs ) = default;
    // Tself & operator = ( const Tself & ar_rhs ) = default;
    ~ct_complex_multi() {}
    void swap( Tself & r_rhs_in ) { m_values.swap( r_rhs_in.m_values ); }
    void clone( Tself & r_rhs_in ) { m_values.clone( r_rhs_in.m_values ); }

    const T & get( size_t index_in ) const       // For read access
    {
        lmx_assert( index_in < m_values.size() );
        return m_values.at(index_in);
    }
    T & get( size_t index_in )                   // For read/write access
    {
        while( m_values.size() <= index_in )
            m_values.push_back_w_autop( new T );
        return m_values[index_in];
    }
    const T & get() const       // For read access - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return get( 0 );
    }
    T & get()                // For read/write access - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return get( 0 );
    }
    void append()                               // For write access
    {
        m_values.push_back_w_autop( new T );
    }
    void append( T * p_v_in )                 // For write access
    {
        m_values.push_back_w_autop( p_v_in );
    }
    void append( typename uniq_ptr< T >::type & aapr_v )  // For write access - C100827_0943
    {
        m_values.push_back( aapr_v );
    }
    T & back()                              // For write access
    {
        return m_values.back();
    }
    void insert( size_t index_in )               // For write access
    {
        m_values.insert_w_autop( index_in, new T );
    }
    void insert( size_t index_in, T * p_v_in )               // For write access
    {
        m_values.insert_w_autop( index_in, p_v_in );
    }
    void insert( size_t index_in, typename uniq_ptr< T >::type & aapr_v )  // For write access - C100827_0943
    {
        m_values.insert( index_in, aapr_v );
    }
    T & assign( size_t index_in, const T & a ) // Deep copy
    {
        while( m_values.size() <= index_in )
            m_values.push_back_w_autop( new T );
        return (m_values[index_in] = a);
    }
    T & assign( size_t index_in, T * p_v_in )      // C110301_1621 - Polymorphic assign
    {
        return m_values.assign( index_in, p_v_in );
    }
    T & assign( const T & a ) // Deep copy - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return assign( 0, a );
    }
    T & assign( T * p_v_in )      // C110301_1621 - Polymorphic assign - C110301_1550 - For when multi occurs is restricted to single or optional
    {
        return assign( 0, p_v_in );
    }
    void erase( size_t index_in ) { m_values.erase( index_in ); }
    void clear() { m_values.clear(); }
    size_t size() const { return m_values.size(); }
    bool empty() const { return m_values.empty(); }
    bool is_value_set() const { return ! empty(); } // C110301_1550 - For when multi occurs is restricted to single or optional
    void unset() { clear(); }   // C110301_1550 - For when multi occurs is restricted to single or optional

    bool is_occurs_ok( size_t min_occurs_in ) const  // For maxOccurs unbounded
    {
        return m_values.size() >= min_occurs_in;
    }
    bool is_occurs_ok( size_t min_occurs_in, size_t max_occurs_in ) const
    {
        return min_occurs_in <= m_values.size() && m_values.size() <= max_occurs_in;
    }
    bool operator == ( const Tself & r_rhs_in ) const
    {
        return m_values == r_rhs_in.m_values;
    }
    bool operator != ( const Tself & r_rhs_in ) const { return ! (*this == r_rhs_in); }
    bool iseq( const Tself & r_rhs_in ) const
    {
        if( m_values.size() != r_rhs_in.size() )
            return false;
        for( size_t i=0; i<m_values.size(); ++i )
            if( ! (m_values[i].iseq( &r_rhs_in.m_values[i] ) ) )
                return false;
        return true;
    }

    Tcontainer & raw_container() { return m_values.raw_container(); }
    const Tcontainer & raw_container() const { return m_values.raw_container(); }
};

template< typename T >
class ct_typed_validation_spec;

//------------------------------------------------------------------------------
//                   Signed char safe versions of isxxxx functions
//------------------------------------------------------------------------------

inline bool xisalpha( int x ) { return x > 0 && LMXSTDCRT::isalpha( x ); }
inline bool xisspace( int x ) { return x > 0 && LMXSTDCRT::isspace( x ); }
inline bool xisalnum( int x ) { return x > 0 && LMXSTDCRT::isalnum( x ); }
inline bool xisdigit( int x ) { return x > 0 && LMXSTDCRT::isdigit( x ); }
inline bool xisxdigit( int x ) { return x > 0 && LMXSTDCRT::isxdigit( x ); }
inline bool xisprint( int x ) { return x > 0 && LMXSTDCRT::isprint( x ); }

//------------------------------------------------------------------------------
//                         Compiler STL support fixes
//------------------------------------------------------------------------------

inline int stringncompare( const std::string &r_lhs_in, const char *p_rhs_in,
                        size_t first_in, size_t num_in )
{
#if defined( __GNUC__ ) && __GNUC__ == 2
    size_t len = LMXSTDCRT::strlen( p_rhs_in );
    if( num_in > len ) num_in = len;
    return strncmp( r_lhs_in.c_str() + first_in, p_rhs_in, num_in );
#else
    return r_lhs_in.compare( first_in, num_in, p_rhs_in );
#endif
}

inline int stringncompare( const std::string &r_lhs_in, const char *p_rhs_in, size_t rhs_len_in,
                        size_t first_in, size_t num_in )
{
#if defined( __GNUC__ ) && __GNUC__ == 2
    size_t len = LMXSTDCRT::strlen( p_rhs_in );
    if( num_in > len ) num_in = len;
    return strncmp( r_lhs_in.c_str() + first_in, p_rhs_in, num_in );
#else
    return r_lhs_in.compare( first_in, num_in, p_rhs_in, rhs_len_in );
#endif
}

inline int stringcompare( const std::string &r_lhs_in, const char *p_rhs_in, size_t rhs_len_in )
{
#if defined( __GNUC__ ) && __GNUC__ == 2
    return strcmp( r_lhs_in.c_str(), p_rhs_in );
#else
    return r_lhs_in.compare( 0, rhs_len_in, p_rhs_in, rhs_len_in );
#endif
}

} // End of namespace lmx

#if defined( _MSC_VER ) && _MSC_VER >= 1400
#pragma warning (pop)  // Restore VC8 'safe' warnings
#endif

#endif // LMXINTERNALS_H

//------------------------------------------------------------------------------
//                  Copyright (c) 2003-2015 Codalogic Ltd.
//------------------------------------------------------------------------------

