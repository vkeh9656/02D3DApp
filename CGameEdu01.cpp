#include "CGameEdu01.h"
#include "stdio.h"

CGameEdu01::CGameEdu01(void)
{
}

CGameEdu01::~CGameEdu01(void)
{
}

BOOL CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2)
{
	float fDistance;
	D3DXVECTOR3 vDiff;

	vDiff = vCenter2 - vCenter1;
	fDistance = D3DXVec3Length(&vDiff);

	if (fDistance <= (fRadius1 + fRadius2))
		return TRUE; // 충돌
	return FALSE; // 비충돌
}


void CGameEdu01::OnInit()
{
	RECT rect;
	D3DVIEWPORT9 vp;
	GetClientRect(m_hWnd, &rect);

	vp.X = 0;
	vp.Y = 0;
	vp.Width = rect.right - rect.left;	// 좌표개념이 아니라 크기개념
	vp.Height = rect.bottom - rect.top;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;

	m_Eye.x = 0.0f; // 0
	m_Eye.y = 5.0f; // 0
	m_Eye.z = -30.0f;// 

	m_At.x = 0.0f;
	m_At.y = 0.0f;
	m_At.z = 0.0f;

	m_Up.x = 0.0f;
	m_Up.y = 1.0f;
	m_Up.z = 0.0f;

	D3DXMatrixLookAtLH(&m_matView, &m_Eye, &m_At, &m_Up);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	m_pd3dDevice->SetViewport(&vp);

	/*m_Axis.OnInit(m_pd3dDevice);*/
	//D3DXCreateBox(m_pd3dDevice, 2.0f, 2.0f, 2.0f, &m_pBoxMesh, NULL);
	/*D3DXCreateTeapot(m_pd3dDevice, &m_pTeapotMesh, NULL);*/
	//D3DXCreateCylinder(m_pd3dDevice, 2.0f, 2.0f, 5.0f, 100, 10, &m_pCylinderMesh, NULL);
	//D3DXCreateSphere(m_pd3dDevice, 3.0f, 30, 10, &m_pSphereMesh, NULL);
	//m_Ground.Create(m_pd3dDevice, 200, 100, 0.5);
	//m_fScale = 1.0f;

	D3DXCreateFont(m_pd3dDevice, 15, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		L"System", &m_pFont);

	D3DXCreateSphere(m_pd3dDevice, 1.0f, 20, 20, &m_pMesh, NULL);

	m_Sphere[0].fRadius = 1.0f;
	m_Sphere[0].fScaling = 1.0f;
	m_Sphere[0].vTrans = D3DXVECTOR3(0, 0, 0);

	m_Sphere[1].fRadius = 1.0f;
	m_Sphere[1].fScaling = 2.0f;
	m_Sphere[1].vTrans = D3DXVECTOR3(5, 0, 0);
	
	m_bIsCollision = FALSE;

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	
}

void CGameEdu01::OnRender()
{

	//D3DXMATRIX matScale;
	//D3DXMATRIX matRotation;
	//D3DXQUATERNION vQuaternion;
	/*D3DXMATRIX matRotationX, matRotationY, matRotationZ, matRotation;
	float fRotX, fRotY, fRotZ;

	fRotX = D3DXToRadian(45);
	fRotY = D3DXToRadian(45);
	fRotZ = D3DXToRadian(90);*/

	//D3DXMATRIX matTranslation;

	//D3DXVECTOR3 v1(1.0f, 1.0f, 0.0f);

	// 쿼터니온 회전
	// 쿼터니온으로 나온 값 자체로는 사용이 안됨. (행렬로 이 값을 바꿔줘야함.)
	//D3DXQuaternionRotationAxis(&vQuaternion, &v1, GetTickCount64() * 0.005f);
	//D3DXMatrixRotationQuaternion(&matRotation, &vQuaternion); // 쿼터니온 값을 행렬로 바꿔줌


	// S*R*T 연산 통합
	//D3DXMATRIX matRotationY, matWorld, matTrans, matScaling;
	//float fScaling[3] = { 0.3f, 0.6f, 1.0f };
	//D3DXVECTOR3 vTrans[3] = { D3DXVECTOR3(0.0f, 0.0f,0.0f), D3DXVECTOR3(2.0f, 0.0f,0.0f), D3DXVECTOR3(5.0f, 0.0f,0.0f) };
	//D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);



	//m_Axis.OnRender();
	//m_Cube.OnRender();

	//m_Ground.OnRender();
	
	//m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 크기 변환
	//D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);	
	
	// 고정 축 회전
	//D3DXMatrixRotationX(&matRotation, GetTickCount64() * 0.005f); // X축 회전
	//D3DXMatrixRotationY(&matRotation, GetTickCount64() * 0.005f); // Y축 회전
	//D3DXMatrixRotationZ(&matRotation, GetTickCount64() * 0.005f); // Z축 회전

	// 임의의 축 회전
	//D3DXMatrixRotationAxis(&matRotation, &v1, GetTickCount64() * 0.005f);

	//D3DXMatrixRotationX(&matRotationX, fRotX);
	//D3DXMatrixRotationY(&matRotationY, fRotY);
	//D3DXMatrixRotationZ(&matRotationZ, fRotZ);

	//D3DXMatrixRotationYawPitchRoll(&matRotation, fRotY, fRotX, fRotZ);
	//matRotation = matRotationZ * matRotationX * matRotationY;

	// 이동
	//D3DXMatrixTranslation(&matTranslation, 5.0f, 0.0f, 3.0f);


	//// SRT 통합
	//// 첫번째 Teapot
	//D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);
	//D3DXMatrixScaling(&matScaling, fScaling[0], fScaling[0], fScaling[0]);
	//D3DXMatrixTranslation(&matTrans, vTrans[0].x, vTrans[0].y, vTrans[0].z);
	//matWorld = matScaling * matRotationY * matTrans; // S*R*T
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//m_pTeapotMesh->DrawSubset(0);

	//// 두번째 Teapot
	//D3DXMatrixScaling(&matScaling, fScaling[1], fScaling[1], fScaling[1]);
	//D3DXMatrixTranslation(&matTrans, vTrans[1].x, vTrans[1].y, vTrans[1].z);
	//matWorld = matScaling * matRotationY * matTrans;
	//D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//m_pTeapotMesh->DrawSubset(0);

	//// 세번째 Teapot
	//D3DXMatrixScaling(&matScaling, fScaling[2], fScaling[2], fScaling[2]);
	//D3DXMatrixTranslation(&matTrans, vTrans[2].x, vTrans[2].y, vTrans[2].z);
	//matWorld = matScaling * matTrans * matRotationY;

	
	
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//m_pTeapotMesh->DrawSubset(0);

	//m_pBoxMesh->DrawSubset(0);	
	//pCylinderMesh->DrawSubset(0);
	//m_pSphereMesh->DrawSubset(0);

	//char str[100];
	//RECT rt = { 10, 10, 0, 0 };
	
	//sprintf(str, "FPS: %d", m_nFPS);
	//m_pFont->DrawTextA(NULL, str, -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	//m_nFPSCount++;




	char string[100];
	RECT rt;
	D3DXMATRIX matWorld, matScale, matTrans;

	for (int i = 0; i < 2; i++)
	{
		D3DXMatrixTranslation(&matTrans, m_Sphere[i].vTrans.x, m_Sphere[i].vTrans.y, m_Sphere[i].vTrans.z);
		D3DXMatrixScaling(&matScale, m_Sphere[i].fScaling, m_Sphere[i].fScaling, m_Sphere[i].fScaling);

		matWorld = matScale * matTrans;
		m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pMesh->DrawSubset(0);
	}

	SetRect(&rt, 10, 10, 0, 0);

	if (m_bIsCollision)
		m_pFont->DrawTextA(NULL, "충돌", -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	else
		m_pFont->DrawTextA(NULL, "비충돌", -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	
}

void CGameEdu01::OnUpdate()
{
	/*if (GetAsyncKeyState(VK_LEFT) < 0)
		m_fScale += 0.1f;

	if (GetAsyncKeyState(VK_RIGHT) < 0)
		m_fScale -= 0.1f;*/



	//DWORD dwCurTime = GetTickCount64();
	//static DWORD dwOldTime = GetTickCount64();
	//static DWORD dwAccumulateTime = 0; // 누적 경과 시간
	//
	//m_dwElapsedTime = dwCurTime - dwOldTime; // 프레임 경과 시간
	//dwOldTime = dwCurTime;

	//dwAccumulateTime += m_dwElapsedTime; // 누적
	//if (dwAccumulateTime >= 1000) // 1초 경과  체크
	//{
	//	dwAccumulateTime = 0;
	//	m_nFPS = m_nFPSCount;
	//	m_nFPSCount = 0;
	//}

	DWORD dwCurTime = GetTickCount64();
	static DWORD dwOldTime = GetTickCount64();
	m_dwElapsedTime = dwCurTime - dwOldTime;
	dwOldTime = dwCurTime;

	if (GetAsyncKeyState(VK_UP))
	{
		m_Sphere[0].vTrans.y += m_dwElapsedTime * 0.003f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_Sphere[0].vTrans.y -= m_dwElapsedTime * 0.003f;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_Sphere[0].vTrans.x -= m_dwElapsedTime * 0.003f;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_Sphere[0].vTrans.x += m_dwElapsedTime * 0.003f;
	}

	m_bIsCollision = CheckSphereIntersect(m_Sphere[0].vTrans,
		m_Sphere[0].fRadius * m_Sphere[0].fScaling,
		m_Sphere[1].vTrans,
		m_Sphere[1].fRadius * m_Sphere[1].fScaling);
		 
}

void CGameEdu01::OnRelease()
{
	//m_Cube.OnRelease();
	//m_pBoxMesh->Release();
	//m_pTeapotMesh->Release();
	//m_pCylinderMesh->Release();
	//m_pSphereMesh->Release();
	//m_Axis.OnRelease();
	//m_Ground.OnRelease();
	
	m_pMesh->Release();
	m_pFont->Release();
}

