-- assumes that the config postProcessThreshold is set low to allow for the logic in this script to take precedence.


-- add entities by name with custom score threshold to this table
local custom_pp_threshold = {}
custom_pp_threshold['pii/id/nocontext/ar'] = 0.45
custom_pp_threshold['pii/id/context/ar'] = 0.45
custom_pp_threshold['pii/id/nocontext/us'] = 0.45
custom_pp_threshold['pii/id/context/us'] = 0.45

-- entities not configured will use this new value
local custom_default_pp_threshold = 0.5

function processmatch (edkmatch)
    if edkmatch then
		local entity_name = edkmatch:getEntityName()
		local score = edkmatch:getScore()
		--print("name: " .. entity_name)
		--print("value: " .. edkmatch:getOutputText())
		--print("score: " .. score)

		if (custom_pp_threshold[entity_name] ~= nil) then
			--print("entity found in custom_pp_threshold[] table")
			if (score < custom_pp_threshold[entity_name]) then
				--print("score too low")
				return false
			end
		else
			--print("entity NOT found in custom_pp_threshold[] table")
			if (score < custom_default_pp_threshold) then
				--print("score too low")
				return false
			end
		end	
	end
	
	return true
end
