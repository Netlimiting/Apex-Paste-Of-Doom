#include "skin system.hpp"

SkinSystem::SkinSystem()
{
	static int SKINID = 0;
	int ActiveWeapon = sdk.LocalPlayer->GetWeaponIndex();
	if (ActiveWeapon == WeaponIDs::KNIFE)
		return;

	switch (ActiveWeapon)
	{
	case 112: // p2020
		if (SelectedSkin::Pistol::p2020::P2020[0])
			SKINID = 2;
		else if (SelectedSkin::Pistol::p2020::P2020[1])
			SKINID = 3;
		else if (SelectedSkin::Pistol::p2020::P2020[2])
			SKINID = 4;
		else if (SelectedSkin::Pistol::p2020::P2020[3])
			SKINID = 5;
		else if (SelectedSkin::Pistol::p2020::P2020[4])
			SKINID = 6;
		else if (SelectedSkin::Pistol::p2020::P2020[5])
			SKINID = 8;
		else if (SelectedSkin::Pistol::p2020::P2020[6])
			SKINID = 9;
		else if (SelectedSkin::Pistol::p2020::P2020[7])
			SKINID = 10;
		break;

	case 85://re45
		if (SelectedSkin::Pistol::re45::re45[0])
			SKINID = 1;
		else if (SelectedSkin::Pistol::re45::re45[1])
			SKINID = 2;
		else if (SelectedSkin::Pistol::re45::re45[2])
			SKINID = 3;
		else if (SelectedSkin::Pistol::re45::re45[3])
			SKINID = 4;
		else if (SelectedSkin::Pistol::re45::re45[4])
			SKINID = 5;
		else if (SelectedSkin::Pistol::re45::re45[5])
			SKINID = 6;
		else if (SelectedSkin::Pistol::re45::re45[6])
			SKINID = 7;
		else if (SelectedSkin::Pistol::re45::re45[7])
			SKINID = 8;
		else if (SelectedSkin::Pistol::re45::re45[8])
			SKINID = 9;
		else if (SelectedSkin::Pistol::re45::re45[9])
			SKINID = 10;
		else if (SelectedSkin::Pistol::re45::re45[10])
			SKINID = 11;
		else if (SelectedSkin::Pistol::re45::re45[11])
			SKINID = 12;
		else if (SelectedSkin::Pistol::re45::re45[12])
			SKINID = 13;
		else if (SelectedSkin::Pistol::re45::re45[13])
			SKINID = 14;
		else if (SelectedSkin::Pistol::re45::re45[14])
			SKINID = 15;
		else if (SelectedSkin::Pistol::re45::re45[15])
			SKINID = 16;
		break;

	case 84: //alternator
		if (SelectedSkin::Pistol::alternator::alternator[0])
			SKINID = 1;
		else if (SelectedSkin::Pistol::alternator::alternator[1])
			SKINID = 2;
		else if (SelectedSkin::Pistol::alternator::alternator[2])
			SKINID = 3;
		else if (SelectedSkin::Pistol::alternator::alternator[3])
			SKINID = 4;
		else if (SelectedSkin::Pistol::alternator::alternator[4])
			SKINID = 5;
		else if (SelectedSkin::Pistol::alternator::alternator[5])
			SKINID = 6;
		else if (SelectedSkin::Pistol::alternator::alternator[6])
			SKINID = 7;
		else if (SelectedSkin::Pistol::alternator::alternator[7])
			SKINID = 8;
		else if (SelectedSkin::Pistol::alternator::alternator[8])
			SKINID = 10;
		else if (SelectedSkin::Pistol::alternator::alternator[9])
			SKINID = 11;
		else if (SelectedSkin::Pistol::alternator::alternator[10])
			SKINID = 12;
		else if (SelectedSkin::Pistol::alternator::alternator[11])
			SKINID = 14;
		else if (SelectedSkin::Pistol::alternator::alternator[12])
			SKINID = 15;

		break;
	}

	sdk.LocalPlayer->SetSkin(SKINID);

}