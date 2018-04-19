//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Utility_Functions.h - 
//\ 
//\ These are global functions which are useful throughout the entire program, using 
//\ String_To_UpperCase allows for a string of any case to be passed as an argument to
//\ a function and them uppercased to be a match to a statement.
//\====================================================================================
#ifndef _UTILITY_FUNCTIONS_H_
#define _UTILITY_FUNCTIONS_H_


#include <string>

#define PI 3.14159265f



std::string String_To_UpperCase( std::string cString );
bool Get_IsCharacterValid( char c );
float DegreesToRadians( float deg );


#endif