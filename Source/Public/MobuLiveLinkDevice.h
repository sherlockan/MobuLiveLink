// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MobuLiveLinkCommon.h"
#include "IStreamObject.h"
#include "Misc/CommandLine.h"
#include "Async/TaskGraphInterfaces.h"
#include "Modules/ModuleManager.h"
#include "UObject/Object.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/OutputDevice.h"

//--- Registration defines
#define MOBULIVELINK__CLASSNAME		FMobuLiveLink
#define MOBULIVELINK__CLASSSTR		"MobuLiveLink"

#define IntToChar(input) std::to_string(input).c_str()
#define FStringToChar(input) ((std::string)TCHAR_TO_UTF8(*input)).c_str()

//! Simple input device.
class FMobuLiveLink : public FBDevice
{
	//--- FiLMBOX declaration
	FBDeviceDeclare(FMobuLiveLink, FBDevice);
public:
	void StartLiveLink();
	void StopLiveLink();

	//--- FiLMBOX Construction/Destruction
	bool FBCreate() override;		//!< FiLMBOX constructor.
	void FBDestroy() override;		//!< FiLMBOX destructor.

	//--- Initialisation/Shutdown
	bool Init();		//!< Initialize/create device.
	bool Done();		//!< Remove device.
	bool Reset();		//!< Reset device.
	bool Stop();		//!< Stop device (offline).
	bool Start();		//!< Start device (online).

	//--- The following will be called by the real-time engine.
	void DeviceIONotify(kDeviceIOs  Action, FBDeviceNotifyInfo &DeviceNotifyInfo) override;	//!< Notification of/for Device IO.
	bool DeviceEvaluationNotify(kTransportMode Mode, FBEvaluateInfo* EvaluateInfo) override;	//!< Evaluation the device (write to hardware).
	bool DeviceOperation(kDeviceOperations Operation) override;	//!< Operate device.

	//--- FBX Load/Save.
	bool FbxStore(FBFbxObject* FbxObject, kFbxObjectStore StoreWhat) override;	//!< Store in FBX file.
	bool FbxRetrieve(FBFbxObject* FbxObject, kFbxObjectStore StoreWhat) override;	//!< Retrieve from FBX file.

	//--- Events
	void EventSceneChange(HISender Sender, HKEvent Event);
	void EventRenderUpdate(HISender Sender, HKEvent Event);

public:
	const FString mProviderName = TEXT("Mobu Live Link");
	TMap<int32, TSharedPtr<IStreamObject>> StreamObjects;
	
	TSharedPtr<ILiveLinkProvider> LiveLinkProvider;

	void UpdateStreamObjects();

	void SetDirty(bool bNewDirty) { bIsDirty = bNewDirty; };
	bool IsDirty() const { return bIsDirty; };

	void SetRefreshUI(bool bNewRefreshUI) { bShouldRefreshUI = bNewRefreshUI; };
	bool ShouldRefreshUI() const { return bShouldRefreshUI; };

	const TArray<TPair<FString, FFrameRate>> SampleOptions =
	{
		TPair<FString, FFrameRate>(FString("30hz"), FFrameRate(30, 1)),
		TPair<FString, FFrameRate>(FString("50hz"), FFrameRate(50, 1)),
		TPair<FString, FFrameRate>(FString("60hz"), FFrameRate(60, 1)),
		TPair<FString, FFrameRate>(FString("100hz"), FFrameRate(100, 1)),
		TPair<FString, FFrameRate>(FString("120hz"), FFrameRate(120, 1)),
		TPair<FString, FFrameRate>(FString("Before Render"), FFrameRate(-1, 1)),
	};

	FFrameRate CurrentSampleRate;
	void UpdateSampleRate();

	int32 GetNextUID();
private:
	int32 NextUID = 1;

	void UpdateStream(); //!< Get latest data and send to unreal

	int32 GetCurrentSampleRateIndex();

	bool bIsDirty;
	bool bShouldRefreshUI;

	bool bShouldUpdateInRenderCallback; //!< Whether to update after render or to update in device evaluation

	FBDeviceSamplingMode SamplingType;
	FBFastLock mCleanUpLock;

	TMap<FBSceneChangeType, const char *> SceneChangeNameMap;

	double LastEvaluationTime;

	void SetDeviceInformation(const char* NewDeviceInformation);
	void TickCoreTicker();
};

