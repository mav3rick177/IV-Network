/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CNetworkEntity.h"
#include <Network/CBitStream.h>
#include <CLogFile.h>
#include "CPlayerEntity.h"
#include "CVehicleEntity.h"
#include <CCore.h>
extern CCore * g_pCore;

CNetworkEntity::CNetworkEntity() :
	m_vecPosition(CVector3()),
	m_vecRotation(CVector3()),
	m_vecMoveSpeed(CVector3()),
	m_vecTurnSpeed(CVector3()),
	m_vecDirection(CVector3()),
	m_vecRoll(CVector3()),
	m_entityId(INVALID_ENTITY),
	m_eType(UNKNOWN_ENTITY)
{

}

CNetworkEntity::CNetworkEntity(eEntityType eType)
: m_vecPosition(CVector3()),
m_vecRotation(CVector3()),
m_vecMoveSpeed(CVector3()),
m_vecTurnSpeed(CVector3()),
m_vecDirection(CVector3()),
m_vecRoll(CVector3()),
m_entityId(INVALID_ENTITY),
m_eType(eType)
{
}

CNetworkEntity::CNetworkEntity(eEntityType eType, EntityId entityId)
: m_vecPosition(CVector3()),
m_vecRotation(CVector3()),
m_vecMoveSpeed(CVector3()),
m_vecTurnSpeed(CVector3()),
m_vecDirection(CVector3()),
m_vecRoll(CVector3()),
m_entityId(entityId),
m_eType(eType)
{
}


CNetworkEntity::~CNetworkEntity()
{
}

void CNetworkEntity::GetPosition(CVector3& vecPos)
{
	vecPos = m_vecPosition;
}

void CNetworkEntity::SetPosition(const CVector3& vecPos)
{
	m_vecPosition = vecPos;
}

void CNetworkEntity::GetRotation(CVector3& vecRot)
{
	vecRot = m_vecRotation;
}

void CNetworkEntity::SetRotation(const CVector3& vecRot)
{
	m_vecRotation = vecRot;
}

void CNetworkEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	vecMoveSpeed = m_vecMoveSpeed;
}

void CNetworkEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	m_vecMoveSpeed = vecMoveSpeed;
}

void CNetworkEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	vecTurnSpeed = m_vecTurnSpeed;
}

void CNetworkEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	m_vecTurnSpeed = vecTurnSpeed;
}

void CNetworkEntity::GetDirectionSpeed(CVector3& vecDirectionSpeed)
{
	vecDirectionSpeed = m_vecDirection;
}

void CNetworkEntity::SetDirectionSpeed(const CVector3& vecDirectionSpeed)
{
	m_vecDirection = vecDirectionSpeed;
}

void CNetworkEntity::GetRollSpeed(CVector3& vecRollSpeed)
{
	vecRollSpeed = m_vecRoll;
}

void CNetworkEntity::SetRollSpeed(const CVector3& vecRollSpeed)
{
	m_vecRoll = vecRollSpeed;
}

bool CNetworkEntity::IsMoving()
{
	if(!(m_vecMoveSpeed.fX == 0 && m_vecMoveSpeed.fY == 0 && (m_vecMoveSpeed.fZ >= -0.000020 && m_vecMoveSpeed.fZ <= 0.000020)))
		return true;

	return false;
}

void CNetworkEntity::StopMoving()
{
	m_vecMoveSpeed = CVector3();
}

#if 0
/*
 * @ This function handles the current packages from the network entity
 * @ So it stores the current values, which are used in the sync package
*/
void CNetworkEntity::Pulse(CPlayerEntity * pPlayer)
{
	// Check if our player ptr
	if(pPlayer)
	{
		// Update player handle
		if(!m_pPlayerEntity)
			m_pPlayerEntity = pPlayer;

		/*
		 * > First start updating basic entity members(e.g. position, movement etc.)
		*/

		// Get the latest position
		pPlayer->GetPosition(m_vecPosition);

		// Get the latest move speed
		pPlayer->GetMoveSpeed(m_vecMoveSpeed);

		// Get the latest turn speed
		pPlayer->GetTurnSpeed(m_vecTurnSpeed);

		// Get the latest direction speed
		pPlayer->GetPlayerPed()->GetDirection(m_vecDirection);

		// Get the latest roll speed
		pPlayer->GetPlayerPed()->GetRoll(m_vecRoll);

		/*
		 * > Now render specific player parts(e.g. rotation, crouch state etc.)
		*/
		// Get the latest rotation
		m_pPlayerHandle.fHeading = pPlayer->GetRotation();

		// Get the latest crouch state
		m_pPlayerHandle.bDuckState = pPlayer->GetPlayerPed()->IsDucking();

		// Get the control state
		pPlayer->GetControlState(&m_pPlayerHandle.pControlState);

		/*
		 * > At last, fetch the weapon data
		*/

		// Get the arm heading circles
		pPlayer->GetContextData()->GetArmHeading(m_pPlayerHandle.sWeaponData.fArmsHeadingCircle);

		// Get the arm rotation circles
		pPlayer->GetContextData()->GetArmUpDown(m_pPlayerHandle.sWeaponData.fArmsUpDownRotation);

		// Get the aim at coordinates
		pPlayer->GetContextData()->GetWeaponAimTarget(m_pPlayerHandle.sWeaponData.vecAimAtCoordinates);

		// Get the shot at coordinates
		pPlayer->GetContextData()->GetWeaponShotSource(m_pPlayerHandle.sWeaponData.vecShotAtCoordinates);

		// Get the shot at target specific coordinates
		pPlayer->GetContextData()->GetWeaponShotTarget(m_pPlayerHandle.sWeaponData.vecShotAtTarget);

		// Get the look at aiming coordinates
		g_pCore->GetGame()->GetCamera()->GetAimPosition(&m_pPlayerHandle.sWeaponData.vecAimAtCoordinates);
	}
}
#endif
#if 0
/*
 * @ This function handles the current packages from the network entity
 * @ So it stores the current values, which are used in the sync package
*/
//void CNetworkEntity::Pulse(CVehicleEntity * pVehicle)
{
	// Check if our player ptr
	if(pVehicle)
	{
		// Get the latest position
		pVehicle->GetPosition(m_vecPosition);

		// Get the latest movespeed
		pVehicle->GetMoveSpeed(m_vecMoveSpeed);

		// Get the latest turnspeed
		pVehicle->GetTurnSpeed(m_vecTurnSpeed);

		// Get the latest direction
		pVehicle->GetGameVehicle()->GetDirection(m_vecDirection);

		// Get the latest roll
		pVehicle->GetGameVehicle()->GetRoll(m_vecRoll);
	}
}
#endif 

