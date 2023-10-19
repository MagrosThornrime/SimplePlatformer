#pragma once

#include "../resources/resource_manager.h"
#include "characters.h"
#include "algorithm"

enum AnimationState{
    idle,
    jump,
    fall,
    run1,
    run2,
    run3,
    run4,
    run5,
    run6
};

class AnimationEngine{
    ResourceManager* resourceManager;
    std::map<AnimationState, std::string> spriteNames;
    AnimationState lastState;
    int runCounter = 0;
    int maxTicks = 7;

    AnimationState nextRunState();

public:
    explicit AnimationEngine(ResourceManager* resourceManager) : resourceManager(resourceManager), lastState() {}

    void setSpriteName(AnimationState state, const std::string& name);
    Texture* getSprite(CharacterState characterState);
};