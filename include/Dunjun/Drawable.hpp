#ifndef DUNJUN_DRAWABLE_HPP
#define DUNJUN_DRAWABLE_HPP

#include <Dunjun/Transform.hpp>

namespace Dunjun
{
class Renderer;

class Drawable
{
protected:
	virtual void draw(Renderer& renderer, Transform t) const = 0;

private:
	friend class Renderer;
};
} // namespace Dunjun

#endif
