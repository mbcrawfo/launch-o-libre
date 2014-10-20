#pragma once

#include "types.h"

/**
 * The base class for all components used by entities.
 */
class Component
{
protected:
  // the parent that owns this component
  StrongEntityPtr parent;

public:
  /**
   * @param _parent The owner of this component.
   */
  Component(StrongEntityPtr _parent);

  /**
   * @return The id for the implementing component type.
   */
  virtual ComponentTypeID getID() const = 0;

  /**
   * Initializes this component.
   * @return false if initialization failed.
   */
  virtual bool initialize() { return true;  }

  /**
   * Performs the frame update for this component.
   * @param deltaMs The elapsed time since the last update.
   */
  virtual void update(const float deltaMs) {}

  /**
   * Destroys the component, freeing resources.
   */
  virtual void destroy() = 0;
};