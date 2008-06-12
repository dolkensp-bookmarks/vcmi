#ifndef GLOBAL_H
#define GLOBAL_H
#define CHECKTIME 1
#if CHECKTIME
#include "timeHandler.h"
#include <boost/logic/tribool.hpp>
#include <iostream>
#include "int3.h"
#define THC
#else 
#define THC //
#endif
enum Ecolor {RED, BLUE, TAN, GREEN, ORANGE, PURPLE, TEAL, PINK}; //player's colors
enum EterrainType {border=-1, dirt, sand, grass, snow, swamp, rough, subterranean, lava, water, rock};
enum Eriver {noRiver=0, clearRiver, icyRiver, muddyRiver, lavaRiver};
enum Eroad {dirtRoad=1, grazvelRoad, cobblestoneRoad};
enum Eformat { WoG=0x33, AB=0x15, RoE=0x0e,  SoD=0x1c};
enum EvictoryConditions {artifact, gatherTroop, gatherResource, buildCity, buildGrail, beatHero, 
	captureCity, beatMonster, takeDwellings, takeMines, transportItem, winStandard=255};
enum ElossCon {lossCastle, lossHero, timeExpires, lossStandard=255};
enum EHeroClasses {HERO_KNIGHT, HERO_CLERIC, HERO_RANGER, HERO_DRUID, HERO_ALCHEMIST, HERO_WIZARD, 
	HERO_DEMONIAC, HERO_HERETIC, HERO_DEATHKNIGHT, HERO_NECROMANCER, HERO_WARLOCK, HERO_OVERLORD, 
	HERO_BARBARIAN, HERO_BATTLEMAGE, HERO_BEASTMASTER, HERO_WITCH, HERO_PLANESWALKER, HERO_ELEMENTALIST};
#ifdef _DEBUG
class CGameInfo;
extern CGameInfo* CGI;
#else
#define CGI (CGameInfo::mainObj)
#endif
#define CURPLINT (((CPlayerInterface*)((CGameInfo::mainObj)->playerint[(CGameInfo::mainObj)->state->currentPlayer]))) 
#define LOCPLINT (((CPlayerInterface*)((CGameInfo::mainObj)->playerint[(CGameInfo::mainObj)->localPlayer]))) 
//CURPLINT gives pointer to the interface of human player which is currently making turn, 
//LOCPLINT gives pointer to the interface which is currently showed (on this machine)

#define HEROI_TYPE (0)
#define TOWNI_TYPE (1)

//#define LOGUJ

#ifdef LOGUJ
#define LOG(x) std::cout<<x;
#define LOGE(x) std::cout<<x<<std::endl;
#else
#define LOG(x) ;
#define LOGE(x) ;
#endif

const int F_NUMBER = 9; //factions (town types) quantity
const int PLAYER_LIMIT = 8; //player limit per map
const int HEROES_PER_TYPE=8; //amount of heroes of each type
const int SKILL_QUANTITY=28;
const int SKILL_PER_HERO=8;
const int ARTIFACTS_QUANTITY=171;
const int HEROES_QUANTITY=156;
const int SPELLS_QUANTITY=70;
const int RESOURCE_QUANTITY=8;
const int TERRAIN_TYPES=10;
const int PRIMARY_SKILLS=4;
const int NEUTRAL_PLAYER=255;
const int NAMES_PER_TOWN=16;
const int CREATURES_PER_TOWN = 7; //without upgrades
const int MAX_BUILDING_PER_TURN = 1;

#define MARK_BLOCKED_POSITIONS false
#define MARK_VISITABLE_POSITIONS false

#define DEFBYPASS

#ifdef _WIN32
	#ifdef VCMI_DLL
		#define DLL_EXPORT __declspec(dllexport)
	#else
		#define DLL_EXPORT __declspec(dllimport)
	#endif
#else
	#if defined(__GNUC__) && __GNUC__ >= 4
		#define DLL_EXPORT	__attribute__ ((visibility("default")))
	#else
		#define DLL_EXPORT
	#endif
#endif

#define HANDLE_EXCEPTION  \
	catch (const std::exception& e) {	\
	std::cerr << e.what() << std::endl;	\
	}									\
	catch (const std::exception * e)	\
	{									\
		std::cerr << e->what()<< std::endl;	\
		delete e;						\
	}									

#endif //GLOBAL_H