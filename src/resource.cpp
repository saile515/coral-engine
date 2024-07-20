#include "resource.hpp"
#include "scene.hpp"

namespace coral
{

START_REFLECTION(Resource)
END_REFLECTION()

START_REFLECTION(Scene)
REFLECT_PROPERTY(children)
END_REFLECTION()

} // namespace coral
