#include "animation_engine.h"

void AnimationEngine::setSpriteName(AnimationState state, const std::string& name) {
    spriteNames[state] = name;
}

AnimationState AnimationEngine::nextRunState() {
    runCounter++;
    if(runCounter < maxTicks){
        return lastState;
    }
    const AnimationState runStates[6] = {run1, run2, run3, run4, run5, run6};
    const AnimationState* last = std::find(std::begin(runStates), std::end(runStates), lastState);
    long index = std::distance(runStates, last);
    runCounter = 0;
    return runStates[(index + 1) % 6];

}

Texture* AnimationEngine::getSprite(CharacterState characterState) {
    AnimationState state;
    switch(characterState){
        case normal:
            state = idle;
            break;
        case jumping:
            state = jump;
            break;
        case falling:
            state = fall;
            break;
        case running:
            state = nextRunState();
            break;
    }
    lastState = state;
    std::string name = spriteNames[state];
    Texture* texture = resourceManager->getTexture(name);
    return texture;
}
