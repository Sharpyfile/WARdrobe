--Script generated by GroveW

function pillRedStart()
end

function pillRedUpdate(dt)
end

function addToEQ(type)
    if eqFull() == false then
        addToEquipment(type)
        destroyEntity(gameplayManager, entity)
    end
end

function pillRedOnCollisionEnter(box)
    if getTag(box) == "player" then
        addToEQ("red")
    end
end