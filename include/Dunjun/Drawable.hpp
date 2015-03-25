#ifndef DUNJUN_DRAWABLE_HPP
#define DUNJUN_DRAWABLE_HPP

namespace Dunjun
{
class Renderer;
class Transform;

class Drawable
{
protected:
	virtual void draw(Renderer& renderer, Transform t) const = 0;

private:
	friend class Renderer;
};
} // namespace Dunjun

#endif
