

#define calc_size(size, str) CalcTextSizeA(size, FLT_MAX, 0, str.c_str())

#define HOOKAF(ret, func, ...) \
    ret (*old_##func)(__VA_ARGS__); \
    ret hook_##func(__VA_ARGS__)

#define const_ptr(object, offset) *reinterpret_cast<uintptr_t*>(object + offset)

#define Str(ret) std::to_string(ret).c_str()

#define const_ptr_set(type, object, offset) *reinterpret_cast<type*>(object + offset)

#define const_field(type, object, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(object) + offset)

#define const_field_set(ret, first, second, val) *reinterpret_cast<ret*>(reinterpret_cast<uintptr_t>(first) + second) = val

#define const_dict(retf, rets, first, second) *reinterpret_cast<monoDictionary<retf, rets>**>(reinterpret_cast<uintptr_t>(first) + second)

#define const_array(retf, first, second) *reinterpret_cast<monoArray<retf>**>(reinterpret_cast<uintptr_t>(first) + second)

static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x + rhs, lhs.y + rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x - rhs, lhs.y - rhs); }
static inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
static inline ImVec4  operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4  operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4  operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

inline ImVec2 flooring(ImVec2 vec) {
    return { static_cast<float>(vec.x), (float)int(vec.y) };
}

inline ImVec2 flooring(float x, float y) {
    return { (float)int(x), (float)int(y) };
}

inline ImVec2 flooring(int x, int y) {
    return { (float)x, (float)y };
}



void AddText(ImFont* font, float size, bool shadow, bool outline, const ImVec2& textpos,ImColor col, std::string value, ImDrawList* drawlist = ImGui::GetBackgroundDrawList()) {

const char* ctext = value.c_str();

if(outline){
        drawlist->AddText(font, size, flooring(textpos) + ImVec2(-1, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(0, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(1, -1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(-1, 0), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(1, 0), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(-1, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(0, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);
            drawlist->AddText(font, size, flooring(textpos) + ImVec2(1, 1), ImColor(0.0f, 0.0f, 0.0f, col.Value.w * 0.75f), ctext);

}
        if (shadow) drawlist->AddText(font, size, { textpos.x + 2, textpos.y + 2 }, ImColor(5, 5, 5, (int)float(col.Value.w * 255)), ctext);
        drawlist->AddText(font, size, textpos, col, ctext);
}




float NormalizeAngle (float angle){
    while (angle>360)
        angle -= 360;
    while (angle<0)
        angle += 360;
    return angle;
}
Vector3 NormalizeAngles (Vector3 angles){
    angles.x = NormalizeAngle (angles.x);
    angles.y = NormalizeAngle (angles.y);
    angles.z = NormalizeAngle (angles.z);
    return angles;
}
Vector3 ToEulerRad(Quaternion q1){
    //float Rad2Deg = 360.0f / (M_PI * 2.0f);
    float sqw = q1.w * q1.w;
    float sqx = q1.x * q1.x;
    float sqy = q1.y * q1.y;
    float sqz = q1.z * q1.z;
    float unit = sqx + sqy + sqz + sqw;
    float test = q1.x * q1.w - q1.y * q1.z;
    Vector3 v;

    if (test>0.4995f*unit) {
        v.y = 2.0f * atan2f (q1.y, q1.x);
        v.x = M_PI / 2.0f;
        v.z = 0;
        return NormalizeAngles(v * Rad2Deg);
    }
    if (test<-0.4995f*unit) {
        v.y = -2.0f * atan2f (q1.y, q1.x);
        v.x = -M_PI / 2.0f;
        v.z = 0;
        return NormalizeAngles (v * Rad2Deg);
    }
    Quaternion q(q1.w, q1.z, q1.x, q1.y);
    v.y = atan2f (2.0f * q.x * q.w + 2.0f * q.y * q.z, 1 - 2.0f * (q.z * q.z + q.w * q.w)); // yaw
    v.x = asinf (2.0f * (q.x * q.z - q.w * q.y)); // pitch
    v.z = atan2f (2.0f * q.x * q.y + 2.0f * q.z * q.w, 1 - 2.0f * (q.y * q.y + q.z * q.z)); // roll
    return NormalizeAngles (v * Rad2Deg);
}

struct display {
ImVec2 wh;
float width;
float height;
}disp;


struct Angles {
   float yaw, pitch;
};



struct RaycastHit {
    Vector3 Point, Normal;
    unsigned int FaceID;
    float Distance;
    Vector2 UV;
    int m_Collider;
};

struct ObscuredInt{
int key;
int hidden;
bool inited;int fakeValue;
bool fakeValueActive;
int get(){
	return hidden ^ key;
}
void set(uintptr_t loc, int val){
*(int *)(loc + 0x4) = val ^ key;
}
};


