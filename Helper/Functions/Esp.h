
#define ScreenWidth  [UIScreen mainScreen].bounds.size.width
#define ScreenHeight [UIScreen mainScreen].bounds.size.height


template <typename T>
inline T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

inline float lerp(float a, float b, float f) {
	return clamp<float>(a + f * (b - a),a > b ? b : a,a > b ? a : b);
}

inline ImColor collerp(ImColor a, ImColor b, float f) {
  return {a.Value.x + f * (b.Value.x - a.Value.x), a.Value.y + f * (b.Value.y - a.Value.y), a.Value.z + f * (b.Value.z - a.Value.z), a.Value.w + f * (b.Value.w - a.Value.w)};
}


