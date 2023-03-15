#pragma once
#include "CD3DApp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>
#include "CAxis.h"
#include "CGround.h"

struct SPHERE_PROPERTY
{
	D3DXVECTOR3 vTrans; // �߽����� ���� ����(�̵� ����)
	float		fScaling;
	float		fRadius;
};

struct BOX_PROPERTY
{
	D3DXVECTOR3 vTrans; // �߽����� ���� ����(�̵� ����)
	float		fScaling;
	D3DXVECTOR3	vMin, vMax;
};

struct BULLET
{
	int nLife;					// ����
	D3DXVECTOR3 vPos;			// �̵�
	D3DXMATRIX matTranslation;	// �̵� ���
};

struct BULLET_PROPERTY
{
	float fBulletVelocity;		// �̵� �ӵ�
	float fScale;				// ũ��
	D3DXMATRIX matScale;		// ũ�� ���
};

struct PLAYER
{
	int nLife;					// ����
	D3DXVECTOR3 vPos;			// �̵�
	float fScale;				// ũ��
	float fRotationY;			// ȸ��
	float fVelocity;			// �ӷ�
	DWORD dwBulletFireTime;		// �̻��� �߻� �ð� ����
	DWORD dwOldBulletFireTime;	// ���� �̻��� �߻� �ð� (���� ����)

	D3DXMATRIX matWorld;		// ���� ���
	D3DXMATRIX matScale;		// ũ�� ���
	D3DXMATRIX matRotationY;	// ȸ�� ���
	D3DXMATRIX matTranslation;	// �̵� ���
};

class CGameEdu01 : public CD3DApp
{
//private:
	/*HWND m_hWnd;*/	// �Ƴ� �� �ڵ鶧����... ���⼭ �ѹ� �� �����ع����ϱ� �θ�Ŭ������ ����� �ڵ��� �������Ծ�..

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

	// ���ΰ�
	PLAYER m_sPlayer;
	BULLET_PROPERTY m_sPlayerBulletProperty;
	BULLET m_sPlayerBullet[10];
	

	// CAxis m_Axis;
	



	// float m_fScale;
	

	/*LPD3DXMESH m_pBoxMesh;
	LPD3DXMESH m_pSphereMesh;*/
	/*LPD3DXMESH m_pCylinderMesh;*/
	

	// ��Ʈ
	 DWORD m_dwElapsedTime;
	/*LPD3DXFONT m_pFont;

	unsigned int m_nFPS, m_nFPSCount;*/

public:
	CGameEdu01(void);
	~CGameEdu01(void);
};