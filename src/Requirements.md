# Requirements
* Given a v1, v2, or v3 ioda file component (group, dimension, variable, attribute) name, return the ioda v3 name.
* When creating a ioda file component, adjust the component meta structure to match the ioda v3 meta structure
  * Adjust variable dimensions and type.
  * Add dimension variables
  * Adjust attribute fill values
## Approach
* Create a class for each file component to 