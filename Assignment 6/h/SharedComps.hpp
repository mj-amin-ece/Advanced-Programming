#ifndef SHARED_COMPARISON
#define SHARED_COMPARISON

template<typename T>
class Shared_less
{
	
public:
	bool operator()(const std::shared_ptr<T>& a,const std::shared_ptr<T>& b) const {
		return (*a.get() < *b.get());
	}
};

#endif
