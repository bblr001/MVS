#pragma once

#define USE_GIGE

// Include files to use the PYLON API
#include <pylon/PylonIncludes.h>
#include <stdlib.h>

using namespace Pylon;

#if defined( USE_1394 )
// Settings to use  Basler 1394 cameras
#include <pylon/1394/Basler1394Camera.h>
typedef Pylon::CBasler1394Camera Camera_t;
using namespace Basler_IIDC1394CameraParams;
using namespace Basler_IIDC1394StreamParams;
#elif defined ( USE_GIGE )
// settings to use Basler GigE cameras
#include <pylon/gige/BaslerGigECamera.h>
typedef Pylon::CBaslerGigECamera Camera_t;
using namespace Basler_GigECameraParams;
using namespace Basler_GigEStreamParams;
#else
#error Camera type is not specified. For example, define USE_GIGE for using GigE cameras
#endif

//#include <windows.h>
#include <vector>

using namespace Pylon;
//using namespace GenApi;
using namespace std;


/*
* \brief Automatic locking of block statements 
* 
* class T requirements are the functions void Lock() and void Unlock().
*/
template<class T> 
class CAutoLock
{
  T& m_LockingObject;
public:
  CAutoLock( T& obj )
    : m_LockingObject( obj )
  {
    m_LockingObject.Lock();
  }
  ~CAutoLock()
  {
    m_LockingObject.Unlock();
  }
};

class CGrabBuffer
{
public:
	CGrabBuffer(const size_t ImageSize);
	~CGrabBuffer();
	uint8_t* GetBufferPointer(void) { return m_pBuffer; }
	StreamBufferHandle GetBufferHandle(void) { return m_hBuffer; }
	void SetBufferHandle(StreamBufferHandle hBuffer) { m_hBuffer = hBuffer; };

protected:
	uint8_t *m_pBuffer;
	StreamBufferHandle m_hBuffer;
};


/// Wrapper for Win32 CriticalSection
class CAutoCriticalSection
{
  /// the Win32 critical section
  CRITICAL_SECTION m_CS;
public:
  /// constructor
  CAutoCriticalSection()
  {
    ::InitializeCriticalSection( &m_CS );
  }
  /// destructor
  ~CAutoCriticalSection()
  {
    ::DeleteCriticalSection( &m_CS );
  }

private:
  CAutoCriticalSection( const CCriticalSection & );           // not implemented
  CAutoCriticalSection& operator=( const CCriticalSection& ); // not implemented
public:
  /// wait for ownership
  void Lock()
  {
    ::EnterCriticalSection( &m_CS );
  }
  /// release ownership
  void Unlock()
  {
    ::LeaveCriticalSection( &m_CS );
  }
  /// attempt to gain ownership - true if entering
  bool TryLock()
  {
#if _WIN32_WINNT >= 0x0400
    return ::TryEnterCriticalSection( &m_CS )!= 0;
#else
    assert( FALSE && _T( "TryLock not implemented" ) );
    return false;
#endif
  }

};


typedef CAutoLock<CAutoCriticalSection> MyCLock;


//! Template class to calculate a moving average
/*! \param T Type of the measurement data (typically double or float)
\param span Number of samples used of computing the mean
The class is thread safe.
*/
template <class T, unsigned int span = 10>
class CMovingAvg
{
  
public:
  //! Default constructor
  CMovingAvg() : m_v(span) 
  {
    Reset();
  }
  
  //! Add a data item to the moving average
  void Add(T sample) 
  { 
    MyCLock lck( m_CritSect );
    //m_CritSect.Lock();
    int idx = m_n % span;
    if ( m_n < span )
    {
      m_v[idx] = sample;
      m_Sum += sample;
    }
    else
    {
      m_Sum -= m_v[idx];
      m_Sum += sample;
      m_v[idx] = sample;
    }
    m_n++;
  }
  
  //! Get the average
  double Avg() {
    double res = 0;
    MyCLock lck( m_CritSect );
    //m_CritSect.Lock();
    if ( m_n != 0 )
    {
      res = m_n < span ? m_Sum / (double) m_n : m_Sum / (double) span;
    }
    //m_CritSect.Unlock();
    return res;
  }
  
  //! Reset the moving average clearing the history
  void Reset() {
    MyCLock lck( m_CritSect );
    //m_CritSect.Lock();
    m_Sum = 0.0;
    m_n = 0;
    //m_CritSect.Unlock();
  }
  
protected:
  //! The current sum
  double m_Sum;
  
  //! Number of measurement data
  unsigned int m_n;
  
  //! Vector holding #span data items
  std::vector<T> m_v;
  
  //! critical section guarding the access to the class
  CAutoCriticalSection m_CritSect;
  
};



class CStopWatch
{
public:
	/// Constructor, starts time measurement
	CStopWatch(){ Start(); }

	/// Start the stop watch 
	void Start(){ QueryPerformanceCounter(&m_StartTime); }

	/// Stop. The elapsed time is returned. The stop watch may be started again
	double Stop(bool StartAgain)
	{
		QueryPerformanceCounter(&m_StopTime);
		double theElapsedTime = ElapsedTime();
		if(StartAgain)
			m_StartTime = m_StopTime; 
		return theElapsedTime;
	}

	/// Return the elapsed time in seconds between start() and stop()
	double ElapsedTime()
	{
		LARGE_INTEGER timerFrequency;
		QueryPerformanceFrequency(&timerFrequency);

		__int64 oldTicks = ((__int64)m_StartTime.HighPart << 32) + (__int64)m_StartTime.LowPart;
		__int64 newTicks = ((__int64)m_StopTime.HighPart << 32) + (__int64)m_StopTime.LowPart;
		long double timeDifference = (long double) (newTicks - oldTicks);

		long double ticksPerSecond = (long double) (((__int64)timerFrequency.HighPart << 32) 
			+ (__int64)timerFrequency.LowPart);

		return (double)(timeDifference / ticksPerSecond);
	}

private:
	/// zero-point for time measurement
	LARGE_INTEGER m_StartTime;

	/// last time stamp
	LARGE_INTEGER m_StopTime;
};




