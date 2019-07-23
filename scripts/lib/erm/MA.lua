local logError = logError
local ReceiverBase = require("core:erm.ReceiverBase")
local EntitiesChanged = require("netpacks.EntitiesChanged")

local CREATURE = 3

local RES = {[0] = "wood", [1] = "mercury", [2] = "ore", [3] = "sulfur", [4] = "crystal", [5] = "gems", [6] = "gold", [7] = "mithril"}

local SERVICES = SERVICES
local creatures = SERVICES:creatures()

local getCreatureByIndex = creatures.getByIndex
local function creatureByIndex(index)
	return getCreatureByIndex(creatures, index)
end

local function sendChanges(creatureIndex, data)
	local pack = EntitiesChanged.new()

	pack:update(CREATURE, creatureIndex, data)

	SERVER:commitPackage(pack)
end

local MA = ReceiverBase:new()

local function checkCreatureIndex(creatureIndex)
	assert(creatureIndex ~= nil, "!!MA requires creature identifier")

	if type(creatureIndex) == "string" then
		error("Identifier resolving is not implemented")
	end

	return creatureIndex
end

local function createModifier(scope, jsonKey, getterKey)

	local f = function (Self, x, creatureIndex, p1)
		local creatureIndex = checkCreatureIndex(creatureIndex)

		if p1 == nil then
			local creature = creatureByIndex(creatureIndex)
			return nil, creature[getterKey](creature)
		else
			local packData = {config = {}}

			local config = packData.config

			for _, v in ipairs(scope) do
				config[v] = {}
				config = config[v]
			end

			config[jsonKey] = p1

			sendChanges(creatureIndex, packData)
			return
		end
	end

	return f
end

MA.A = createModifier({}, "attack", "getBaseAttack")
MA.B = createModifier({}, "spellPoints" ,"getBaseSpellPoints")
MA.D = createModifier({}, "defense" ,"getBaseDefense")
MA.E = createModifier({"damage"}, "max", "getBaseDamageMax")
MA.F = createModifier({}, "fightValue" ,"getFightValue")
MA.G = createModifier({}, "growth" ,"getGrowth")
MA.H = createModifier({"advMapAmount"}, "max" ,"getAdvMapAmountMax")
MA.I = createModifier({}, "aiValue" ,"getAIValue")
MA.L = createModifier({}, "level" , "getLevel")
MA.M = createModifier({"damage"}, "min", "getBaseDamageMin")
MA.N = createModifier({}, "shots" , "getBaseShots")
MA.O = createModifier({}, "faction" ,"getFactionIndex")
MA.P = createModifier({}, "hitPoints" ,"getBaseHitPoints")
MA.R = createModifier({}, "horde" , "getHorde")
MA.S = createModifier({}, "speed" , "getBaseSpeed")
MA.V = createModifier({"advMapAmount"}, "min","getAdvMapAmountMin")

function MA:C(x, creatureIndex, resIndex, cost)
	local creatureIndex = checkCreatureIndex(creatureIndex)

	if cost == nil then
		local creature = creatureByIndex(creatureIndex)
		return nil, nil, creature:getCost(resIndex)
	else
		local packData = {config = {cost = {[RES[resIndex]] = cost}}}
		sendChanges(creatureIndex, packData)
	end
end

function MA:U(x, creatureIndex, upgradeIndex)
	-- -2 - no upgrade
	-- -1 - usual upgrade
	logError("!!MA:U is not implemented")
end


function MA:X(x, creatureIndex, flagsMask)
	logError("!!MA:X is not implemented")
	return
end

return MA
