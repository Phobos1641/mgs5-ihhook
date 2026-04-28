this.photoInfos={
	{missionCode=20010,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=20010,  photoId=30,  photoType=1,  targetTypeLangId="target_type_rescue"},
}
function this.UpdateChangeLocationMenu()
  local photoInfos={
	{missionCode=10020,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10036,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10033,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10040,  photoId=10,  photoType=0,  targetTypeLangId="target_type_recovery"},
	{missionCode=10041,  photoId=20,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10041,  photoId=30,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10041,  photoId=40,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10044,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10052,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10054,  photoId=10,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10070,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10080,  photoId=20,  photoType=0,  targetTypeLangId="target_type_destruction"},
	{missionCode=10080,  photoId=30,  photoType=0,  targetTypeLangId="target_type_destruction"},
	{missionCode=10086,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10086,  photoId=20,  photoType=1,  targetTypeLangId="target_type_tailing"},
	{missionCode=10082,  photoId=10,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10090,  photoId=10,  photoType=0,  targetTypeLangId="target_type_recovery"},
	{missionCode=10090,  photoId=20,  photoType=0,  targetTypeLangId="target_type_tracking"},
	{missionCode=10195,  photoId=10,  photoType=1,  targetTypeLangId="target_type_tailing"},
	{missionCode=10195,  photoId=20,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10091,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10091,  photoId=20,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10100,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10110,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10121,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10121,  photoId=20,  photoType=1,  targetTypeLangId="target_type_tracking"},
	{missionCode=10115,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10120,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10085,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10085,  photoId=20,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10200,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10200,  photoId=20,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10211,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10081,  photoId=10,  photoType=1,  targetTypeLangId="target_type_rescue"},
	{missionCode=10130,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10150,  photoId=10,  photoType=1,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10151,  photoId=10,  photoType=1,  targetTypeLangId="target_type_destruction"},
	{missionCode=10045,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10093,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10093,  photoId=20,  photoType=1,  targetTypeLangId="target_type_recovery"},
	{missionCode=10171,  photoId=10,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10171,  photoId=20,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10171,  photoId=30,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10171,  photoId=40,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10171,  photoId=50,  photoType=0,  targetTypeLangId="target_type_exclusion"},
	{missionCode=10260,  photoId=10,  photoType=1,  targetTypeLangId="target_type_recovery"},
  }
  local out_photoInfo=photoInfo
  for _,info in ipairs(this.photoInfos)do
	local overwrite
	for index, info_ in ipairs(photoInfos) do
		if info.missionCode==info_.missionCode 
			and info.photoId==info_.photoId 
			and info.photoType==info_.photoType then
			out_photoInfo[index].targetTypeLangId=info.targetTypeLangId
			overwrite=true
			break
		end
	end
	if not overwrite then
		table.insert(out_photoInfo,info)
	end
  end
  if IHH then
    IHH.UpdatePhotoInfo(out_photoInfo)
  end
end