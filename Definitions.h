//constains all classes declarations and other things
//#define DEBUG_MESSAGES
//#define SHADER_MESSAGES //Display shader uniform messages (not found etc)

//external includes
//SLD
#include <SDL.h>
//FreeImage
#include <FreeImage.h>
//OPENGL
#include <gl\glew.h>
#include <gl\gl.h>
//GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_access.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\norm.hpp>
#include <glm\gtx\component_wise.hpp>
//ASSIMP
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp/scene.h>
#include <assimp/types.h>
#include <assimp/vector3.h>
//BULLET
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include<BulletCollision\NarrowPhaseCollision\btRaycastCallback.h>
//FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

//custom type for decimals, default: float
typedef float real;



//forward declarations of classes
//allow declaration of pointers to them
class Camera;
class CollisionObject;
class Entity;
class EventFunction;
class FrameBuffer;
class InputManager;
class Light;
class Material;
class Math;
class Mesh;
class MovableObject;
class PhysicsManager;
class RayCast;
class Renderer;
class ResourceManager;
class RigidBody;
class Root;
class SceneManager;
class SceneNode;
class Shader;
class Texture;
class Timer;
class UIButton;
class UIDisplayer;
class UILabel;
class UIManager;
class UIObject;
class UIWindow;
class Window;

//Not included
//class Singleton
//class GameResource;