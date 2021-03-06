/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2003 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef VRLIB_VEC3F
#define VRLIB_VEC3F 1

#include <ostream>

#include <vr/Vec2.h>
#include <vr/vrMath.h>

namespace vr {

/** General purpose float triple for use as vertices, vectors and normals.
 * Provides general math operations from addition through to cross products.
 * No support yet added for float * Vec3 - is it necessary?
 * Need to define a non-member non-friend operator*  etc.
 * Vec3 * float is okay
 */
   class Vec3
   {
      public:
        typedef float value_type;

         value_type _v[3];

         Vec3() { _v[0]=0.0; _v[1]=0.0; _v[2]=0.0;}
         Vec3(value_type x,value_type y,value_type z) { _v[0]=x; _v[1]=y; _v[2]=z; }
         Vec3(value_type const v[3]) { _v[0]=v[0]; _v[1]=v[1]; _v[2]=v[2]; }
         Vec3(const Vec2& v2,value_type zz)
         {
            _v[0] = v2[0];
            _v[1] = v2[1];
            _v[2] = zz;
         }


         inline bool operator == (const Vec3& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2]; }
        
         inline bool operator != (const Vec3& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2]; }

         inline bool operator <  (const Vec3& v) const
         {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else return (_v[2]<v._v[2]);
         }

         inline value_type* ptr() { return _v; }
         inline const value_type* ptr() const { return _v; }

         inline void set( value_type x, value_type y, value_type z)
         {
            _v[0]=x; _v[1]=y; _v[2]=z;
         }

         inline void set( const Vec3& rhs)
         {
            _v[0]=rhs._v[0]; _v[1]=rhs._v[1]; _v[2]=rhs._v[2];
         }

         inline value_type& operator [] (int i) { return _v[i]; }
         inline value_type operator [] (int i) const { return _v[i]; }

         inline value_type& x() { return _v[0]; }
         inline value_type& y() { return _v[1]; }
         inline value_type& z() { return _v[2]; }

         inline value_type x() const { return _v[0]; }
         inline value_type y() const { return _v[1]; }
         inline value_type z() const { return _v[2]; }

         inline bool valid() const { return !isNaN(); }
         inline bool isNaN() const { return vr::isNaN(_v[0]) || vr::isNaN(_v[1]) || vr::isNaN(_v[2]); }

         /** Dot product. */
         inline value_type operator * (const Vec3& rhs) const
         {
            return _v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2];
         }

         /** Cross product. */
         inline const Vec3 operator ^ (const Vec3& rhs) const
         {
            return Vec3(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
                        _v[2]*rhs._v[0]-_v[0]*rhs._v[2] ,
                        _v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
         }

         /** Multiply by scalar. */
         inline const Vec3 operator * (value_type rhs) const
         {
            return Vec3(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs);
         }

         /** Unary multiply by scalar. */
         inline Vec3& operator *= (value_type rhs)
         {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            return *this;
         }

         /** Divide by scalar. */
         inline const Vec3 operator / (value_type rhs) const
         {
            return Vec3(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs);
         }

         /** Unary divide by scalar. */
         inline Vec3& operator /= (value_type rhs)
         {
            _v[0]/=rhs;
            _v[1]/=rhs;
            _v[2]/=rhs;
            return *this;
         }

         /** Binary vector add. */
         inline const Vec3 operator + (const Vec3& rhs) const
         {
            return Vec3(_v[0]+rhs._v[0], _v[1]+rhs._v[1], _v[2]+rhs._v[2]);
         }

         /** Unary vector add. Slightly more efficient because no temporary
          * intermediate object.
          */
         inline Vec3& operator += (const Vec3& rhs)
         {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            return *this;
         }

         /** Binary vector subtract. */
         inline const Vec3 operator - (const Vec3& rhs) const
         {
            return Vec3(_v[0]-rhs._v[0], _v[1]-rhs._v[1], _v[2]-rhs._v[2]);
         }

         /** Unary vector subtract. */
         inline Vec3& operator -= (const Vec3& rhs)
         {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            return *this;
         }

         /** Negation operator. Returns the negative of the Vec3. */
         inline const Vec3 operator - () const
         {
            return Vec3 (-_v[0], -_v[1], -_v[2]);
         }

         /** Length of the vector = sqrt( vec . vec ) */
         inline value_type length() const
         {
            return sqrtf( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );
         }

         /** Length squared of the vector = vec . vec */
         inline value_type length2() const
         {
            return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2];
         }

         /** Normalize the vector so that it has length unity.
          * Returns the previous length of the vector.
          */
         inline value_type normalize()
         {
            value_type norm = Vec3::length();
            if (norm>0.0)
            {
               value_type inv = 1.0f/norm;
               _v[0] *= inv;
               _v[1] *= inv;
               _v[2] *= inv;
            }                
            return( norm );
         }

         inline Vec3 normalized() const
         {
            value_type norm = Vec3::length();
            if (norm>0.0)
            {
               value_type inv = 1.0f/norm;
               Vec3 normal(*this);
               normal *= inv;
               return normal;
            }
            else
            {
               return Vec3(0, 0, 0);
            }
         }

         friend inline std::ostream& operator << (std::ostream& output, const Vec3& vec);

   };    // end of class Vec3

   inline std::ostream& operator << (std::ostream& output, const Vec3& vec)
   {
      output << vec._v[0] << " "
             << vec._v[1] << " "
             << vec._v[2];
      return output;     // to enable cascading
   }

   const Vec3 X_AXIS(1.0,0.0,0.0);
   const Vec3 Y_AXIS(0.0,1.0,0.0);
   const Vec3 Z_AXIS(0.0,0.0,1.0);

}    // end of namespace osg

#endif
