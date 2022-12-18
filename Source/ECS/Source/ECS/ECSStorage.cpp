#include "ECSStorage.h"

namespace Inf
{
ECSStorage& ECSStorage::Self()
{
	static ECSStorage self;
	return self;
}
}
