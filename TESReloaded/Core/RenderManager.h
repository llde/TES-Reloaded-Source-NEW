#pragma once

class NiD3DVertexShaderEx : public NiD3DVertexShader
{

public:
	ShaderRecord*			ShaderProg;
	IDirect3DVertexShader9*	ShaderHandleBackup;
	char*					ShaderName;

};

class NiD3DPixelShaderEx : public NiD3DPixelShader
{

public:
	ShaderRecord*			ShaderProg;
	IDirect3DPixelShader9*	ShaderHandleBackup;
	char*					ShaderName;

};

class RenderManager: public NiDX9Renderer
{

public:

	void				Initialize();
	void				ResolveDepthBuffer();
	void				GetSceneCameraData();
	void				SetupSceneCamera();
	void				SetSceneGraph();

	D3DXVECTOR4			CameraForward;
	D3DXVECTOR4			CameraPosition;
	IDirect3DSurface9*	BackBuffer;
	IDirect3DSurface9*	DepthSurface;
	IDirect3DTexture9*	DepthTexture;
	IDirect3DTexture9*	DepthTextureINTZ;
	RECT				SaveGameScreenShotRECT;
	bool				IsSaveGameScreenShot;
	bool				FirstPersonView;
	bool				RESZ;
	
};