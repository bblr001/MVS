// Contains a configuration that sets the Image AOI.
#pragma once

#include <pylon/ConfigurationEventHandler.h>

namespace Pylon
{
    class CInstantCamera;
}
class CameraConfiguration : public Pylon::CConfigurationEventHandler
{
public:    
    void OnOpened( Pylon::CInstantCamera& camera) 
    {
        try
        {
            // Allow all the names in the namespace GenApi to be used without qualification.
            using namespace GenApi;

            // Get the camera control object.
            INodeMap &control = camera.GetNodeMap();

            // Get the parameters for setting the image area of interest (Image AOI).
            const CIntegerPtr width = control.GetNode("Width");
            const CIntegerPtr height = control.GetNode("Height");
            const CIntegerPtr offsetX = control.GetNode("OffsetX");
            const CIntegerPtr offsetY = control.GetNode("OffsetY");

            // Maximize the Image AOI.
            if (IsWritable(offsetX))
            {
                offsetX->SetValue(offsetX->GetMin());
            }
            if (IsWritable(offsetY))
            {
                offsetY->SetValue(offsetY->GetMin());
            }
            width->SetValue(width->GetMax());
            height->SetValue(height->GetMax());  

			// Get the Packet Size for 1394 cameras
			const CIntegerPtr packetSize1394 = control.GetNode("PacketSize");
			// Set the Packet Size to 4096 by default.
			// For 1394-b cameras you may set the Packet Size up to 8192 Byte, 
			// which may be needed in order to reach the given maximum frame rate.
            if (IsWritable(packetSize1394))
            {
                packetSize1394->SetValue(4096);
            }

			// Get the Packet Size for GigE cameras
			const CIntegerPtr packetSizeGigE= control.GetNode("GevSCPSPacketSize");
			// Set the Packet Size to 1500 by default.
			// If your network adapter and/or switch supported Jumbo Frames,
			// you may consider using higher values for Packet Size, e.g. 3000, 6000, 9000.
			// By rule of thumb, the bigger the Packet Size- the better the overall performance.
            if (IsWritable(packetSizeGigE))
            {
                packetSizeGigE->SetValue(1500);
            }

        }
        catch (GenICam::GenericException& e)
        {
            throw RUNTIME_EXCEPTION( "Could not apply configuration. GenICam::GenericException caught in OnOpened method msg=%hs", e.what());
        }
    }
};

