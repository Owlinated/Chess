#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.inl>

#include "King.h"
#include "src/objects/ObjectManager.h"
#include "src/objects/moves/Castling.h"
#include "src/objects/Field.h"
#include "src/objects/Board.h"


King::King(Board& board, const int objectId, Field& field) : Piece(board, objectId, field)
{
}

void King::Init()
{
  Piece::Init();
  y_rotation_ = glm::half_pi<float>();
}

std::vector<std::shared_ptr<MoveBase>> King::GetMoves()
{
  std::vector<std::shared_ptr<MoveBase>> result;
  AddHitOrMove(field->up, result);
  AddHitOrMove(field->down, result);
  AddHitOrMove(field->left, result);
  AddHitOrMove(field->right, result);
  if (field->up)
  {
    AddHitOrMove(field->up->left, result);
    AddHitOrMove(field->up->right, result);
  }
  if (field->down)
  {
    AddHitOrMove(field->down->left, result);
    AddHitOrMove(field->down->right, result);
  }
  if (board_.IsCastlingPossible(IsWhite(), true))
    result.push_back(std::make_shared<Castling>(this, board_.GetRook(IsWhite(), true).get(), field->left->left, field->left));
  if (board_.IsCastlingPossible(IsWhite(), false))
    result.push_back(std::make_shared<Castling>(this, board_.GetRook(IsWhite(), false).get(), field->right->right, field->right));
  return result;
}

bool King::IsCopyable() const
{
  return false;
}
