// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "ArticulatedObjectManager.h"

#ifdef ESP_BUILD_WITH_BULLET
#include "esp/physics/bullet/objectWrappers/ManagedBulletArticulatedObject.h"
#endif

namespace esp {
namespace physics {

ArticulatedObjectManager::ArticulatedObjectManager()
    : esp::physics::PhysicsObjectBaseManager<ManagedArticulatedObject>::
          PhysicsObjectBaseManager("ArticulatedObject") {
  // build this manager's copy constructor map
  this->copyConstructorMap_["ManagedArticulatedObject"] =
      &ArticulatedObjectManager::createObjectCopy<ManagedArticulatedObject>;

  // build the function pointers to proper wrapper construction methods, keyed
  // by the wrapper names
  managedObjTypeConstructorMap_["ManagedArticulatedObject"] =
      &ArticulatedObjectManager::createPhysicsObjectWrapper<
          ManagedArticulatedObject>;

#ifdef ESP_BUILD_WITH_BULLET
  this->copyConstructorMap_["ManagedBulletArticulatedObject"] =
      &ArticulatedObjectManager::createObjectCopy<
          ManagedBulletArticulatedObject>;
  managedObjTypeConstructorMap_["ManagedBulletArticulatedObject"] =
      &ArticulatedObjectManager::createPhysicsObjectWrapper<
          ManagedBulletArticulatedObject>;
#endif
}  // ctor

std::shared_ptr<ManagedArticulatedObject>
ArticulatedObjectManager::addArticulatedObjectFromURDF(
    const std::string& filepath,
    bool fixedBase,
    float globalScale,
    float massScale,
    bool forceReload) {
  if (auto physMgr = this->getPhysicsManager()) {
    int newAObjID = physMgr->addArticulatedObjectFromURDF(
        filepath, fixedBase, globalScale, massScale, forceReload);
    return this->getObjectCopyByID(newAObjID);
  }
  return nullptr;
}

std::shared_ptr<ManagedArticulatedObject>
ArticulatedObjectManager::addArticulatedObjectFromURDFWithDrawables(
    const std::string& filepath,
    gfx::DrawableGroup* drawables,
    bool fixedBase,
    float globalScale,
    float massScale,
    bool forceReload) {
  if (auto physMgr = this->getPhysicsManager()) {
    int newAObjID = physMgr->addArticulatedObjectFromURDF(
        filepath, drawables, fixedBase, globalScale, massScale, forceReload);
    return this->getObjectCopyByID(newAObjID);
  }
  return nullptr;
}

}  // namespace physics
}  // namespace esp