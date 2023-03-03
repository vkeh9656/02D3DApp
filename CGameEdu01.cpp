#include "CGameEdu01.h"

CGameEdu01::CGameEdu01(void)
{
}

CGameEdu01::~CGameEdu01(void)
{
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

	m_Eye.x = 10.0f; // 0
	m_Eye.y = 10.0f; // 0
	m_Eye.z = -15.0f;// -8

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

	m_Axis.OnInit(m_pd3dDevice);
	//D3DXCreateBox(m_pd3dDevice, 2.0f, 2.0f, 2.0f, &m_pBoxMesh, NULL);
	D3DXCreateTeapot(m_pd3dDevice, &m_pTeapotMesh, NULL);
	//D3DXCreateCylinder(m_pd3dDevice, 2.0f, 2.0f, 5.0f, 100, 10, &m_pCylinderMesh, NULL);
	//D3DXCreateSphere(m_pd3dDevice, 3.0f, 30, 10, &m_pSphereMesh, NULL);
	m_fScale = 1.0f;
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
	D3DXMATRIX matRotationY, matWorld, matTrans, matScaling;
	float fScaling[3] = { 0.3f, 0.6f, 1.0f };
	D3DXVECTOR3 vTrans[3] = { D3DXVECTOR3(0.0f, 0.0f,0.0f), D3DXVECTOR3(2.0f, 0.0f,0.0f), D3DXVECTOR3(5.0f, 0.0f,0.0f) };
	D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);



	m_Axis.OnRender();
	/*m_Cube.OnRender();*/

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 크기 변환
	//D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);	
	
	// 고정 축 회전
	//D3DXMatrixRotationX(&matRotation, GetTickCount64() * 0.005f); // X축 회전
	//D3DXMatrixRotationY(&matRotation, GetTickCount64() * 0.005f); // Y축 회전
	//D3DXMatrixRotationZ(&matRotation, GetTickCount64() * 0.005f); // Z축 회전

	// 임의의 축 회전
	/*D3DXMatrixRotationAxis(&matRotation, &v1, GetTickCount64() * 0.005f);*/

	/*D3DXMatrixRotationX(&matRotationX, fRotX);
	D3DXMatrixRotationY(&matRotationY, fRotY);
	D3DXMatrixRotationZ(&matRotationZ, fRotZ);*/

	//D3DXMatrixRotationYawPitchRoll(&matRotation, fRotY, fRotX, fRotZ);
	//matRotation = matRotationZ * matRotationX * matRotationY;

	// 이동
	//D3DXMatrixTranslation(&matTranslation, 5.0f, 0.0f, 3.0f);


	// SRT 통합
	// 첫번째 Teapot
	D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);
	D3DXMatrixScaling(&matScaling, fScaling[0], fScaling[0], fScaling[0]);
	D3DXMatrixTranslation(&matTrans, vTrans[0].x, vTrans[0].y, vTrans[0].z);
	matWorld = matScaling * matRotationY * matTrans; // S*R*T
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);

	// 두번째 Teapot
	D3DXMatrixScaling(&matScaling, fScaling[1], fScaling[1], fScaling[1]);
	D3DXMatrixTranslation(&matTrans, vTrans[1].x, vTrans[1].y, vTrans[1].z);
	matWorld = matScaling * matRotationY * matTrans;
	D3DXMatrixRotationY(&matRotationY, GetTickCount64() * 0.005f);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);

	// 세번째 Teapot
	D3DXMatrixScaling(&matScaling, fScaling[2], fScaling[2], fScaling[2]);
	D3DXMatrixTranslation(&matTrans, vTrans[2].x, vTrans[2].y, vTrans[2].z);
	matWorld = matScaling * matTrans * matRotationY;

	
	
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pTeapotMesh->DrawSubset(0);

	//m_pBoxMesh->DrawSubset(0);	
	//pCylinderMesh->DrawSubset(0);
	//m_pSphereMesh->DrawSubset(0);
}

void CGameEdu01::OnUpdate()
{
	if (GetAsyncKeyState(VK_LEFT) < 0)
		m_fScale += 0.1f;

	if (GetAsyncKeyState(VK_RIGHT) < 0)
		m_fScale -= 0.1f;
}

void CGameEdu01::OnRelease()
{
	//m_Cube.OnRelease();
	//m_pBoxMesh->Release();
	m_pTeapotMesh->Release();
	//m_pCylinderMesh->Release();
	//m_pSphereMesh->Release();
	m_Axis.OnRelease();
	
}

