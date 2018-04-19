#include "Vector2.h"
#include <math.h>

//-=-=-=-=-=-=-=-=-=-=-=
//	Constructors
//=-=-=-=-=-=-=-=-=-=-=-
Vector2::Vector2()
{
	X = 0;
	Y = 0;
}




//============================
//	Constructor Overloading 
//============================
Vector2::Vector2(float a_fX, float a_fY)
{
	// Sets the values of X & Y  
	X = a_fX;
	Y = a_fY;
}




//============================
//		Deconstructor
//============================
Vector2::~Vector2()
{

}















//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//				Public Functions
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//=======================
//	Get Angle
//=======================
float Vector2::GetAngle( Vector2 a_Vector2 )
{
	return Angle( a_Vector2 );
}



//=======================
//	Get DotProduct
//=======================
float Vector2::GetDotProduct( Vector2 &a_Vec2 ) 
{
	return DotProduct(a_Vec2);
}




//=======================
//	Get Magnitude
//=======================
float Vector2::GetMagnitude()
{
	return Magnitude();
}



//=======================
//	Get Length
//=======================
float Vector2::GetLength()
{
	return Length();
}



//=======================
//	Get Normalised
//=======================
Vector2 Vector2::GetNormalised(Vector2 &a_Vec2)
{
	return Normalise( a_Vec2 );
}



//=======================
//	Get Perpendicular
//=======================
Vector2 Vector2::GetPerpendicular()
{
	return Perpendicular();
}



//=======================
// Get Perpendicular Anti
//=======================
Vector2 Vector2::GetPerpendicularAnti()
{
	return PerpendicularAnti();
}



//=======================
//	Get Lerp Vector2
//=======================
Vector2 Vector2::GetLerpVector2( unsigned int iPointBetweenVectors_ZeroToOneHundred, Vector2 vPointA, Vector2 vPointB )
{
	float fPoint = ((float)iPointBetweenVectors_ZeroToOneHundred * 0.01f);

	Vector2 vLerpedVector; 
	vLerpedVector.X = ( vPointA.X + fPoint * ( vPointA.X - vPointB.X));
	vLerpedVector.Y = ( vPointA.Y + fPoint * ( vPointA.Y - vPointB.Y));

	return vLerpedVector;
}















//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//				Private Functions
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//=======================
//		Angle
//=======================
float Vector2::Angle( Vector2 a_Vector2 )
{
	GetNormalised( a_Vector2 );

	Vector2 vRight = a_Vector2.GetPerpendicular();

	float fSide = vRight.DotProduct( *this );
	float fAngle = acosf(a_Vector2.DotProduct( *this ));

	if(fSide < 0.0f)
	{
		fAngle *= -1;
	}

	return fAngle;
}



//=======================
//		Dot Product
//=======================
float Vector2::DotProduct(const Vector2 &a_Vec2)
{
	return ((X * a_Vec2.X) + (Y * a_Vec2.Y));
}




//=======================
//		Length
//=======================
float Vector2::Length()
{
	m_fLength = GetMagnitude();

	if ( m_fLength > 0.f )
	{
		m_fLength = sqrtf( m_fLength );
	}

	return m_fLength;
}



//=======================
//		Magnitude
//=======================
float Vector2::Magnitude()
{
	return sqrt( (X * X) + (Y * Y ) );
}



//=======================
//	   Perpendicular
//=======================
Vector2 Vector2::Perpendicular()
{
	return Vector2( Y, -X );
}




//=======================
//	Perpendicular Anti
//=======================
Vector2 Vector2::PerpendicularAnti()
{
	return Vector2( -Y, X );
}




//=======================
//		Normalise
//=======================
Vector2 Vector2::Normalise( Vector2 &a_Vec2 )
{
	GetLength(); // Get Length

	a_Vec2.X = X / m_fLength;
	a_Vec2.Y = Y / m_fLength;

	return a_Vec2;
}















//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//			Operator Overloading
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//=======================
//		 ( == )
//=======================
bool Vector2::operator == ( const Vector2 &rhs )
{
	if( X == rhs.X && Y == rhs.Y )
	{	return true;	}
	else
	{	return false;	}
}



//=======================
//		( != )
//=======================
bool Vector2::operator != ( const Vector2 &rhs )
{
	if( X != rhs.X || Y != rhs.Y )
	{	return true;	}
	else
	{	return false;	}
}



//=======================
//		( + )
//=======================
Vector2 Vector2::operator + ( const Vector2 &rhs )
{
	return Vector2( X + rhs.X, Y + rhs.Y );
}



//=======================
//		( += )
//=======================
Vector2 Vector2::operator += ( const Vector2 &rhs )
{
	return Vector2( X += rhs.X, Y += rhs.Y );
}


//=======================
//		( - )
//=======================
Vector2 Vector2::operator - ( const Vector2 &rhs )
{
	return Vector2( X - rhs.X, Y - rhs.Y );
}



//=======================
//		( -= )
//=======================
Vector2 Vector2::operator -= ( const Vector2 &rhs )
{
	return Vector2( X -= rhs.X, Y -= rhs.Y );
}



//=======================
//		( / )
//=======================
Vector2 Vector2::operator / ( const Vector2 &rhs )
{
	return Vector2( X / rhs.X, Y / rhs.Y );
}



//=======================
//		( *= )
//=======================
Vector2 Vector2::operator *= ( const Vector2 &rhs )
{
	return Vector2( X *= rhs.X, Y *= rhs.Y );
}



//=======================
//		( /= )
//=======================
Vector2 Vector2::operator /= ( const Vector2 &rhs )
{
	return Vector2( X /= rhs.X, Y /= rhs.Y );
}