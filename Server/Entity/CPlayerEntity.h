//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CPlayerEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include "CNetworkEntity.h"

class CPlayerEntity : public CNetworkEntity {
private:

public:
	CPlayerEntity();
	~CPlayerEntity();
};

#endif // CPlayerEntity_h