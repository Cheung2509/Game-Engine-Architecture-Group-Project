#include "Collectables.h"

Collectables::Collectables(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
	// needs collision to trigger pick up player owning collectable number may need to be changed

}
		else
		{
			return false;
		}
	}

	return true;
}