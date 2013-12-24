// pylon_utilities.cpp
//
#include "stdafx.h"

#include "pylon_utilities.h"


// -----------------------------------------------------------------
//   Implementation of the CGrabBuffer class
// -----------------------------------------------------------------

// Constructor allocates the image buffer
CGrabBuffer::CGrabBuffer(const size_t ImageSize):m_pBuffer(NULL)
{
	m_pBuffer = new uint8_t[ ImageSize ];
	if (NULL == m_pBuffer)
	{
		GenICam::GenericException e("Not enough memory to allocate image buffer", __FILE__, __LINE__);
		throw e;
	}
};

// Freeing the memory
CGrabBuffer::~CGrabBuffer()
{
	if (NULL != m_pBuffer)
		delete[] m_pBuffer;
};
