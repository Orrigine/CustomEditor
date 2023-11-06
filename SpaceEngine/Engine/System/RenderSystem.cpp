#include "RenderSystem.h"

namespace SpaceEngine {
	RenderSystem::RenderSystem()
	{
	}

	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::init(
		std::unordered_map<unsigned int, std::shared_ptr<Entity>>* 
		sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication)
	{
		std::unordered_map<unsigned int, std::shared_ptr<Transform>> 
			transormComponents = Transform::getComponents();
		std::unordered_map<unsigned int, std::shared_ptr<BoxMesh>> 
			boxMeshComponents =  BoxMesh::getComponents();
		std::unordered_map<unsigned int, std::shared_ptr<SphereMesh>>
			sphereMeshComponents = SphereMesh::getComponents();

		for (auto elm = sceneEntitiesMap->begin(); elm != sceneEntitiesMap->end(); elm++) {
			unsigned int entityId = elm->first;
			Vector3f position = transormComponents[entityId]->getPosition();
			Vector3f rotation = transormComponents[entityId]->getRotation();
			Vector3f scale = transormComponents[entityId]->getScale();
			if (boxMeshComponents[entityId]) {
				/*Vector3f position = transormComponents[entityId]->getPosition();
				Vector3f rotation = transormComponents[entityId]->getRotation();
				Vector3f scale = transormComponents[entityId]->getScale();*/
				renderApplication->createGameObject(boxMeshComponents[entityId]->getMeshType(), DirectX::Colors::BurlyWood,
					position.x, position.y, position.z, scale.x, scale.y, scale.z);
					//cout << elm->first << " \t\t\t" << i->second << endl;
			}
			if (sphereMeshComponents[entityId]) {
				renderApplication->createGameObject(sphereMeshComponents[entityId]->getMeshType(), DirectX::Colors::BurlyWood,
					position.x, position.y, position.z, scale.x, scale.y, scale.z);
			}
		}
	}

	void RenderSystem::update(std::unordered_map<unsigned int, std::shared_ptr<Entity>>* sceneEntitiesMap, std::shared_ptr<Render::Window> renderApplication)
	{

	}
}