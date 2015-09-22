#if defined( _MSC_VER )
#if !defined( _CRT_SECURE_NO_WARNINGS )
#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
#endif
#endif

#include "tinyxml2.h"
#include <cstdlib>
#include <cstring>
#include <ctime>

#if defined( _MSC_VER )
#include <direct.h>		// _mkdir
#include <crtdbg.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#elif defined(MINGW32) || defined(__MINGW32__)
#include <io.h>  // mkdir
#else
#include <sys/stat.h>	// mkdir
#endif

using namespace tinyxml2;
using namespace std;
int gPass = 0;
int gFail = 0;

bool XMLTest (const char* testString, const char* expected, const char* found, bool echo=true, bool extraNL=false )
{
    bool pass;
    if ( !expected && !found )
        pass = true;
    else if ( !expected || !found )
        pass = false;
    else
        pass = !strcmp( expected, found );
    if ( pass )
        printf ("[pass]");
    else
        printf ("[fail]");
    
    if ( !echo ) {
        printf (" %s\n", testString);
    }
    else {
        if ( extraNL ) {
            printf( " %s\n", testString );
            printf( "%s\n", expected );
            printf( "%s\n", found );
        }
        else {
            printf (" %s [%s][%s]\n", testString, expected, found);
        }
    }
    
    if ( pass )
        ++gPass;
    else
        ++gFail;
    return pass;
}


template< class T > bool XMLTest( const char* testString, T expected, T found, bool echo=true )
{
    bool pass = ( expected == found );
    if ( pass )
        printf ("[pass]");
    else
        printf ("[fail]");
    
    if ( !echo )
        printf (" %s\n", testString);
    else
        printf (" %s [%d][%d]\n", testString, static_cast<int>(expected), static_cast<int>(found) );
    
    if ( pass )
        ++gPass;
    else
        ++gFail;
    return pass;
}


void NullLineEndings( char* p )
{
    while( p && *p ) {
        if ( *p == '\n' || *p == '\r' ) {
            *p = 0;
            return;
        }
        ++p;
    }
}



int main( int argc, const char ** argv )
{
#if defined( _MSC_VER ) && defined( DEBUG )
_CrtMemCheckpoint( &startMemState );
// Enable MS Visual C++ debug heap memory leaks dump on exit
_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif

if ( argc < 2 ) {
printf("enter instances file path\n");
exit(-1);
} else {
XMLDocument* doc = new XMLDocument();
clock_t startTime = clock();
doc->LoadFile( argv[1] );
clock_t loadTime = clock();
int errorID = doc->ErrorID();

printf( "Test file '%s'. ErrorID=%d\n", argv[1], errorID );
if ( !errorID ) {
  printf( "Load time=%u\n",   (unsigned)(loadTime - startTime) );
    
  XMLElement* element0 = doc->FirstChildElement("IRP_Roadef_Challenge_Instance");
if(element0 != NULL) {
    XMLElement* unit = element0->FirstChildElement("unit");
    
    XMLElement* customers = element0->FirstChildElement("customers");
    XMLElement* nbrcustomers = customers->LastChildElement("IRP_Roadef_Challenge_Instance_Customers");
    printf("number of customers in the instance: %s\n", nbrcustomers->FirstChildElement("index")->GetText());

printf("1 good continue\n");
XMLElement* elem1 = element0 ->FirstChildElement("timeMatrices");
if(elem1) {
  printf("2 good continue\n");
  XMLElement* elem2 = elem1->FirstChildElement("ArrayOfInt");
  if (elem2) {
    printf("3 good continue\n");
    XMLElement* elem3 = elem2->FirstChildElement("int");
    while(elem3) {
      printf("4 good continue\n");
      const char * number = elem3->GetText();
      const int t1 = elem3 -> GetInt();
      printf("text found %s\n", number);
      printf("Number found %d\n",t1);
      elem3 = elem3 -> NextSiblingElement("int");
    }
  }
}
  }
} else {
  printf("Error! %s\n Possible error: %s\n%s", doc->ErrorName(),doc->GetErrorStr1(),doc->GetErrorStr2());
}	
delete doc; doc = 0;

    doc = new XMLDocument();
    const char* doctype = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
    doc->Parse(doctype);
    
    XMLElement* output = doc->NewElement("IRP_Roadef_Challenge_Output");
    output->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    output->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
   // output -> SetAttribute("Version", 1);
    
    XMLElement* shifts = doc->NewElement("Shifts");
    
    XMLElement* newshift = doc->NewElement("IRP_Roadef_Challenge_Shift_");
    XMLElement* index = doc->NewElement("index");
    index->SetText(0);
    newshift->InsertFirstChild(index);
    doc->InsertEndChild(output);
    output->InsertEndChild(shifts);
    shifts->InsertFirstChild(newshift);
    doc->SaveFile("solution.xml");
    delete doc;
    
    doc=0;
    exit(0);
}
}
