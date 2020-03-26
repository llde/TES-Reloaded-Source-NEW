#pragma once

class TESObjectREFR;

class NiNode;
class NiPick;
class NiTextKeyExtraData;
class NiFormArray;
class NiStringPalette;
class NiStream;
class NiTimeController;
class NiPropertyState;
class NiDynamicEffectState;
class NiProperty;
class NiFogProperty;
class NiAlphaProperty;
class NiMaterialProperty;
class NiTexturingProperty;
class NiCullingProcess;
class NiDynamicEffect;
class NiControllerManager;
class NiVisibleArray;
class NiAdditionalGeometryData;
class NiGeometryGroup;
class NiRenderedCubeMap;
class NiTexture;
class NiTriShape;
class NiTriStrips;
class NiPixelData;
class NiParticles;
class NiLines;
class NiGeometryGroupManager;
class NiScreenElements;
class NiSourceCubeMap;
class NiRenderer;
class Ni2DBuffer;
class NiD3DRenderStateGroup;
class NiD3DShaderProgram;
class NiD3DShader;
class NiDX9LightManager;
class NiDX9VertexBufferManager;
class NiDX9ShaderConstantManager;
class NiDX9IndexBufferManager;
class NiDX9TextureManager;
class NiDX9RenderedTextureData;
class NiDX9RenderedCubeMapData;
class NiDX9DynamicTextureData;
class NiDX9AdapterDesc;
class NiDX9DeviceDesc;
class NiDX9Renderer;
class NiDX9RenderState;
class NiDX92DBufferData;

struct NiRTTI {
	const char* name;
	NiRTTI*		parent;
};
assert(sizeof(NiRTTI) == 0x008);

class NiPoint3 {
public:
	float x;
	float y;
	float z;
};
assert(sizeof(NiPoint3) == 0x00C);

class NiVector4 {
public:
	float x;
	float y;
	float z;
	float w;
};
assert(sizeof(NiVector4) == 0x010);

class NiMatrix33 {
public:
	float data[3][3];
};
assert(sizeof(NiMatrix33) == 0x024);

class NiTransform {
public:
	NiMatrix33	rot;		// 00
	NiPoint3	pos;		// 24
	float		scale;		// 30
};
assert(sizeof(NiTransform) == 0x034);

class NiSphere {
public:
	float x;
	float y;
	float z;
	float radius;
};
assert(sizeof(NiSphere) == 0x010);

class NiFrustum {
public:
	float	Left;		// 00
	float	Right;		// 04
	float	Top;		// 08
	float	Bottom;		// 0C
	float	Near;		// 10
	float	Far;		// 14
	UInt8	Ortho;		// 18
	UInt8	pad18[3];
};
assert(sizeof(NiFrustum) == 0x01C);

class NiViewport {
public:
	float	l;
	float	r;
	float	t;
	float	b;
};
assert(sizeof(NiViewport) == 0x010);

class NiColor {
public:
	float	r;
	float	g;
	float	b;
};
assert(sizeof(NiColor) == 0x00C);

class NiColorAlpha {
public:
	float	r;
	float	g;
	float	b;
	float	a;
};
assert(sizeof(NiColorAlpha) == 0x010);

template <typename T>
class NiTList {
public:
	struct Node {
		Node* next;
		Node* prev;
		T* data;
	};

	virtual void	Destructor(bool free);
	virtual Node*	AllocateNode();
	virtual void	FreeNode(Node* node);

	Node*	start;		// 004
	Node*	end;		// 008
	UInt32	numItems;	// 00C
};
assert(sizeof(NiTList<void>) == 0x010);

template <typename TKey, typename TData>
class NiTMap {
public:
	struct Entry {
		Entry*	next;
		TKey	key;
		TData*	data;
	};

	virtual UInt32	CalculateBucket(UInt32 key);
	virtual bool	CompareKey(UInt32 lhs, UInt32 rhs);
	virtual void	Fn_03(UInt32 arg0, UInt32 arg1, UInt32 arg2);	// assign to entry
	virtual void	Fn_04(UInt32 arg);
	virtual void	Fn_05();	// locked operations
	virtual void	Fn_06();	// locked operations

	UInt32			m_numBuckets;	// 4
	Entry**			m_buckets;		// 8
	UInt32			m_numItems;		// C
};
assert(sizeof(NiTMap<void, void>) == 0x010);

template <typename T>
class NiTArray {
public:
	void**	_vtbl;			// 00
	T*		data;			// 04
	UInt16	capacity;		// 08 - init'd to size of preallocation
	UInt16	firstFreeEntry;	// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16	numObjs;		// 0C - init'd to 0
	UInt16	growSize;		// 0E - init'd to size of preallocation
};
assert(sizeof(NiTArray<void>) == 0x010);

template <typename T>
class NiTLargeArray {
public:
	void**	_vtbl;			// 00
	T*		data;			// 04
	UInt32	capacity;		// 08 - init'd to size of preallocation
	UInt32	firstFreeEntry;	// 0C - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt32	numObjs;		// 10 - init'd to 0
	UInt32	growSize;		// 14 - init'd to size of preallocation
};
assert(sizeof(NiTLargeArray<void>) == 0x018);

class NiPixelFormat {
public:
	enum Format {
		kFormat_RGB = 0,
		kFormat_RGBA,
		kFormat_PAL,
		kFormat_PALALPHA,
		kFormat_DXT1,
		kFormat_DXT3,
		kFormat_DXT5,
		kFormat_RGB24NONINTERLEAVED,
		kFormat_BUMP,
		kFormat_BUMPLUMA,
		kFormat_RENDERERSPECIFIC,
		kFormat_ONE_CHANNEL,
		kFormat_TWO_CHANNEL,
		kFormat_THREE_CHANNEL,
		kFormat_FOUR_CHANNEL,
		kFormat_DEPTH_STENCIL,
		kFormat_UNKNOWN,
		kFormat_MAX
	};

	enum Component {
		kComp_RED = 0,
		kComp_GREEN,
		kComp_BLUE,
		kComp_ALPHA,
		kComp_COMPRESSED,
		kComp_OFFSET_U,
		kComp_OFFSET_V,
		kComp_OFFSET_W,
		kComp_OFFSET_Q,
		kComp_LUMA,
		kComp_HEIGHT,
		kComp_VECTOR_X,
		kComp_VECTOR_Y,
		kComp_VECTOR_Z,
		kComp_PADDING,
		kComp_INTENSITY,
		kComp_INDEX,
		kComp_DEPTH,
		kComp_STENCIL,
		kComp_EMPTY,
		kComp_MAX
	};

	enum Representation {
		kRep_NORM_INT = 0,
		kRep_HALF,
		kRep_FLOAT,
		kRep_INDEX,
		kRep_COMPRESSED,
		kRep_UNKNOWN,
		kRep_INT,
		kRep_MAX
	};

	enum Tiling {
		kTile_NONE = 0,
		kTile_XENON,
		kTile_MAX
	};

	struct NiComponentSpec {
		Component		eComponent;			// 0
		Representation	eRepresentation;	// 4
		UInt8			BitsPerComponent;	// 8
		UInt8			Signed;				// 9
		UInt8			padA[2];			// A
	};

	UInt8			BitsPerPixel;	// 00
	UInt8			SRGBSpace;		// 01
	UInt8			pad02[2];
	Format			eFormat;		// 04
	Tiling			eTiling;		// 08
	UInt32			RendererHint;	// 0C
	UInt32			ExtraData;		// 10
	NiComponentSpec	Components[4];	// 14
};
assert(sizeof(NiPixelFormat) == 0x044);

#if defined(NEWVEGAS)
class NiRefObject {
public:
	virtual void		Destructor(bool freeThis);	// 00
	virtual void		Free(void);					// 01

	UInt32				m_uiRefCount;	// 004
};
assert(sizeof(NiRefObject) == 0x008);

class NiObject : public NiRefObject {
public:
	virtual NiRTTI*		GetType();		// 02
	virtual NiNode*		GetAsNiNode();	// 03 
	virtual UInt32		Unk_04();		// 04
	virtual UInt32		Unk_05();		// 05
	virtual UInt32		Unk_06();		// 06
	virtual UInt32		Unk_07();		// 07
	virtual UInt32		Unk_08();		// 08
	virtual UInt32		Unk_09();		// 09
	virtual UInt32		Unk_0A();		// 0A
	virtual UInt32		Unk_0B();		// 0B
	virtual UInt32		Unk_0C();		// 0C
	virtual UInt32		Unk_0D();		// 0D
	virtual UInt32		Unk_0E();		// 0E
	virtual UInt32		Unk_0F();		// 0F
	virtual UInt32		Unk_10();		// 10
	virtual UInt32		Unk_11();		// 11
	virtual NiObject*	Copy();			// 12
	virtual void		Load(NiStream* stream);
	virtual void		PostLoad(NiStream* stream);
	virtual void		FindNodes(NiStream* stream);
	virtual void		Save(NiStream* stream);
	virtual bool		Compare(NiObject* obj);
	virtual void		DumpAttributes(NiTArray <char*>* dst);
	virtual void		DumpChildAttributes(NiTArray <char*>* dst);
	virtual void		Unk_1A();
	virtual void		Unk_1B(UInt32 arg);
	virtual void		Unk_1C();
	virtual void		GetType2();	
	virtual void		Unk_1E(UInt32 arg);
	virtual void		Unk_1F();
	virtual void		Unk_20();
	virtual void		Unk_21();
	virtual void		Unk_22();
};
assert(sizeof(NiObject) == 0x008);

class NiExtraData : public NiObject {
public:
	virtual	bool	Unk_23();
	virtual bool	Unk_24();

	char*	m_pcName;	// 08
};
assert(sizeof(NiExtraData) == 0x00C);

class NiObjectNET : public NiObject {
public:
	void				SetName(const char* Name) { char* (__cdecl* CreateString)(const char*) = (char* (__cdecl*)(const char*))0x00A5B690; char* S = CreateString(Name); ThisCall(0x00A5B950, this, &S); }

	const char*			m_pcName;						// 008
	NiTimeController*	m_controller;					// 00C
	NiExtraData**		m_extraDataList;				// 010
	UInt16				m_extraDataListLen;				// 014
	UInt16				m_extraDataListCapacity;		// 016
};
assert(sizeof(NiObjectNET) == 0x018);

class NiAVObject : public NiObjectNET {
public:
	virtual void			UpdateControllers(float fTime);
	virtual void			Unk_24();
	virtual void			Unk_25();
	virtual NiAVObject*		GetObjectByName(const char* Name);
	virtual void*			Unk_27();
	virtual void			UpdateDownwardPass(float fTime, bool bUpdateControllers);
	virtual void			UpdateSelectedDownwardPass(float fTime);
	virtual void			UpdateRigidDownwardPass(float fTime);
	virtual void			UpdatePropertiesDownward(NiPropertyState* ParentState);
	virtual void			UpdateEffectsDownward(NiDynamicEffectState* ParentState);
	virtual void			UpdateTransformData();
	virtual void			UpdateTransformBound();
	virtual void			OnVisible(NiCullingProcess* CullingProcess);
	virtual void			Unk_30(void* arg);			// get NiMaterialProperty, pass to arg if found
	virtual void			Unk_31(void* arg);
	virtual void			Unk_32(void* arg);
	virtual void			Unk_33(void* arg);
	virtual void			Unk_34(void* arg);
	virtual void			Unk_35(void* arg);
	virtual void			Unk_36(void* arg);	// last is 036 verified

	enum {
		kFlag_AppCulled					= 1 << 0,	// originally named m_bAppCulled but they appear to have used bitfields
		kFlag_SelUpdate					= 1 << 1,
		kFlag_SelUpdateTransforms		= 1 << 2,
		kFlag_SelUpdatePropControllers	= 1 << 3,
		kFlag_SelUpdateRigid			= 1 << 4,
	};

	NiNode*					m_parent;				// 018
	UInt32					unk001C;				// 01C
	NiSphere				m_kWorldBound;			// 020
	UInt32					m_flags;				// 030
	NiTransform				m_localTransform;		// 034
	NiTransform				m_worldTransform;		// 068
};
assert(sizeof(NiAVObject) == 0x9C);

class NiNode : public NiAVObject {
public:
	virtual void		AddObject(NiAVObject* nChild, UInt8 FirstAvail); // Add child node
	virtual NiAVObject* RemoveObject(NiAVObject** RemovedChild, NiAVObject* nChild);
	virtual NiAVObject* RemoveObjectAt(NiAVObject** RemovedChild, UInt32 Index);
	virtual NiAVObject* SetObjectAt(NiAVObject** SetChild, UInt32 Index, NiAVObject* nChild);
	virtual void		ApplyTransform(const NiMatrix33& Mat, const NiPoint3& Trn, bool OnLeft);
	virtual bool		Unk_3B(void);
	virtual bool		Unk_3C(void);
	virtual bool		Unk_3D(void);
	virtual bool		Unk_3E(void);
	virtual bool		Unk_3F(void);

	NiTArray<NiAVObject*>	m_children;	// 09C
};
assert(sizeof(NiNode) == 0xAC);

class NiBillboardNode : public NiNode {
public:
	virtual void	Unk_40();

	UInt32			unkAC[2];		// AC
};
assert(sizeof(NiBillboardNode) == 0xB4);

class NiCamera : public NiAVObject {
public:
	float			WorldToCam[4][4];	// 94
	NiFrustum		Frustum;			// D4
	float			MinNearPlaneDist;	// F8
	float			MaxFarNearRatio;	// FC
	NiViewport		ViewPort;			// 100
	float			LODAdjust;			// 110
};
assert(sizeof(NiCamera) == 0x114);

class SceneGraph : public NiNode {
public:
	float			GetFarPlaneDistance() { return ThisCallF(0x00C52450, this); }
	void			SetCameraFOV(float FoV) { ThisCall(0x00C52020, this, FoV, 0 , NULL, 0); }

	NiCamera*		camera;					// AC
	UInt32			unkB0;					// B0
	void*			cullingProcess;			// B4 BSCullingProcess
	UInt8			IsMinFarPlaneDistance;	// B8 The farplane is set to 20480.0 when the flag is true. Probably used for interiors.
	UInt8			padB8[3];
	float			cameraFOV;				// BC
};
assert(sizeof(SceneGraph) == 0xC0);

class NiDynamicEffect : public NiAVObject {
public:
	UInt8			byte9C;			// 9C
	UInt8			byte9D;			// 9D
	UInt8			byte9E;			// 9E
	UInt8			byte9F;			// 9F
	UInt32			unkA0;			// A0
	UInt32			unkA4;			// A4
	UInt32			unkA8;			// A8
	UInt32			unkAC;			// AC
	UInt32			unkB0;			// B0
	UInt32			unkB4;			// B4
	UInt32			unkB8;			// B8
	UInt32			unkBC;			// BC
	UInt32			unkC0;			// C0
};
assert(sizeof(NiDynamicEffect) == 0xC4);

class NiLight : public NiDynamicEffect {
public:
	float			fadeValue;			// C4
	NiColor			ambientColor;		// C8
	NiColor			directionalColor;	// D4
};
assert(sizeof(NiLight) == 0xE0);

class NiPointLight : public NiLight {
public:
	float			radius;				// E0
	float			fltE4;				// E4
	float			fltE8;				// E8
	UInt32			unkEC;				// EC
	float			attenuation1;		// F0
	float			attenuation2;		// F4
	float			attenuation3;		// F8
};
assert(sizeof(NiPointLight) == 0xFC);

class NiDirectionalLight : public NiLight {
public:
	NiColor			fogColor;			// E0
	UInt32			unkEC;				// EC
	NiPoint3		direction;			// F0
};
assert(sizeof(NiDirectionalLight) == 0xFC);

class NiVBChip {
public:
	UInt32					Index;      // 00
	UInt32					Unk04;		// 04 union { NiVBBlock* m_pkBlock; NiVBDynamicSet* m_pkDynamicSet; };
	IDirect3DVertexBuffer9* VB;			// 08
	UInt32					Offset;		// 0C
	UInt32					LockFlags;	// 10
	UInt32					Size;		// 14
	NiVBChip*				Next;		// 18
	NiVBChip*				Prev;		// 1C
};
assert(sizeof(NiVBChip) == 0x020);

class NiGeometryBufferData {
public:
	virtual void		Destructor(bool freeThis);			// 00
	virtual void		Free();								// 01

	UInt32							Flags;					// 04
	NiGeometryGroup*				GeometryGroup;			// 08
	UInt32							FVF;					// 0C
	IDirect3DVertexDeclaration9*	VertexDeclaration;		// 10
	UInt32							unk10;					// 14
	UInt32							VertCount;				// 18
	UInt32							MaxVertCount;			// 1C
	UInt32							StreamCount;			// 20
	UInt32*							VertexStride;			// 24
	NiVBChip**						VBChip;					// 28
	UInt32							IndexCount;				// 2C
	UInt32							IBSize;					// 30
	IDirect3DIndexBuffer9*			IB;						// 34
	UInt32							BaseVertexIndex;		// 38
	D3DPRIMITIVETYPE				PrimitiveType;			// 3C
	UInt32							TriCount;				// 40
	UInt32							MaxTriCount;			// 44
	UInt32							NumArrays;				// 48
	UInt16*							ArrayLengths;			// 4C
	UInt16*							IndexArray;				// 50
};
assert(sizeof(NiGeometryBufferData) == 0x54);

class NiGeometryData : public NiObject {
public:
	enum Consistency {
		MUTABLE			 = 0x0000,
		STATIC			 = 0x4000,
		VOLATILE		 = 0x8000,
		CONSISTENCY_MASK = 0xF000,
	};

	UInt16						Vertices;			// 008
	UInt16						Unk00A;				// 00A
	UInt16						Unk00C;				// 00C
	UInt16						Unk00E;				// 00E
	UInt32						Unk010;				// 010
	UInt32						Unk014;				// 014
	UInt32						Unk018;				// 018
	UInt32						Unk01C;				// 01C
	NiPoint3*					Vertex;				// 020
	NiPoint3*					Normal;				// 024
	NiColorAlpha*				Color;				// 028
	UInt32						Texture;			// 02C NiPoint2*
	UInt32						Unk030;				// 030
	NiGeometryBufferData*		BuffData;			// 034
	UInt8						Unk038;				// 038
	UInt8						Unk039;				// 039
	UInt8						Unk03A;				// 03A
	UInt8						Unk03B;				// 03B
	UInt8						Unk03C;				// 03C
	UInt8						pad03C[3];
};
assert(sizeof(NiGeometryData) == 0x40);

class NiSkinPartition : public NiObject {
public:
	class Partition {
	public:
		void**					_vtbl;			// 00
		UInt16*					pBones;			// 04
		float*					Weights;		// 08
		UInt32					Unk04[4];		// 0C
		UInt16					Vertices;		// 1C
		UInt16					Triangles;		// 1E
		UInt16					Bones;			// 20
		UInt16					Strips;			// 22
		UInt16					BonesPerVertex; // 24
		UInt16					pad28;
		NiGeometryBufferData*	BuffData;		// 28
	};

	UInt32		PartitionsCount;		// 08
	Partition*	Partitions;				// 0C
};
assert(sizeof(NiSkinPartition) == 0x10);

class NiSkinData : public NiObject {
public:
	class BoneVertData {
	public:
		UInt16	Verts;		// 00
		float	Weight;		// 04
	};

	class BoneData {
	public:
		NiTransform		SkinToBone;		// 00
		NiPoint3		Center;			// 34
		float			Radius;			// 38
		BoneVertData*	BoneVertData;	// 3C
		UInt16			Verts;			// 40
		UInt16			pad44;
	};

	NiSkinPartition*	SkinPartition;		// 08
	NiTransform			RootParentToSkin;	// 0C
	BoneData*			BoneData;			// 40
	UInt32				Bones;				// 44

};
assert(sizeof(NiSkinData) == 0x48);

class NiSkinInstance : public NiObject {
public:
	NiSkinData*			SkinData;				// 08
	NiSkinPartition*	SkinPartition;			// 0C
	NiAVObject*			RootParent;				// 10
	NiAVObject**		BoneObjects;			// 14
	UInt32				FrameID;				// 18
	UInt32				Bones;					// 1C
	UInt32				BoneRegisters;			// 20
	UInt32				BoneSize;				// 24
	void*				BoneMatrixes;			// 28 Matrixes array for the bones D3DMATRIX
	void*				SkinToWorldWorldToSkin;	// 2C D3DMATRIX
	UInt32				Unk30;					// 30
};
assert(sizeof(NiSkinInstance) == 0x34);

class NiProperty : public NiObjectNET {
public:
	enum {
		kType_Alpha,
		kType_Dither,
		kType_Material,
		kType_RendSpec,
		kType_Stencil,
		kType_Texturing,
	};
};
assert(sizeof(NiProperty) == 0x18);

class NiPropertyState {
public:
	NiProperty* prop[6];
	// 0 00	NiAlphaProperty
	// 1 04	
	// 2 08	NiMaterialProperty
	// 3 0C	NiSpecificProperty
	// 4 10	NiStencilProperty
	// 5 14	NiTexturingProperty
};

class NiGeometry : public NiAVObject {
public:
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();

	NiPropertyState		propertyState;	// 9C
	UInt32				unkB4;			// B4
	NiGeometryData*		geomData;		// B8
	NiSkinInstance*		skinInstance;	// BC This seems to be a BSDismemberSkinInstance (old NiSkinInstance constructor is never used)
	NiD3DShader*		shader;			// C0
};
assert(sizeof(NiGeometry) == 0xC4);

class NiDX9TextureData : public NiObject {
public:
	NiTexture*				pTexture;		// 08
	UInt32					Unk0C;			// 0C
	UInt32					Unk10;			// 10
	NiPixelFormat			PixelFormat;	// 14
	UInt8					Unk58;			// 58
	UInt8					Unk59;			// 59
	UInt8					Unk5A;			// 5A
	UInt8					Unk5B;			// 5B
	UInt32					Unk5C;			// 5C
	NiDX9Renderer*			pRenderer;		// 60
	IDirect3DBaseTexture9*	dTexture;		// 64
	UInt32					Levels;			// 68
};
assert(sizeof(NiDX9TextureData) == 0x6C);

class NiDX9SourceTextureData : public NiDX9TextureData {
public:
	UInt8					ReplacementData;	// 6C
	UInt8					Mipmap;				// 6D
	UInt8					pad64[2];
	UInt32					FormattedSize;		// 70
	UInt32					Palette;			// 74 NiPalette
	UInt32					LevelsSkipped;		// 78
	UInt32					SourceRevID;		// 7C
	UInt32					PalRevID;			// 80
};
assert(sizeof(NiDX9SourceTextureData) == 0x84);

class NiTexture : public NiObjectNET {
public:
	virtual UInt32	GetWidth();
	virtual UInt32	GetHeight();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();

	enum PixelLayout {
		kPixelLayout_Palette8BPP = 0,
		kPixelLayout_Raw16BPP,
		kPixelLayout_Raw32BPP,
		kPixelLayout_Compressed,
		kPixelLayout_Bumpmap,
		kPixelLayout_Palette4BPP,
		kPixelLayout_Default,
	};

	enum AlphaFormat {
		kAlpha_None = 0,
		kAlpha_Binary,	// 1bpp
		kAlpha_Smooth,	// 8bpp
		kAlpha_Default,
	};

	enum MipMapFlag {
		kMipMap_Disabled = 0,
		kMipMap_Enabled,
		kMipMap_Default,
	};

	struct FormatPrefs {
		PixelLayout pixelLayout;
		AlphaFormat alphaFormat;
		MipMapFlag	mipmapFormat;
	};

	UInt32				pixelLayout;	// 018
	UInt32				alphaFormat;	// 01C
	UInt32				mipmapFormat;	// 020
	NiDX9TextureData*	rendererData;	// 024
	NiTexture*			nextTex;		// 028 - linked list updated in ctor/dtor
	NiTexture*			prevTex;		// 02C
};
assert(sizeof(NiTexture) == 0x30);

class NiSourceTexture : public NiTexture {
public:
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();

	char*			ddsPath1;		// 30
	char*			ddsPath2;		// 34
	UInt32			unk38;			// 38
	UInt32			unk3C;			// 3C
	UInt32			unk40;			// 40
	UInt32			unk44;			// 44
};
assert(sizeof(NiSourceTexture) == 0x48);

class NiRenderedTexture : public NiTexture {
public:
	virtual void* Unk_2C();

	void*	unk030;		// 030
	UInt32	pad034;		// 034
	UInt32	pad038;		// 038
	UInt32	pad03C;		// 03C
};
assert(sizeof(NiRenderedTexture) == 0x040);

class NiD3DTextureStage;
class NiD3DShaderConstantMap;

class NiD3DShaderDeclaration : public NiObject {
public:
	NiDX9Renderer*				Renderer;		// 008
	NiDX9VertexBufferManager*	BufferManager;	// 00C
	IDirect3DDevice9*			Device;			// 010
	UInt32						Unk014;			// 014
	UInt32						Unk018;			// 018
	UInt32						Unk01C;			// 01C
	UInt32						StreamCount;	// 020
	UInt32						Unk024;			// 024
	UInt32						Unk028;			// 028
};
assert(sizeof(NiD3DShaderDeclaration) == 0x02C);

class NiDX9ShaderDeclaration : public NiD3DShaderDeclaration {
public:
	UInt32		Unk02C;			// 02C
	UInt32		Unk030;			// 030
	UInt32		Unk034;			// 034
};
assert(sizeof(NiDX9ShaderDeclaration) == 0x038);

class NiD3DShaderProgram : public NiRefObject {
public:
	enum ProgramType {
		PROGRAM_VERTEX = 0,
		PROGRAM_PIXEL,
		PROGRAM_GEOMETRY,
		PROGRAM_MAX
	};

	ProgramType			eProgramType;		// 08
	char*				Name;				// 0C
	char*				ShaderProgramName;	// 10
	UInt32				CodeSize;			// 14
	void*				Unk018;				// 18
	void*				Unk01C;				// 1C
	IDirect3DDevice9*	Device;				// 20
	NiDX9Renderer*		Renderer;			// 24
	NiDX9RenderState*	RenderState;		// 28
};
assert(sizeof(NiD3DShaderProgram) == 0x2C);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	UInt8							SoftwareVP;		// 2C
	UInt8							pad[3];			// 2D
	UInt32							Usage;			// 30
	IDirect3DVertexShader9*			ShaderHandle;	// 34
	IDirect3DVertexDeclaration9*	Declaration;	// 38
};
assert(sizeof(NiD3DVertexShader) == 0x3C);

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	IDirect3DPixelShader9* ShaderHandle;	// 2C
};
assert(sizeof(NiD3DPixelShader) == 0x30);

class NiD3DPass {
public:
	void**							_vtbl;						// 00
	char							Name[16];					// 04
	UInt32							CurrentStage;				// 14
	UInt32							StageCount;					// 18
	UInt32							TexturesPerPass;			// 1C
	NiTArray<NiD3DTextureStage*>	Stages;						// 20
	NiD3DRenderStateGroup*			RenderStateGroup;			// 30
	NiD3DShaderConstantMap*			PixelConstantMap;			// 34
	char*							PixelShaderProgramFile;		// 38
	char*							PixelShaderEntryPoint;		// 3C
	char*							PixelShaderTarget;			// 40
	NiD3DPixelShader*				PixelShader;				// 44
	NiD3DShaderConstantMap*			VertexConstantMap;			// 48
	UInt8							Unk04C;						// 4C
	UInt8							pad04C[3];
	char*							VertexShaderProgramFile;	// 50
	char*							VertexShaderEntryPoint;		// 54
	char*							VertexShaderTarget;			// 58
	NiD3DVertexShader*				VertexShader;				// 5C
	UInt8							SoftwareVP;					// 60
	UInt8							RendererOwned;				// 61
	UInt8							pad[2];
	UInt32							RefCount;					// 64
};
assert(sizeof(NiD3DPass) == 0x68);

class NiShader : public NiRefObject {
public:
	char*		Name;					// 008
	UInt32		Unk00C;					// 00C
	UInt8		Unk010;					// 010
	UInt8		pad010[3];
};
assert(sizeof(NiShader) == 0x14);

class NiD3DShaderInterface : public NiShader {
public:
	IDirect3DDevice9*	D3DDevice;		// 014
	NiDX9Renderer*		D3DRenderer;	// 018
	NiDX9RenderState*	D3DRenderState;	// 01C
	UInt8				Unk020;			// 020
	UInt8				pad01C[3];
};
assert(sizeof(NiD3DShaderInterface) == 0x24);

class NiD3DShader : public NiD3DShaderInterface {
public:
	UInt8					IsInitialized;		// 024
	UInt8					Unk021;				// 025
	UInt8					pad021[2];
	NiD3DShaderDeclaration* ShaderDeclaration;	// 028
	NiD3DRenderStateGroup*  RenderStateGroup;	// 02C
	NiD3DShaderConstantMap* PixelConstantMap;	// 030
	NiD3DShaderConstantMap* VertexConstantMap;	// 034
	UInt32					Unk038[14];			// 038
};
assert(sizeof(NiD3DShader) == 0x70);

class BSShader : public NiD3DShader {
public:
	UInt32		Unk070;			// 070
	UInt32		Unk074;			// 074
	UInt32		Unk078;			// 078
};
assert(sizeof(BSShader) == 0x7C);

class WaterShader : public BSShader {
public:
	UInt32				Unk07C[70];		// 07C
	NiD3DVertexShader*	Vertex[3];		// 194
	NiD3DPixelShader*	Pixel[38];		// 1A0
	UInt32				Unk238[6];		// 238
};
assert(sizeof(WaterShader) == 0x250);

class BSImageSpaceShader : public BSShader {
public:
	UInt32				Unk07C[18];	// 07C
	NiD3DVertexShader*	Vertex;		// 0C4
	NiD3DPixelShader*	Pixel;		// 0C8
};
assert(sizeof(BSImageSpaceShader) == 0xCC);

class WaterShaderHeightMap : public BSImageSpaceShader {
public:
	UInt32				Unk0CC;		// 0CC
};
assert(sizeof(WaterShaderHeightMap) == 0xD0);

class Ni2DBuffer : public NiObject {
public:
	UInt32				width;	// 008
	UInt32				height;	// 00C
	NiDX92DBufferData*	data;	// 010
};
assert(sizeof(Ni2DBuffer) == 0x014);

class NiDepthStencilBuffer : public Ni2DBuffer {};
assert(sizeof(NiDepthStencilBuffer) == 0x014);

class NiDX92DBufferData : public NiRefObject {
public:
	virtual void		func02();												// 02
	virtual void		func03();												// 03
	virtual void		func04();												// 04
	virtual	void		func05();												// 05
	virtual	void		func06();												// 06
	virtual void		func07();												// 07
	virtual void		func08();												// 08
	virtual void		func09();												// 09
	virtual void		func0A();												// 0A
	virtual void		func0B();												// 0B
	virtual void		func0C();												// 0C
	virtual void		func0D();												// 0D
	virtual void		func0E();												// 0E
	virtual void		func0F();												// 0F
	virtual void		func10();												// 10
	virtual void		func11();												// 11
	virtual void		func12();												// 12
	virtual void		func13();												// 13
	virtual void		func14();												// 14
	virtual void		func15();												// 15
	virtual void		func16();												// 16
	virtual void		func17();												// 17
	virtual void		func18();												// 18
	virtual void		func19();												// 19
	virtual void		func1A();												// 1A

	Ni2DBuffer*			ParentData;												// 08
	UInt32				Unk0C;													// 0C
	UInt32				Unk10;													// 10
	IDirect3DSurface9*	Surface;												// 14
};

class NiRenderTargetGroup : public NiObject {
public:
	virtual UInt32					GetWidth(UInt32 Index);											// 23
	virtual UInt32					GetHeight(UInt32 Index);										// 24
	virtual UInt32					GetDepthStencilWidth();											// 25
	virtual UInt32					GetDepthStencilHeight();										// 26
	virtual const NiPixelFormat*	GetPixelFormat(UInt32 Index);									// 27
	virtual const NiPixelFormat*	GetDepthStencilPixelFormat();									// 28
	virtual UInt32					GetBufferCount();											// 29
	virtual bool					AttachBuffer(Ni2DBuffer* Buffer, UInt32 Index);					// 2A
	virtual bool					AttachDepthStencilBuffer(NiDepthStencilBuffer* DepthBuffer);	// 2B
	virtual Ni2DBuffer*				GetBuffer(UInt32 Index);										// 2C
	virtual NiDepthStencilBuffer*	GetDepthStencilBuffer();										// 2D
	virtual void*					GetRendererData();												// 2E
	virtual void					SetRendererData(void* RendererData);							// 2F
	virtual void*					GetRenderTargetData(UInt32 RenderTargetIndex);					// 30
	virtual void*					GetDepthStencilBufferRendererData();							// 31
	virtual void					func32();													// 32
	virtual void					func33();													// 33

	UInt32							Unk08;						// 08
	Ni2DBuffer*						RenderTargets[4];			// 0C
	UInt32							numRenderTargets;			// 1C
	NiDepthStencilBuffer*			DepthStencilBuffer;			// 20
	void*							RenderData;					// 24
};
assert(sizeof(NiRenderTargetGroup) == 0x28);

class NiDX9RenderState : public NiRefObject {
public:
	virtual void							UpdateRenderState(const NiPropertyState* pkNew);// 02
	virtual void							SetAlpha(void* AlphaProperty);					// 03
	virtual void							SetDither(void* DitherProperty);				// 04
	virtual void							SetFog(NiFogProperty* FogProperty);				// 05
	virtual void							SetMaterial(void* u1);							// 06
	virtual void							SetShadeMode(void* ShadeProperty);				// 07
	virtual void							SetSpecular(void* SpecularProperty);			// 08
	virtual void							SetStencil(void* StencilProperty);				// 09
	virtual void							SetWireframe(void* WireframeProperty);			// 0A
	virtual void 							SetZBuffer(void* ZBufferProperty);				// 0B
	virtual void							RestoreAlpha();									// 0C
	virtual void							SetVertexBlending(UInt16 u1);					// 0D
	virtual void							SetNormalization(void* u1);						// 0E
	virtual void							func_0F(UInt32 u1);								// 0F
	virtual float							GetVar088();									// 10
	virtual void							func_11(float u1);								// 11
	virtual void							func_12(float u1, float u2);					// 12
	virtual BOOL							func_13();										// 13
	virtual void							func_14(BOOL u1);								// 14
	virtual void							func_15(UInt32 u1);								// 15
	virtual void							InitializeRenderStates();						// 16
	virtual void							BackUpAllStates();								// 17
	virtual void 							RestoreRenderState(D3DRENDERSTATETYPE state);	// 18
	virtual void							RestoreAllRenderStates();						// 19
	virtual void 							SetRenderState(D3DRENDERSTATETYPE state, UInt32 value, UInt8 Arg3, UInt8 Arg4);					// 1A
	virtual UInt32							GetRenderState(D3DRENDERSTATETYPE state);														// 1B
	virtual void							ClearPixelShaders();																			// 1C
	virtual void							BackUpPixelShader();																			// 1D
	virtual void							func_1E();																						// 1E
	virtual void							SetPixelShader(IDirect3DPixelShader9* PixelShader, UInt8 BackUp);								// 1F
	virtual IDirect3DPixelShader9*			GetPixelShader();																				// 20
	virtual	void							RestorePixelShader();																			// 21
	virtual void							RemovePixelShader(IDirect3DPixelShader9* PixelShader);											// 22
	virtual void							SetVertexShader(IDirect3DVertexShader9* pShader, UInt8 BackUp);									// 23
	virtual IDirect3DVertexShader9*			GetVertexShader();																				// 24
	virtual void							RestoreVertexShader();																			// 25
	virtual void							RemoveVertexShader(IDirect3DVertexShader9* pShader);											// 26
	virtual void							SetFVF(UInt32 FVF, UInt8 BackUp);																// 27
	virtual UInt32							GetFVF();																						// 28
	virtual void							RestoreFVF();																					// 29
	virtual void							ClearFVF(UInt32 FVF);																			// 2A
	virtual void							SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl, UInt8 BackUp);							// 2B
	virtual IDirect3DVertexDeclaration9*	GetVertexDeclaration();																			// 2C
	virtual void							RestoreVertexDeclaration();																		// 2D
	virtual void							ClearVertexDeclatation(IDirect3DVertexDeclaration9* pDecl);										// 2E
	virtual void							func_02F();																						// 2F
	virtual void 							SetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type, UInt32 Value, UInt8 BackUp);	// 30
	virtual UInt32							GetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type);								// 31
	virtual void							func_032();																						// 32
	virtual void							SetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 BackUp);			// 33
	virtual UInt32 							GetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);										// 34
	virtual void							RestoreSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);									// 35
	virtual void							ClearTextureList();																				// 36
	virtual void							SetTexture(UInt32 Sampler, IDirect3DBaseTexture9* pTexture);									// 37
	virtual IDirect3DBaseTexture9*			GetTexture(UInt32 Sampler);																		// 38
	virtual void							RemoveTexture(IDirect3DBaseTexture9* pTexture);													// 39
	virtual void							SetSoftwareVertexProcessing(UInt8 bSoftware);													// 3A
	virtual UInt8							GetSoftwareVertexProcessing();																	// 3B
	virtual void							SetVar_0FF4(UInt8 u1);																			// 3C
	virtual UInt8							GetVar_0FF4();																					// 3D
	virtual void							SetVar_0FF5(UInt8 u1);																			// 3E
	virtual UInt8							GetVar_0FF5();																					// 3F
	virtual void							Reset();																						// 40
	virtual void							func_041();																						// 41

	UInt32							Flags;							// 0008
	UInt32							unk000C[(0x0074 - 0x000C) >> 2];// 000C
	NiAlphaProperty*				DisabledAlphaProperty;			// 0074
	float							CameraNear;						// 0078
	float							CameraFar;						// 007C
	float							CameraDepthRange;				// 0080
	float							MaxFogFactor;					// 0084
	float							MaxFogValue;					// 0088
	NiColor							CurrentFogColor;				// 008C
	UInt32                          Unk98[1046];					// 0098
	NiDX9ShaderConstantManager*		ShaderConstantManager;			// 10F0
	UInt8							ForceNormalizeNormals;			// 10F4
	UInt8							InternalNormalizeNormals;		// 10F5
	UInt8							UsingSoftwareVP;				// 10F6
	UInt8							Declaration;					// 10F7
	IDirect3DDevice9*				Device;							// 10F8
	NiDX9Renderer*					Renderer;						// 10FC
	UInt32							unk1000[(0x1018 - 0x1000) >> 2];// 1100
	D3DCAPS9						Caps;							// 1118
};
assert(offsetof(NiDX9RenderState, Device) == 0x10F8);
assert(sizeof(NiDX9RenderState) == 0x1248);

class NiRenderer : public NiObject {
public:
	enum ClearFlags {
		kClear_BACKBUFFER = 0x1,
		kClear_STENCIL = 0x2,
		kClear_ZBUFFER = 0x4,
		kClear_NONE = 0,
		kClear_ALL = kClear_BACKBUFFER | kClear_STENCIL | kClear_ZBUFFER
	};

	virtual void			Unk_23();
	virtual void			Unk_24();
	virtual void			Unk_25();
	virtual void			Unk_26();
	virtual void			Unk_27();
	virtual void			Unk_28();
	virtual void			Unk_29();
	virtual void			Unk_2A();
	virtual void			Unk_2B();
	virtual void			Unk_2C();
	virtual void			Unk_2D();
	virtual void			Unk_2E();
	virtual void			Unk_2F();
	virtual void			Unk_30();
	virtual void			Unk_31();
	virtual NiRenderTargetGroup* GetDefaultRT();	// get back buffer rt
	virtual NiRenderTargetGroup* GetCurrentRT();	// get currentRTGroup
	virtual void			Unk_34();
	virtual void			Unk_35();
	virtual void			Unk_36();
	virtual void			Unk_37();
	virtual void 			Unk_38();
	virtual void 			Unk_39();
	virtual void			Unk_3A();
	virtual void			Unk_3B();
	virtual void			PurgeGeometry(NiGeometryData* geo);
	virtual void			PurgeMaterial(NiMaterialProperty* material);
	virtual void			PurgeEffect(NiDynamicEffect* effect);
	virtual void			PurgeScreenTexture();
	virtual void			PurgeSkinPartition(NiSkinPartition* skinPartition);
	virtual void			PurgeSkinInstance(NiSkinInstance* skinInstance);
	virtual void			Unk_42();
	virtual bool			Unk_43();
	virtual void			Unk_44();
	virtual bool			FastCopy(void* src, void* dst, RECT* srcRect, SInt32 xOffset, SInt32 yOffset);
	virtual bool			Copy(void* src, void* dst, RECT* srcRect, RECT* dstRect, UInt32 filterMode);
	virtual void			Unk_47();
	virtual bool			Unk_48(void* arg);
	virtual void			Unk_49();
	virtual void			Unk_4A(float arg);
	virtual void 			Unk_4B(UInt32 size);
	virtual void			Unk_4C(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_4D(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_4E(void* buf);
	virtual void			CreateSourceTexture(NiSourceTexture* texture);
	virtual bool			CreateRenderedTexture(NiRenderedTexture* arg);
	virtual bool			CreateSourceCubeMap(NiSourceCubeMap* arg);
	virtual bool			CreateRenderedCubeMap(NiRenderedCubeMap* arg);
	virtual bool			CreateDynamicTexture(void* arg);
	virtual void			Unk_54();
	virtual bool			CreateDepthStencil(NiDepthStencilBuffer* arg, void* textureFormat);
	virtual void			Unk_56();
	virtual void			Unk_57();
	virtual void			Unk_58();
	virtual void			Unk_59();
	virtual void			Unk_5A();
	virtual void			Unk_5B();
	virtual void			Unk_5C();
	virtual void			Unk_5D();
	virtual void			Unk_5E();
	virtual bool			BeginScene();
	virtual bool			EndScene();
	virtual void			DisplayScene();
	virtual void			Clear(float* rect, UInt32 flags);
	virtual void			SetupCamera(NiPoint3* pos, NiPoint3* at, NiPoint3* up, NiPoint3* right, NiFrustum* frustum, float* viewport);
	virtual void			SetupScreenSpaceCamera(float* viewport);
	virtual bool			BeginUsingRenderTargetGroup(NiRenderTargetGroup* renderTarget, ClearFlags clearFlags);
	virtual bool			EndUsingRenderTargetGroup();
	virtual void			BeginBatch(UInt32 arg0, UInt32 arg1);
	virtual void			EndBatch();
	virtual void			BatchRenderShape(void* arg);
	virtual void			BatchRenderStrips(void* arg);
	virtual void			RenderTriShape(NiTriShape* obj);
	virtual void			RenderTriStrips(NiTriStrips* obj);
	virtual void			RenderTriShape2(NiTriShape* obj);
	virtual void			RenderTriStrips2(NiTriStrips* obj);
	virtual void			RenderParticles(NiParticles* obj);
	virtual void			RenderLines(NiLines* obj);
	virtual void			RenderScreenTexture();

	UInt32					Unk008[126];				// 008
	UInt32					SceneState;					// 200
	UInt32					Unk204;						// 204
	UInt32					Unk208;						// 208
	UInt32					Unk20C;						// 20C
};
assert(sizeof(NiRenderer) == 0x210);

class NiDX9Renderer : public NiRenderer {
public:
	class PrePackObject;

	enum FrameBufferFormat {
		FBFMT_UNKNOWN = 0,
		FBFMT_R8G8B8,
		FBFMT_A8R8G8B8,
		FBFMT_X8R8G8B8,
		FBFMT_R5G6B5,
		FBFMT_X1R5G5B5,
		FBFMT_A1R5G5B5,
		FBFMT_A4R4G4B4,
		FBFMT_R3G3B2,
		FBFMT_A8,
		FBFMT_A8R3G3B2,
		FBFMT_X4R4G4B4,
		FBFMT_R16F,
		FBFMT_G16R16F,
		FBFMT_A16B16G16R16F,
		FBFMT_R32F,
		FBFMT_G32R32F,
		FBFMT_A32B32G32R32F,
		FBFMT_NUM
	};

	enum DepthStencilFormat {
		DSFMT_UNKNOWN = 0,
		DSFMT_D16_LOCKABLE = 70,
		DSFMT_D32 = 71,
		DSFMT_D15S1 = 73,
		DSFMT_D24S8 = 75,
		DSFMT_D16 = 80,
		DSFMT_D24X8 = 77,
		DSFMT_D24X4S4 = 79,
	};

	enum PresentationInterval {
		PRESENT_INTERVAL_IMMEDIATE = 0,
		PRESENT_INTERVAL_ONE = 1,
		PRESENT_INTERVAL_TWO = 2,
		PRESENT_INTERVAL_THREE = 3,
		PRESENT_INTERVAL_FOUR = 4,
		PRESENT_INTERVAL_NUM
	};

	enum SwapEffect {
		SWAPEFFECT_DEFAULT,
		SWAPEFFECT_DISCARD,
		SWAPEFFECT_FLIP,
		SWAPEFFECT_COPY,
		SWAPEFFECT_NUM
	};

	enum FrameBufferMode {
		FBMODE_DEFAULT,
		FBMODE_LOCKABLE,
		FBMODE_MULTISAMPLES_2 = 0x00010000,
		FBMODE_MULTISAMPLES_3 = 0x00020000,
		FBMODE_MULTISAMPLES_4 = 0x00030000,
		FBMODE_MULTISAMPLES_5 = 0x00040000,
		FBMODE_MULTISAMPLES_6 = 0x00050000,
		FBMODE_MULTISAMPLES_7 = 0x00060000,
		FBMODE_MULTISAMPLES_8 = 0x00070000,
		FBMODE_MULTISAMPLES_9 = 0x00080000,
		FBMODE_MULTISAMPLES_10 = 0x00090000,
		FBMODE_MULTISAMPLES_11 = 0x000a0000,
		FBMODE_MULTISAMPLES_12 = 0x000b0000,
		FBMODE_MULTISAMPLES_13 = 0x000c0000,
		FBMODE_MULTISAMPLES_14 = 0x000d0000,
		FBMODE_MULTISAMPLES_15 = 0x000e0000,
		FBMODE_MULTISAMPLES_16 = 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK = 0x0000FFFF,
		FBMODE_NUM = 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};
	void							PackGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiD3DShaderDeclaration* ShaderDeclaration) {}
	void							PackSkinnedGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition, NiD3DShaderDeclaration* ShaderDeclaration) {}
	void							CalculateBoneMatrixes(NiSkinInstance* SkinInstance, NiTransform* WorldTrasform) { ThisCall(0x00E6FE30, this, SkinInstance, WorldTrasform, false, 3, true); }

	UInt32							pad210[(0x288 - 0x210) >> 2];	// 210
	IDirect3DDevice9*				device;							// 288
	D3DCAPS9						caps;							// 28C
	HANDLE							deviceWindow;					// 3BC
	HANDLE							focusWindow;					// 3C0
	char							rendererInfo[0x200];			// 3C4
	UInt32							adapterIdx;						// 5C4
	UInt32							d3dDevType;						// 5C8 - D3DDEVTYPE
	UInt32							d3dDevFlags;					// 5CC - D3DCREATE
	UInt8							softwareVertexProcessing;		// 5D0 - !D3DCREATE_HARDWARE_VERTEXPROCESSING
	UInt8							mixedVertexProcessing;			// 5D1 - D3DCREATE_MIXED_VERTEXPROCESSING
	UInt8							pad5D2[2];						// 5D2
	UInt32							Unk5D4[15];						// 5D4
	NiTMap<void*, PrePackObject*>	PrePackObjects;					// 610 - NiTPointerMap <NiVBBlock *, NiDX9Renderer::PrePackObject *>
	UInt32							Unk620[153];					// 620
	NiRenderTargetGroup*			defaultRTGroup;					// 884 - back buffer
	NiRenderTargetGroup*			currentRTGroup;					// 888
	NiRenderTargetGroup*			currentscreenRTGroup;			// 88C
	NiTMap<HWND*, NiRenderTargetGroup*>	screenRTGroups;					// 890 - NiTPointerMap <HWND *, NiPointer <NiRenderTargetGroup> >
	UInt32							Unk8A0[6];						// 8A0
	NiDX9RenderState*				renderState;					// 8B8
	UInt32							Unk8BC[33];						// 8BC
	D3DXMATRIXA16					worldMatrix;				// 940
	D3DMATRIX						viewMatrix;					// 980
	D3DMATRIX						projMatrix;					// 9C0
	D3DMATRIX						UnkMatrix;					// A00
	D3DMATRIX						invViewMatrix;				// A40
	UInt32							UnkA80[6];					// A80
	UInt32							width;						// A98
	UInt32							height;						// A9C
	UInt32							flags;						// AA0
	UInt32							windowDevice;				// AA4
	UInt32							windowFocus;				// AA8
	UInt32							adapterType;				// AAC
	UInt32							deviceType;					// AB0
	FrameBufferFormat				frameBufferFormat;			// AB4
	DepthStencilFormat				depthStencilFormat;			// AB8
	PresentationInterval			presentationInterval;		// ABC
	SwapEffect						swapEffect;					// AC0
	FrameBufferMode					frameBufferMode;			// AC4
	UInt32							backBufferCount;			// AC8
	RefreshRate						refreshRate;				// ACC
	UInt32							UnkAD0[44];					// AD0
};
assert(offsetof(NiDX9Renderer, device) == 0x288);
assert(offsetof(NiDX9Renderer, defaultRTGroup) == 0x884);
assert(offsetof(NiDX9Renderer, height) == 0xA9C);
assert(sizeof(NiDX9Renderer) == 0xB80);

class NiControllerSequence : public NiObject {
public:
	virtual void	Unk_23();

	struct ControlledBlock {
		void*	unk00;		// 00 NiInterpolator*
		void*	unk04;		// 04 NiMultiTargetTransformController*
		UInt32	unk08;		// 08
		UInt8	unk0C;		// 0C
		UInt8	pad0C[3];
	};

	const char*				sequenceName;			// 08
	UInt32					numControlledBlocks;	// 0C
	UInt32					arrayGrowBy;			// 10
	ControlledBlock**		controlledBlocks;		// 14
	const char**			unkNodeName;			// 18
	float					weight;					// 1C
	NiTextKeyExtraData*		textKeyData;			// 20
	UInt32					cycleType;				// 24
	float					frequency;				// 28
	float					startTime;				// 2C
	float					stopTime;				// 30
	float					flt34;					// 34
	float					flt38;					// 38
	float					flt3C;					// 3C
	NiControllerManager*	manager;				// 40
	UInt32					unk44;					// 44
	UInt32					unk48;					// 48
	float					flt4C;					// 4C
	float					flt50;					// 50
	float					flt54;					// 54
	UInt32					unk58;					// 58
	const char*				rootNodeName;			// 5C
	UInt32					unk60[5];				// 60
};
assert(sizeof(NiControllerSequence) == 0x74);

#elif defined(OBLIVION)
class NiRefObject {
public:
	virtual void	Destructor(bool freeThis);

	UInt32			m_uiRefCount;				// 004
};
assert(sizeof(NiRefObject) == 0x008);

class NiObject : public NiRefObject {
public:
	virtual NiRTTI*		GetType();
	virtual NiObject*	Unk_02();
	virtual UInt32		Unk_03();
	virtual UInt32		Unk_04();
	virtual UInt32		Unk_05();
	virtual NiObject*	Copy();
	virtual void		Load(NiStream* stream);
	virtual void		PostLoad(NiStream* stream);
	virtual void		FindNodes(NiStream* stream);
	virtual void		Save(NiStream* stream);
	virtual bool		Compare(NiObject* obj);
	virtual void		DumpAttributes(NiTArray <char*>* dst);
	virtual void		DumpChildAttributes(NiTArray <char*>* dst);
	virtual void		Unk_0E();
	virtual void		Unk_0F(UInt32 arg);
	virtual void		Unk_10();
	virtual void		Unk_11();
	virtual void		Unk_12(UInt32 arg);
};
assert(sizeof(NiObject) == 0x008);

class NiExtraData : public NiObject {
public:
	virtual	bool	Unk_13();
	virtual bool	Unk_14();

	char*	m_pcName;	// 08
};
assert(sizeof(NiExtraData) == 0x00C);

class TESObjectExtraData : public NiExtraData {
public:
	TESObjectREFR*	refr;	// 0C
};
assert(sizeof(TESObjectExtraData) == 0x010);

class NiObjectNET : public NiObject {
public:
	void				SetName(const char* Name) { ThisCall(0x006FF420, this, Name); }

	const char*			m_pcName;						// 008
	NiTimeController*	m_controller;					// 00C
	NiExtraData**		m_extraDataList;				// 010
	UInt16				m_extraDataListLen;				// 014
	UInt16				m_extraDataListCapacity;		// 016
};
assert(sizeof(NiObjectNET) == 0x018);

class NiAVObject : public NiObjectNET {
public:
	virtual void		UpdateControllers(float fTime);
	virtual void		Unk_14();
	virtual void		ApplyTransform(NiMatrix33* Mat, NiPoint3* Trn, bool OnLeft);
	virtual NiAVObject* GetObjectByName(const char* Name);
	virtual void*		Unk_17();
	virtual void		UpdateDownwardPass(float fTime, bool bUpdateControllers);
	virtual void		UpdateSelectedDownwardPass(float fTime);
	virtual void		UpdateRigidDownwardPass(float fTime);
	virtual void		UpdatePropertiesDownward(NiPropertyState* ParentState);
	virtual void		UpdateEffectsDownward(NiDynamicEffectState* ParentState);
	virtual void		UpdateWorldData();
	virtual void		UpdateWorldBound();
	virtual void		OnVisible(NiCullingProcess* CullingProcess);
	virtual void		Unk_20(void* arg);			// get NiMaterialProperty, pass to arg if found

	enum {
		kFlag_AppCulled					= 1 << 0, // originally named m_bAppCulled but they appear to have used bitfields
		kFlag_SelUpdate					= 1 << 1, // Selective update flags
		kFlag_SelUpdateTransforms		= 1 << 2,
		kFlag_SelUpdatePropControllers	= 1 << 3,
		kFlag_SelUpdateRigid			= 1 << 4,
		kFlag_DisplayObject				= 1 << 5, // For use with occlusion culling system
		kFlag_DisableSorting			= 1 << 6, // For use with sorting/accumulation system
		kFlag_SelTransformsOverride		= 1 << 7, // Selective update over-ride flags
		kFlag_IsNode					= 1 << 8, // Is the object a leaf or a node
	};

	UInt16					m_flags;				// 018
	UInt8					pad01A[2];				// 01A
	NiNode*					m_parent;				// 01C
	NiSphere				m_kWorldBound;			// 020
	NiTransform				m_localTransform;		// 030
	NiTransform				m_worldTransform;		// 064
	NiTList<NiProperty>		m_propertyList;			// 098
	NiObject*				m_spCollisionObject;	// 0A8
};
assert(sizeof(NiAVObject) == 0x0AC);

class NiNode : public NiAVObject {
public:
	virtual void				AddObject(NiAVObject* nChild, UInt8 FirstAvail); // Add child node
	virtual NiAVObject*			RemoveObject(NiAVObject** RemovedChild, NiAVObject* nChild);
	virtual NiAVObject*			RemoveObjectAt(NiAVObject** RemovedChild, UInt32 Index);
	virtual NiAVObject*			SetObjectAt(NiAVObject** SetChild, UInt32 Index, NiAVObject* nChild);
	virtual void				Unk_25();
	virtual bool				Unk_26();
	
	TESObjectREFR*				GetRef() { return ((TESObjectExtraData*)ThisCall(0x006FF9C0, this, "REF"))->refr; }

	NiTArray<NiAVObject*>		m_children;			// 0AC
	NiTList<NiDynamicEffect*>	m_effects;			// 0BC
	NiSphere					m_combinedBounds;	// 0CC
};
assert(sizeof(NiNode) == 0x0DC);

class NiBillboardNode : public NiNode {
public:
	enum {
		kMode_AlwaysFaceCamera = 0,
		kMode_RotateAboutUp,
		kMode_RigidFaceCamera,
		kMode_AlwaysFaceCenter,
		kMode_RigidFaceCenter,
		kMode_BSRotateAboutUp,
		kMode_Mask = 7,

		kFlag_Unk3 = 1 << 3,
	};

	UInt16	flags;				// 0DC
	UInt8	pad0DE[2];			// 0DE
	float	lastUpdateTime;		// 0E0
};
assert(sizeof(NiBillboardNode) == 0x0E4);

class NiCamera : public NiAVObject {
public:
	float		WorldToCam[4][4];		// 0AC
	NiFrustum	Frustum;				// 0EC
	float		MinNearPlaneDist;		// 108
	float		MaxFarNearRatio;		// 10C
	NiViewport	ViewPort;				// 110
	float		LODAdjust;				// 120
};
assert(sizeof(NiCamera) == 0x124);

class SceneGraph : public NiNode {
public:
	float				GetFarPlaneDistance() { return ThisCallF(0x00410EE0, this); }

	NiCamera*			camera;					// 0DC
	UInt32				unk0E0;					// 0E0
	NiCullingProcess*	cullingProcess;			// 0E4
	UInt8				IsMinFarPlaneDistance;	// 0E8 The farplane is set to 20480.0 when the flag is true. Probably used for interiors.
	UInt8				pad0E8[3];
	float				cameraFOV;				// 0EC
};
assert(sizeof(SceneGraph) == 0x0F0);

class NiDynamicEffect : public NiAVObject {
public:
	virtual UInt32	GetEffectType();

	UInt8	enable;		// 0AC
	UInt8	pad0AD[3];	// 0AD
	UInt32	unk0B0;		// 0B0 - init'd to monotonically increasing number (uid?)
	UInt32	unk0B4;		// 0B4
	UInt32	unk0B8;		// 0B8 - init'd to 1

	NiTList<NiNode>		affectedNodes;		// 0BC
	NiTList<NiNode>		unaffectedNodes;	// 0CC
};
assert(sizeof(NiDynamicEffect) == 0x0DC);

class NiLight : public NiDynamicEffect {
public:
	float	m_fDimmer;	// 0DC
	NiColor	m_kAmb;		// 0E0
	NiColor	m_kDiff;	// 0EC
	NiColor	m_kSpec;	// 0F8
	UInt32	unk104;		// 104
};
assert(sizeof(NiLight) == 0x108);

class NiPointLight : public NiLight {
public:
	float	m_fAtten0;	// 108
	float	m_fAtten1;	// 10C
	float	m_fAtten2;	// 110
};
assert(sizeof(NiPointLight) == 0x114);

class NiDirectionalLight : public NiLight {
public:
	NiPoint3	m_direction;	// 108
};
assert(sizeof(NiDirectionalLight) == 0x114);

class NiVBChip {
public:
	UInt32					Index;      // 00
	UInt32					Unk04;		// 04 union { NiVBBlock* m_pkBlock; NiVBDynamicSet* m_pkDynamicSet; };
	IDirect3DVertexBuffer9* VB;			// 08
	UInt32					Offset;		// 0C
	UInt32					LockFlags;	// 10
	UInt32					Size;		// 14
	NiVBChip*				Next;		// 18
	NiVBChip*				Prev;		// 1C
};
assert(sizeof(NiVBChip) == 0x020);

class NiGeometryBufferData {
public:
	UInt32							Flags;					// 00
	NiGeometryGroup*				GeometryGroup;			// 04
	UInt32							FVF;					// 08
	IDirect3DVertexDeclaration9*	VertexDeclaration;		// 0C
	UInt32							unk10;					// 10
	UInt32							VertCount;				// 14
	UInt32							MaxVertCount;			// 18
	UInt32							StreamCount;			// 1C
	UInt32*							VertexStride;			// 20
	NiVBChip**						VBChip;					// 24
	UInt32							IndexCount;				// 28
	UInt32							IBSize;					// 2C
	IDirect3DIndexBuffer9*			IB;						// 30
	UInt32							BaseVertexIndex;		// 34
	D3DPRIMITIVETYPE				PrimitiveType;			// 38
	UInt32							TriCount;				// 3C
	UInt32							MaxTriCount;			// 40
	UInt32							NumArrays;				// 44
	UInt16*							ArrayLengths;			// 48
	UInt16*							IndexArray;				// 4C
};
assert(sizeof(NiGeometryBufferData) == 0x050);

class NiGeometryData : public NiObject {
public:
	enum Consistency {
		MUTABLE			 = 0x0000,
		STATIC			 = 0x4000,
		VOLATILE		 = 0x8000,
		CONSISTENCY_MASK = 0xF000,
	};

	UInt16						Vertices;			// 008
	UInt16						Unk00A;				// 00A
	UInt32						Unk00C;				// 00C
	UInt32						Unk010;				// 010
	UInt32						Unk014;				// 014
	UInt32						Unk018;				// 018
	NiPoint3*					Vertex;				// 01C
	NiPoint3*					Normal;				// 020
	NiColorAlpha*				Color;				// 024
	UInt32						Texture;			// 028 NiPoint2*
	UInt16						ActiveVertices;		// 02C
	UInt16						DataFlags;			// 02E
	UInt8						KeepFlags;			// 030
	UInt8						CompressFlags;		// 031
	UInt8						pad030[2];
	NiAdditionalGeometryData*	AdditionalGeomData;	// 034
	NiGeometryBufferData*		BuffData;			// 038
	UInt8						Unk03C;				// 03C
	UInt8						Unk03D;				// 03D
	UInt8						pad03C[2];
};
assert(sizeof(NiGeometryData) == 0x040);

class NiSkinPartition : public NiObject {
public:
	class Partition {
	public:
		void**					_vtbl;			// 00
		UInt16*					pBones;			// 04
		float*					Weights;		// 08
		UInt32					Unk04[4];		// 0C
		UInt16					Vertices;		// 1C
		UInt16					Triangles;		// 1E
		UInt16					Bones;			// 20
		UInt16					Strips;			// 22
		UInt16					BonesPerVertex; // 24
		UInt16					pad24;
		NiGeometryBufferData*	BuffData;		// 28
	};

	UInt32		PartitionsCount;		// 08
	Partition*	Partitions;				// 0C
};
assert(sizeof(NiSkinPartition) == 0x010);

class NiSkinData : public NiObject {
public:
	class BoneVertData {
	public:
		UInt16	Verts;		// 00
		float	Weight;		// 04
	};

	class BoneData {
	public:
		NiTransform		SkinToBone;		// 00
		NiPoint3		Center;			// 34
		float			Radius;			// 38
		BoneVertData*	BoneVertData;	// 3C
		UInt16			Verts;			// 40
		UInt16			pad44;
	};

	NiSkinPartition*	SkinPartition;		// 08
	NiTransform			RootParentToSkin;	// 0C
	UInt32				Bones;				// 40
	BoneData*			BoneData;			// 44
};
assert(sizeof(NiSkinData) == 0x048);

class NiSkinInstance : public NiObject {
public:
	NiSkinData*			SkinData;				// 08
	NiSkinPartition*	SkinPartition;			// 0C
	NiAVObject*			RootParent;				// 10
	NiAVObject**		BoneObjects;			// 14
	UInt32				FrameID;				// 18
	UInt32				Bones;					// 1C
	void*				BoneMatrixes;			// 20 Matrixes array for the bones D3DMATRIX
	UInt32				BoneRegisters;			// 24
	void*				SkinToWorldWorldToSkin;	// 28 D3DMATRIX
};
assert(sizeof(NiSkinInstance) == 0x02C);

class NiGeometry : public NiAVObject {
public:
	virtual void	Render(NiRenderer* arg);
	virtual void	Unk_22(NiRenderer* arg);
	virtual void	SetGeomData(NiObject* obj);
	virtual void	Unk_24();		// geomData->Unk_15()
	virtual void	Unk_25(NiRenderer* arg);

	NiPropertyState*		propertyState;		// 0AC
	NiDynamicEffectState*	dynamicEffectState;	// 0B0
	NiGeometryData*			geomData;			// 0B4
	NiSkinInstance*			skinInstance;		// 0B8
	NiD3DShader*			shader;				// 0BC BSShader
};
assert(sizeof(NiGeometry) == 0x0C0);

class NiTextureData {
public:
	void**			_vtbl;			// 00
	NiTexture*		pTexture;		// 04
	NiDX9Renderer*	pRenderer;		// 08
	NiPixelFormat	PixelFormat;	// 0C
};
assert(sizeof(NiTextureData) == 0x050);

class NiDX9TextureData : public NiTextureData {
public:
	IDirect3DBaseTexture9*  dTexture;		// 50
	UInt32					Width;			// 54
	UInt32					Height;			// 58
	UInt32					Levels;			// 5C
};
assert(sizeof(NiDX9TextureData) == 0x060);

class NiDX9SourceTextureData : public NiDX9TextureData {
public:
	UInt32					unk60;				// 60
	UInt8					ReplacementData;	// 64
	UInt8					Mipmap;				// 65
	UInt8					pad64;
	UInt32					FormattedSize;		// 68
	UInt32					Palette;			// 6C NiPalette
	UInt32					LevelsSkipped;		// 70
	UInt32					SourceRevID;		// 74
	UInt32					PalRevID;			// 78
};
assert(sizeof(NiDX9SourceTextureData) == 0x07C);

class NiTexture : public NiObjectNET {
public:
	virtual UInt32	GetWidth();
	virtual UInt32	GetHeight();

	enum PixelLayout {
		kPixelLayout_Palette8BPP = 0,
		kPixelLayout_Raw16BPP,
		kPixelLayout_Raw32BPP,
		kPixelLayout_Compressed,
		kPixelLayout_Bumpmap,
		kPixelLayout_Palette4BPP,
		kPixelLayout_Default,
	};

	enum AlphaFormat {
		kAlpha_None = 0,
		kAlpha_Binary,	// 1bpp
		kAlpha_Smooth,	// 8bpp
		kAlpha_Default,
	};

	enum MipMapFlag {
		kMipMap_Disabled = 0,
		kMipMap_Enabled,
		kMipMap_Default,
	};

	struct FormatPrefs {
		PixelLayout pixelLayout;
		AlphaFormat alphaFormat;
		MipMapFlag	mipmapFormat;
	};

	UInt32			pixelLayout;	// 018
	UInt32			alphaFormat;	// 01C
	UInt32			mipmapFormat;	// 020
	NiTextureData*	rendererData;	// 024
	NiTexture*		nextTex;		// 028 - linked list updated in ctor/dtor
	NiTexture*		prevTex;		// 02C
};
assert(sizeof(NiTexture) == 0x030);

class NiSourceTexture : public NiTexture {
public:
	virtual void	Unk_15();
	virtual void	FreePixelData();
	virtual bool	Unk_17();

	UInt8		unk030;				// 030 - is static?
	UInt8		unk031[3];			// 031
	void*		unk034;				// 034
	const char* fileName;			// 038
	NiObject*	pixelData;			// 03C - NiPixelData
	UInt8		loadDirectToRender;	// 040
	UInt8		persistRenderData;	// 041
	UInt8		pad042[2];			// 042
	void*		unk044;				// 044
};
assert(sizeof(NiSourceTexture) == 0x048);

class NiRenderedTexture : public NiTexture {
public:
	virtual void* Unk_15();

	Ni2DBuffer* buffer;		// 030
	UInt8		unk034;		// 034
	UInt8		pad034[3];
	D3DFORMAT	format;		// 038
	UInt8		unk03C;		// 03C
	UInt8		pad03C;
};
assert(sizeof(NiRenderedTexture) == 0x040);

class NiD3DTextureStage {
public:
	UInt32				Stage;				// 00
	NiTexture*			Texture;			// 04
	UInt32				Unk08;				// 08
};
assert(sizeof(NiD3DTextureStage) == 0x00C);

class NiD3DShaderConstantMapEntry {
public:
	void**				_vtbl;				// 00
	UInt32				Unk04;				// 04
	UInt32				Unk08;				// 08
	char*				Key;				// 0C
	UInt32				Internal;			// 10
	UInt32				Flags;				// 14
	UInt32				Extra;				// 18
	UInt32				ShaderRegister;		// 1C
	UInt32				RegisterCount;		// 20
	char*				VariableName;		// 24
	UInt32				DataSize;			// 28
	UInt32				DataStride;			// 2C
	void*				DataSource;			// 30
	UInt8				Unk34;				// 34
	UInt8				pad34[3];
};
assert(sizeof(NiD3DShaderConstantMapEntry) == 0x038);

class NiD3DShaderConstantMap {
public:
	void**									_vtbl;				// 00
	UInt32									Unk04;				// 04
	UInt32									Unk08;				// 08
	NiTArray<NiD3DShaderConstantMapEntry*>	Entries;			// 0C
	UInt8									Modified;			// 1C
	UInt8									pad1C[3];
	NiD3DShaderProgram*						LastShaderProgram;	// 20
	UInt32									Unk24;				// 24
	IDirect3DDevice9*						Device;				// 28
	NiDX9Renderer*							Renderer;			// 2C
	NiDX9RenderState*						RenderState;		// 30

};
assert(sizeof(NiD3DShaderConstantMap) == 0x034);

class NiD3DSCMVertex : public NiD3DShaderConstantMap { };

class NiD3DSCMPixel : public NiD3DShaderConstantMap { };

class NiD3DShaderDeclaration : public NiObject {
public:
	NiDX9Renderer*				Renderer;		// 008
	NiDX9VertexBufferManager*	BufferManager;	// 00C
	IDirect3DDevice9*			Device;			// 010
	UInt32						Unk014;			// 014
	UInt32						Unk018;			// 018
	UInt32						Unk01C;			// 01C
	UInt32						StreamCount;	// 020
	UInt32						Unk024;			// 024
	UInt32						Unk028;			// 028
};
assert(sizeof(NiD3DShaderDeclaration) == 0x02C);

class NiDX9ShaderDeclaration : public NiD3DShaderDeclaration {
public:
	UInt32		Unk02C;			// 02C
	UInt32		Unk030;			// 030
	UInt32		Unk034;			// 034
};
assert(sizeof(NiDX9ShaderDeclaration) == 0x038);

class NiD3DShaderProgram : public NiRefObject {
public:
	enum ProgramType {
		PROGRAM_VERTEX = 0,
		PROGRAM_PIXEL,
		PROGRAM_GEOMETRY,
		PROGRAM_MAX
	};

	ProgramType				eProgramType;		// 08
	char*					Name;				// 0C
	char*					ShaderProgramName;	// 10
	UInt32					CodeSize;			// 14
	void*					Unk018;				// 18
	IDirect3DDevice9*		Device;				// 1C
	NiDX9Renderer*			Renderer;			// 20
	NiDX9RenderState*		RenderState;		// 24
};
assert(sizeof(NiD3DShaderProgram) == 0x028);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	UInt8							SoftwareVP;		// 28
	UInt8							pad[3];			// 29
	UInt32							Usage;			// 2C
	IDirect3DVertexShader9*			ShaderHandle;	// 30
	IDirect3DVertexDeclaration9*	Declaration;	// 34
};
assert(sizeof(NiD3DVertexShader) == 0x038);

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	IDirect3DPixelShader9* ShaderHandle;	// 28
};
assert(sizeof(NiD3DPixelShader) == 0x02C);

class NiD3DPass {
public:
	void**							_vtbl;						// 00
	char							Name[16];					// 04
	UInt32							CurrentStage;				// 14
	UInt32							StageCount;					// 18
	UInt32							TexturesPerPass;			// 1C
	NiTArray<NiD3DTextureStage*>	Stages;						// 20
	NiD3DRenderStateGroup*			RenderStateGroup;			// 30
	NiD3DShaderConstantMap*			PixelConstantMap;			// 34
	char*							PixelShaderProgramFile;		// 38
	char*							PixelShaderEntryPoint;		// 3C
	char*							PixelShaderTarget;			// 40
	NiD3DPixelShader*				PixelShader;				// 44
	NiD3DShaderConstantMap*			VertexConstantMap;			// 48
	char*							VertexShaderProgramFile;	// 4C
	char*							VertexShaderEntryPoint;		// 50
	char*							VertexShaderTarget;			// 54
	NiD3DVertexShader*				VertexShader;				// 58
	UInt8							SoftwareVP;					// 5C
	UInt8							RendererOwned;				// 5D
	UInt8							pad[2];
	UInt32							RefCount;					// 60
};
assert(sizeof(NiD3DPass) == 0x064);

class NiShader : public NiRefObject {
public:
	char*		Name;					// 008
	UInt32		Unk00C;					// 00C
};
assert(sizeof(NiShader) == 0x010);

class NiD3DShaderInterface : public NiShader {
public:
	IDirect3DDevice9*	D3DDevice;		// 010
	NiDX9Renderer*		D3DRenderer;	// 014
	NiDX9RenderState*	D3DRenderState;	// 018
	UInt8				Unk01C;			// 01C
	UInt8				Unk01D;			// 01D
	UInt8				pad[2];
};
assert(sizeof(NiD3DShaderInterface) == 0x020);

class NiD3DShader : public NiD3DShaderInterface {
public:
	UInt8					IsInitialized;		// 020
	UInt8					Unk021;				// 021
	UInt8					pad021[2];
	NiD3DShaderDeclaration* ShaderDeclaration;	// 024
	NiD3DRenderStateGroup*  RenderStateGroup;	// 028
	NiD3DShaderConstantMap* PixelConstantMap;	// 02C
	NiD3DShaderConstantMap* VertexConstantMap;	// 030
	UInt32					CurrentPassIndex;	// 034
	UInt32					PassCount;			// 038
	NiD3DPass* CurrentPass;		// 03C
	NiTArray<NiD3DPass*>	Passes;				// 040
	UInt32					Unk050[8];			// 050
};
assert(sizeof(NiD3DShader) == 0x70);

class BSShader : public NiD3DShader {
public:
	UInt32		Unk070;			// 070
	UInt32		Unk074;			// 074
	UInt32		Unk078;			// 078
};
assert(sizeof(BSShader) == 0x7C);

class GeometryDecalShader : public BSShader {
public:
	UInt32				Unk07C[2];		// 07C
	NiD3DVertexShader*	Vertex[2];		// 084
	NiD3DPixelShader*	Pixel[2];		// 08C
	UInt32				Unk104[3];		// 094
};
assert(sizeof(GeometryDecalShader) == 0x0A0);

class WaterShader : public BSShader {
public:
	UInt32				Unk07C[16];		// 07C
	NiD3DVertexShader*	Vertex[2];		// 0BC
	NiD3DPixelShader*	Pixel[16];		// 0C4
	UInt32				Unk104[5];		// 104
};
assert(sizeof(WaterShader) == 0x118);

class TallGrassShader : public BSShader {
public:
	UInt32				Unk07C[6];			// 07C
	NiD3DVertexShader*	Vertex1[20];		// 094 Vertex1 + Vertex2 are a unique array but we split it for fast use (1 are compiled 1_1 and 2 are compiled 2_0)
	NiD3DVertexShader*	Vertex2[20];		// 0E4
	NiD3DPixelShader*	Pixel1[2];			// 134 Pixel1 + Pixel2 are a unique array but we split it for fast use (1 are compiled 1_1 and 2 are compiled 2_0)
	NiD3DPixelShader*	Pixel2[7];			// 13C
	float*				InstanceData;		// 158 Pointer to a struct of 912 floats (228 registers)
	UInt32				Unk15C;				// 15C
	UInt16				InstanceDataCount;	// 160
	UInt16				pad160;				// 162
	UInt32				Unk164[12];			// 164
};
assert(sizeof(TallGrassShader) == 0x194);

class BSImageSpaceShader : public BSShader {
public:
	UInt32		Unk07C;		// 07C
	UInt32		Unk080;		// 080
	UInt32		Unk084;		// 084
	UInt32		Unk088;		// 088
	UInt32		Unk08C;		// 08C
};
assert(sizeof(BSImageSpaceShader) == 0x90);

class WaterShaderDisplacement : public BSImageSpaceShader {
public:
	UInt32				Unk090[9];		// 090
	NiD3DVertexShader*	Vertex[8];		// 0B4
	NiD3DPixelShader*	Pixel[8];		// 0D4
	UInt32				Unk0F4[13];		// 0F4
};
assert(sizeof(WaterShaderDisplacement) == 0x128);

class WaterShaderHeightMap : public BSImageSpaceShader {
public:
	UInt32				Unk090[8];		// 090
	NiD3DVertexShader*	Vertex;			// 0B0
	NiD3DPixelShader*	Pixel[7];		// 0B4
	UInt32				Unk0D0[15];		// 0D0
};
assert(sizeof(WaterShaderHeightMap) == 0x10C);

class HDRShader : public BSImageSpaceShader {
public:
	NiD3DVertexShader*	Vertex[8];		// 090
	NiD3DPixelShader*	Pixel[8];		// 0B0
	UInt32				Unk0D0;			// 0D0
	UInt32				Unk0D4[13];		// 0D4
	UInt32				Unk108[7];		// 108
};
assert(sizeof(HDRShader) == 0x124);

class SpeedTreeLeafShader : public BSShader {
public:
	NiVector4			LeafData[48];	// 07C
	NiD3DVertexShader*	Vertex[4];		// 37C
	NiD3DPixelShader*	Pixel[2];		// 38C
	UInt32				Unk394;			// 394
};
assert(sizeof(SpeedTreeLeafShader) == 0x398);

class ShadowLightShader : public BSShader {
public:
	UInt32				Unk07C[8];		// 07C
};
assert(sizeof(ShadowLightShader) == 0x09C);

class ParallaxShader : public ShadowLightShader {
public:
	NiD3DVertexShader* Vertex[36];		// 09C
	NiD3DPixelShader* Pixel[30];		// 12C
};
assert(sizeof(ParallaxShader) == 0x1A4);

class SkinShader : public ShadowLightShader {
public:
	NiD3DVertexShader* Vertex[20];		// 09C
	NiD3DPixelShader* Pixel[10];		// 0EC
};
assert(sizeof(SkinShader) == 0x114);

class ShaderDefinition {
public:
	NiDX9ShaderDeclaration* ShaderDeclaration;
	BSShader* Shader;
};
assert(sizeof(ShaderDefinition) == 0x008);

class Ni2DBuffer : public NiObject {
public:
	UInt32				width;	// 008
	UInt32				height;	// 00C
	NiDX92DBufferData*	data;	// 010
};
assert(sizeof(Ni2DBuffer) == 0x014);

class NiDepthStencilBuffer : public Ni2DBuffer {};
assert(sizeof(NiDepthStencilBuffer) == 0x014);

class NiDX92DBufferData : public NiRefObject {
public:
	virtual UInt32		GetWidth();												// 01
	virtual UInt32		GetHeight();											// 02
	virtual void*		GetVar10();												// 03
	virtual NiRTTI*		GetRTTI();												// 04
	virtual	UInt32		func05();												// 05
	virtual	UInt32		func06();												// 06
	virtual UInt32		func07();												// 07
	virtual UInt32		func08();												// 08
	virtual UInt32		func09();												// 09
	virtual UInt32		func0A();												// 0A
	virtual bool		ReleaseSurface1();										// 0B
	virtual bool		GetBufferData(IDirect3DDevice9* D3DDevice);					// 0C
	virtual bool		SetRenderTarget(IDirect3DDevice9* D3DDevice, UInt32 Index);	// 0D
	virtual bool		SetDepthTarget(IDirect3DDevice9* D3DDevice);				// 0E
	virtual void		ReleaseSurface2();										// 0F

	Ni2DBuffer*			ParentData;												// 08
	IDirect3DSurface9*	Surface;												// 0C
};
assert(sizeof(NiDX92DBufferData) == 0x010);

class NiDX9ImplicitBufferData : public NiDX92DBufferData {
public:
	NiPixelFormat*			PixelFormat;								// 10
	D3DPRESENT_PARAMETERS	PresentParams;								// 14
	IDirect3DDevice9*		Device;										// 4C
};
assert(sizeof(NiDX9ImplicitBufferData) == 0x050);

class NiDX9ImplicitDepthStencilBufferData : public NiDX92DBufferData { };
assert(sizeof(NiDX9ImplicitDepthStencilBufferData) == 0x010);

class NiDX9TextureBufferData : public NiDX92DBufferData { };
assert(sizeof(NiDX9TextureBufferData) == 0x010);

class NiRenderTargetGroup : public NiObject {
public:
	virtual UInt32					GetWidth(UInt32 Index);											// 13
	virtual UInt32					GetHeight(UInt32 Index);										// 14
	virtual UInt32					GetDepthStencilWidth();											// 15
	virtual UInt32					GetDepthStencilHeight();										// 16
	virtual const NiPixelFormat*	GetPixelFormat(UInt32 Index);									// 17
	virtual const NiPixelFormat*	GetDepthStencilPixelFormat();									// 18
	virtual UInt32					GetBufferCount();												// 19
	virtual bool					AttachBuffer(Ni2DBuffer* Buffer, UInt32 Index);					// 1A
	virtual bool					AttachDepthStencilBuffer(NiDepthStencilBuffer* DepthBuffer);	// 1B
	virtual Ni2DBuffer*				GetBuffer(UInt32 Index);										// 1C
	virtual NiDepthStencilBuffer*	GetDepthStencilBuffer();										// 1D
	virtual void*					GetRendererData();												// 1E
	virtual void					SetRendererData(void* RendererData);							// 1F
	virtual void*					GetRenderTargetData(UInt32 RenderTargetIndex);					// 20
	virtual void*					GetDepthStencilBufferRendererData();							// 21

	Ni2DBuffer*						RenderTargets[4];			// 08
	UInt32							numRenderTargets;			// 18
	NiDepthStencilBuffer*			DepthStencilBuffer;			// 1C
	void*							RenderData;					// 20
};
assert(sizeof(NiRenderTargetGroup) == 0x024);

class NiDX9RenderState : public NiRefObject {
public:
	virtual void						 UpdateRenderState(const NiPropertyState* pkNew);							// 01
	virtual void						 SetAlpha(void* AlphaProperty);												// 02
	virtual void						 SetDither(void* DitherProperty);											// 03
	virtual void						 SetFog(NiFogProperty* FogProperty);										// 04
	virtual void						 SetMaterial(void* u1);														// 05
	virtual void						 SetShadeMode(void* ShadeProperty);											// 06
	virtual void						 SetSpecular(void* SpecularProperty);										// 07
	virtual void						 SetStencil(void* StencilProperty);											// 08
	virtual void						 SetWireframe(void* WireframeProperty);										// 09
	virtual void 						 SetZBuffer(void* ZBufferProperty);											// 0A
	virtual void						 RestoreAlpha();															// 0B
	virtual void						 SetVertexBlending(UInt16 u1);												// 0C
	virtual void						 SetNormalization(void* u1);												// 0D
	virtual void						 func_0E(UInt32 u1);														// 0E - doesn't do anything
	virtual float						 GetVar088();																// 0F
	virtual void						 func_10(float u1);															// 10
	virtual void						 func_11(float u1, float u2);												// 11
	virtual BOOL						 GetLeftHanded();															// 12
	virtual void						 func_13(BOOL u1);															// 13
	virtual void						 func_14(UInt32 u1);														// 14
	virtual void						 InitializeRenderStates();													// 15
	virtual void						 BackUpAllStates();															// 16
	virtual void 						 RestoreRenderState(D3DRENDERSTATETYPE state);								// 17
	virtual void						 RestoreAllRenderStates();													// 18
	virtual void 						 SetRenderState(D3DRENDERSTATETYPE state, UInt32 value, UInt8 BackUp);		// 19
	virtual UInt32						 GetRenderState(D3DRENDERSTATETYPE state);									// 1A
	virtual void						 ClearPixelShaders();														// 1B
	virtual void						 BackUpPixelShader();														// 1C
	virtual void						 func_1D();																	// 1D
	virtual void						 SetPixelShader(IDirect3DPixelShader9* PixelShader, UInt8 BackUp);			// 1E
	virtual IDirect3DPixelShader9*		 GetPixelShader();															// 1F
	virtual	void						 RestorePixelShader();														// 20
	virtual void						 RemovePixelShader(IDirect3DPixelShader9* PixelShader);						// 21
	virtual void						 SetVertexShader(IDirect3DVertexShader9* pShader, UInt8 BackUp);			// 22
	virtual IDirect3DVertexShader9*		 GetVertexShader();															// 23
	virtual void						 RestoreVertexShader();														// 24
	virtual void						 RemoveVertexShader(IDirect3DVertexShader9* pShader);						// 25
	virtual void						 SetFVF(UInt32 FVF, UInt8 BackUp);											// 26
	virtual UInt32						 GetFVF();																	// 27
	virtual void						 RestoreFVF();																// 28
	virtual void						 ClearFVF(UInt32 FVF);														// 29
	virtual void						 SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl, UInt8 BackUp);	// 2A
	virtual IDirect3DVertexDeclaration9* GetVertexDeclaration();													// 2B
	virtual void						 RestoreVertexDeclaration();												// 2C
	virtual void						 ClearVertexDeclatation(IDirect3DVertexDeclaration9* pDecl);				// 2D
	virtual void						 func_02E();																// 2E
	virtual void						 func_02F();																// 2F
	virtual void						 func_030();																// 30
	virtual void						 func_031();																// 31
	virtual void 						 SetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type, UInt32 Value, UInt8 BackUp);	// 32
	virtual UInt32						 GetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type);								// 33
	virtual void						 SetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 BackUp);			// 34
	virtual UInt32 						 GetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);										// 35
	virtual void						 RestoreSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);									// 36
	virtual void						 ClearTextureList();																			// 37
	virtual void						 SetTexture(UInt32 Sampler, IDirect3DBaseTexture9* pTexture);									// 38
	virtual IDirect3DBaseTexture9*		 GetTexture(UInt32 Sampler);																	// 39
	virtual void						 RemoveTexture(IDirect3DBaseTexture9* pTexture);												// 3A
	virtual void						 SetSoftwareVertexProcessing(UInt8 bSoftware);													// 3B
	virtual UInt8						 GetSoftwareVertexProcessing();																	// 3C
	virtual void						 SetVar_0FF4(UInt8 u1);																			// 3D
	virtual UInt8						 GetVar_0FF4();																					// 3E
	virtual void						 SetVar_0FF5(UInt8 u1);																			// 3F
	virtual UInt8						 GetVar_0FF5();																					// 40
	virtual void						 Reset();																						// 41
	virtual void						 func_042();																					// 42

	struct NiRenderStateSetting {
		UInt32 CurrentValue;
		UInt32 PreviousValue;
	};

	UInt32							Flags;							// 0008
	UInt32							unk000C[(0x0074 - 0x000C) >> 2];// 000C
	NiAlphaProperty*				DisabledAlphaProperty;			// 0074
	float							CameraNear;						// 0078
	float							CameraFar;						// 007C
	float							CameraDepthRange;				// 0080
	float							MaxFogFactor;					// 0084
	float							MaxFogValue;					// 0088
	NiColor							CurrentFogColor;				// 008C
	UInt32							unk098[23];						// 0098
	UInt32							LeftHanded;						// 00F4
	UInt32							unk0F8[10];						// 00F8
	NiRenderStateSetting			RenderStateSettings[256];		// 0120
	NiRenderStateSetting			TextureStageStateSettings[128];	// 0920
	NiRenderStateSetting			SamplerStateSettings[80];		// 0D20
	UInt32							unk0FA0[(0x0FF0 - 0x0FA0) >> 2];// 0FA0
	NiDX9ShaderConstantManager*		ShaderConstantManager;			// 0FF0
	UInt8							ForceNormalizeNormals;			// 0FF4
	UInt8							InternalNormalizeNormals;		// 0FF5
	UInt8							UsingSoftwareVP;				// 0FF6
	UInt8							Declaration;					// 0FF7
	IDirect3DDevice9*				Device;							// 0FF8
	NiDX9Renderer*					Renderer;						// 0FFC
	UInt32							unk1000[(0x1018 - 0x1000) >> 2];// 1000
	D3DCAPS9						Caps;							// 1018
};
assert(offsetof(NiDX9RenderState, Device) == 0x0FF8);
assert(sizeof(NiDX9RenderState) == 0x1148);

class NiAccumulator : public NiObject {
public:
	virtual void	Start(NiCamera* camera);
	virtual void	Stop();
	virtual void	Add(NiVisibleArray* list);
	virtual bool	Fn_16();

	NiCamera*		camera;	// 08
};
assert(sizeof(NiAccumulator) == 0x00C);

class NiRenderer : public NiObject {
public:
	enum ClearFlags {
		kClear_BACKBUFFER	= 0x1,
		kClear_STENCIL		= 0x2,
		kClear_ZBUFFER		= 0x4,
		kClear_NONE			= 0,
		kClear_ALL			= kClear_BACKBUFFER | kClear_STENCIL | kClear_ZBUFFER
	};

	enum {
		kCopyFilterMode_None = 0,
		kCopyFilterMode_Point,
		kCopyFilterMode_Linear,
	};

	virtual bool			Unk_13(UInt32 arg);
	virtual const char*		GetRendererDesc();	// builds a string "<adapter id> (<dev type>-<dev flags>)"
	virtual UInt32			GetFlags();
	virtual void			SetClearDepth(float arg);
	virtual float			GetClearDepth();
	virtual void			SetClearColor4(float* src);
	virtual void			SetClearColor3(float* src);
	virtual void			GetClearColor(float* dst);
	virtual void			SetClearStencil(UInt32 src);
	virtual UInt32			GetClearStencil();
	virtual bool			Unk_1D(NiRenderTargetGroup* renderTarget);
	virtual void			Unk_1E();
	virtual NiRenderTargetGroup* GetDefaultRT();	// get back buffer rt
	virtual NiRenderTargetGroup* GetCurrentRT();	// get currentRTGroup
	virtual UInt8			Unk_21();			// get unkA90 (u8)
	virtual void			Unk_22();			// passthrough to currentRTGroup2->Fn1D
	virtual void			Unk_23();			// currentRTGroup2->Fn1C(0);
	virtual void			Unk_24(UInt32 arg);		// sub_773960(arg, &unk6F4);
	virtual void*			Unk_25(void* arg0, UInt32 arg1, UInt32 arg2);	// something with pixel format conversion
	virtual void*			Unk_26(void* arg);			// Unk_25(arg, 0x20, 8) - something with pixel format conversion
	virtual UInt32			Unk_27();			// get unk894 - current/max num render targets?
	virtual UInt32			Unk_28();			// get unk898
	virtual void			Unk_29();			// passthrough to textureManager->Fn03
	virtual bool			Unk_2A(UInt32 arg);		// set dword_B42050, return true
	virtual UInt32			Unk_2B();			// get dword_B42050
	virtual bool			Unk_2C(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual void			PurgeGeometry(NiGeometryData* geo);
	virtual void			PurgeMaterial(NiMaterialProperty* material);			// passthrough to renderState->DeleteMaterial
	virtual void			PurgeEffect(NiDynamicEffect* effect);
	virtual void			PurgeScreenTexture();
	virtual void			PurgeSkinPartition(NiSkinPartition* skinPartition);
	virtual void			PurgeSkinInstance(NiSkinInstance* skinInstance);
	virtual void			Unk_33();
	virtual bool			Unk_34();
	virtual void			Unk_35();
	virtual bool			FastCopy(void* src, void* dst, RECT* srcRect, SInt32 xOffset, SInt32 yOffset);
	virtual bool			Copy(void* src, void* dst, RECT* srcRect, RECT* dstRect, UInt32 filterMode);
	virtual void			Unk_38();			// passthrough to renderState->Fn12
	virtual bool			Unk_39(void* arg);		// renderState->Fn13(arg);
	virtual void			Unk_3A();			// passthrough to renderState->Fn0F
	virtual void			Unk_3B(float arg);		// renderState->Fn10(arg);
	virtual void*			Unk_3C(UInt32 size);	// FormHeap_Allocate(size);
	virtual void			Unk_3D(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_3E(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_3F(void* buf);		// FormHeap_Free(buf);
	virtual bool			Unk_40(UInt32 arg0);
	virtual void			CreateSourceTexture(NiSourceTexture* texture);			// locks cs2
	virtual bool			CreateRenderedTexture(NiRenderedTexture* arg);	// make a NiDX9RenderedTextureData, store it in unk8C0
	virtual bool			CreateSourceCubeMap(NiSourceCubeMap* arg);				// make a NiDX9SourceCubeMapData
	virtual bool			CreateRenderedCubeMap(NiRenderedCubeMap* arg);	// make a NiDX9RenderedCubeMapData, store it in unk8D0
	virtual bool			CreateDynamicTexture(void* arg);					// make a NiDX9DynamicTextureData, store it in unk8E0
	virtual void			CreatePalette(void* arg);
	virtual bool			CreateDepthStencil(NiDepthStencilBuffer* arg, void* textureFormat);
	virtual void			LockDynamicTexture(void* arg0, void* arg1);
	virtual void			UnLockDynamicTexture(void* arg);
	virtual void			LockRenderer();
	virtual void			UnlockRenderer();
	virtual bool			BeginScene();
	virtual bool			EndScene();
	virtual void			DisplayScene();
	virtual void			Clear(float* rect, UInt32 flags);
	virtual void			SetupCamera(NiPoint3* pos, NiPoint3* at, NiPoint3* up, NiPoint3* right, NiFrustum* frustum, float* viewport);
	virtual void			SetupScreenSpaceCamera(float* viewport);
	virtual bool			BeginUsingRenderTargetGroup(NiRenderTargetGroup* renderTarget, ClearFlags clearFlags);
	virtual bool			EndUsingRenderTargetGroup();
	virtual void			BeginBatch(UInt32 arg0, UInt32 arg1);	// set unk61C, unk620
	virtual void			EndBatch();
	virtual void			BatchRenderShape(void* arg);
	virtual void			BatchRenderStrips(void* arg);
	virtual void			RenderTriShape(NiTriShape* obj);
	virtual void			RenderTriStrips(NiTriStrips* obj);		// points to the same function as above
	virtual void			RenderTriShape2(NiTriShape* obj);		// calls DrawIndexedPrimitive
	virtual void			RenderTriStrips2(NiTriStrips* obj);	// calls DIP/DP
	virtual void			RenderParticles(NiParticles* obj);
	virtual void			RenderLines(NiLines* obj);				// calls DIP/SetStreamSource/SetIndices
	virtual void			RenderScreenTexture();

	// 080
	struct CriticalSection {
		CRITICAL_SECTION	cs;								// 000
		UInt32				pad018[(0x078 - 0x018) >> 2];	// 018
		UInt32				curThread;						// 078
		UInt32				entryCount;						// 07C
	};

	NiAccumulator*			accumulator;					// 008 BSShaderAccumulator
	NiPropertyState*		propertyState;					// 00C
	NiDynamicEffectState*	dynamicEffectState;				// 010
	UInt32					pad014[(0x080 - 0x014) >> 2];	// 00C
	CriticalSection			RendererLock;					// 080
	CriticalSection			PrecacheCriticalSection;		// 100
	CriticalSection			SourceDataCriticalSection;		// 180
	UInt32					unk200;							// 200
	UInt32					unk204;							// 204
	UInt32					unk208;							// 208
	UInt8					unk20C;							// 20C
	UInt8					unk20D;							// 20D
	UInt8					pad20E[2];						// 20E
};
assert(sizeof(NiRenderer) == 0x210);

class NiDX9Renderer : public NiRenderer {
public:
	class PrePackObject;

	// 58
	class Unk6F4 {
	public:
		UInt32	unk00;
		UInt32	unk04;
		UInt32	unk08;
		UInt32	unk0C;
		UInt32	unk10;
		UInt32	unk14;
		UInt32	unk18;
		UInt32	unk1C;
		UInt32	unk20;
		UInt32	unk24;
		UInt32	unk28;
		UInt32	unk2C;
		UInt32	unk30;
		UInt32	unk34;
		UInt32	unk38;
		UInt32	unk3C;
		UInt32	unk40;
		UInt32	unk44;
		UInt32	unk48;
		UInt32	unk4C;
		UInt32	unk50;
		UInt32	unk54;
	};

	enum FrameBufferFormat {
		FBFMT_UNKNOWN = 0,
		FBFMT_R8G8B8,
		FBFMT_A8R8G8B8,
		FBFMT_X8R8G8B8,
		FBFMT_R5G6B5,
		FBFMT_X1R5G5B5,
		FBFMT_A1R5G5B5,
		FBFMT_A4R4G4B4,
		FBFMT_R3G3B2,
		FBFMT_A8,
		FBFMT_A8R3G3B2,
		FBFMT_X4R4G4B4,
		FBFMT_R16F,
		FBFMT_G16R16F,
		FBFMT_A16B16G16R16F,
		FBFMT_R32F,
		FBFMT_G32R32F,
		FBFMT_A32B32G32R32F,
		FBFMT_NUM
	};

	enum DepthStencilFormat {
		DSFMT_UNKNOWN = 0,
		DSFMT_D16_LOCKABLE = 70,
		DSFMT_D32 = 71,
		DSFMT_D15S1 = 73,
		DSFMT_D24S8 = 75,
		DSFMT_D16 = 80,
		DSFMT_D24X8 = 77,
		DSFMT_D24X4S4 = 79,
	};

	enum PresentationInterval {
		PRESENT_INTERVAL_IMMEDIATE = 0,
		PRESENT_INTERVAL_ONE = 1,
		PRESENT_INTERVAL_TWO = 2,
		PRESENT_INTERVAL_THREE = 3,
		PRESENT_INTERVAL_FOUR = 4,
		PRESENT_INTERVAL_NUM
	};

	enum SwapEffect {
		SWAPEFFECT_DEFAULT,
		SWAPEFFECT_DISCARD,
		SWAPEFFECT_FLIP,
		SWAPEFFECT_COPY,
		SWAPEFFECT_NUM
	};

	enum FrameBufferMode {
		FBMODE_DEFAULT,
		FBMODE_LOCKABLE,
		FBMODE_MULTISAMPLES_2			= 0x00010000,
		FBMODE_MULTISAMPLES_3			= 0x00020000,
		FBMODE_MULTISAMPLES_4			= 0x00030000,
		FBMODE_MULTISAMPLES_5			= 0x00040000,
		FBMODE_MULTISAMPLES_6			= 0x00050000,
		FBMODE_MULTISAMPLES_7			= 0x00060000,
		FBMODE_MULTISAMPLES_8			= 0x00070000,
		FBMODE_MULTISAMPLES_9			= 0x00080000,
		FBMODE_MULTISAMPLES_10			= 0x00090000,
		FBMODE_MULTISAMPLES_11			= 0x000a0000,
		FBMODE_MULTISAMPLES_12			= 0x000b0000,
		FBMODE_MULTISAMPLES_13			= 0x000c0000,
		FBMODE_MULTISAMPLES_14			= 0x000d0000,
		FBMODE_MULTISAMPLES_15			= 0x000e0000,
		FBMODE_MULTISAMPLES_16			= 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK				= 0x0000FFFF,
		FBMODE_NUM						= 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};

	virtual bool		DeleteRenderedCubeMap(NiRenderedCubeMap* arg);
	virtual bool		DeleteTexture(NiTexture* arg);					
	virtual bool		DeleteDynamicTexture(UInt32 arg);		

	void				PackGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiD3DShaderDeclaration* ShaderDeclaration) { ThisCall(0x00767B40, this, GeoData, ModelData, SkinInstance, ShaderDeclaration, 0); }
	void				PackSkinnedGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition, NiD3DShaderDeclaration* ShaderDeclaration) { ThisCall(0x00763130, this, GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration, 0); }
	void				CalculateBoneMatrixes(NiSkinInstance* SkinInstance, NiTransform* WorldTrasform) { ThisCall(0x007655F0, this, SkinInstance, WorldTrasform, false, 3, true); }

	UInt32								pad210[(0x280 - 0x210) >> 2];	// 210
	IDirect3DDevice9*					device;							// 280
	D3DCAPS9							caps;							// 284
	HANDLE								deviceWindow;					// 3B4
	HANDLE								focusWindow;					// 3B8
	char								rendererInfo[0x200];			// 3BC
	UInt32								adapterIdx;						// 5BC
	UInt32								d3dDevType;						// 5C0 - D3DDEVTYPE
	UInt32								d3dDevFlags;					// 5C4 - D3DCREATE
	UInt8								softwareVertexProcessing;		// 5C8 - !D3DCREATE_HARDWARE_VERTEXPROCESSING
	UInt8								mixedVertexProcessing;			// 5C9 - D3DCREATE_MIXED_VERTEXPROCESSING
	UInt8								pad5CA[2];						// 5CA
	NiDX9AdapterDesc*					adapterDesc;					// 5CC
	NiDX9DeviceDesc*					deviceDesc;						// 5D0
	D3DCOLOR							clearColor;						// 5D4
	float								clearDepth;						// 5D8
	UInt32								clearStencil;					// 5DC
	UInt32								rendFlags;						// 5E0
	char								behavior[32];					// 5E4
	NiTMap<void*, PrePackObject*>		PrePackObjects;					// 604 - NiTPointerMap <NiVBBlock *, NiDX9Renderer::PrePackObject *>
	UInt32								pad624[(0x648 - 0x614) >> 2];	// 614
	NiPoint3							camRight;						// 648
	NiPoint3							camUp;							// 654
	NiPoint3							modelCamRight;					// 660
	NiPoint3							modelCamUp;						// 66C
	float								NearDepth;						// 678
	float								DepthRange;						// 67C
	D3DMATRIX							identityMatrix;					// 680
	D3DVIEWPORT9						viewport;						// 6C0
	UInt32								HWBones;						// 6D8
	UInt32								MaxStreams;						// 6DC
	UInt32								Unk6E0;							// 6E0
	UInt32								Unk6E4;							// 6E4
	UInt8								pad6E8;							// 6E8
	UInt8								unk6E9;							// 6E9
	UInt8								pad6EA[2];						// 6EA
	UInt32								ResetCounter;					// 6EC
	UInt8								lostDevice;						// 6F0 - disables drawing
	UInt8								pad6F1[3];						// 6F1
	Unk6F4								unk6F4[4];						// 6F4
	UInt32								DefaultTextureFormat[4];		// 854 //NiPixelFormat*
	NiPixelData*						DefaultTextureData[4];			// 864
	UInt32								unk874;							// 874 - init'd to 0x16
	NiRenderTargetGroup*				defaultRTGroup;					// 878 - probably back buffer
	NiRenderTargetGroup*				currentRTGroup;					// 87C
	NiRenderTargetGroup*				currentscreenRTGroup;			// 880
	NiTMap<HWND*, NiRenderTargetGroup*>	screenRTGroups;					// 884 - NiTPointerMap <HWND *, NiPointer <NiRenderTargetGroup> >
	UInt32								unk894;							// 894
	UInt8								unk898;							// 898
	UInt8								pad899[3];						// 899
	NiObject*							unk89C;							// 89C - NiPropertyState (0x30)
	NiGeometryGroupManager*				geometryGroupMgr;				// 8A0
	NiGeometryGroup*					unk8A4;							// 8A4 - NiUnsharedGeometryGroup
	NiGeometryGroup*					unk8A8;							// 8A8 - NiDynamicGeometryGroup
	NiDX9RenderState*					renderState;					// 8AC
	NiDX9VertexBufferManager*			vertexBufferMgr;				// 8B0
	NiDX9IndexBufferManager*			indexBufferMgr;					// 8B4
	NiDX9TextureManager*				textureMgr;						// 8B8
	NiDX9LightManager*					lightMgr;						// 8BC
	NiTMap<NiRenderedTexture*, NiDX9RenderedTextureData*>	renderedTextures;				// 8C0 - NiTPointerMap <NiRenderedTexture *, NiDX9RenderedTextureData *>
	NiTMap<NiRenderedCubeMap*, NiDX9RenderedCubeMapData*>	renderedCubeMaps;				// 8D0 - NiTPointerMap <NiRenderedCubeMap *, NiDX9RenderedCubeMapData *>
	NiTMap<void* , NiDX9DynamicTextureData*>	dynamicTextures;				// 8E0 - NiTPointerMap <NiDynamicTexture *, NiDX9DynamicTextureData *>
	NiTexture*							ClipperImage;					// 8F0
	NiTList <NiDX92DBufferData*>		atDisplayFrame;					// 8F4
	NiTList <NiD3DShaderInterface*>		shaderInterfaces;				// 904
	UInt32								Unk914;							// 914
	UInt32								Unk918;							// 918
	UInt32								Unk91C;							// 91C
	UInt32								Unk920;							// 920
	UInt32								Unk924;							// 924
	UInt32								Unk928;							// 928
	UInt32								Unk92C;							// 92C
	UInt32								Unk930;							// 930
	UInt32								Unk934;							// 934
	UInt32								Unk938;							// 938
	UInt32								Unk93C;							// 93C
	D3DXMATRIXA16						worldMatrix;					// 940
	D3DMATRIX							viewMatrix;						// 980
	D3DMATRIX							projMatrix;						// 9C0
	D3DMATRIX							invViewMatrix;					// A00
	UInt32								ScreenTextureVerts;				// A40 NiPoint2*
	NiColorAlpha*						ScreenTextureColors;			// A44
	UInt32								ScreenTextureTexCoords;			// A48 NiPoint2*
	UInt16								unkA4C;							// A4C
	UInt8								unkA4E[2];						// A4E
	UInt16*								ScreenTextureIndices;			// A50
	UInt32								NumScreenTextureIndices;		// A54
	UInt32								width;							// A58
	UInt32								height;							// A5C
	UInt32								flags;							// A60
	UInt32								windowDevice;					// A64
	UInt32								windowFocus;					// A68
	UInt32								adapterType;					// A6C
	UInt32								deviceType;						// A70
	FrameBufferFormat					frameBufferFormat;				// A74
	DepthStencilFormat					depthStencilFormat;				// A78
	PresentationInterval				presentationInterval;			// A7C
	SwapEffect							swapEffect;						// A80
	FrameBufferMode						frameBufferMode;				// A84
	UInt32								backBufferCount;				// A88
	RefreshRate							refreshRate;					// A8C
	UInt8								unkA90;							// A90
	UInt8								padA91[3];						// A91
	NiD3DShader*						defaultShader;					// A94
	NiTArray <void>						unkA98;							// A98 Callback
	NiTArray <void*>					unkAA8;							// AA8
	NiTArray <void>						lostDeviceCallbacks;			// AB8 LostDeviceCallback
	NiTArray <void*>					lostDeviceCallbacksRefcons;		// AC8
	UInt32								padAD0[(0xB00 - 0xAD8) >> 2];	// AD8
};
assert(offsetof(NiDX9Renderer, device) == 0x280);
assert(offsetof(NiDX9Renderer, viewport) == 0x6C0);
assert(offsetof(NiDX9Renderer, height) == 0xA5C);
assert(sizeof(NiDX9Renderer) == 0xB00);

class NiControllerSequence : public NiObject {
public:
	enum {
		kState_Inactive = 0,
		kState_Animating,
		kState_EaseIn,
		kState_EaseOut,
		kState_TransSource,
		kState_TransDest,
		kState_MorphSource
	};

	enum {
		kCycle_Loop = 0,
		kCycle_Reverse,
		kCycle_Clamp,
	};

	struct ArrayItem {
		NiRefObject*	unk00;		// 00
		NiRefObject*	unk04;		// 04
		UInt32			unk08;		// 08
		UInt8			unk0C;		// 0C
		UInt8			pad0C[3];
	};

	struct Unk018 {
		NiRefObject* unk00;	// 00
		UInt16		unk04;		// 04
		UInt16		unk06;		// 06
		UInt16		unk08;		// 08
		UInt16		unk0A;		// 0A
		UInt16		unk0C;		// 0C
		UInt8		pad0E[2];	// 0E
	};

	char*				 filePath;		// 008
	UInt32				 arraySize;		// 00C
	UInt32				 arrayGrowBy;	// 010
	ArrayItem*			 interpArray;	// 014
	Unk018*				 unk018;		// 018
	float				 weight;		// 01C
	NiTextKeyExtraData*  TextKeys;		// 020
	UInt32				 cycleType;		// 024
	float				 freq;			// 028
	float				 beginkey;		// 02C
	float				 endkey;		// 030
	float				 last;			// 034
	float				 weightLast;	// 038
	float				 lastScaled;	// 03C
	NiControllerManager* controllerMgr; // 040
	UInt32				 state;			// 044
	float				 offset;		// 048
	float				 start;			// 04C - offset * -1?
	float				 end;			// 050
	UInt32				 unk054;		// 054
	UInt32				 unk058;		// 058
	char*				 accumRootName;	// 05C
	NiAVObject*			 accumRoot;		// 060
	NiStringPalette*	 unk064;		// 064
};
assert(sizeof(NiControllerSequence) == 0x068);

class NiAVObjectPalette : public NiObject { };
assert(sizeof(NiAVObjectPalette) == 0x008);

class NiDefaultAVObjectPalette : public NiAVObjectPalette {
public:
	NiTMap<void*, NiAVObject>	avObjectMap;	// 008
	UInt32						unk018;			// 018
	NiNode*						niNode;			// 01C
};
assert(sizeof(NiDefaultAVObjectPalette) == 0x020);

class NiProperty : public NiObjectNET {
public:
	enum {
		kType_Alpha,
		kType_Dither,
		kType_Fog,
		kType_Material,
		kType_RendSpec,
		kType_Shade,
		kType_Specular,
		kType_Stencil,
		kType_Texturing,
		kType_VertexColor,
		kType_WireFrame,
		kType_ZBuffer,
		kType_MAXTYPES
	};

	virtual UInt32	GetPropertyType();
	virtual void	Update(float unk0);
};
assert(sizeof(NiProperty) == 0x018);

class NiShadeProperty : public NiProperty {
public:
	virtual UInt32 Unk_15();

	UInt16	flags;		// 018
	UInt8	pad01A[2];	// 01A
};
assert(sizeof(NiShadeProperty) == 0x01C);

class NiPropertyState : public NiRefObject {
public:
	NiProperty* prop[10]; // 008
	//  0 08
	//  1 0C
	//  2 10
	//  3 14
	//  4 18
	//  5 1C
	//  6 20
	//  7 24
	//  8 28
	//  9 2C
};
assert(sizeof(NiPropertyState) == 0x030);

#endif