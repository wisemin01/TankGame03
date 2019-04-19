#pragma once

template <class T>
void Lerp(T& p, T end, float spd)
{
	p = (p) + (end - (p)) * spd;
}

template <class T>
void Swap(T& a1, T& a2)
{
	T temp = a1;
	a1 = a2;
	a2 = temp;
}

template <class T>
T random(T min, T max)
{
	if (min > max) Swap<T>(min, max);

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<T> range(min, max);

	return range(rnd);
}

template <>
float random(float min, float max);

template<>
inline float random(float min, float max)
{
	if (min > max) Swap<float>(min, max);

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_real_distribution<float> range(min, max);

	return range(rnd);
}