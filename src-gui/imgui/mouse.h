// -*-c++-*-

// Mouse state struct

#ifndef MOUSE_H
#define MOUSE_H

// A mouse class to encapsulate all information about the state of the
// mouse when it is hovering a certain window region.
struct MouseState
{
  bool hover   = false;
  bool lclick  = false;
  bool mclick  = false;
  bool rclick  = false;
  bool ldrag   = false;
  bool rdrag   = false;
  bool ldclick = false;
  float scroll = 0.f;
};
#endif