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
  explicit Component(StrongEntityPtr _parent);

  virtual ~Component() = default;

  /**
   * @return The id for the implementing component type.
   */
  virtual ComponentTypeID getID() const = 0;

  /**
   * Initializes this component.
   * @return false if initialization failed.
   */
  virtual bool initialize();

  /**
   * Performs the frame update for this component.
   * @param deltaMs The elapsed time since the last update.
   */
  virtual void update(const float deltaMs);

  /**
   * Destroys the component, freeing resources.
   * A class that overrides this method MUST call Component::destroy() to break 
   * the Entity->Component circular dependency.
   */
  virtual void destroy();
};