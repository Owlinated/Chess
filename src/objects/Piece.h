// Abstract Class for all pieces
#ifndef PIECE_H
#define PIECE_H

#include "Drawable.h"
#include "src/collision/Collision.h"
#include <vector>

class Board;
class Field;
class MoveBase;
class Geometry;

class Piece : public Drawable
{
public:
  Piece(Board& board, int objectId, Field& field);
  void Init() override;
  void Draw(glm::mat4 projectionMatrix) override;
  void DrawShadow(glm::mat4 projectionMatrix) override;

  void Update(float elapsedTimeMs) override;
  void MouseClick() override;

  glm::vec3 Position3D() override;
  glm::vec3 Position() const;
  virtual bool IsWhite() const, IsTransformable() const, IsCopyable() const;
  Field& GetField() const;
  void SetField(Field& field, bool sim = false);
  virtual std::vector<std::shared_ptr<MoveBase>> GetMoves() = 0;
  int GetIdWithoutColor() const;
  bool is_moved = false;

  const Collision& GetBoundingBox() const { return bounding_box_; }

protected:
  virtual void UpdateBb(glm::vec3 position);
  std::string GetVertexShader() override;
  std::string GetFragmentShader() override;
  void AddHitOrMove(Field* field, std::vector<std::shared_ptr<MoveBase>>& moves);

  glm::vec3 position_, size_;
  Collision bounding_box_;
  float y_rotation_;
  Board& board_;
  Field* field;
};


#endif // PIECE_H
