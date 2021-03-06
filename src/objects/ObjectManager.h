#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <GL/glew.h>
#include <vector>
#include "src/texture/TextureManager.h"
#include "src/geometry/GeometryManager.h"
#include "src/animation/AnimationManager.h"
#include "src/collision/CollisionManager.h"
#include "Camera.h"
#include "Skybox.h"

class Board;
class Clock;
class Drawable;
class Updatable;

class ObjectManager
{
public:
  ObjectManager();
  void Init();
  void NewGame();
  void Update(float elapsedTime);
  void Draw();
  void AddObject(std::shared_ptr<Drawable> object);
  void AddObject(std::shared_ptr<Updatable> object);
  void AddPost(std::shared_ptr<Drawable> object);

  void MouseButton(int button, int action);
  void MouseMove(double xPos, double yPos);
  void MouseWheel(double xOffset, double yOffset);

  // Stores the state of the game. represents current game
  Board* game_board = nullptr;
  Clock* clock{};

  void SetTheme(int theme);

  static ObjectManager instance;
  static TextureManager texture;
  static GeometryManager geometry;
  static AnimationManager animation;
  static CollisionManager collision;

protected:
  static void UpdateFramebuffer(GLuint& framebuffer, GLuint& texture, GLuint& depth, int width, int height);
  std::vector<std::shared_ptr<Updatable>> updatables_;
  std::vector<std::shared_ptr<Drawable>> objects_, post_processors_;
  Camera camera_;
  Skybox skybox_;
  bool mouse_down_happened_ = false, mouse_up_happened_ = false;
  std::shared_ptr<Drawable> mouse_down_object_ = nullptr;
  glm::vec2 last_mouse_;
  int theme_{};

private:
  std::shared_ptr<Drawable> GetClickedObject(glm::vec2 mousePos, glm::mat4 viewProjection) const;
  static glm::mat4 MirrorMat(glm::vec3 normal, float distance);
  GLuint mirror_frame_buffer_ = 0;
  GLuint mirror_texture_ = 0;
  GLuint mirror_depth_ = 0;
  GLuint post_frame_buffer_ = 0;
  GLuint post_texture_ = 0;
  GLuint post_depth_ = 0;
  GLuint post_frame_buffer_2_ = 0;
  GLuint post_texture_2_ = 0;
  GLuint post_depth_2_ = 0;
  GLuint shadow_frame_buffer_ = 0;
  GLuint shadow_texture_ = 0;
  GLuint shadow_depth_ = 0;
  int res_width_ = 0, res_height_ = 0;
};


#endif // OBJECT_MANAGER_H
