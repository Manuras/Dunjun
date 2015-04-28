#ifndef DUNJUN_NONCOPYABLE_HPP
#define DUNJUN_NONCOPYABLE_HPP

namespace Dunjun
{
class NonCopyable
{
protected:
	NonCopyable() {}

private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};
} // namespace Dunjun

#endif
