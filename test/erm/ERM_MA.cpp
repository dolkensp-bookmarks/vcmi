/*
 * ERM_MA.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "../scripting/ScriptFixture.h"
#include "../JsonComparer.h"

#include "../../lib/NetPacks.h"
#include "../../lib/serializer/Cast.h"

#include "../mock/mock_CreatureService.h"
#include "../mock/mock_Creature.h"

namespace test
{
namespace scripting
{

using namespace ::testing;

class ERM_MA : public Test, public ScriptFixture
{
public:
	CreatureServiceMock creatureService;
	CreatureMock oldCreature;

	std::vector<EntityChanges> actualChanges;

	void onCommit(CPackForClient * pack)
	{
		EntitiesChanged * ec = dynamic_ptr_cast<EntitiesChanged>(pack);

		if(ec)
		{
			vstd::concatenate(actualChanges, ec->changes);
		}
		else
		{
			GTEST_FAIL() << "Invalid NetPack";
		}
	}

protected:
	void SetUp() override
	{
		ScriptFixture::setUp();
		EXPECT_CALL(servicesMock, creatures()).WillRepeatedly(Return(&creatureService));
		EXPECT_CALL(creatureService, getByIndex(Eq(68))).WillRepeatedly(Return(&oldCreature));
	}
};

TEST_F(ERM_MA, Example)
{
	const int32_t COST = 876;
	const int32_t ATTACK = 19;
	const int32_t DEFENSE = 17;
	const int32_t HIT_POINTS = 55;
	const int32_t SPEED = 10;
	const int32_t DAMAGE_MIN = 13;
	const int32_t DAMAGE_MAX = 21;
	const int32_t SHOTS = 1;
	const int32_t CASTS = 3;
	const int32_t GROWTH = 10;
	const int32_t HORDE = 9;
	const int32_t AI_VALUE = 3300;
	const int32_t FIGHT_VALUE = 2400;
	const int32_t LEVEL = 7;
	const int32_t FACTION = 35;

	const int32_t FLAG_MASK = 394370;

	static_assert(FLAG_MASK == (1 << 1 | 1 << 7 | 1 << 10 | 1 << 17 | 1 << 18), "Wrong flag mask meaning");

	EXPECT_CALL(oldCreature, getCost(Eq(6))).WillOnce(Return(COST));
	EXPECT_CALL(oldCreature, getBaseAttack()).WillOnce(Return(ATTACK));
	EXPECT_CALL(oldCreature, getBaseDefense()).WillOnce(Return(DEFENSE));
	EXPECT_CALL(oldCreature, getBaseHitPoints()).WillOnce(Return(HIT_POINTS));
	EXPECT_CALL(oldCreature, getBaseSpeed()).WillOnce(Return(SPEED));
	EXPECT_CALL(oldCreature, getBaseDamageMin()).WillOnce(Return(DAMAGE_MIN));
	EXPECT_CALL(oldCreature, getBaseDamageMax()).WillOnce(Return(DAMAGE_MAX));
	EXPECT_CALL(oldCreature, getBaseShots()).WillOnce(Return(SHOTS));

	EXPECT_CALL(oldCreature, getGrowth()).WillOnce(Return(GROWTH));
	EXPECT_CALL(oldCreature, getBaseSpellPoints()).WillOnce(Return(CASTS));
	EXPECT_CALL(oldCreature, getHorde()).WillOnce(Return(HORDE));
	EXPECT_CALL(oldCreature, getAIValue()).WillOnce(Return(AI_VALUE));
	EXPECT_CALL(oldCreature, getFightValue()).WillOnce(Return(FIGHT_VALUE));
	EXPECT_CALL(oldCreature, getLevel()).WillOnce(Return(LEVEL));
	EXPECT_CALL(oldCreature, getFactionIndex()).WillOnce(Return(FACTION));

	EXPECT_CALL(oldCreature, isDoubleWide()).WillOnce(Return(false));

	EXPECT_CALL(serverMock, apply(Matcher<CPackForClient *>(_))).Times(AtLeast(1)).WillRepeatedly(Invoke(this, &ERM_MA::onCommit));

	std::stringstream source;
	source << "VERM" << std::endl;
	source << "!#MA:C68/6/?v1 A68/?v2 D68/?v3 P68/?v4 S68/?v5 M68/?v6 E68/?v7 N68/?v8 G68/?v9 B68/?v10 R68/?v11 I68/?v12 F68/?v13 L68/?v14 O68/?v15 X68/?v16;" << std::endl;
	source << "!#MA:C68/6/750 A68/17 D68/15 P68/50 S68/9 M68/12 E68/20 N68/0 G68/1 B68/2 R68/0 I68/3388 F68/2420 L68/6 O68/4 X68/394371;" << std::endl;

	{
		loadScript(VLC->scriptHandler->erm, source.str());
		SCOPED_TRACE("\n" + subject->code);
		runServer();
	}

	JsonNode actualState = context->saveState();

	const JsonNode & v = actualState["ERM"]["v"];

	EXPECT_EQ(v["1"].Integer(), COST);
	EXPECT_EQ(v["2"].Integer(), ATTACK);
	EXPECT_EQ(v["3"].Integer(), DEFENSE);
	EXPECT_EQ(v["4"].Integer(), HIT_POINTS);
	EXPECT_EQ(v["5"].Integer(), SPEED);
	EXPECT_EQ(v["6"].Integer(), DAMAGE_MIN);
	EXPECT_EQ(v["7"].Integer(), DAMAGE_MAX);
	EXPECT_EQ(v["8"].Integer(), SHOTS);

	EXPECT_EQ(v["9"].Integer(), GROWTH);
	EXPECT_EQ(v["10"].Integer(), CASTS);
	EXPECT_EQ(v["11"].Integer(), HORDE);
	EXPECT_EQ(v["12"].Integer(), AI_VALUE);
	EXPECT_EQ(v["13"].Integer(), FIGHT_VALUE);
	EXPECT_EQ(v["14"].Integer(), LEVEL);
	EXPECT_EQ(v["15"].Integer(), FACTION);
	EXPECT_EQ(v["16"].Integer(), FLAG_MASK);

	JsonNode merged(JsonNode::JsonType::DATA_STRUCT);

	for(EntityChanges & change : actualChanges)
	{
		EXPECT_EQ(change.metatype, Metatype::CREATURE);
		EXPECT_EQ(change.entityIndex,68);
		JsonUtils::merge(merged, change.data);
	}

	JsonNode expectedMerged(JsonNode::JsonType::DATA_STRUCT);

	JsonNode & config = expectedMerged["config"];
	config["cost"]["gold"].Integer() = 750;
	config["attack"].Integer() = 17;
	config["defense"].Integer() = 15;
	config["hitPoints"].Integer() = 50;
	config["speed"].Integer() = 9;
	config["damage"]["min"].Integer() = 12;
	config["damage"]["max"].Integer() = 20;
	config["shots"].Integer() = 0;

	config["growth"].Integer() = 1;
	config["spellPoints"].Integer() = 2;
	config["horde"].Integer() = 0;
	config["aiValue"].Integer() = 3388;
	config["fightValue"].Integer() = 2420;
	config["level"].Integer() = 6;
	config["faction"].Integer() = 4;

	{
		JsonComparer c(false);
		c.compare("updateData", merged, expectedMerged);
	}

}


}
}
