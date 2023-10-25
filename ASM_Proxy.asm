.CODE

extern g_ExportFnList:QWORD

DllMain_Wrapper PROC
	jmp g_ExportFnList[0*8]
DllMain_Wrapper ENDP

XInputEnable_Wrapper PROC
	jmp g_ExportFnList[1*8]
XInputEnable_Wrapper ENDP

XInputGetBatteryInformation_Wrapper PROC
	jmp g_ExportFnList[2*8]
XInputGetBatteryInformation_Wrapper ENDP

XInputGetCapabilities_Wrapper PROC
	jmp g_ExportFnList[3*8]
XInputGetCapabilities_Wrapper ENDP

XInputGetDSoundAudioDeviceGuids_Wrapper PROC
	jmp g_ExportFnList[4*8]
XInputGetDSoundAudioDeviceGuids_Wrapper ENDP

XInputGetKeystroke_Wrapper PROC
	jmp g_ExportFnList[5*8]
XInputGetKeystroke_Wrapper ENDP

XInputGetState_Wrapper PROC
	jmp g_ExportFnList[6*8]
XInputGetState_Wrapper ENDP

XInputSetState_Wrapper PROC
	jmp g_ExportFnList[7*8]
XInputSetState_Wrapper ENDP

ExportByOrdinal100 PROC
	jmp g_ExportFnList[8*8]
ExportByOrdinal100 ENDP

ExportByOrdinal101 PROC
	jmp g_ExportFnList[9*8]
ExportByOrdinal101 ENDP

ExportByOrdinal102 PROC
	jmp g_ExportFnList[10*8]
ExportByOrdinal102 ENDP

ExportByOrdinal103 PROC
	jmp g_ExportFnList[11*8]
ExportByOrdinal103 ENDP

END