#ifndef CONFIG_H
#define CONFIG_H

class Config {
public:

  static int geo_resolution1, geo_resolution2, shadow_resolution;

  static bool ai;

  static bool changed;

  static int viewport_width, viewport_height;

  static bool change_theme, new_game, undo_turn, demo;

  static bool full_screen;
};

#endif // CONFIG_H
