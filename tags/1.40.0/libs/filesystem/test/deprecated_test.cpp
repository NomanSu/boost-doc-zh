//  deprecated_test program --------------------------------------------------//

//  Copyright Beman Dawes 2002
//  Copyright Vladimir Prus 2002

//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

//  This test verifies that various deprecated names still compile. This is
//  important to preserve existing code that uses the old names.

#include <boost/filesystem.hpp>
#include <boost/test/minimal.hpp>

namespace fs = boost::filesystem;
using boost::filesystem::path;

#define PATH_CHECK( a, b ) check( a, b, __LINE__ )

namespace
{
  std::string platform( BOOST_PLATFORM );

  int errors;

  void check( const fs::path & source,
              const std::string & expected, int line )
  {
    if ( source.string()== expected ) return;

    ++errors;

    std::cout << '(' << line << ") source.string(): \"" << source.string()
              << "\" != expected: \"" << expected
              << "\"" << std::endl;
  }

  void check_normalize()
  {
    PATH_CHECK( path("").normalize(), "" );
    PATH_CHECK( path("/").normalize(), "/" );
    PATH_CHECK( path("//").normalize(), "//" );
    PATH_CHECK( path("///").normalize(), "/" );
    PATH_CHECK( path("f").normalize(), "f" );
    PATH_CHECK( path("foo").normalize(), "foo" );
    PATH_CHECK( path("foo/").normalize(), "foo/." );
    PATH_CHECK( path("f/").normalize(), "f/." );
    PATH_CHECK( path( "/foo" ).normalize(), "/foo" );
    PATH_CHECK( path( "foo/bar" ).normalize(), "foo/bar" );
    PATH_CHECK( path("..").normalize(), ".." );
    PATH_CHECK( path("../..").normalize(), "../.." );
    PATH_CHECK( path("/..").normalize(), "/.." );
    PATH_CHECK( path("/../..").normalize(), "/../.." );
    PATH_CHECK( path("../foo").normalize(), "../foo" );
    PATH_CHECK( path("foo/..").normalize(), "." );
    PATH_CHECK( path("foo/../").normalize(), "./." );
    PATH_CHECK( (path("foo") / "..").normalize() , "." );
    PATH_CHECK( path("foo/...").normalize(), "foo/..." );
    PATH_CHECK( path("foo/.../").normalize(), "foo/.../." );
    PATH_CHECK( path("foo/..bar").normalize(), "foo/..bar" );
    PATH_CHECK( path("../f").normalize(), "../f" );
    PATH_CHECK( path("/../f").normalize(), "/../f" );
    PATH_CHECK( path("f/..").normalize(), "." );
    PATH_CHECK( (path("f") / "..").normalize() , "." );
    PATH_CHECK( path("foo/../..").normalize(), ".." );
    PATH_CHECK( path("foo/../../").normalize(), "../." );
    PATH_CHECK( path("foo/../../..").normalize(), "../.." );
    PATH_CHECK( path("foo/../../../").normalize(), "../../." );
    PATH_CHECK( path("foo/../bar").normalize(), "bar" );
    PATH_CHECK( path("foo/../bar/").normalize(), "bar/." );
    PATH_CHECK( path("foo/bar/..").normalize(), "foo" );
    PATH_CHECK( path("foo/bar/../").normalize(), "foo/." );
    PATH_CHECK( path("foo/bar/../..").normalize(), "." );
    PATH_CHECK( path("foo/bar/../../").normalize(), "./." );
    PATH_CHECK( path("foo/bar/../blah").normalize(), "foo/blah" );
    PATH_CHECK( path("f/../b").normalize(), "b" );
    PATH_CHECK( path("f/b/..").normalize(), "f" );
    PATH_CHECK( path("f/b/../").normalize(), "f/." );
    PATH_CHECK( path("f/b/../a").normalize(), "f/a" );
    PATH_CHECK( path("foo/bar/blah/../..").normalize(), "foo" );
    PATH_CHECK( path("foo/bar/blah/../../bletch").normalize(), "foo/bletch" );
    PATH_CHECK( path( "//net" ).normalize(), "//net" );
    PATH_CHECK( path( "//net/" ).normalize(), "//net/" );
    PATH_CHECK( path( "//..net" ).normalize(), "//..net" );
    PATH_CHECK( path( "//net/.." ).normalize(), "//net/.." );
    PATH_CHECK( path( "//net/foo" ).normalize(), "//net/foo" );
    PATH_CHECK( path( "//net/foo/" ).normalize(), "//net/foo/." );
    PATH_CHECK( path( "//net/foo/.." ).normalize(), "//net/" );
    PATH_CHECK( path( "//net/foo/../" ).normalize(), "//net/." );

    PATH_CHECK( path( "/net/foo/bar" ).normalize(), "/net/foo/bar" );
    PATH_CHECK( path( "/net/foo/bar/" ).normalize(), "/net/foo/bar/." );
    PATH_CHECK( path( "/net/foo/.." ).normalize(), "/net" );
    PATH_CHECK( path( "/net/foo/../" ).normalize(), "/net/." );

    PATH_CHECK( path( "//net//foo//bar" ).normalize(), "//net/foo/bar" );
    PATH_CHECK( path( "//net//foo//bar//" ).normalize(), "//net/foo/bar/." );
    PATH_CHECK( path( "//net//foo//.." ).normalize(), "//net/" );
    PATH_CHECK( path( "//net//foo//..//" ).normalize(), "//net/." );

    PATH_CHECK( path( "///net///foo///bar" ).normalize(), "/net/foo/bar" );
    PATH_CHECK( path( "///net///foo///bar///" ).normalize(), "/net/foo/bar/." );
    PATH_CHECK( path( "///net///foo///.." ).normalize(), "/net" );
    PATH_CHECK( path( "///net///foo///..///" ).normalize(), "/net/." );

    if ( platform == "Windows" )
    {
      PATH_CHECK( path( "c:.." ).normalize(), "c:.." );
      PATH_CHECK( path( "c:foo/.." ).normalize(), "c:" );

      PATH_CHECK( path( "c:foo/../" ).normalize(), "c:." );

      PATH_CHECK( path( "c:/foo/.." ).normalize(), "c:/" );
      PATH_CHECK( path( "c:/foo/../" ).normalize(), "c:/." );
      PATH_CHECK( path( "c:/.." ).normalize(), "c:/.." );
      PATH_CHECK( path( "c:/../" ).normalize(), "c:/../." );
      PATH_CHECK( path( "c:/../.." ).normalize(), "c:/../.." );
      PATH_CHECK( path( "c:/../../" ).normalize(), "c:/../../." );
      PATH_CHECK( path( "c:/../foo" ).normalize(), "c:/../foo" );
      PATH_CHECK( path( "c:/../foo/" ).normalize(), "c:/../foo/." );
      PATH_CHECK( path( "c:/../../foo" ).normalize(), "c:/../../foo" );
      PATH_CHECK( path( "c:/../../foo/" ).normalize(), "c:/../../foo/." );
      PATH_CHECK( path( "c:/..foo" ).normalize(), "c:/..foo" );
    }
    else // POSIX
    {
      PATH_CHECK( path( "c:.." ).normalize(), "c:.." );
      PATH_CHECK( path( "c:foo/.." ).normalize(), "." );
      PATH_CHECK( path( "c:foo/../" ).normalize(), "./." );
      PATH_CHECK( path( "c:/foo/.." ).normalize(), "c:" );
      PATH_CHECK( path( "c:/foo/../" ).normalize(), "c:/." );
      PATH_CHECK( path( "c:/.." ).normalize(), "." );
      PATH_CHECK( path( "c:/../" ).normalize(), "./." );
      PATH_CHECK( path( "c:/../.." ).normalize(), ".." );
      PATH_CHECK( path( "c:/../../" ).normalize(), "../." );
      PATH_CHECK( path( "c:/../foo" ).normalize(), "foo" );
      PATH_CHECK( path( "c:/../foo/" ).normalize(), "foo/." );
      PATH_CHECK( path( "c:/../../foo" ).normalize(), "../foo" );
      PATH_CHECK( path( "c:/../../foo/" ).normalize(), "../foo/." );
      PATH_CHECK( path( "c:/..foo" ).normalize(), "c:/..foo" );
    }
  }
} // unnamed namespace

//----------------------------------------------------------------------------//

int test_main( int /*argc*/, char * /*argv*/[] )
{
  // The choice of platform is make at runtime rather than compile-time
  // so that compile errors for all platforms will be detected even though
  // only the current platform is runtime tested.
  platform = ( platform == "Win32" || platform == "Win64" || platform == "Cygwin" )
               ? "Windows"
               : "POSIX";
  std::cout << "Platform is " << platform << '\n';

  path::default_name_check( fs::no_check );

  fs::directory_entry de( "foo/bar" );

  de.replace_leaf( "", fs::file_status(), fs::file_status() );

  de.leaf();
  de.string();

  fs::path ng( " no-way, Jose" );
  BOOST_CHECK( !fs::is_regular( ng ) );  // verify deprecated name still works
  BOOST_CHECK( !fs::symbolic_link_exists( "nosuchfileordirectory" ) );

  check_normalize();
 
// extension() tests ---------------------------------------------------------//

  BOOST_CHECK( fs::extension("a/b") == "" );
  BOOST_CHECK( fs::extension("a/b.txt") == ".txt" );
  BOOST_CHECK( fs::extension("a/b.") == "." );
  BOOST_CHECK( fs::extension("a.b.c") == ".c" );
  BOOST_CHECK( fs::extension("a.b.c.") == "." );
  BOOST_CHECK( fs::extension("") == "" );
  BOOST_CHECK( fs::extension("a/") == "." );
  
// basename() tests ----------------------------------------------------------//

  BOOST_CHECK( fs::basename("b") == "b" );
  BOOST_CHECK( fs::basename("a/b.txt") == "b" );
  BOOST_CHECK( fs::basename("a/b.") == "b" ); 
  BOOST_CHECK( fs::basename("a.b.c") == "a.b" );
  BOOST_CHECK( fs::basename("a.b.c.") == "a.b.c" );
  BOOST_CHECK( fs::basename("") == "" );
  
// change_extension tests ---------------------------------------------------//

  BOOST_CHECK( fs::change_extension("a.txt", ".tex").string() == "a.tex" );
  BOOST_CHECK( fs::change_extension("a.", ".tex").string() == "a.tex" );
  BOOST_CHECK( fs::change_extension("a", ".txt").string() == "a.txt" );
  BOOST_CHECK( fs::change_extension("a.b.txt", ".tex").string() == "a.b.tex" );  
  // see the rationale in html docs for explanation why this works
  BOOST_CHECK( fs::change_extension("", ".png").string() == ".png" );

  return errors;
}