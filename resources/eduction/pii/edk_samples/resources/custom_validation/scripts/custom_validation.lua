-- This sample script leverages getMatchContext() configured with ContextCharactersBeforeMatch / ContextCharactersAfterMatch.
-- Two use cases are represented in this sample script:
-- 1. custom validation to reduce false positives in particular scenarios
-- 2. returning a context window as an edkmatch component that yields more information about the match

local invalid_prefix_regex = {}
invalid_prefix_regex['pii/medical_terms/icd10cm/eng'] = ".*\\/$"	-- check for trailing slash as in a URL

local invalid_postfix_regex = {}
invalid_postfix_regex['pii/medical_terms/icd10cm/eng'] = "^\\/.*"	-- check for leading slash as in a URL

-- NOTE: the extra \ in the RegEx is an artifact of Lua using \ as an escape character
-- NOTE: Assumption below is that BOTH invalid_prefix_regex[] and invalid_postfix_regex[] have patterns.  Accommodations to allow for either to have pattern or nil could be made.

function processmatch (edkmatch)
	local invalid_match = false

	local before, matched, after
	
    if edkmatch then
		local entity_name = edkmatch:getEntityName()
		--print("")
		--print("entity: " .. entity_name)
		--print("original: " .. edkmatch:getMatchedText())
		--print("normalized: " .. edkmatch:getOutputText())

		--local before, matched, after = "" 
		before, matched, after = edkmatch:getMatchContext()
		-- make sure before is not nil due to CFG not enabling
		if (before == nil) then
			return true
		end
		
		-- check if entity has all numeric values
		if (is_all_numeric(edkmatch:getMatchedText()) == true) then
			--print("Original value is all numeric")

			-- All numeric entities could be embedded in a floating point number and result in a match because . or , is typically treated as whitespace.
	
			-- See if before text is acceptable per invalid_prefix_regex[]
			-- Then check after if before passes. Do before separate from after is intentional, so as to do less work when possible. 
			-- NOTE: allowing for either . or , as delimiter accounts for varying number formatting conventions per locale.
			-- NOTE: a leading or trailing digit is intentionally required in this example to permit "My SSN is 12345679. Please do not share."
			-- NOTE: the extra \ is for \d is artifact of Lua using \ as an escape character

			--print("before text: " .. before)
			--print("after text: " .. after)
			-- if there's digits and . or , before then a floating number or similar was found

			if (regex_search(before, "\\d+[,.]$") ~= nil) then
				--print("before portion triggered invalid match")
				invalid_match = true
			else
				-- if there's digits and . or , before then a floating number or similar was found
				if (regex_search(after, "^[.,]\\d+") ~= nil) then
					--print("after portion triggered invalid match")
					invalid_match = true
				end
			end
		else
			-- see if current match has a validation pattern
			if (invalid_prefix_regex[entity_name] ~= nil) then

				--print("entity found in invalid_prefix_regex[] table")
				--print("before text: " .. before)
				--print("after text: " .. after)
				--print("invalid_prefix_regex: " .. invalid_prefix_regex[entity_name])
				--print("invalid_postfix_regex: " .. invalid_postfix_regex[entity_name])
			
				if (regex_match(before, invalid_prefix_regex[entity_name]) ~= nil) then
					--print("before portion triggered invalid match")
					invalid_match = true
				else
					if (regex_match(after, invalid_postfix_regex[entity_name]) ~= nil) then
						--print("after portion triggered invalid match")
						invalid_match = true
					else
						--print("invalid_*_regex[] failed, so valid match")
					end
				end
			else
				--print("skipping validation, entity NOT found in invalid_prefix_regex[]")
			end
		end
	end
	
	-- add a component MATCH_CONTEXT to address use case #2
	-- using gobble_whitespace() around combined text maybe make sense to add
	local component = edkmatch:addComponent("MATCH_CONTEXT", 0, 0)
	component:setText(before .. matched .. after)		
	
	if (invalid_match == true) then
		--print("returning false, aka invalid")
		return false
	else
		--print("returning true, aka valid")
		return true
	end
end

function is_all_numeric(value)

	-- NOTE: adding remove delimiters from all numeric pattern using utils.extract_digits in common/utils.lua is a consideration.	
	
	if (regex_match(value, "\\d+") ~= nil) then
		return true
	end

	return false
end