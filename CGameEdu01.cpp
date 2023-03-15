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

BOOL CheckCubeIntersect(D3DXVECTOR3* vMin1, D3DXVECTOR3* vMax1, D3DXVECTOR3* vMin2, D3DXVECTOR3* vMax2)
{
	if (vMin1->x <= vMax2->x && vMax1->x >= vMin2->x &&
		vMin1->y <= vMax2->y && vMax1->y >= vMin2->y &&
		vMin1->z <= vMax2->z && vMax1->z >= vMin2->z)
		return TRUE;
	return FALSE;
}


void CGameEdu01::OnInit()
{
	int i;

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
	m_Eye.y = 10.0f; // 0
	m_Eye.z = -32.0f;// 

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

	D3DXCreateTeapot(m_pd3dDevice, &m_pTeapotMesh, NULL);
	D3DXCreateCylinder(m_pd3dDevice, 2.0f, 2.0f, 10.0f, 15, 10, &m_pPlayerBulletMesh, NULL);
	m_Ground.Create(m_pd3dDevice, 20, 6, 2.0f);

	// Note: 주인공 설정
	m_sPlayer.nLife = 10;
	m_sPlayer.fScale = 0.7f;
	m_sPlayer.fRotationY = -D3DXToRadian(90);
	m_sPlayer.vPos = D3DXVECTOR3(0.0f, 0.0f, -9 * 2.0f);
	m_sPlayer.fVelocity = 0.005f;
	m_sPlayer.dwBulletFireTime = 400;
	m_sPlayer.dwOldBulletFireTime = GetTickCount64();

	D3DXMatrixScaling(&m_sPlayer.matScale, m_sPlayer.fScale, m_sPlayer.fScale, m_sPlayer.fScale);
	D3DXMatrixTranslation(&m_sPlayer.matTranslation, m_sPlayer.vPos.x, m_sPlayer.vPos.y, m_sPlayer.vPos.z);
	D3DXMatrixRotationY(&m_sPlayer.matRotationY, m_sPlayer.fRotationY);


	// Note: 주인공 Bullet 설정
	m_sPlayerBulletProperty.fBulletVelocity = 0.01f;
	m_sPlayerBulletProperty.fScale = 0.08f;
	D3DXMatrixScaling(&m_sPlayerBulletProperty.matScale, m_sPlayerBulletProperty.fScale, m_sPlayerBulletProperty.fScale, m_sPlayerBulletProperty.fScale);


	/*m_Axis.OnInit(m_pd3dDevice);*/
	//D3DXCreateBox(m_pd3dDevice, 2.0f, 2.0f, 2.0f, &m_pBoxMesh, NULL);
	
	//D3DXCreateCylinder(m_pd3dDevice, 2.0f, 2.0f, 5.0f, 100, 10, &m_pCylinderMesh, NULL);
	//D3DXCreateSphere(m_pd3dDevice, 3.0f, 30, 10, &m_pSphereMesh, NULL);
	
	//m_fScale = 1.0f;

	/*D3DXCreateFont(m_pd3dDevice, 15, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		L"System", &m_pFont);*/

	/*D3DXCreateBox(m_pd3dDevice, 1.0f, 1.0f, 1.0f, &m_pMesh, NULL);*/

	//D3DXVECTOR3* pVertices;
	//
	//// VertexBuffer에 접근하기 위해선 우선 Lock을 걸어야됨!
	//m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

	//// Vertex Buffer 뒤져서 최소값 최대값을 딱 추출해냄.
	//D3DXComputeBoundingBox(pVertices, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &m_vMin, &m_vMax);
	//m_pMesh->UnlockVertexBuffer();

	//D3DXMATRIX matScale, matTrans, matWorld;
	//m_Box[0].fScaling = 2.0f;
	//m_Box[0].vTrans = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	//D3DXMatrixTranslation(&matTrans, m_Box[0].vTrans.x, m_Box[0].vTrans.y, m_Box[0].vTrans.z);
	//D3DXMatrixScaling(&matScale, m_Box[0].fScaling, m_Box[0].fScaling, m_Box[0].fScaling);
	//matWorld = matScale * matTrans; // 실제로 나타내고자 하는 월드의 행렬
	//D3DXVec3TransformCoord(&m_Box[0].vMin, &m_vMin, &matWorld); // 그 행렬에서의 최초의 미니멈과 맥시멈 좌표를 구해냄
	//D3DXVec3TransformCoord(&m_Box[0].vMax, &m_vMax, &matWorld); // 그 행렬에서의 최초의 미니멈과 맥시멈 좌표를 구해냄


	//m_Box[1].fScaling = 1.0f;
	//m_Box[1].vTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXMatrixTranslation(&matTrans, m_Box[1].vTrans.x, m_Box[1].vTrans.y, m_Box[1].vTrans.z);
	//D3DXMatrixScaling(&matScale, m_Box[1].fScaling, m_Box[1].fScaling, m_Box[1].fScaling);
	//matWorld = matScale * matTrans; // 실제로 나타내고자 하는 월드의 행렬
	//D3DXVec3TransformCoord(&m_Box[1].vMin, &m_vMin, &matWorld); // 그 행렬에서의 최초의 미니멈과 맥시멈 좌표를 구해냄
	//D3DXVec3TransformCoord(&m_Box[1].vMax, &m_vMax, &matWorld); // 그 행렬에서의 최초의 미니멈과 맥시멈 좌표를 구해냄



	//D3DXCreateSphere(m_pd3dDevice, 1.0f, 20, 20, &m_pMesh, NULL);


	/*m_Sphere[0].fRadius = 1.0f;
	m_Sphere[0].fScaling = 1.0f;
	m_Sphere[0].vTrans = D3DXVECTOR3(0, 0, 0);

	m_Sphere[1].fRadius = 1.0f;
	m_Sphere[1].fScaling = 2.0f;
	m_Sphere[1].vTrans = D3DXVECTOR3(5, 0, 0);*/
	
	m_bIsCollision = FALSE;


	
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




	/*char string[100];
	RECT rt;
	D3DXMATRIX matWorld, matScale, matTrans;

	for (int i = 0; i < 2; i++)
	{
		D3DXMatrixTranslation(&matTrans, m_Box[i].vTrans.x, m_Box[i].vTrans.y, m_Box[i].vTrans.z);
		D3DXMatrixScaling(&matScale, m_Box[i].fScaling, m_Box[i].fScaling, m_Box[i].fScaling);

		matWorld = matScale * matTrans;
		m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pMesh->DrawSubset(0);
	}

	SetRect(&rt, 10, 10, 0, 0);

	if (m_bIsCollision)
		m_pFont->DrawTextA(NULL, "충돌", -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	else
		m_pFont->DrawTextA(NULL, "비충돌", -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));*/

	int i;
	D3DXMATRIX matWorld;
	m_Ground.OnRender();

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (i = 0; i < 10; i++) 
	{
		if (m_sPlayerBullet[i].nLife > 0)
		{
			matWorld = m_sPlayerBulletProperty.matScale * m_sPlayerBullet[i].matTranslation;
			m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pPlayerBulletMesh->DrawSubset(0);
		}
	}

	// 주인공
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_sPlayer.matWorld);
	m_pTeapotMesh->DrawSubset(0);
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

	int i, j;

	
	static DWORD dwOldTime = GetTickCount64();
	DWORD dwCurTime = GetTickCount64();
	m_dwElapsedTime = dwCurTime - dwOldTime;
	dwOldTime = dwCurTime;

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_sPlayer.vPos.x - (m_dwElapsedTime * m_sPlayer.fVelocity) >= -6.0f)
			m_sPlayer.vPos.x -= m_dwElapsedTime * m_sPlayer.fVelocity;
		/*m_Box[0].vTrans.x -= m_dwElapsedTime * 0.003f;*/
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_sPlayer.vPos.x + (m_dwElapsedTime * m_sPlayer.fVelocity) <= 6.0f)
			m_sPlayer.vPos.x += m_dwElapsedTime * m_sPlayer.fVelocity;
		/*m_Box[0].vTrans.x += m_dwElapsedTime * 0.003f;*/
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (m_sPlayer.vPos.z + (m_dwElapsedTime * m_sPlayer.fVelocity) <= 20.0f)
			m_sPlayer.vPos.z += m_dwElapsedTime * m_sPlayer.fVelocity;

		/*m_Box[0].vTrans.y += m_dwElapsedTime * 0.003f;*/
		
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_sPlayer.vPos.z - (m_dwElapsedTime * m_sPlayer.fVelocity) >= -19.0f)
			m_sPlayer.vPos.z -= m_dwElapsedTime * m_sPlayer.fVelocity;

		/*m_Box[0].vTrans.y -= m_dwElapsedTime * 0.003f;*/
	}

	if (GetAsyncKeyState('S') < 0)	// 주인공 미사일 발사
	{
		if (dwCurTime - m_sPlayer.dwOldBulletFireTime >= m_sPlayer.dwBulletFireTime)
		{
			m_sPlayer.dwOldBulletFireTime = dwCurTime;

			for (i = 0; i < 10; i++)
			{
				if (m_sPlayerBullet[i].nLife <= 0)
				{
					m_sPlayerBullet[i].nLife = 1;
					m_sPlayerBullet[i].vPos = m_sPlayer.vPos;
					m_sPlayerBullet[i].vPos.z += 1.0f;
					break;
				}
			}
		}
	}

	for (i = 0; i < 10; i++)
	{
		if (m_sPlayerBullet[i].nLife > 0)
		{
			m_sPlayerBullet[i].vPos.z += m_dwElapsedTime * m_sPlayerBulletProperty.fBulletVelocity;
			if (m_sPlayerBullet[i].vPos.z >= 20.0f) // 경계 영역 충돌
				m_sPlayerBullet[i].nLife = 0;
			else
				D3DXMatrixTranslation(&m_sPlayerBullet[i].matTranslation, m_sPlayerBullet[i].vPos.x, m_sPlayerBullet[i].vPos.y, m_sPlayerBullet[i].vPos.z);
		}
	}

	//D3DXMATRIX matScale, matTrans, matWorld;
	//D3DXMatrixTranslation(&matTrans, m_Box[0].vTrans.x, m_Box[0].vTrans.y, m_Box[0].vTrans.z);
	//D3DXMatrixScaling(&matScale, m_Box[0].fScaling, m_Box[0].fScaling, m_Box[0].fScaling);

	//matWorld = matScale * matTrans;
	//D3DXVec3TransformCoord(&m_Box[0].vMin, &m_vMin, &matWorld);
	//D3DXVec3TransformCoord(&m_Box[0].vMax, &m_vMax, &matWorld);

	//m_bIsCollision = CheckCubeIntersect(&m_Box[0].vMin, &m_Box[0].vMax, &m_Box[1].vMin, &m_Box[1].vMax);


	// player의 행렬을 바꿔서 이동
	D3DXMatrixTranslation(&m_sPlayer.matTranslation, m_sPlayer.vPos.x, m_sPlayer.vPos.y, m_sPlayer.vPos.z);
	m_sPlayer.matWorld = m_sPlayer.matScale * m_sPlayer.matRotationY * m_sPlayer.matTranslation;
}

void CGameEdu01::OnRelease()
{
	//m_Cube.OnRelease();
	//m_pBoxMesh->Release();
	//m_pTeapotMesh->Release();
	//m_pCylinderMesh->Release();
	//m_pSphereMesh->Release();
	//m_Axis.OnRelease();
	m_Ground.OnRelease();
	m_pTeapotMesh->Release();
	m_pMesh->Release();
	//m_pFont->Release();
}

