#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
  Camera();
  void Init();
  void Reset();
  void MouseDown();
  void MouseUp();
  void MouseMove(glm::vec2 mousePos);
  // 1 corresponds to 1 revolution
  void MouseWheel(float wheelDelta);
  void SetBoardSide(bool whiteSide);
  glm::mat4 ViewMat() const;
  glm::mat4 ViewMatAtCamera() const;
  glm::mat4 ViewProjectionShadow() const;
  static glm::mat4 Projection();
  glm::vec3 Position() const;
  glm::vec3 Up() const;

  glm::vec2 old_mouse;
  glm::vec2 camera_rotation;
  float zoom_factor;

private:
  glm::vec2 auto_rotation_;
  bool mouse_moving_, white_side_;
};

#endif // CAMERA_H
