function processmatch (edkmatch)
    if edkmatch then
        local text = edkmatch:getOutputText()
        if text:len() > 8 then
            return false
        end
        return true
    end
end