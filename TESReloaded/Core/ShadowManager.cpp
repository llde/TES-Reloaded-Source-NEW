#if defined(NEWVEGAS)
#define RenderStateArgs 0, 0
#define RefHasNode Ref->renderData && Ref->renderData->niNode
#define RefNode Ref->renderData->niNode
#define PlayerNode Player->renderData->niNode
#define GeoProperty Geo->propertyState.prop
#define kRockParams 0x01200658
#define kRustleParams 0x01200668
#define kWindMatrixes 0x01200688
static const UInt32 kRenderShadowMapHook = 0x00870C39;
static const UInt32 kRenderShadowMapReturn = 0x00870C41;
static const UInt32 kLeavesNodeName = 0x0066A115;
static const UInt32 kLeavesNodeNameReturn = 0x0066A11E;
static const void* VFTNiNode = (void*)0x0109B5AC;
static const void* VFTBSFadeNode = (void*)0x010A8F90;
static const void* VFTBSFaceGenNiNode = (void*)0x010660DC;
static const void* VFTBSTreeNode = (void*)0x010668E4;
static const void* VFTNiTriShape = (void*)0x0109D454;
static const void* VFTNiTriStrips = (void*)0x0109CD44;
static const float ShadowMapObjectMinBound = 0.0f;
#elif defined(OBLIVION)
#define RenderStateArgs 0
#define RefHasNode Ref->niNode
#define RefNode Ref->niNode
#define PlayerNode Player->niNode
#define GeoProperty Geo->propertyState->prop
#define kRockParams 0x00B46778
#define kRustleParams 0x00B46788
#define kWindMatrixes 0x00B467B8
static const UInt32 kRenderShadowMapHook = 0x0040C919;
static const UInt32 kRenderShadowMapReturn = 0x0040C920;
static const void* VFTNiNode = (void*)0x00A7E38C;
static const void* VFTBSFadeNode = (void*)0x00A3F944;
static const void* VFTBSFaceGenNiNode = (void*)0x00A64F5C;
static const void* VFTBSTreeNode = (void*)0x00A65854;
static const void* VFTNiTriShape = (void*)0x00A7ED5C;
static const void* VFTNiTriStrips = (void*)0x00A7F27C;
static const float ShadowMapObjectMinBound = 10.0f;
#endif
#define OrthoMapSize 256
#define OrthoMapRadius 2048.0f
#define OrthoMapZRange 4096.0f

ShadowManager::ShadowManager() {
	
	Logger::Log("Starting the shadows manager...");
	TheShadowManager = this;
	
	IDirect3DDevice9* Device = TheRenderManager->device;
	const DWORD ShadowMapSize = TheSettingManager->SettingsMain.ShadowMode.ShadowMapSize;

	ShadowMapTexture = NULL,
	ShadowMapSurface = NULL;
	ShadowMapDepthSurface = NULL;
	OrthoMapTexture = NULL,
	OrthoMapSurface = NULL;
	OrthoMapDepthSurface = NULL;
	ShadowMapRadius = TheSettingManager->SettingsMain.ShadowMode.ShadowMapRadius;
	ShadowMapZRange = TheSettingManager->SettingsMain.ShadowMode.ShadowMapZRange;
	ShadowMapVertex = new ShaderRecord();
	if (ShadowMapVertex->LoadShader("ShadowMap.vso")) {
		Device->CreateVertexShader((const DWORD*)ShadowMapVertex->Function, &ShadowMapVertexShader);
	}
	else {
		delete ShadowMapVertex;
		ShadowMapVertex = NULL;
	}
	ShadowMapPixel = new ShaderRecord();
	if (ShadowMapPixel->LoadShader("ShadowMap.pso")) {
		Device->CreatePixelShader((const DWORD*)ShadowMapPixel->Function, &ShadowMapPixelShader);
	}
	else {
		delete ShadowMapPixel;
		ShadowMapPixel = NULL;
	}
	Device->CreateTexture(ShadowMapSize, ShadowMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &ShadowMapTexture, NULL);
	Device->CreateDepthStencilSurface(ShadowMapSize, ShadowMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &ShadowMapDepthSurface, NULL);
	ShadowMapTexture->GetSurfaceLevel(0, &ShadowMapSurface);
	ShadowMapViewPort = { 0, 0, ShadowMapSize, ShadowMapSize, 0.0f, 1.0f };
	TheShaderManager->ShaderConst.Shadow_Data.w = ShadowMapSize;

	Device->CreateTexture(OrthoMapSize, OrthoMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &OrthoMapTexture, NULL);
	Device->CreateDepthStencilSurface(OrthoMapSize, OrthoMapSize, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &OrthoMapDepthSurface, NULL);
	OrthoMapTexture->GetSurfaceLevel(0, &OrthoMapSurface);
	OrthoMapViewPort = { 0, 0, OrthoMapSize, OrthoMapSize, 0.0f, 1.0f };

}

void CreateD3DMatrix(D3DMATRIX* Matrix, NiTransform* Transform) {

	NiMatrix33* Rot = &Transform->rot;
	NiPoint3* Pos = &Transform->pos;
	float Scale = Transform->scale;

	Matrix->_11 = Rot->data[0][0] * Scale;
	Matrix->_12 = Rot->data[1][0] * Scale;
	Matrix->_13 = Rot->data[2][0] * Scale;
	Matrix->_14 = 0.0f;
	Matrix->_21 = Rot->data[0][1] * Scale;
	Matrix->_22 = Rot->data[1][1] * Scale;
	Matrix->_23 = Rot->data[2][1] * Scale;
	Matrix->_24 = 0.0f;
	Matrix->_31 = Rot->data[0][2] * Scale;
	Matrix->_32 = Rot->data[1][2] * Scale;
	Matrix->_33 = Rot->data[2][2] * Scale;
	Matrix->_34 = 0.0f;
	Matrix->_41 = Pos->x - TheRenderManager->CameraPosition.x;
	Matrix->_42 = Pos->y - TheRenderManager->CameraPosition.y;
	Matrix->_43 = Pos->z - TheRenderManager->CameraPosition.z;
	Matrix->_44 = 1.0f;

}

TESObjectREFR* ShadowManager::GetRef(TESObjectREFR* Ref) {
	
	SettingsMainStruct::ShadowModeStruct* ShadowMode = &TheSettingManager->SettingsMain.ShadowMode;
	TESObjectREFR* r = NULL;

	if (Ref && RefHasNode) {
		UInt8 TypeID = Ref->baseForm->typeID;
		if ((TypeID == TESForm::FormType::kFormType_Activator && ShadowMode->Activators) ||
			(TypeID == TESForm::FormType::kFormType_Door && ShadowMode->Doors) ||
			(TypeID == TESForm::FormType::kFormType_Stat && ShadowMode->Statics) ||
			(TypeID == TESForm::FormType::kFormType_Tree && ShadowMode->Trees) ||
			((TypeID == TESForm::FormType::kFormType_NPC || TypeID == TESForm::FormType::kFormType_Creature) && ShadowMode->Actors))
			r = Ref;
	}
	return r;

}

TESObjectREFR* ShadowManager::GetRefO(TESObjectREFR* Ref) {

	TESObjectREFR* r = NULL;

	if (Ref && RefHasNode) {
		UInt8 TypeID = Ref->baseForm->typeID;
		if (TypeID == TESForm::FormType::kFormType_Stat) r = Ref;
	}
	return r;

}

void ShadowManager::RenderObject(NiAVObject* Object, bool HasWater) {

	if (Object && Object->m_kWorldBound.radius >= ShadowMapObjectMinBound) {
		if (*(void**)Object == VFTNiNode || *(void**)Object == VFTBSFadeNode || *(void**)Object == VFTBSFaceGenNiNode || *(void**)Object == VFTBSTreeNode) {
			NiNode* Node = (NiNode*)Object;
			for (int i = 0; i < Node->m_children.numObjs; i++) {
				RenderObject(Node->m_children.data[i], HasWater);
			}
		}
		else if (*(void**)Object == VFTNiTriShape || *(void**)Object == VFTNiTriStrips) {
			NiGeometry* Geo = (NiGeometry*)Object;
			if (Geo->shader) {
				if (!HasWater || (HasWater && Geo->m_worldTransform.pos.z > TheShaderManager->ShaderConst.Water_waterSettings.x)) {
					NiGeometryBufferData* GeoData = Geo->geomData->BuffData;
					if (GeoData) {
						Render(Geo);
					}
					else if (Geo->skinInstance && Geo->skinInstance->SkinPartition && Geo->skinInstance->SkinPartition->Partitions) {
						GeoData = Geo->skinInstance->SkinPartition->Partitions[0].BuffData;
						if (GeoData) Render(Geo);
					}
				}
			}
		}
	}

}

void ShadowManager::Render(NiGeometry* Geo) {
	
	IDirect3DDevice9* Device = TheRenderManager->device;
	NiDX9RenderState* RenderState = TheRenderManager->renderState;
	int StartIndex = 0;
	int PrimitiveCount = 0;
	int StartRegister = 9;
	NiGeometryData* ModelData = Geo->geomData;
	NiGeometryBufferData* GeoData = ModelData->BuffData;
	NiSkinInstance* SkinInstance = Geo->skinInstance;
	NiD3DShaderDeclaration* ShaderDeclaration = Geo->shader->ShaderDeclaration;
	
	if (GeoData) {
		TheShaderManager->ShaderConst.Shadow_Data.x = 0.0f;
		CreateD3DMatrix(&TheShaderManager->ShaderConst.ShadowWorld, &Geo->m_worldTransform);
		if (Geo->m_parent->m_pcName && !memcmp(Geo->m_parent->m_pcName, "Leaves", 6)) {
			NiVector4* RockParams = (NiVector4*)kRockParams;
			NiVector4* RustleParams = (NiVector4*)kRustleParams;
			NiVector4* WindMatrixes = (NiVector4*)kWindMatrixes;
			TheShaderManager->ShaderConst.Shadow_Data.x = 2.0f;
			SpeedTreeLeafShaderProperty* STProp = (SpeedTreeLeafShaderProperty*)GeoProperty[NiProperty::kType_RendSpec];
			BSTreeNode* Node = (BSTreeNode*)Geo->m_parent->m_parent;
			NiDX9SourceTextureData* Texture = (NiDX9SourceTextureData*)Node->TreeModel->LeavesTexture->rendererData;
			Device->SetVertexShaderConstantF(63, (float*)&BillboardRight, 1);
			Device->SetVertexShaderConstantF(64, (float*)&BillboardUp, 1);
			Device->SetVertexShaderConstantF(65, (float*)RockParams, 1);
			Device->SetVertexShaderConstantF(66, (float*)RustleParams, 1);
			Device->SetVertexShaderConstantF(67, (float*)WindMatrixes, 16);
			Device->SetVertexShaderConstantF(83, STProp->leafData->leafBase, 48);
			RenderState->SetTexture(0, Texture->dTexture);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP, false);
			RenderState->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT, false);
			RenderState->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT, false);
		}
		TheRenderManager->PackGeometryBuffer(GeoData, ModelData, SkinInstance, ShaderDeclaration);
		for (int i = 0; i < GeoData->StreamCount; i++) {
			Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
		}
		Device->SetIndices(GeoData->IB);
		if (GeoData->FVF)
			Device->SetFVF(GeoData->FVF);
		else
			Device->SetVertexDeclaration(GeoData->VertexDeclaration);
		ShadowMapVertex->SetCT();
		ShadowMapPixel->SetCT();
		for (int i = 0; i < GeoData->NumArrays; i++) {
			if (GeoData->ArrayLengths)
				PrimitiveCount = GeoData->ArrayLengths[i] - 2;
			else
				PrimitiveCount = GeoData->TriCount;
			Device->DrawIndexedPrimitive(GeoData->PrimitiveType, GeoData->BaseVertexIndex, 0, GeoData->VertCount, StartIndex, PrimitiveCount);
			StartIndex += PrimitiveCount + 2;
		}
	}
	else {
		TheShaderManager->ShaderConst.Shadow_Data.x = 1.0f;
		NiSkinPartition* SkinPartition = SkinInstance->SkinPartition;
		D3DPRIMITIVETYPE PrimitiveType = (SkinPartition->Partitions[0].Strips == 0) ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP;
		TheRenderManager->CalculateBoneMatrixes(SkinInstance, &Geo->m_worldTransform);
		if (SkinInstance->SkinToWorldWorldToSkin) memcpy(&TheShaderManager->ShaderConst.ShadowWorld, SkinInstance->SkinToWorldWorldToSkin, 0x40);
		for (int p = 0; p < SkinPartition->PartitionsCount; p++) {
			StartIndex = 0;
			StartRegister = 9;
			NiSkinPartition::Partition* Partition = &SkinPartition->Partitions[p];
			for (int i = 0; i < Partition->Bones; i++) {
				UInt16 NewIndex = (Partition->pBones == NULL) ? i : Partition->pBones[i];
				Device->SetVertexShaderConstantF(StartRegister, ((float*)SkinInstance->BoneMatrixes) + (NewIndex * 3 * 4), 3);
				StartRegister += 3;
			}
			GeoData = Partition->BuffData;
			TheRenderManager->PackSkinnedGeometryBuffer(GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration);
			for (int i = 0; i < GeoData->StreamCount; i++) {
				Device->SetStreamSource(i, GeoData->VBChip[i]->VB, 0, GeoData->VertexStride[i]);
			}
			Device->SetIndices(GeoData->IB);
			if (GeoData->FVF)
				Device->SetFVF(GeoData->FVF);
			else
				Device->SetVertexDeclaration(GeoData->VertexDeclaration);
			ShadowMapVertex->SetCT();
			ShadowMapPixel->SetCT();
			for (int i = 0; i < GeoData->NumArrays; i++) {
				if (GeoData->ArrayLengths)
					PrimitiveCount = GeoData->ArrayLengths[i] - 2;
				else
					PrimitiveCount = GeoData->TriCount;
				Device->DrawIndexedPrimitive(PrimitiveType, GeoData->BaseVertexIndex, 0, Partition->Vertices, StartIndex, PrimitiveCount);
				StartIndex += PrimitiveCount + 2;
			}
		}
	}

}

void ShadowManager::RenderShadowMap() {
#if defined(OBLIVION)
	// This part "creates" a fake canopy map only one time to avoid random canopy shadows if i forgot to replace a shader.
	// By now i cannot disable the canopy map pass in Oblivion.ini otherwise the game changes the shaders used for the rendering.
	NiRenderedTexture* CanopyMap = *(NiRenderedTexture**)0x00B4310C;
	if (!CanopyMap) {
		NiRenderedTexture* (__cdecl * CreateNiRenderedTexture)(UInt32, UInt32, NiRenderer*, NiTexture::FormatPrefs*) = (NiRenderedTexture* (__cdecl *)(UInt32, UInt32, NiRenderer*, NiTexture::FormatPrefs*))0x0072A9B0;
		void (__cdecl * SetTextureCanopyMap)(NiRenderedTexture*) = (void (__cdecl *)(NiRenderedTexture*))0x00441850;
		NiTexture::FormatPrefs FP = { NiRenderedTexture::kPixelLayout_Raw32BPP, NiRenderedTexture::kAlpha_Smooth, NiRenderedTexture::kMipMap_Default };
		SetTextureCanopyMap(CreateNiRenderedTexture(1, 1, TheRenderManager, &FP));
	}
#endif
	if (TheShaderManager->ShaderConst.currentWorldSpace) {
		if (ShadowMapVertex && ShadowMapPixel) {
			IDirect3DSurface9* DepthSurface = NULL;
			IDirect3DDevice9* Device = TheRenderManager->device;
			NiDX9RenderState* RenderState = TheRenderManager->renderState;
			D3DXVECTOR4* SunDir = &TheShaderManager->ShaderConst.SunDir;
			D3DXVECTOR4 OrthoDir = D3DXVECTOR3(0.05f, 0.05f, 1.0f);
			D3DXMATRIX View;
			D3DXMATRIX Proj;
			D3DXMATRIX CameraInvProj;
			D3DXVECTOR3 Eye, At;
			D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

			Device->GetDepthStencilSurface(&DepthSurface);

			TheRenderManager->SetupSceneCamera();
			At.x = PlayerNode->m_worldTransform.pos.x - TheRenderManager->CameraPosition.x;
			At.y = PlayerNode->m_worldTransform.pos.y - TheRenderManager->CameraPosition.y;
			At.z = PlayerNode->m_worldTransform.pos.z - TheRenderManager->CameraPosition.z;

			Eye.x = At.x - ShadowMapZRange * SunDir->x * -1;
			Eye.y = At.y - ShadowMapZRange * SunDir->y * -1;
			Eye.z = At.z - ShadowMapZRange * SunDir->z * -1;
			D3DXMatrixLookAtRH(&View, &Eye, &At, &Up);
			D3DXMatrixOrthoRH(&Proj, 2.0f * ShadowMapRadius, (1 + SunDir->z) * ShadowMapRadius, 0.0f, 2.0f * ShadowMapZRange);
			TheShaderManager->ShaderConst.ShadowViewProj = View * Proj;
			D3DXMatrixInverse(&CameraInvProj, NULL, (D3DXMATRIX*)&TheRenderManager->projMatrix);
			TheShaderManager->ShaderConst.ShadowCameraToLight = CameraInvProj * TheRenderManager->invViewMatrix * TheShaderManager->ShaderConst.ShadowViewProj;
			BillboardRight = { View._11, View._21, View._31, 0.0f };
			BillboardUp = { View._12, View._22, View._32, 0.0f };
			Device->SetRenderTarget(0, ShadowMapSurface);
			Device->SetDepthStencilSurface(ShadowMapDepthSurface);
			Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
			if (TheSettingManager->SettingsMain.ShadowMode.Enabled && SunDir->z > 0.0f) {
				Device->BeginScene();
				RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ZWRITEENABLE, 1, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
				Device->SetViewport(&ShadowMapViewPort);
				Device->SetVertexShader(ShadowMapVertexShader);
				Device->SetPixelShader(ShadowMapPixelShader);
				for (int x = 0; x < *SettingGridsToLoad; x++) {
					for (int y = 0; y < *SettingGridsToLoad; y++) {
						if (TESObjectCELL* Cell = Tes->gridCellArray->GetCell(x, y)) {
							TList<TESObjectREFR>::TNode* Entry = &Cell->objectList.First;
							while (Entry) {
								if (TESObjectREFR* Ref = GetRef(Entry->item)) RenderObject(RefNode, TheShaderManager->ShaderConst.HasWater);
								Entry = Entry->next;
							}
						}
					}
				}
				Device->EndScene();
			}

			Eye.x = At.x - OrthoMapZRange * OrthoDir.x * -1;
			Eye.y = At.y - OrthoMapZRange * OrthoDir.y * -1;
			Eye.z = At.z - OrthoMapZRange * OrthoDir.z * -1;
			D3DXMatrixLookAtRH(&View, &Eye, &At, &Up);
			D3DXMatrixOrthoRH(&Proj, 2.0f * OrthoMapRadius, (1 + OrthoDir.z) * OrthoMapRadius, 0.0f, 2.0f * OrthoMapZRange);
			TheShaderManager->ShaderConst.ShadowViewProj = View * Proj;
			D3DXMatrixInverse(&CameraInvProj, NULL, (D3DXMATRIX*)&TheRenderManager->projMatrix);
			TheShaderManager->ShaderConst.OrthoCameraToRain = CameraInvProj * TheRenderManager->invViewMatrix * TheShaderManager->ShaderConst.ShadowViewProj;
			BillboardRight = { View._11, View._21, View._31, 0.0f };
			BillboardUp = { View._12, View._22, View._32, 0.0f };
			Device->SetRenderTarget(0, OrthoMapSurface);
			Device->SetDepthStencilSurface(OrthoMapDepthSurface);
			Device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 0.25f, 0.25f, 0.55f), 1.0f, 0L);
			if (TheShaderManager->ShaderConst.Rain_Data.x) {
				Device->BeginScene();
				RenderState->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ZWRITEENABLE, 1, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE, RenderStateArgs);
				RenderState->SetRenderState(D3DRS_ALPHABLENDENABLE, 0, RenderStateArgs);
				Device->SetViewport(&OrthoMapViewPort);
				Device->SetVertexShader(ShadowMapVertexShader);
				Device->SetPixelShader(ShadowMapPixelShader);
				if (TESObjectCELL* Cell = Player->parentCell) {
					TList<TESObjectREFR>::TNode* Entry = &Cell->objectList.First;
					while (Entry) {
						if (TESObjectREFR* Ref = GetRefO(Entry->item)) RenderObject(RefNode, TheShaderManager->ShaderConst.HasWater);
						Entry = Entry->next;
					}
				}
				Device->EndScene();
			}

			TheShaderManager->ShaderConst.Shadow_Data.y = TheSettingManager->SettingsMain.ShadowMode.Quality;
			TheShaderManager->ShaderConst.Shadow_Data.z = TheSettingManager->SettingsMain.ShadowMode.Darkness;
			if (SunDir->z < 0.1f) {
				if (TheShaderManager->ShaderConst.Shadow_Data.z == 0.0f) TheShaderManager->ShaderConst.Shadow_Data.z = 0.1f;
				TheShaderManager->ShaderConst.Shadow_Data.z += log(SunDir->z) / -10;
				if (TheShaderManager->ShaderConst.Shadow_Data.z > 1.0f) TheShaderManager->ShaderConst.Shadow_Data.z = 1.0f;
			}

			Device->SetDepthStencilSurface(DepthSurface);
		}
	}
	else {
		Global->RenderShadowMaps();
	}
	
}

static __declspec(naked) void RenderShadowMapHook() {

	__asm
	{
		pushad
		mov		ecx, TheShadowManager
		call	ShadowManager::RenderShadowMap
		popad
		jmp		kRenderShadowMapReturn
	}

}

#if defined(NEWVEGAS)
void LeavesNodeName(BSTreeNode* TreeNode) {
	
	TreeNode->m_children.data[1]->SetName("Leaves");

}

static __declspec(naked) void LeavesNodeNameHook() {

	__asm
	{
		pushad
		push	eax 
		call	LeavesNodeName
		pop		eax
		popad
		jmp		kLeavesNodeNameReturn
	}

}
#endif

void CreateShadowsHook() {
	
	WriteRelJump(kRenderShadowMapHook,	(UInt32)RenderShadowMapHook);

#if defined(NEWVEGAS)
	WriteRelJump(kLeavesNodeName, (UInt32)LeavesNodeNameHook);
#elif defined(OBLIVION)
	// This part "disables" the canopy map pass but values are anyway passed to the shaders (they are not used when OR shadows).
	// By now i cannot disable the canopy map pass in Oblivion.ini otherwise the game changes the shaders used for the rendering.
	WriteRelJump(0x0040D637, 0x0040D655); //Avoid tree canopy shadows rendering
	WriteRelJump(0x004425F7, 0x00442621); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	WriteRelJump(0x004446FB, 0x00444723); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	WriteRelJump(0x00444CCF, 0x00444CF9); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
	WriteRelJump(0x0055F5C9, 0x0055F5ED); //Skip canopy map deinitialization (the game disposes/recreates the map every cell changed)
#endif
}