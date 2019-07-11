/*
 * api/Services.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/Services.h>

#include <vcmi/ArtifactService.h>
#include <vcmi/CreatureService.h>
#include <vcmi/FactionService.h>
#include <vcmi/HeroClassService.h>
#include <vcmi/HeroTypeService.h>
#include <vcmi/SkillService.h>
#include <vcmi/spells/Service.h>

#include "../LuaWrapper.h"

namespace scripting
{
namespace api
{

class ServicesProxy : public OpaqueWrapper<const Services, ServicesProxy>
{
public:
	using Wrapper = OpaqueWrapper<const Services, ServicesProxy>;

	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class ArtifactServiceProxy : public OpaqueWrapper<const ArtifactService, ArtifactServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const ArtifactService, ArtifactServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class CreatureServiceProxy : public OpaqueWrapper<const CreatureService, CreatureServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const CreatureService, CreatureServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class FactionServiceProxy : public OpaqueWrapper<const FactionService, FactionServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const FactionService, FactionServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class HeroClassServiceProxy : public OpaqueWrapper<const HeroClassService, HeroClassServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const HeroClassService, HeroClassServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class HeroTypeServiceProxy : public OpaqueWrapper<const HeroTypeService, HeroTypeServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const HeroTypeService, HeroTypeServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class SkillServiceProxy : public OpaqueWrapper<const SkillService, SkillServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const SkillService, SkillServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

class SpellServiceProxy : public OpaqueWrapper<const spells::Service, SpellServiceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const spells::Service, SpellServiceProxy>;
	static const std::vector<typename Wrapper::RegType> REGISTER;
};

}
}


