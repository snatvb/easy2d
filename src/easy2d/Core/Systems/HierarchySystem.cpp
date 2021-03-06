#include <easy2d/Core/Systems/HierarchySystem.hpp>
// #include <easy2d/Components/Transform.hpp>
// #include <easy2d/Components/Hierarchy.hpp>

namespace easy2d
{

  void HierarchySystem::execute()
  {
    auto view = world->registry.view<Transform, const Hierarchy>();
    for (auto [entity, transform, hierarchy] : view.each())
    {
      transform.position *= 0;
      transform.rotation = 0;
      transform.scale.set(1.0f, 1.0f);
      _applyTransformWithParents(transform, &hierarchy);
    }
  }

  // ------------------------------------

  void HierarchySystem::_applyTransformWithParents(Transform &transform, const Hierarchy *hierarchy)
  {
    if (hierarchy)
    {
      const auto &parentTransform = world->registry.get<Transform>(hierarchy->parent);
      if (const auto *parentHierarchy = world->registry.try_get<Hierarchy>(hierarchy->parent))
      {
        transform.position = transform.position + parentTransform.local.position;
        transform.rotation = transform.rotation + parentTransform.local.rotation;
        transform.scale = transform.scale * parentTransform.local.scale;
        _applyTransformWithParents(transform, parentHierarchy);
      }
      else
      {
        transform.position = transform.position + parentTransform.local.position + parentTransform.position;
        transform.scale = transform.scale * parentTransform.local.scale * parentTransform.scale;
        transform.rotation = transform.rotation + parentTransform.local.rotation + parentTransform.rotation;
      }
    }
  }
} // -- easy2d
