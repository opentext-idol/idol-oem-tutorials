local redaction_character = "x"


function processmatch (edkmatch)
    if edkmatch then
		local text = edkmatch:getMatchedText()
		local first, middle, last = regex_match(text, "(\\d{4})(.*)(\\d{4})")
		middle = regex_replace_all(middle, "\\d", redaction_character)
		
		edkmatch:setOutputText(first .. middle .. last) 
	end
	
	return true
end
