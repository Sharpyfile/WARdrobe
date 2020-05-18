#pragma once

#include "ecs.hpp"
#include "Model.hpp"
#include "Animator.hpp"

class AnimationSystem : public System
{
public:
    void Update(float                             dt,
	            std::shared_ptr<ComponentManager> componentManager) override;
	void Init(std::shared_ptr<ComponentManager> componentManager);
};


void AnimationSystem::Init(std::shared_ptr<ComponentManager> componentManager)
{
	
    for (auto& entity : entities)
	{		
	 	auto& model = componentManager->GetComponent<Model>(entity);
	 	auto& animator = componentManager->GetComponent<Animator>(entity);
	 	animator.animatedModel = &componentManager->GetComponent<Model>(entity);
	 	animator.PlayAnimation(&model.animations.at(0));		 
	}
}

void AnimationSystem::Update(float                             dt,
	            std::shared_ptr<ComponentManager> componentManager)
{
    for (auto& entity : entities)
	{
		auto& animator = componentManager->GetComponent<Animator>(entity);
		animator.Update(dt);		 
	}
}