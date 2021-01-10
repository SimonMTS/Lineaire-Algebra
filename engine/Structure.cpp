#include "Structure.hpp"

#include <iostream>

int Structure::PrevIDs = 0;

void Structure::AddComponent(const Component& c) { Components.push_back(c); }

void Structure::RegisterPerTickAction(
    const function<void(const int tick, Structure& structure, Renderer& r)>&
        callback) {
  PerTickAction = callback;
}

void Structure::ExecutePerTickAction(const int tick, Renderer& r) {
  if (PerTickAction) PerTickAction(tick, *this, r);
}

void Structure::operator*=(const cMatrix& m) {
  for (auto& comp : Components) {
    for (auto& square : comp.Squares) {
      square.P1 = ((square.P1 + comp.Pos) * m) - comp.Pos;
      square.P2 = ((square.P2 + comp.Pos) * m) - comp.Pos;
      square.P3 = ((square.P3 + comp.Pos) * m) - comp.Pos;
      square.P4 = ((square.P4 + comp.Pos) * m) - comp.Pos;
    }
  }
}

void Structure::CalcAABB() {
  vector<double> newAABB;

  newAABB.push_back(GetMinPoint(0));
  newAABB.push_back(GetMinPoint(1));
  newAABB.push_back(GetMinPoint(2));
  newAABB.push_back(GetMaxPoint(0));
  newAABB.push_back(GetMaxPoint(1));
  newAABB.push_back(GetMaxPoint(2));

  this->AABB = newAABB;
}

bool Structure::IsCollidingWith(const Structure& other) {
  if (*this == other) return false;

  bool collX = false;
  {
    auto mySmallestX = (this->AABB[0] + this->State[0][3]);
    auto myLargestX = (this->AABB[3] + this->State[0][3]);

    auto otherSmallestX = (other.AABB[0] + other.State.at(0)[3]);
    auto otherLargestX = (other.AABB[3] + other.State.at(0)[3]);

    if (mySmallestX >= otherSmallestX && mySmallestX <= otherLargestX) {
      collX = true;
    }
    if (myLargestX >= otherSmallestX && myLargestX <= otherLargestX) {
      collX = true;
    }
    if (mySmallestX <= otherSmallestX && myLargestX >= otherLargestX) {
      collX = true;
    }
  }

  bool collY = false;
  {
    auto mySmallestY = (this->AABB[1] + this->State[1][3]);
    auto myLargestY = (this->AABB[4] + this->State[1][3]);

    auto otherSmallestY = (other.AABB[1] + other.State.at(1)[3]);
    auto otherLargestY = (other.AABB[4] + other.State.at(1)[3]);

    if (mySmallestY >= otherSmallestY && mySmallestY <= otherLargestY) {
      collY = true;
    }
    if (myLargestY >= otherSmallestY && myLargestY <= otherLargestY) {
      collY = true;
    }
    if (mySmallestY <= otherSmallestY && myLargestY >= otherLargestY) {
      collY = true;
    }
  }

  bool collZ = false;
  {
    auto mySmallestZ = (this->AABB[2] + this->State[2][3]);
    auto myLargestZ = (this->AABB[5] + this->State[2][3]);

    auto otherSmallestZ = (other.AABB[2] + other.State.at(2)[3]);
    auto otherLargestZ = (other.AABB[5] + other.State.at(2)[3]);

    if (mySmallestZ >= otherSmallestZ && mySmallestZ <= otherLargestZ) {
      collZ = true;
    }
    if (myLargestZ >= otherSmallestZ && myLargestZ <= otherLargestZ) {
      collZ = true;
    }
    if (mySmallestZ <= otherSmallestZ && myLargestZ >= otherLargestZ) {
      collZ = true;
    }
  }

  return collX && collY && collZ;
}

bool Structure::operator==(const Structure& other) {
  return this->ID == other.ID;
}

double Structure::GetMinPoint(const int axis) {
  double lowest = numeric_limits<double>::max();

  for (auto& c : Components) {
    for (auto& s : c.Squares) {
      for (auto& p : {s.P1, s.P2, s.P3, s.P4}) {
        cVector point_from_origin = c.Pos + p;

        cMatrix orientation = State;
        orientation[0][3] = 0;
        orientation[1][3] = 0;
        orientation[2][3] = 0;

        point_from_origin *= orientation;

        double pCord;
        switch (axis) {
          case 0:
            pCord = point_from_origin.X;
            break;
          case 1:
            pCord = point_from_origin.Y;
            break;
          case 2:
            pCord = point_from_origin.Z;
            break;
        }

        if (pCord < lowest) {
          lowest = pCord;
        }
      }
    }
  }

  return lowest;
}

double Structure::GetMaxPoint(const int axis) {
  double highest = numeric_limits<double>::min();

  for (auto& c : Components) {
    for (auto& s : c.Squares) {
      for (auto& p : {s.P1, s.P2, s.P3, s.P4}) {
        cVector point_from_origin = c.Pos + p;

        cMatrix orientation = State;
        orientation[0][3] = 0;
        orientation[1][3] = 0;
        orientation[2][3] = 0;

        point_from_origin *= orientation;

        double pCord;
        switch (axis) {
          case 0:
            pCord = point_from_origin.X;
            break;
          case 1:
            pCord = point_from_origin.Y;
            break;
          case 2:
            pCord = point_from_origin.Z;
            break;
        }

        if (pCord > highest) {
          highest = pCord;
        }
      }
    }
  }

  return highest;
}