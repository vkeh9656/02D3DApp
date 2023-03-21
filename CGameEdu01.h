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
	D3DXVECTOR3 vMin, vMax;		// 충돌 좌표
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

	// 주인공 충돌 좌표
	D3DXVECTOR3 vMin, vMax;
};

struct ENEMY
{
	int nLife;				// 생명
	DWORD dwAppearTime;		// 출현 시각
	D3DXVECTOR3 vPos;

	DWORD dwOldFireTime;	// 미사일 발사 이전 시간
	D3DXMATRIX matTranslation;	// 이동 행렬
};

struct  ENEMY_PROPERTY
{
	float fMoveVelocity;	// 속력
	float fScale;			// 크기

	DWORD dwFireTime;		// 미사일 발사 시간 간격
	D3DXMATRIX matScale;	// 크기
	D3DXVECTOR3 vMin, vMax;
};



class CGameEdu01 : public CD3DApp
{
//private:
	/*HWND m_hWnd;*/	

private:
	virtual void OnInit();
	virtual void OnRender();
	virtual void OnUpdate();
	virtual void OnRelease();
	
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR3 m_Eye, m_At, m_Up;
	
	CGround m_Ground;

	LPD3DXMESH m_pTeapotMesh;		// 주인공
	LPD3DXMESH m_pPlayerBulletMesh;	// 주인공 미사일 (원기둥)
	LPD3DXMESH m_pEnemyBoxMesh;		// 적
	LPD3DXMESH m_pEnemyBulletMesh;	// 적 미사일

	// 주인공
	PLAYER m_sPlayer;
	BULLET_PROPERTY m_sPlayerBulletProperty;	// 주인공 미사일 전체 속성
	BULLET m_sPlayerBullet[10];					// 주인공 미사일 개별 속성
	
	// 적 캐릭터
	ENEMY_PROPERTY m_EnemyProperty;
	ENEMY m_Enemy[100];							// 적 캐릭터 100개
	BULLET_PROPERTY m_EnemyBulletProperty;		// 적 캐릭터 미사일 전체 속성
	BULLET m_EnemyBullet[100];					// 적 미사일, memory pool 기법으로 넉넉하게 확보
	int m_nEnemyIndex;							// 적 캐릭터 출현 인덱스

	DWORD m_dwElapsedTime; // 프레임 경과 시간

	// 스테이지 정보
	DWORD m_dwGameStartTime;
	DWORD m_dwGameElapsedTime;

	int m_nEnemyCount;
public:
	CGameEdu01(void);
	~CGameEdu01(void);
};