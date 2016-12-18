#pragma once
namespace my
{
	template <typename Iterator, typename Object>
	Iterator find(Iterator start, Iterator end, const Object & x)
	{
		for (auto iter = start; iter != end; ++iter)
		{
			if (*iter == x)
				return iter;
		}
		return end;
	}
}
namespace ans
{
	template <typename Iterator, typename Object>
	Iterator find(Iterator start, Iterator end, const Object & x)
	{
		Iterator iter = start;
		while (iter != end && *iter != x)
			++iter;
		return iter;
	}
}