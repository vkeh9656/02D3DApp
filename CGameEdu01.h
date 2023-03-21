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
	D3DXVECTOR3 vMin, vMax;		// �浹 ��ǥ
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

	// ���ΰ� �浹 ��ǥ
	D3DXVECTOR3 vMin, vMax;
};

struct ENEMY
{
	int nLife;				// ����
	DWORD dwAppearTime;		// ���� �ð�
	D3DXVECTOR3 vPos;

	DWORD dwOldFireTime;	// �̻��� �߻� ���� �ð�
	D3DXMATRIX matTranslation;	// �̵� ���
};

struct  ENEMY_PROPERTY
{
	float fMoveVelocity;	// �ӷ�
	float fScale;			// ũ��

	DWORD dwFireTime;		// �̻��� �߻� �ð� ����
	D3DXMATRIX matScale;	// ũ��
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

	LPD3DXMESH m_pTeapotMesh;		// ���ΰ�
	LPD3DXMESH m_pPlayerBulletMesh;	// ���ΰ� �̻��� (�����)
	LPD3DXMESH m_pEnemyBoxMesh;		// ��
	LPD3DXMESH m_pEnemyBulletMesh;	// �� �̻���

	// ���ΰ�
	PLAYER m_sPlayer;
	BULLET_PROPERTY m_sPlayerBulletProperty;	// ���ΰ� �̻��� ��ü �Ӽ�
	BULLET m_sPlayerBullet[10];					// ���ΰ� �̻��� ���� �Ӽ�
	
	// �� ĳ����
	ENEMY_PROPERTY m_EnemyProperty;
	ENEMY m_Enemy[100];							// �� ĳ���� 100��
	BULLET_PROPERTY m_EnemyBulletProperty;		// �� ĳ���� �̻��� ��ü �Ӽ�
	BULLET m_EnemyBullet[100];					// �� �̻���, memory pool ������� �˳��ϰ� Ȯ��
	int m_nEnemyIndex;							// �� ĳ���� ���� �ε���

	DWORD m_dwElapsedTime; // ������ ��� �ð�

	// �������� ����
	DWORD m_dwGameStartTime;
	DWORD m_dwGameElapsedTime;

	int m_nEnemyCount;
public:
	CGameEdu01(void);
	~CGameEdu01(void);
};