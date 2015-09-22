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
      XMLElement* customers = element0->FirstChildElement("customers");
      XMLElement* nbrcustomers = customers->LastChildElement("IRP_Roadef_Challenge_Instance_Customers");
      printf("number of customers in the instance: %s\n", nbrcustomers->FirstChildElement("index")->GetText());
      if(element0 != NULL) {
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
	      printf("text found %s\n", number);
	      elem3 = elem3 -> NextSiblingElement("int");
	    }
	  }
	}
      }
    } else {
      printf("Error!");
    }	
    delete doc; doc = 0;



    exit(0);
  }
}
