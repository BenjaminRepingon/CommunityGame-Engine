#ifndef _VEC_HPP_
# define _VEC_HPP_

#include <sstream>
# include "Point.tpp"

template <typename T>
class Quat;

template <typename T, u_int8_t D>
class Vec : public Point<T, D>
{
public:
	inline T		squaredNorm( void ) const
	{
		T	result( 0 );

		for ( int i = 0; i < D; ++i )
			result += this->_values[i] * this->_values[i];
		return ( result );
	}

	inline T		norm( void ) const
	{
		return ( sqrt( this->squaredNorm() ) );
	}

	inline Vec &	normalize( void )
	{
		T		length;

		length = this->norm();
		if ( length == T(0) )
			return ( *this );
		for ( int i = 0; i < D; ++i )
			(*this)[i] /= length;
		return ( *this );
	}

	inline Vec		normalized( void ) const
	{
		Vec		result;
		T		length;

		length = this->norm();
		if ( length == T(0) )
			return ( result );
		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / length;
		return ( result );
	}

	inline T		dot( const Vec & r ) const
	{
		T result = T(0);

		for ( int i = 0; i < D; ++i )
			result += (*this)[i] * r[i];
		return ( result );
	}

	inline Vec		reflect( const Vec & normal ) const
	{
		return ( *this - ( normal * ( this->dot( normal ) * 2 ) ) );
	}

	inline Vec		operator+( const Vec & rhs ) const
	{
		Vec		result;

		for ( int i = 0; i < D; i++ )
			result[i] = (*this)[i] + rhs[i];
		return ( result );
	}

	inline Vec		operator-( const Vec & rhs ) const
	{
		Vec		result;

		for ( int i = 0; i < D; i++ )
			result[i] = (*this)[i] - rhs[i];
		return ( result );
	}

	inline Vec &	operator+=( Vec const & rhs )
	{
		*this = *this + rhs;
		return ( *this );
	}

	inline Vec &	operator-=( Vec const & rhs )
	{
		*this = *this - rhs;
		return ( *this );
	}

	inline Vec		operator*( Vec const & rhs ) const
	{
		Vec		result;

		for ( int i = 0; i < D; i++ )
			result[i] = (*this)[i] * rhs[i];
		return ( result );
	}

	inline Vec		operator*( T const & value ) const
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] * value;
		return (  result );
	}

	inline Vec &	operator*=( Vec const & rhs )
	{
		*this = *this * rhs;
		return ( *this );
	}

	inline Vec &	operator*=( T const & value )
	{
		*this = *this * value;
		return ( *this );
	}

	inline Vec		operator/( Vec const & rhs ) const
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / rhs[i];
		return ( result );
	}

	inline Vec		operator/( T const & value ) const
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / value;
		return (  result );
	}

	inline Vec &	operator/=( Vec const & rhs )
	{
		*this = *this / rhs;
		return ( *this );
	}

	inline Vec &	operator/=( T const & value )
	{
		*this = *this / value;
		return ( *this );
	}

	inline std::string	toString( void )
	{
		std::stringstream o;

		o << "(";
		for ( int i = 0; i < D; ++i )
		{
			o << "[" << i << "]: " << (*this)[i];
			if ( i + 1 != D )
				o << ", ";
		}
		o << ")";
		return ( o.str() );
	}
};

template <typename T>
class Vec2 : public Vec<T, 2>
{
public:
	static const Vec2<T> ZERO;

	Vec2( void )
	{
		(*this)[0] = 0;
		(*this)[1] = 0;
	}

	Vec2( T x, T y )
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}

	Vec2( Point< T, 2 > point )
	{
		(*this)[0] = point[0];
		(*this)[1] = point[1];
	}

	inline Vec2( Vec2<T> const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline Vec2<T> &	operator=( Vec2<T> const & rhs )
	{
		for ( int i = 0; i < 2; ++i )
			this->_values[i] = rhs[i];
		return ( *this );
	}

	T				cross( const Vec2<T>& r ) const
	{
		return ( this->getX() * r.getX() - this->getY() * r.getY() );
	}

	/**
	 * GETTER
	 */
	inline T		getX( void ) const
	{
		return ( (*this)[0] );
	}
	inline T		getY( void ) const
	{
		return ( (*this)[1] );
	}

	/**
	 * SETTER
	 */
	inline void		setX( const T & x )
	{
		(*this)[0] = x;
	}
	inline void		setY( const T & y )
	{
		(*this)[1] = y;
	}

	inline void		set( const T & x, const T & y )
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}
};

template <typename T>
Vec2<T> const Vec2<T>::ZERO = Vec2( T( 0 ), T( 0 ) );

template <typename T>
class Vec3 : public Vec<T, 3>
{
public:
	static const Vec3<T> ZERO;

	Vec3( void )
	{
		(*this)[0] = 0;
		(*this)[1] = 0;
		(*this)[2] = 0;
	}

	Vec3( T x, T y, T z )
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	Vec3( Point< T, 3 > point )
	{
		(*this)[0] = point[0];
		(*this)[1] = point[1];
		(*this)[2] = point[2];
	}

	inline Vec3( Vec3<T> const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline Vec3<T> &	operator=( Vec3<T> const & rhs )
	{
		for ( int i = 0; i < 3; ++i )
			this->_values[i] = rhs[i];
		return ( *this );
	}

	inline Vec3<T>	cross( const Vec3<T> & r ) const
	{
		T x = (*this)[1] * r[2] - (*this)[2] * r[1];
		T y = (*this)[2] * r[0] - (*this)[0] * r[2];
		T z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return ( Vec3<T>( x, y, z ) );
	}

	Vec3<T>			rotate( const Quat<T> & rot );

	/**
	 * GETTER
	 */
	inline T		getX( void ) const
	{
		return ( (*this)[0] );
	}

	inline T		getY( void ) const
	{
		return ( (*this)[1] );
	}

	inline T		getZ( void ) const
	{
		return ( (*this)[2] );
	}

	/**
	 * SETTER
	 */
	inline void		setX( const T & x )
	{
		(*this)[0] = x;
	}

	inline void		setY( const T & y )
	{
		(*this)[1] = y;
	}

	inline void		setZ( const T & z )
	{
		(*this)[2] = z;
	}

	inline void		set( const T & x, const T & y, const T & z )
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}
};
template <typename T>
Vec3<T> const Vec3<T>::ZERO = Vec3( T( 0 ), T( 0 ), T( 0 ) );

template <typename T>
Vec3<T>	Vec3<T>::rotate( const Quat<T> & rot )
{
	Quat<T> conjugateQ = rot.conjugated();
	Quat<T> w = rot * ( * this ) * conjugateQ;

	return ( Vec3<T>( w.getI(), w.getJ(), w.getK() ) );
}

#endif // ! _VEC_HPP_
