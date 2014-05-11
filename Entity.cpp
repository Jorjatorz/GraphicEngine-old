#include "Entity.h"


#include "Mesh.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneNode.h"

Entity::Entity(std::string mNewName, SceneManager* newSceneManager)
{
	//apart from movableobject constructor
	mName = mNewName;
	mModelMatrix = glm::mat4(1.0); //identity
	mMesh = NULL;
	mMeshName = "NULL";
	mMaterial = ResourceManager::getSingletonPtr()->createMaterial("DefaultMaterial"); 
	mSceneManager = newSceneManager;
	meshAttached = false;

	mTypeOfMovableObject = tTypeEnum::Entity;
}

Entity::Entity(std::string mNewName, std::string meshName, SceneManager* newSceneManager)
{
	mName = mNewName;
	mModelMatrix = glm::mat4(1.0); //identity
	mSceneManager = newSceneManager;
	meshAttached = false;
	mMaterial = ResourceManager::getSingletonPtr()->createMaterial("DefaultMaterial"); 

	mTypeOfMovableObject = tTypeEnum::Entity;

	attachMesh(meshName); //load mesh
}


Entity::~Entity(void)
{
}

void Entity::process(glm::mat4 perspectiveViewSceneNodeM, glm::mat4 viewMatrix, glm::vec3 parentPos, glm::vec3 parentOrient)
{
	render(perspectiveViewSceneNodeM);
}

#include "Root.h"
#include "Timer.h"
#include "Material.h"

void Entity::render(glm::mat4 perspectiveViewSceneNodeM)
{
	if(meshAttached)
	{
		//apply shader
		Shader* shad = mMaterial->getShader();
		mSceneManager->bindShader(shad);

		//Send uniforms	

		//send matrix
		glm::mat4 finalMatrix = perspectiveViewSceneNodeM * mModelMatrix; //final matrix composed of pers * view * node * model matrix
		shad->UniformMatrix("finalM", finalMatrix);
		glm::mat4 normalM = glm::inverseTranspose(mSceneManager->getViewMatrix() * mParentSceneNode->getSceneNodeMatrix() * mModelMatrix);
		shad->UniformMatrix("normalM", normalM);
		//send material uniforms
		mMaterial->applyMaterial();

		for(int i = 0; i < mMesh->mMeshComponentsVector.size(); ++i)
		{
			//render
			mMesh->bindMeshArray(mMesh->mMeshComponentsVector[i]);

			glDrawElements(GL_TRIANGLES, mMesh->mMeshComponentsVector[i].mIndexVector.size(), GL_UNSIGNED_INT, 0);

			mMesh->unbindMeshArray();

		}

		mSceneManager->unbindShader();
	}
}

void Entity::attachMesh(std::string meshName)
{
	mMeshName = meshName;

	ResourceManager* mResourceManager = ResourceManager::getSingletonPtr(); //resourcemanager pointer
	mMesh = mResourceManager->loadMesh(mMeshName, mMeshName); //allocate new mesh

	mModelMatrix = mMesh->meshMatrix;

	meshAttached = true;
}

void Entity::deAttachMesh()
{
	mMeshName = "NULL";
	mMesh = NULL;
	meshAttached = false;
}

void Entity::attachMaterial(std::string materialName)
{
	mMaterial = ResourceManager::getSingletonPtr()->loadMaterial(materialName, materialName);
}