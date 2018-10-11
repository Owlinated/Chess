#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Field.h"
#include "ObjectManager.h"
#include "src/Objects.h"
#include "src/animation/FadeAnimation.h"
#include "src/Config.h"
#include "src/Logger.h"
#include "src/texture/Shader.h"
#include "src/geometry/Geometry.h"
#include "src/collision/Collision.h"
#include "Board.h"
#include "src/texture/Texture.h"


Field::Field(Board* board, const int boardX, const int boardY, const bool inactive) {
  inactive_ = inactive;
  board_ = board;
  boardX_ = boardX;
  boardY_ = boardY;
  position_ = glm::vec3(boardX_ * 2 - 7, 0, boardY_ * 2 - 7);
  object_id_ = objects::field00 + boardX * 8 + boardY;
  const auto size = glm::vec3(2, 10, 2);
  boundingBox_ = CollisionManager::GetAABB(CenterPosition() - size * 0.5f, CenterPosition() + size * 0.5f);
}

void Field::Init() {
  Drawable::Init();
  geometry_ = ObjectManager::geometry.GetCube();

  model_view_matrix_ = scale(glm::mat4(), glm::vec3(1, 0.5f, 1));
  model_view_matrix_ = translate(model_view_matrix_, CenterPosition());
}

void Field::RecreateGeometry() {
  // Fields geometry is always a cube
}

void Field::Draw(glm::mat4 projectionMatrix) {
  if (inactive_) return;

  if (program_ == nullptr) {
    Logger::Error("program not loaded");
  }
  program_->Use();

  ObjectManager::texture.GetTexture(object_id_)[0]->Bind();
  if (ovelayOpacity_ > 0) {
    ObjectManager::texture.GetTexture(object_id_)[overlayNumber_]->Bind(GL_TEXTURE_2D, 1);
    const auto animateOverlay = overlayNumber_ == 2;
    program_->Bind(animateOverlay, "textureAnimated");
    if (animateOverlay) {
      const auto overlayRotation = board_->overlay_rotation;
      auto rotation = glm::mat2(cos(overlayRotation), sin(overlayRotation), -sin(overlayRotation), cos(overlayRotation));
      rotation *= board_->overlay_scale;
      program_->Bind(rotation, "texTransform");
    }
  }

  glActiveTexture(GL_TEXTURE0 + 2);
  glBindTexture(GL_TEXTURE_2D, reflection_texture);
  glActiveTexture(GL_TEXTURE0 + 3);
  glBindTexture(GL_TEXTURE_2D, shadow_texture);

  program_->Bind(0, "tex");
  program_->Bind(1, "texOverlay");
  program_->Bind(2, "texReflection");
  program_->Bind(3, "texShadow");

  auto texSize = glm::vec2(Config::viewport_width, Config::viewport_height);
  program_->Bind(texSize, "texSize");

  program_->Bind(ovelayOpacity_, "overlayOpacity");

  auto view_projection_shadow = shadow_view_projection * model_view_matrix_;
  auto tra_inv_model_matrix = transpose(inverse(model_view_matrix_));
  program_->Bind(projectionMatrix, "view_projection_matrix");
  program_->Bind(view_projection_shadow, "view_projection_shadow");
  program_->Bind(model_view_matrix_, "model_matrix");
  program_->Bind(tra_inv_model_matrix, "tra_inv_model_matrix");

  program_->Bind(light_pos, "lightPos");
  program_->Bind(cam_pos, "camPos");

  auto la = glm::vec3(0.5f, 0.5f, 0.5f);
  auto ka = glm::vec3(0.5f, 0.5f, 0.5f);
  auto ld = glm::vec3(0.5f, 0.5f, 0.5f);
  auto kd = glm::vec3(1, 1, 1);
  program_->Bind(la, "La");
  program_->Bind(ka, "ka");
  program_->Bind(ld, "Ld");
  program_->Bind(kd, "kd");

  program_->Bind(ObjectManager::texture.Reflectivity(object_id_), "reflectivity");
  program_->Bind(ObjectManager::texture.Shininess(object_id_), "shininess");

  geometry_->Draw();
}

void Field::DrawShadow(glm::mat4 projection_matrix) {
  if (inactive_) return;
  program_shadow_->Use();

  auto view_projection_shadow = projection_matrix * model_view_matrix_;
  program_shadow_->Bind(view_projection_shadow, "view_projection_shadow");

  geometry_->Draw();
}

void Field::Update(float elapsedTimeMs) {
  (void)elapsedTimeMs;
}

void Field::MouseClick(glm::vec3 position) {
  if (!boundingBox_->Contains(position)) return;
  if (CurrentPiece) {
    board_->PieceClick(CurrentPiece);
  }
  else {
    board_->FieldClick(this);
  }
}

glm::vec3 Field::TopPosition() const
{
  if (inactive_)
    return CenterPosition();
  return position_;
}

glm::vec3 Field::CenterPosition() const
{
  return position_ - glm::vec3(0, 1, 0);
}

std::string Field::GetVertexShader() {
  return "res/shader/Mirror.vs.glsl";
}

std::string Field::GetFragmentShader() {
  return "res/shader/Mirror.fs.glsl";
}

void Field::EnableOverlay(const bool enabled) {
  if (enabled != overlayEnabled_) {
    ObjectManager::animation.PlayIndependent(new FadeAnimation<float>(350, ovelayOpacity_, overlayEnabled_, enabled));
  }

  overlayEnabled_ = enabled;
}

void Field::SetOverlayNumber(int overlay) {
  overlayNumber_ = overlay;
}

int Field::Row() const
{
  return boardX_;
}

int Field::Column() const
{
  return boardY_;
}

glm::vec3 Field::Position3D() {
  return CenterPosition();
}