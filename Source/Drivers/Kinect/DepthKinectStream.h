#ifndef _DEPTH_KINECT_STREAM_H_
#define _DEPTH_KINECT_STREAM_H_

#include "BaseKinectStream.h"

struct INuiSensor;
namespace kinect_device {

class DepthKinectStream : public BaseKinectStream
{
public:
	DepthKinectStream(KinectStreamImpl* pStreamImpl);

	virtual void frameReceived(NUI_IMAGE_FRAME& imageFrame, NUI_LOCKED_RECT &LockedRect);

	virtual OniStatus convertDepthToColorCoordinates(StreamBase* colorStream, int depthX, int depthY, OniDepthPixel depthZ, int* pColorX, int* pColorY);
	
	virtual OniStatus getProperty(int propertyId, void* data, int* pDataSize);

	virtual OniBool isPropertySupported(int propertyId);

	virtual void notifyAllProperties();

};
} // namespace kinect_device
#endif //_DEPTH_KINECT_STREAM_H_
