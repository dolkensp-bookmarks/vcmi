#include "../stdafx.h"
#include "CCreatureHandler.h"
#include "CLodHandler.h"
#include <sstream>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/replace.hpp>

int CCreature::getQuantityID(int quantity)
{
	if (quantity<5)
		return 0;
	if (quantity<10)
		return 1;
	if (quantity<20)
		return 2;
	if (quantity<50)
		return 3;
	if (quantity<100)
		return 4;
	if (quantity<250)
		return 5;
	if (quantity<500)
		return 5;
	if (quantity<1000)
		return 6;
	if (quantity<4000)
		return 7;
	return 8;
}

bool CCreature::isDoubleWide()
{
	return boost::algorithm::find_first(abilityRefs, "DOUBLE_WIDE");
}

bool CCreature::isFlying()
{
	return boost::algorithm::find_first(abilityRefs, "FLYING_ARMY");
}
int CCreature::maxAmount(const std::vector<int> &res) const //how many creatures can be bought
{
	int ret = 2147483645;
	int resAmnt = std::min(res.size(),cost.size());
	for(int i=0;i<resAmnt;i++)
		if(cost[i])
			ret = std::min(ret,res[i]/cost[i]);
	return ret;
}

void CCreatureHandler::loadCreatures()
{
	std::string buf = bitmaph->getTextFile("ZCRTRAIT.TXT");
	int andame = buf.size();
	int i=0; //buf iterator
	int hmcr=0;
	for(i; i<andame; ++i)
	{
		if(buf[i]=='\r')
			++hmcr;
		if(hmcr==2)
			break;
	}
	i+=2;

	while(i<buf.size())
	{
		CCreature ncre;
		ncre.cost.resize(RESOURCE_QUANTITY);
		ncre.level=0;
		int befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.nameSing = buf.substr(befi, i-befi);
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.namePl = buf.substr(befi, i-befi);
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[0] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[1] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[2] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[3] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[4] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[5] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.cost[6] = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.fightValue = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.AIValue = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.growth = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.hordeGrowth = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.hitPoints = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.speed = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.attack = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.defence = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.damageMin = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.damageMax = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.shots = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.spells = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.ammMin = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.ammMax = atoi(buf.substr(befi, i-befi).c_str());
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\t')
				break;
		}
		ncre.abilityText = buf.substr(befi, i-befi);
		++i;

		befi=i;
		for(i; i<andame; ++i)
		{
			if(buf[i]=='\r')
				break;
		}
		ncre.abilityRefs = buf.substr(befi, i-befi);
		i+=2;
		if(ncre.nameSing!=std::string("") && ncre.namePl!=std::string(""))
		{
			ncre.idNumber = creatures.size();
			ncre.isDefinite = true;
			creatures.push_back(ncre);
		}
	}
	for(int bb=1; bb<8; ++bb)
	{
		CCreature ncre;
		ncre.isDefinite = false;
		ncre.indefLevel = bb;
		ncre.indefUpgraded = false;
		creatures.push_back(ncre);
		ncre.indefUpgraded = true;
		creatures.push_back(ncre);
	}

	//loading reference names
	std::ifstream ifs("config/crerefnam.txt"); 
	int tempi;
	std::string temps;
	for (;;)
	{
		ifs >> tempi >> temps;
		if (tempi>=creatures.size())
			break;
		boost::assign::insert(nameToID)(temps,tempi);
		creatures[tempi].nameRef=temps;
	}
	ifs.close();
	ifs.clear();
	for(int i=1;i<=10;i++)
		levelCreatures.insert(std::pair<int,std::vector<CCreature*> >(i,std::vector<CCreature*>()));
	ifs.open("config/monsters.txt"); 
	{
		while(!ifs.eof())
		{
			int id, lvl;
			ifs >> id >> lvl;
			if(lvl>0)
			{
				creatures[id].level = lvl;
				levelCreatures[lvl].push_back(&(creatures[id]));
			}
		}
	}
	ifs.close();
	ifs.clear();

	ifs.open("config/cr_factions.txt"); 
	while(!ifs.eof())
	{
		int id, fact;
		ifs >> id >> fact;
		creatures[id].faction = fact;
	}
	ifs.close();
	ifs.clear();

	ifs.open("config/cr_upgrade_list.txt"); 
	while(!ifs.eof())
	{
		int id, up;
		ifs >> id >> up;
		creatures[id].upgrades.insert(up);
	}
	ifs.close();
	ifs.clear();
	
	//loading unit animation def names
	std::ifstream inp("config/CREDEFS.TXT", std::ios::in | std::ios::binary); //this file is not in lod
	inp.seekg(0,std::ios::end); // na koniec
	int andame2 = inp.tellg();  // read length
	inp.seekg(0,std::ios::beg); // wracamy na poczatek
	char * bufor = new char[andame2]; // allocate memory 
	inp.read((char*)bufor, andame2); // read map file to buffer
	inp.close();
	buf = std::string(bufor);
	delete [andame2] bufor;

	i = 0; //buf iterator
	hmcr = 0;
	for(i; i<andame2; ++i) //omitting rubbish
	{
		if(buf[i]=='\r')
			break;
	}
	i+=2;
	for(int s=0; s<creatures.size()-16; ++s)
	{
		int befi=i;
		std::string rub;
		for(i; i<andame2; ++i)
		{
			if(buf[i]==' ')
				break;
		}
		rub = buf.substr(befi, i-befi);
		++i;

		befi=i;
		for(i; i<andame2; ++i)
		{
			if(buf[i]=='\r')
				break;
		}
		std::string defName = buf.substr(befi, i-befi);
		creatures[s].animDefName = defName;
	}
	loadAnimationInfo();
}

void CCreatureHandler::loadAnimationInfo()
{
	std::string buf = bitmaph->getTextFile("CRANIM.TXT");
	int andame = buf.size();
	int i=0; //buf iterator
	int hmcr=0;
	for(i; i<andame; ++i)
	{
		if(buf[i]=='\r')
			++hmcr;
		if(hmcr==2)
			break;
	}
	i+=2;
	for(int dd=0; dd<creatures.size()-16; ++dd)
	{
		loadUnitAnimInfo(creatures[dd], buf, i);
	}
	return;
}

void CCreatureHandler::loadUnitAnimInfo(CCreature & unit, std::string & src, int & i)
{
	int befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.timeBetweenFidgets = atof(src.substr(befi, i-befi).c_str());
	++i;

	while(unit.timeBetweenFidgets == 0.0)
	{
		for(i; i<src.size(); ++i)
		{
			if(src[i]=='\r')
				break;
		}
		i+=2;
		befi=i;
		for(i; i<src.size(); ++i)
		{
			if(src[i]=='\t')
				break;
		}
		unit.timeBetweenFidgets = atof(src.substr(befi, i-befi).c_str());
		++i;
	}

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.walkAnimationTime = atof(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.attackAnimationTime = atof(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.flightAnimationDistance = atof(src.substr(befi, i-befi).c_str());
	++i;

	///////////////////////

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.upperRightMissleOffsetX = atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.upperRightMissleOffsetY = atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.rightMissleOffsetX = atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.rightMissleOffsetY = atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.lowerRightMissleOffsetX = atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.lowerRightMissleOffsetY = atoi(src.substr(befi, i-befi).c_str());
	++i;

	///////////////////////

	for(int jjj=0; jjj<12; ++jjj)
	{
		befi=i;
		for(i; i<src.size(); ++i)
		{
			if(src[i]=='\t')
				break;
		}
		unit.missleFrameAngles[jjj] = atof(src.substr(befi, i-befi).c_str());
		++i;
	}

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.troopCountLocationOffset= atoi(src.substr(befi, i-befi).c_str());
	++i;

	befi=i;
	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\t')
			break;
	}
	unit.attackClimaxFrame = atoi(src.substr(befi, i-befi).c_str());
	++i;

	for(i; i<src.size(); ++i)
	{
		if(src[i]=='\r')
			break;
	}
	i+=2;
}