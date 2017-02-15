#ifndef SCENE_H
#define SCENE_H

class Game;

class Scene {

public:
     Scene(Game* pGame);
     ~Scene();
     virtual bool load() = 0;
     virtual bool update(float) = 0;
     virtual bool unload() = 0;

protected:
     Game* mGame;
};

#endif /* SCENE_H */
