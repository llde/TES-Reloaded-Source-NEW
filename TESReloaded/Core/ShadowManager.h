#pragma once

class ShadowManager // Never disposed
{ 

public:
	ShadowManager();

	TESObjectREFR*			GetRef(TESObjectREFR* Ref);
	TESObjectREFR*			GetRefO(TESObjectREFR* Ref);
	void					RenderObject(NiAVObject* Node, bool HasWater);
	void					Render(NiGeometry* Geo);
	void					RenderShadowMap();

	IDirect3DTexture9*		ShadowMapTexture;
	IDirect3DSurface9*		ShadowMapSurface;
	IDirect3DSurface9*		ShadowMapDepthSurface;
	ShaderRecord*			ShadowMapVertex;
	ShaderRecord*			ShadowMapPixel;
	IDirect3DVertexShader9* ShadowMapVertexShader;
	IDirect3DPixelShader9*  ShadowMapPixelShader;
	D3DVIEWPORT9			ShadowMapViewPort;
	float					ShadowMapRadius;
	float					ShadowMapZRange;
	NiVector4				BillboardRight;
	NiVector4				BillboardUp;
	IDirect3DTexture9*		OrthoMapTexture;
	IDirect3DSurface9*		OrthoMapSurface;
	IDirect3DSurface9*		OrthoMapDepthSurface;
	D3DVIEWPORT9			OrthoMapViewPort;
};

void CreateShadowsHook();