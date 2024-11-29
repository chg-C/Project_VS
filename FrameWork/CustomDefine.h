#pragma once

#define PI 3.141925

#define D2R(degree) degree * ( PI / 180.0f )
#define R2D(radian) radian / ( PI * 180.0f )

#define MAPSIZE_X 1280
#define MAPSIZE_Y 1280

#define SAFE_DELETE(obj) if(obj != nullptr) { delete obj; obj = nullptr; }
#define SAFE_RELEASE(obj) if(obj != nullptr) { obj->Release(); obj = nullptr; }

struct TextureData {
	IDirect3DTexture9* Texture;
	D3DXIMAGE_INFO imagesinfo;
};