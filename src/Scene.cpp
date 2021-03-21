#include "Scene.hpp"

Scene* Scene::getNextScene() {
	return nextScene;
}

void Scene::destroyNextScene() {
	nextScene = NULL;
}
