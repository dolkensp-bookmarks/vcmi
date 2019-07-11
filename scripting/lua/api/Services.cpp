/*
 * api/Services.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"

#include "Services.h"

#include "Registry.h"

#include "../LuaStack.h"
#include "../LuaCallWrapper.h"


namespace scripting
{
namespace api
{

VCMI_REGISTER_CORE_SCRIPT_API(ServicesProxy);

const std::vector<ServicesProxy::RegType> ServicesProxy::REGISTER =
{
	{"artifacts", LuaCallWrapper<const Services>::createFunctor(&Services::artifacts)},
	{"creatures", LuaCallWrapper<const Services>::createFunctor(&Services::creatures)},
	{"factions", LuaCallWrapper<const Services>::createFunctor(&Services::factions)},
	{"heroClasses", LuaCallWrapper<const Services>::createFunctor(&Services::heroClasses)},
	{"heroTypes", LuaCallWrapper<const Services>::createFunctor(&Services::heroTypes)},
	{"spells", LuaCallWrapper<const Services>::createFunctor(&Services::spells)},
	{"skills", LuaCallWrapper<const Services>::createFunctor(&Services::skills)},
};

VCMI_REGISTER_CORE_SCRIPT_API(ArtifactServiceProxy);

const std::vector<ArtifactServiceProxy::RegType> ArtifactServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<ArtifactID, Artifact>>::createFunctor(&ArtifactService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(CreatureServiceProxy);

const std::vector<CreatureServiceProxy::RegType> CreatureServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<CreatureID, Creature>>::createFunctor(&CreatureService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(FactionServiceProxy);

const std::vector<FactionServiceProxy::RegType> FactionServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<FactionID, Faction>>::createFunctor(&FactionService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(HeroClassServiceProxy);

const std::vector<HeroClassServiceProxy::RegType> HeroClassServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<HeroClassID, HeroClass>>::createFunctor(&HeroClassService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(HeroTypeServiceProxy);

const std::vector<HeroTypeServiceProxy::RegType> HeroTypeServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<HeroTypeID, HeroType>>::createFunctor(&HeroTypeService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(SkillServiceProxy);

const std::vector<SkillServiceProxy::RegType> SkillServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<SecondarySkill, Skill>>::createFunctor(&SkillService::getByIndex)}
};

VCMI_REGISTER_CORE_SCRIPT_API(SpellServiceProxy);

const std::vector<SpellServiceProxy::RegType> SpellServiceProxy::REGISTER =
{
	{"getByIndex", LuaCallWrapper<const EntityServiceT<SpellID, spells::Spell>>::createFunctor(&spells::Service::getByIndex)}
};

}
}
