--Script generated by GroveW

lampDamage = 15.0
lampHitInterval = 3.0

lamps = {}

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

    local lamp = {attacking = false, enemyEntity = enemyEntity, attackTimeStamp = 0.0}
    lamps[entity] = lamp
end

function lampAttackUpdate(dt)
    if lamps[entity].attacking == false then
        setPositionRelativeToEnemy(0.0, 0.0, 0.0, enemies[lamps[entity].enemyEntity])
    end
end

function performAttack(dt)
    local enemy = enemies[entity]
    enemy.attackCo = coroutine.create(enemy.attackCoFunc)
    coroutine.resume(enemy.attackCo, dt)
end

function continueAttack(dt)
    local enemy = enemies[entity]
    coroutine.resume(enemy.attackCo, dt)
end

function lampAttackCoroutine(dt)
    lamps[enemy.colliderEntity].attacking = true
    setBoundingBox(enemy.colliderEntity, componentManager, true)

    local wait = 0.7
    local timeStamp = time

    while time - timeStamp < wait do
        dt = coroutine.yield()
    end

    local z = 0.0
    while z < 4.0 do
        z = z + (5.0 * dt)
        setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
        dt = coroutine.yield()
    end
    z = 4.0
    setPositionRelativeToEnemy(0.0, 0.0, z, enemy)

    while z > 0.0 do
        z = z - (10.0 * dt)
        setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
        dt = coroutine.yield()
    end

    z = 0.0
    setPositionRelativeToEnemy(0.0, 0.0, z, enemy)
    lamps[enemy.colliderEntity].attacking = false

    setBoundingBox(enemy.colliderEntity, componentManager, false)
end

function setPositionRelativeToEnemy(x, y, z, enemy)
    setTransformRelToRotatingParent(enemy.colliderEntity, componentManager, enemy.position.x, enemy.position.y, enemy.position.z, 
    x, y, z,
    enemy.rotation.x, enemy.rotation.y, enemy.rotation.z)
end

function lampAttackOnCollisionEnter(box)
    if time - lamps[entity].attackTimeStamp >= lampHitInterval and getTag(box) == "player" then
        lamps[entity].attackTimeStamp = time
        playerGetHit(lampDamage)
    end
end