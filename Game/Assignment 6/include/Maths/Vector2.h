//\====================================================================================
//\ Author: Christopher Diamond
//\ About : Vector2.h - 
//\ 
//\ Defines the Vector2 Class. This class is used quite often for position and size of
//\ objects.
//\====================================================================================
#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_


class Vector2
{
////////////////////////////////////////////////////////////
public:
////////////////////////////////////////////////////////////

	//===============================================
	//			Constructors & Destructor
	//===============================================
	Vector2();
	Vector2( float a_fX, float a_fY );
	~Vector2();





	//===============================================
	//			Public Declarations
	//===============================================
	float X, Y;

	




	//===============================================
	//			Getter Functions
	//===============================================
	float GetAngle( Vector2 a_rVector2 );
	float GetDotProduct( Vector2 &a_Vec2 );   
	float GetLength();
	float GetMagnitude();
	
	Vector2 GetNormalised( Vector2 &a_Vec2 );
	Vector2 GetPerpendicular();
	Vector2 GetPerpendicularAnti();
	Vector2 GetLerpVector2( unsigned int iPointBetweenVectors_ZeroToOneHundred, Vector2 vPointA, Vector2 vPointB );
	

	//===============================================
	//			Operator Overloads
	//===============================================
	bool	 operator == ( const Vector2 &right );
	bool	 operator != ( const Vector2 &right );
	Vector2  operator +  ( const Vector2 &right );
	Vector2  operator += ( const Vector2 &right ); 
	Vector2  operator -  ( const Vector2 &right );
	Vector2  operator -= ( const Vector2 &right ); 
	Vector2  operator *  ( const Vector2 &right );
	Vector2  operator *= ( const Vector2 &right );
	Vector2  operator /  ( const Vector2 &right );
	Vector2  operator /= ( const Vector2 &right );
	


////////////////////////////////////////////////////////////
private:
////////////////////////////////////////////////////////////
	

	//===============================================
	//			Private Declarations
	//===============================================
	float m_fLength;



	//===============================================
	//			Private Functons
	//===============================================
	float Angle( Vector2 a_Vector2 );
	float DotProduct( const Vector2 &a_Vec2 );
	float Length();
	float Magnitude();

	Vector2 Perpendicular();
	Vector2 PerpendicularAnti();
	Vector2 Normalise( Vector2 &a_Vec2 );	
};

#endif