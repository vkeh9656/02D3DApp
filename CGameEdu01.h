#pragma once
#include "CD3DApp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>
#include "CAxis.h"
#include "CGround.h"


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
	CAxis m_Axis;
	CGround m_Ground;
	float m_fScale;
	LPD3DXMESH m_pTeapotMesh;

	/*LPD3DXMESH m_pBoxMesh;
	LPD3DXMESH m_pSphereMesh;*/
	/*LPD3DXMESH m_pCylinderMesh;*/
	

	// ��Ʈ
	LPD3DXFONT m_pFont;

	DWORD m_dwElapsedTime;
	unsigned int m_nFPS, m_nFPSCount;

public:
	CGameEdu01(void);
	~CGameEdu01(void);
};