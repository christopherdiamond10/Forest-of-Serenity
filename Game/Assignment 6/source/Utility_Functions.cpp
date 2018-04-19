#include "Utility_Functions.h"
#include <locale>

//===============================================
//	UpCase an Entire String
//===============================================
std::string String_To_UpperCase( std::string cString )
{
	std::locale loc;
	std::string sReturnString;
	int iStringLength = cString.length();

	for( int i = 0; i < iStringLength; i++)
	{
		unsigned char c = std::toupper( (unsigned char)cString[i], loc );
		sReturnString += c;
	}

	return sReturnString;
}



//===============================================
//	Get Is Character Valid?
//===============================================
bool Get_IsCharacterValid( char c )
{
	if( c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' ||
		c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || 
		c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z' || c == '1' || 
		c == '2' ||	c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0' || 
		c == '`' ||	c == '-' || c == '=' || c == ';' || c == ',' || c == '.' || c == '/' || c == 91  || c == ' ' ||	
		c == 93  || c == 39 )	// 92 == '\', 91 == '[', 93 == ']', 39 == '
	{
		return true;
	}
	return false;
}



//===============================================
//	Convert Degrees To Radians
//===============================================
float DegreesToRadians( float deg )
{
	return ((PI / 180.0f) * deg);
}