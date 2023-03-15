#pragma once
#include "CD3DApp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>
#include "CAxis.h"
#include "CGround.h"

struct SPHERE_PROPERTY
{
	D3DXVECTOR3 vTrans; // 중심점과 같은 역할(이동 벡터)
	float		fScaling;
	float		fRadius;
};

struct BOX_PROPERTY
{
	D3DXVECTOR3 vTrans; // 중심점과 같은 역할(이동 벡터)
	float		fScaling;
	D3DXVECTOR3	vMin, vMax;
};

struct BULLET
{
	int nLife;					// 생명
	D3DXVECTOR3 vPos;			// 이동
	D3DXMATRIX matTranslation;	// 이동 행렬
};

struct BULLET_PROPERTY
{
	float fBulletVelocity;		// 이동 속도
	float fScale;				// 크기
	D3DXMATRIX matScale;		// 크기 행렬
};

struct PLAYER
{
	int nLife;					// 생명
	D3DXVECTOR3 vPos;			// 이동
	float fScale;				// 크기
	float fRotationY;			// 회전
	float fVelocity;			// 속력
	DWORD dwBulletFireTime;		// 미사일 발사 시간 간격
	DWORD dwOldBulletFireTime;	// 이전 미사일 발사 시각 (연발 방지)

	D3DXMATRIX matWorld;		// 월드 행렬
	D3DXMATRIX matScale;		// 크기 행렬
	D3DXMATRIX matRotationY;	// 회전 행렬
	D3DXMATRIX matTranslation;	// 이동 행렬
};

class CGameEdu01 : public CD3DApp
{
//private:
	/*HWND m_hWnd;*/	// 아나 이 핸들때문에... 여기서 한번 더 선언해버리니까 부모클래스에 선언된 핸들을 못가져왔어..

private:
	virtual void OnInit();
	virtual void OnRender();
	virtual void OnUpdate();
	virtual void OnRelease();
	
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR3 m_Eye, m_At, m_Up;
	
	/*SPHERE_PROPERTY m_Sphere[2];*/
	BOX_PROPERTY m_Box[2];
	D3DXVECTOR3 m_vMin, m_vMax;
	BOOL m_bIsCollision;
	LPD3DXMESH m_pMesh;
	
	LPD3DXFONT m_pFont;

	CGround m_Ground;
	LPD3DXMESH m_pTeapotMesh;
	LPD3DXMESH m_pPlayerBulletMesh;

	// 주인공
	PLAYER m_sPlayer;
	BULLET_PROPERTY m_sPlayerBulletProperty;
	BULLET m_sPlayerBullet[10];
	

	// CAxis m_Axis;
	



	// float m_fScale;
	

	/*LPD3DXMESH m_pBoxMesh;
	LPD3DXMESH m_pSphereMesh;*/
	/*LPD3DXMESH m_pCylinderMesh;*/
	

	// 폰트
	 DWORD m_dwElapsedTime;
	/*LPD3DXFONT m_pFont;

	unsigned int m_nFPS, m_nFPSCount;*/

public:
	CGameEdu01(void);
	~CGameEdu01(void);
};