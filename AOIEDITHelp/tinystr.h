/*
www.sourceforge.net/projects/tinyxml
Original file by Yves Berquin.

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

/*
 * THIS FILE WAS ALTERED BY Tyge Lovset, 7. April 2005.
 *
 * - completely rewritten. compact, clean, and fast implementation.
 * - sizeof(TiXmlString) = pointer size (4 bytes on 32-bit systems)
 * - fixed reserve() to work as per specification.
 * - fixed buggy compares operator==(), operator<(), and operator>()
 * - fixed operator+=() to take a const ref argument, following spec.
 * - added "copy" constructor with length, and most compare operators.
 * - added swap(), clear(), size(), capacity(), operator+().
 */

#ifndef  TIXML_USE_STL
#ifndef TIXML_STRING_INCLUDED
#define TIXML_STRING_INCLUDED
#include "assert.h"
#include "string.h"

#if defined(_MSC_VER) && (_MSC_VER>=1200)

#define TIXML_EXPLICIT explicit
#elif defined(__GNUC__)&&(__GNUC__>=3)
#define TIXML_EXPLICIT explicit
#else
#define TIXML_EXPLICIT
#endif
class TiXmlString{
public:
	typedef size_t size_type;
	static const size_type npos;
	TiXmlString () : rep_(&nullrep_){}
	TiXmlString (const TiXmlString &copy) : rep_(0){
		init(copy.length());
		memcpy(start(),copy.data(),length());
	}
	TIXML_EXPLICIT TiXmlString (const char * copy) : rep_(0) 
	{
       init( static_cast<size_type>( strlen(copy)));
	   memcpy(start(),copy,length());
	}
	TIXML_EXPLICIT TiXmlString( const char * str,size_type len) : rep_(0)
	{
		init(len);
		memcpy(start(),str,len);
	}
	~TiXmlString (){quit();}
	TiXmlString& operator = (const char * copy)
	{
		return assign(copy,(size_type)strlen(copy));
	}
	TiXmlString& operator = (const TiXmlString & copy)
	{
		return assign(copy.start(),copy.length());
	}
	TiXmlString& operator += (const char * suffix)
	{
		return append(suffix,static_cast<size_type>(strlen(suffix)));
	}
	TiXmlString & operator += (char single)
	{
		return append(&single,1);
	}
	TiXmlString& operator += (const TiXmlString & suffix)
	{
		return append(suffix.data(),suffix.length());
	}
	const char * c_str () const { return rep_->str;}
	const char * data () const{return rep_->str;}
	size_type length () const {return rep_->size;}
	size_type size () const { return rep_->size;}
	bool empty() const {return rep_->size == 0;}
	size_type capacity () const {return rep_->capacity;}
	const char & at (size_type index)const
	{
		assert( index < length());
		return rep_->str[index];
	}
	char& operator [] (size_type index) const
	{
		assert( index < length());
		return rep_->str[ index ];
	}
	size_type find (char lookup) const{
		return find(lookup,0);
	}
	size_type find (char tofind,size_type offset) const
	{
		if(offset > length()) return npos;
		for (const char * p = c_str()+offset;*p != '\0';++p)
		{
			if(*p == tofind) return static_cast<size_type>(p - c_str());
		}
		return npos;
	}
	void clear(){
		quit();
		init(0,0);
	}
	void swap(TiXmlString & other)
	{
		Rep* r = rep_;
		rep_ = other.rep_;
		other.rep_ = r;
	}
	void reserve(size_type cap);
	TiXmlString & assign(const char* str,size_type len);
	TiXmlString & append(const char* str,size_type len);
private:
	void init(size_type sz){init(sz,sz);}
	void set_size(size_type sz){rep_->str[rep_->size = sz] = '\0';}
	char * start() const {return rep_->str;}
	char * finish() const {return rep_->str + rep_->size;}
	void init(size_type sz,size_type cap)
	{
		if(cap){
		const size_type bytesNeeded = sizeof(Rep) + cap;
		const size_type intsNeeded = (bytesNeeded + sizeof(int) - 1) / sizeof(int);
		rep_ = reinterpret_cast<Rep*>(new int[intsNeeded]);
		rep_->str[rep_->size = sz] = '\0';
		rep_->capacity = cap;
		}
		else
		{
            rep_ = &nullrep_;
		}
	}
	void quit()
	{
		if (rep_ != &nullrep_)
		{
           delete [] (reinterpret_cast<int*>(rep_));
		}
	}
	struct Rep{
		size_type size,capacity;
		char str[1];
	};
	Rep * rep_;
	static Rep nullrep_;

};
inline bool operator == (const TiXmlString & a,const TiXmlString & b)
{
	return ( a.length() == b.length() )
		&& ( strcmp(a.c_str(),b.c_str()) == 0);
}
inline bool operator < (const TiXmlString & a,const TiXmlString & b)
{
	return strcmp(a.c_str(),b.c_str()) < 0;
}
inline bool operator != (const TiXmlString & a, const TiXmlString & b) { return !(a == b);}
inline bool operator >  (const TiXmlString & a, const TiXmlString & b) {return b < a;}
inline bool operator <= (const TiXmlString & a, const TiXmlString & b) {return !(b < a);}
inline bool operator >= (const TiXmlString & a, const TiXmlString & b) {return !(a < b);}

inline bool operator == (const TiXmlString & a,const char *b) {return strcmp(a.c_str(),b)==0;}
inline bool operator == (const char *b,const TiXmlString & a) {return b == a;}
inline bool operator != (const TiXmlString & a,const char *b) {return !(a == b);}
inline bool operator != (const char * a,const TiXmlString & b){return !(b == a);}
TiXmlString operator + (const TiXmlString & a,const TiXmlString & b);
TiXmlString operator + (const TiXmlString & a,const char * b);
TiXmlString operator + (const char * a,const TiXmlString & b);
class TiXmlOutStream:public TiXmlString
{
public:
	TiXmlOutStream & operator << (const TiXmlString & in)
	{
		*this +=in;
		return *this;
	}
	TiXmlString & operator << (const char * in)
	{
		*this += in;
		return *this;
	}
};
#endif
#endif