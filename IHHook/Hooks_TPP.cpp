#include "Hooks_TPP.h"
#include "IHHook.h"//BaseAddr
#include "spdlog/spdlog.h"

#include "MinHook/MinHook.h"
#include "HookMacros.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>

namespace IHHook {
	std::map<int, long long> locationLangIds{
		{10,0x1b094033d45d},//afgh,tpp_loc_afghan
		{20,0x7114b69e71e7},//mafr,tpp_loc_africa
		{50,0xfa8eaa7758b1},//mtbs,tpp_loc_mb

		//DEBUGNOW proof of concept hack
		//{40,0x27376b6e62ff},//tpp_loc_gntn - caplags langid from his gntn addon
	};
	std::map<int, PhotoInfoString> photoInfoAddon = {};
	bool isCode102 = true;

	namespace Hooks_TPP {
		//tex from here
		//https://discord.com/channels/364177293133873153/364178190588968970/698650439817625691
		//(though still not sure how partoftheworlD recognised this in the first place)
		//If you memory dump the exe after execution of this point ghidra recognises this as entry point in the dumped exe
		//eyeballing the function it seems to be _mainCRTStartup
		//https://stackoverflow.com/questions/22934206/what-is-the-difference-between-main-and-maincrtstartup
		//"mainCRTStartup basically looks like this: 
		//init_tls(); 
		//init_crt(); 
		//run_global_constructors(); 
		//get_args(&argc, &argv); 
		//ret = main(argc, argv); 
		//run_global_destructors(); 
		//exit(ret); 
		//.So, main is in there, some place.� Damon Apr 8 '14 at 11:03"
		//tex so you can find actual main from this
		//not much point hooking it or actual main (lets call it FoxMain to be clearer) at the moment since IHHook is currently a dinput8 proxy which is obviously well past the _crtMain/FoxMain execute point


		uintptr_t missionCode_Addr = 0x142A58A00;
		//uint32_t* missionCode;//tex in header

		//TODO: move to exploration
		//void UnkSomePlayerUpdateFuncHook(intptr_t unkPlayerClass, uintptr_t playerIndex) {
		//	spdlog::trace(__func__);
		//	UnkSomePlayerUpdateFunc(unkPlayerClass, playerIndex);

		//	intptr_t playerClass = unkPlayerClass;
		//	
		//}//UnkSomePlayerUpdateFuncHook

		////Address of signature = mgsvtpp_1_0_15_1_en.exe + 0x012C7570//15.1
		//(UnkAnotherPlayerUpdateFuncButHuge)// 0x1412cf110 = 15.3 DEBUGNOW

		
			
	


		//tex the idroid free roam mission tab had an issue where it wouldn't show the name of custom free roam missions
		//despite there being a map_location_parameter - locationNameLangId = "tpp_loc_<whatever> (that matches tpp_common lng for vanilla free)
		//however the above map does show
		//given that there's a location icon I guess that's set up in engine
		//See IH InfMission.EnableLocationChangeMissions
		//searching for the hashes of the mentioned tpp_loc<> (kept for ref) in the exe finds this function
		//returns strcode64
		//IN: locationLangIds
		long long* GetFreeRoamLangIdHook(long long* langId, short locationCode, short missionCode) {
			spdlog::trace(__func__);

			//DEBUGNOW only missionCode entry in vanilla
			if (missionCode == 30150) {//mtbs_zoo
				*langId = 0xe3d47a6e1e15;//tpp_loc_mb_zoo
				return langId;
			}

			auto iterator = locationLangIds.find(locationCode);
			if (iterator != locationLangIds.end()) {
				*langId = iterator->second;//value
				return langId;
			}

			//if (locationCode == 10) {//afgh
			//	*langId = 0x1b094033d45d;////tpp_loc_afghan
			//	return langId;
			//}
			//if (locationCode == 20) {//mafr
			//	*langId = 0x7114b69e71e7;
			//	return langId;
			//}
			//if (locationCode == 50) {//mtbs
			//	*langId = 0xfa8eaa7758b1;//tpp_loc_mb 
			//	return langId;
			//}


			////DEBUGNOW proof of concept hack
			//if (locationCode == 40) {//gntn
			//	*langId = 0x27376b6e62ff;//tpp_loc_gntn - caplags langid from his gntn addon
			//	return langId;
			//}
			
			*langId = 0xb8a0bf169f98;// "" empty string
			return langId;
		}//GetFreeRoamLangIdHook

		//DEBUGNOW not really tpp only Hooks_Fox?
		static void UnkPrintFuncStubbedOutHook(const char* fmt, ...) {
			//spdlog::trace(__func__);
			va_list args;
			va_start(args, fmt);

			int size = 100;
			std::string message;
			va_list ap;

			while (1) {
				message.resize(size);
				va_start(ap, fmt);
				int n = vsnprintf(&message[0], size, fmt, ap);
				va_end(ap);

				if (n > -1 && n < size) {
					message.resize(n); // Make sure there are no trailing zero char
					break;
				}
				if (n > -1)
					size = n + 1;
				else
					size *= 2;
			}//while(1)

			spdlog::debug("UnkPrintFuncStubbedOutHook: {}", message);
		}//UnkPrintFuncStubbedOutHook

		void nullsub_2Hook(const char* unkSomeIdStr, unsigned long long unkSomeIdNum) {
			//spdlog::trace(__func__);
			if (unkSomeIdStr != NULL) {
				try {
					char idStr[1024];
					sprintf(idStr, "%s", unkSomeIdStr);
					spdlog::debug("nullsub_2 {}", idStr);
				}
				catch(...)  {

				}
			}
		}//nullsub_2Hook

		void CreateHooks() {
			spdlog::trace(__func__);
			//DEBUGNOW hitting some kind of exception on caps machine
			//missionCode = NULL;
			//try {
			//	missionCode = (uint32_t*)((missionCode_Addr - BaseAddr) + RealBaseAddr);
			//}
			//catch (std::runtime_error & e) {
			//	spdlog::error("CHP: runtime exception - {}", e.what());
			//	auto log = spdlog::get("ihhook");
			//	log->flush();
			//}
			//if (missionCode==NULL) {
			//	spdlog::error("CHP: missionCode==NULL");
			//}
			//DEBUGNOW

			//DEBUGNOW
			//if (_mainCRTStartupAddr == NULL) {
			//	bool bleh = true;
			//}

			if (addressSet["GetStrCodeWithLength"] == NULL) {
				spdlog::warn("addr fail: addressSet[\"GetStrCodeWithLength\"] == NULL");
			}
			else {					
				//DEBUGNOW TEST
				char* langId = "tpp_loc_afghan";
				long long tpp_loc_afghanS64 = GetStrCodeWithLength(langId, strlen(langId));

				std::stringstream stream;
				stream << std::hex << tpp_loc_afghanS64;
				std::string result(stream.str());
				spdlog::debug("Str64 tpp_loc_afghan:0x{}", result);

				//0x1b094033d45d//tpp_loc_afghan
					//{ 20,0x7114b69e71e7 },//mafr,tpp_loc_africa
					//{ 50,0xfa8eaa7758b1 },//mtbs,tpp_loc_mb
					////DEBUGNOW proof of concept hack
					//{ 40,0x27376b6e62ff },//tpp_loc_gntn - caplags langid from his gntn addon
			}

			if (addressSet["GetFreeRoamLangId"] == NULL || addressSet["UnkPrintFuncStubbedOut"] == NULL || addressSet["nullsub_2"] == NULL) {
				spdlog::warn("addr == NULL");
			}
			else {
				CREATE_HOOK(GetFreeRoamLangId)
				CREATE_HOOK(UnkPrintFuncStubbedOut)
				CREATE_HOOK(nullsub_2)

				ENABLEHOOK(GetFreeRoamLangId)

				ENABLEHOOK(UnkPrintFuncStubbedOut) //DEBUGNOW
#ifdef _DEBUG
				//ENABLEHOOK(nullsub_2)//DEBUGNOW
#endif // DEBUG
				CREATE_HOOK(GetChangeLocationMenuParameterByLocationId)
				ENABLEHOOK(GetChangeLocationMenuParameterByLocationId)
				CREATE_HOOK(GetPhotoAdditionalTextLangId)
				ENABLEHOOK(GetPhotoAdditionalTextLangId)
				//CREATE_HOOK(RegisterQuestAreaMarker)
				//ENABLEHOOK(RegisterQuestAreaMarker)
				//CREATE_HOOK(IsUseAreaIcon)
				//ENABLEHOOK(IsUseAreaIcon)
				//CREATE_HOOK(ConvertRadioTypeToSpeechLabel)
				//ENABLEHOOK(ConvertRadioTypeToSpeechLabel)
				//CREATE_HOOK(CallWithRadioType)
				//ENABLEHOOK(CallWithRadioType)
				//CREATE_HOOK(ConvertSpeechLabelToRadioType)
				//ENABLEHOOK(ConvertSpeechLabelToRadioType)
				//CREATE_HOOK(IsRaining)
				//ENABLEHOOK(IsRaining)
				//CREATE_HOOK(ConvertToVoiceType)
				//ENABLEHOOK(ConvertToVoiceType)
			}//if addr

			//DEBUGNOW
			//CREATE_HOOK(UnkSomeUpdateFunc)
			//ENABLEHOOK(UnkSomeUpdateFunc)
		}//CreateHooks
		ChangeLocationMenuParameter* GetChangeLocationMenuParameterByLocationIdHook(MotherBaseMissionCommonData* This, unsigned short locationCode)
		{
			//Ensure vanilla cases are handled by original function
			switch (locationCode)
			{
			case TppLocationId::afgh:
			case TppLocationId::mafr:
			case TppLocationId::mtbs:
				return GetChangeLocationMenuParameterByLocationId(This,locationCode);
			}

			//In case original check slips, send mtbs here
			if (locationCode == mtbs)
				return GetMbFreeChangeLocationMenuParameter(This);

			//Joey's structs and iteration code!
			ChangeLocationMenuParameter* params = This->ChangeLocationMenuParams;
			for (uint i = 0; i < This->ChangeLocationMenuParamCount; i++)
			{
				//top line is to ensure this locationcode is a valid free roam location
				if (locationLangIds.find(locationCode) != locationLangIds.end())
					if (params[i].LocationId == locationCode)
						return params + i;
			}
			return nullptr;
		}
		/*static const enum PHOTO_TYPE : byte {
			photo_type_h = 0,
			photo_type_v = 1,
			photo_type_v2 = 2,//??? ASSUMPTION
		};
		static const enum PHOTO_TEXT : byte {
			target_type_rescue = 1,
			target_type_recovery = 2,
			target_type_exclusion = 3,
			target_type_destruction = 4,
			target_type_tracking = 5,
			target_type_tailing = 6,
		};
		struct PhotoInfo {
			unsigned short MissionCode;
			byte PhotoId;
			PHOTO_TYPE PhotoType;
			PHOTO_TEXT TargetType;
		};
		PhotoInfo PHOTO_ADDITIONAL_TEXT[46]{
		  {10020,  10,  photo_type_v,  target_type_rescue},
		  {10036,  10,  photo_type_v,  target_type_exclusion},
		  {10033,  10,  photo_type_v,  target_type_recovery},
		  {10040,  10,  photo_type_h,  target_type_recovery},
		  {10041,  20,  photo_type_v,  target_type_exclusion},
		  {10041,  30,  photo_type_v,  target_type_exclusion},
		  {10041,  40,  photo_type_v,  target_type_exclusion},
		  {10044,  10,  photo_type_v,  target_type_exclusion},
		  {10052,  10,  photo_type_v,  target_type_recovery},
		  {10054,  10,  photo_type_h,  target_type_exclusion},
		  {10070,  10,  photo_type_v,  target_type_recovery},
		  {10080,  20,  photo_type_h,  target_type_destruction},
		  {10080,  30,  photo_type_h,  target_type_destruction},
		  {10086,  10,  photo_type_v,  target_type_rescue},
		  {10086,  20,  photo_type_v,  target_type_tailing},
		  {10082,  10,  photo_type_h,  target_type_exclusion},
		  {10090,  10,  photo_type_h,  target_type_recovery},
		  {10090,  20,  photo_type_h,  target_type_tracking},
		  {10195,  10,  photo_type_v,  target_type_tailing},
		  {10195,  20,  photo_type_v,  target_type_exclusion},
		  {10091,  10,  photo_type_v,  target_type_rescue},
		  {10091,  20,  photo_type_v,  target_type_rescue},
		  {10100,  10,  photo_type_v,  target_type_exclusion},
		  {10110,  10,  photo_type_v,  target_type_rescue},
		  {10121,  10,  photo_type_v,  target_type_exclusion},
		  {10121,  20,  photo_type_v,  target_type_tracking},
		  {10115,  10,  photo_type_v,  target_type_exclusion},
		  {10120,  10,  photo_type_v,  target_type_recovery},
		  {10085,  10,  photo_type_v,  target_type_rescue},
		  {10085,  20,  photo_type_v,  target_type_rescue},
		  {10200,  10,  photo_type_v,  target_type_recovery},
		  {10200,  20,  photo_type_v,  target_type_recovery},
		  {10211,  10,  photo_type_v,  target_type_exclusion},
		  {10081,  10,  photo_type_v,  target_type_rescue},
		  {10130,  10,  photo_type_v,  target_type_recovery},
		  {10150,  10,  photo_type_v,  target_type_exclusion},
		  {10151,  10,  photo_type_v,  target_type_destruction},
		  {10045,  10,  photo_type_v,  target_type_recovery},
		  {10093,  10,  photo_type_v,  target_type_recovery},
		  {10093,  20,  photo_type_v,  target_type_recovery},
		  {10171,  10,  photo_type_h,  target_type_exclusion},
		  {10171,  20,  photo_type_h,  target_type_exclusion},
		  {10171,  30,  photo_type_h,  target_type_exclusion},
		  {10171,  40,  photo_type_h,  target_type_exclusion},
		  {10171,  50,  photo_type_h,  target_type_exclusion},
		  {10260,  10,  photo_type_v,  target_type_recovery},
		};
		static const std::map<byte, ulonglong> PHOTO_TEXT_LANGID{
			{target_type_rescue,0xa59d60747df1},//target_type_rescue			"Rescue Target"
			{target_type_recovery,0x3fc178c7269a},//target_type_recovery		"Extraction Target"
			{target_type_exclusion,0xd158f6869064},//target_type_exclusion		"Elimination Target"
			{target_type_destruction,0x2404a0893924},//target_type_destruction	"Destruction Target"
			{target_type_tracking,0xe3b11024560e},//target_type_tracking		"Tracking Target"
			{target_type_tailing,0xc1ad14dff6fc},//target_type_tailing			"Tailing Target"
		};*/
		std::list<PhotoInfo> addPhotoInfos{};
		unsigned long long __thiscall GetPhotoAdditionalTextLangIdHook(MotherBaseMissionCommonData* This, StringId* ret, unsigned short missionCode, unsigned char photoId, unsigned char photoType)
		{
			spdlog::info("GetPhotoAdditionalTextLangIdHook missionCode={}, photoId={}, photoType={}", missionCode, photoId, photoType);
			
			for (auto const& i : addPhotoInfos) {
				if (i.MissionCode == missionCode)
				{
					if (i.PhotoId == photoId)
					{
						if (i.PhotoType == photoType)
						{
							spdlog::info("GetPhotoAdditionalTextLangIdHook return {:x}\n", *ret);
							*ret = i.TargetTypeLangId;
							return *ret;
						}
					}
				}
			}
			spdlog::info("GetPhotoAdditionalTextLangIdHook return 3 {:x}", *ret);
			return GetPhotoAdditionalTextLangId(This,ret,missionCode,photoId,photoType);
		}

		void AddPhotoAdditionalText(unsigned short missionCode, unsigned char photoId, unsigned char photoType, const char* targetTypeLangIdStr)
		{
			unsigned long long hash = GetStrCodeWithLength(targetTypeLangIdStr, strlen(targetTypeLangIdStr));
			for (std::list<PhotoInfo>::iterator it = addPhotoInfos.begin(); it != addPhotoInfos.end(); ++it){
				if (it->MissionCode == missionCode)
				{
					if (it->PhotoId == photoId)
					{
						if (it->PhotoType == photoType)
						{
							spdlog::info("[GitmoHook] AddPhotoAdditionalText replaced %d %d %d with %s\n",missionCode,photoId,photoType,targetTypeLangIdStr);
							it->TargetTypeLangId = hash;
							return;
						}
					}
				}
			}
			PhotoInfo photoInfo = {
				missionCode,
				photoId,
				static_cast<PHOTO_TYPE>(photoType),
				hash,
			};
			addPhotoInfos.push_back(photoInfo);
			spdlog::info("[GitmoHook] AddPhotoAdditionalText added %d %d %d with %s\n",missionCode,photoId,photoType,targetTypeLangIdStr);
		}
		//bool IsUseAreaIconHook(void* MbDvcMapCallbackIconImpl, uint param_1, uint flags, bool param_3, bool param_4, bool param_5, bool param_6)
		//{
		//	if (param_1 == 0x31)//quest markers in location change menu
		//	{
		//		//spdlog::info("IsUseAreaIconHook param_1={},param_2={},param_3={},param_4={},param_5={},param_6={}", param_1, flags, param_3, param_4, param_5, param_6);

		//		bool flag29 = flags >> 0x1d & 1; //always false?
		//		bool flag30 = flags >> 0x1e & 1; //returning this only shows africa ops
		//		bool flag23 = flags >> 0x17 & 1; //returning this only shows mtbs ops
		//		//both false shows only afgh and addons, and only in afgh
		//		// 
		//		//!flag30 && !flag23 - afghanistan and addons in afghanistan
		//		//flag30 - africa everywhere
		//		//flag23 - mtbs everywhere

		//		//return true;
		//	}
		//	return IsUseAreaIcon(MbDvcMapCallbackIconImpl, param_1, flags, param_3, param_4, param_5, param_6);
		//};
		//static void RegisterQuestAreaMarkerHook(MbDvcSideOpsCallbackImpl* This, SideOpsInfo* sideOpsInfo)
		//{
		//	spdlog::info("RegisterQuestAreaMarkerHook");
		//	spdlog::info("sideOpsInfo: questId={}, locationId={}", sideOpsInfo->questId, sideOpsInfo->locationId);
		//	spdlog::info("sideOpsInfo: iconPos={}, paddingA={}", (ulong)sideOpsInfo->iconPos, (ubyte)sideOpsInfo->paddingA);
		//	spdlog::info("sideOpsInfo: paddingB={}", (ubyte)sideOpsInfo->paddingB);
		//	SideOpsInfo* sideOpInfos = This->sideOpInfo;
		//	for (int i = 0; i < This->questCount; i++)
		//	{
		//		//spdlog::info("MbDvcSideOpsCallbackImpl: i={}, questId={}, locationId={}", i, (sideOpInfos+i)->questId, (sideOpInfos + i)->locationId);
		//	}
		//	//RegisterQuestAreaMarker(This, sideOpsInfo);
		//};
		/*std::map<ubyte, uint> RadioTypeToSpeechLabel = {
			{0x5a,0x5437f13a},//CPR0038
		};
		uint ConvertRadioTypeToSpeechLabelHook(ubyte radioType)
		{
			if (isCode102)
			{
				if (radioType == 0x5a)
				{
					return GetStrCode32("CPR0038_102");
				}
			}
			auto ret = ConvertRadioTypeToSpeechLabel(radioType);
			spdlog::info("ConvertRadioTypeToSpeechLabel({})={}", radioType, ret);
			return ret;
		};
		ubyte ConvertSpeechLabelToRadioTypeHook(uint speechLabel)
		{
			if (isCode102)
			{
				if (speechLabel == GetStrCode32("CPR0038_102"))
				{
					return 0x5a;
				}
			}
			auto ret = ConvertSpeechLabelToRadioType(speechLabel);
			spdlog::info("ConvertSpeechLabelToRadioType({})={}", speechLabel, ret);
			return ret;
		};
		bool IsRainingHook(void* Soldier2, uint param_2)
		{
			bool ret = IsRaining(Soldier2, param_2);
			spdlog::info("IsRaining({})={}", param_2, ret);
			return false;
		};
		uint ConvertToVoiceTypeHook(uint voiceTypeS32)
		{
			//if (voiceTypeS32 == GetStrCode32("chico"))
				//return FNVHash32("chico");
			uint ret = ConvertToVoiceType(voiceTypeS32);
			spdlog::info("ConvertToVoiceType({})={}", voiceTypeS32, ret);
			return ret;
		}*/
	}//Hooks_TPP
}//namespace IHHook