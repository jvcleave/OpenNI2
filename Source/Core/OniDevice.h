/*****************************************************************************
*                                                                            *
*  OpenNI 2.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef _ONI_IMPL_DEVICE_H_
#define _ONI_IMPL_DEVICE_H_

#include "OniDriverHandler.h"
#include "OniCommon.h"
#include "XnList.h"

ONI_NAMESPACE_IMPLEMENTATION_BEGIN

class Context;
class VideoStream;

class DeviceDriver;

class Device
{
public:
	Device(DeviceDriver* pDeviceDriver, const DriverHandler& libraryHandler, const OniDeviceInfo* pDeviceInfo, xnl::ErrorLogger& errorLogger);
	~Device();

	OniStatus open();
	OniStatus close();

	OniStatus getSensorInfoList(OniSensorInfo** pSensors, int& numSensors);

	const OniDeviceInfo* getInfo() const;

	VideoStream* createStream(OniSensorType sensorType);

	OniStatus setProperty(int propertyId, const void* data, int dataSize);
	OniStatus getProperty(int propertyId, void* data, int* pDataSize);
	OniBool isPropertySupported(int propertId);
	void notifyAllProperties();
	OniStatus invoke(int commandId, const void* data, int dataSize);
	OniBool isCommandSupported(int commandId);

	void* getHandle() const {return m_deviceHandle;}
	DeviceDriver* getDeviceDriver() {return m_pDeviceDriver; }

	OniBool isImageRegistrationModeSupported(OniImageRegistrationMode mode);
	OniStatus tryManualTrigger();

	void clearStream(VideoStream* pStream);

	OniStatus enableDepthColorSync(Context* pContext);
	void disableDepthColorSync();
	OniBool isDepthColorSyncEnabled();

	void refreshDepthColorSyncState();
private:

	typedef struct 
	{
		int frameId;
		void* pStream;
	} Seek;

	Device(const Device& other);
	Device& operator=(const Device& other);

	static void ONI_CALLBACK_TYPE stream_PropertyChanged(void* deviceHandle, int propertyId, const void* data, int dataSize, void* pCookie);

	const DriverHandler& m_driverHandler;
	xnl::ErrorLogger& m_errorLogger;
	OniDeviceInfo* m_pInfo;
	bool m_active;

	int m_openCount;

	void* m_deviceHandle;
	DeviceDriver* m_pDeviceDriver;

	xnl::List<VideoStream*> m_streams;
	OniFrameSyncHandle m_depthColorSyncHandle;
	Context* m_pContext;
	OniBool m_syncEnabled;
};

ONI_NAMESPACE_IMPLEMENTATION_END

#endif // _ONI_IMP_DEVICE_H_
