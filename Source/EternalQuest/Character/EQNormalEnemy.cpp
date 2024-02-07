


#include "Character/EQNormalEnemy.h"

#include "AI/EQBaseFSM.h"


AEQNormalEnemy::AEQNormalEnemy()
{
	BaseFsm = CreateDefaultSubobject<UEQBaseFSM>("BasFSM");
}

