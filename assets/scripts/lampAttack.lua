--Script generated by GroveW

lampDamage = 15.0
lampHitInterval = 3.0

function lampAttackStart()
    setBoundingBox(entity, componentManager, false)
    local enemyEntity = -1
    for i, e in pairs(enemies) do
        if e.colliderEntity == -1 then
            e.colliderEntity = entity
            e.attackCoFunc = lampAttackCoroutine
            enemyEntity = i
            break
        end
    end

    local lamp = {attacking = false, enemyEntity = enemyEntity, attackTimeStamp = 0.0, hitTimeStamp = 0.0, hitInterval = 5.0}
    lamps[entity] = lamp
end

function lampAttackUpdate(dt)
    if lamps[entity].attacking == false then
        setPositionRelativeToEnemy(0.0, 0.0, 0.0, enemies[lamps[entity].enemyEntity])
    end
end

function lampAttackCoroutine(dt)
    lamps[enemy.colliderEntity].attacking = true
    setBoundingBox(enemy.colliderEntity, componentManager, true)

    local wait = 0.9
    local timeStamp = time

    while time - timeStamp < wait do
        dt = coroutine.yield()
    end

    local z = 0.0
    while z < 3.0 do
        z = z + (10.0 * dt)
        setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
        dt = coroutine.yield()
    end
    z = 3.0
    setPositionRelativeToEnemy(0.0, 0.0, z, enemy)

    setBoundingBox(enemy.colliderEntity, componentManager, false)

    while z > 0.0 do
        z = z - (20.0 * dt)
        setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
        dt = coroutine.yield()
    end

    z = 0.0
    setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
    lamps[enemy.colliderEntity].attacking = false
end

function lampAttackOnCollisionEnter(box)
    if time - lamps[entity].hitTimeStamp >= damageInterval and getTag(box) == "player" then
        lamps[entity].hitTimeStamp = time
        playerGetHit(lampDamage)
    end
end