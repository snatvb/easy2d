#pragma once

#include <easy2d/Core/System.hpp>
#include <easy2d/Components/Transform.hpp>
#include <easy2d/Components/Hierarchy.hpp>
#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
  class HierarchySystem : public System<HierarchySystem>
  {
  public:
    void execute() override;

  private:
    void _applyTransformWithParents(Transform &transform, const Hierarchy *hierarchy);
  }; // -- HierarchySystem
} // -- easy2d
