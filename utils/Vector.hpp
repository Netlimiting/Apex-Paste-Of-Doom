#pragma once
#include <Windows.h>
#include <math.h>
#include <array>
#include <cmath>
#include <random>
#define M_PI		3.14159265358979323846	
#define Assert( _exp ) ((void)0)
#define RAD2DEG(x) ((x) * (180.0 / M_PI))
#define DEG2RAD(x) ((x) * (M_PI / 180.0f))

struct BaseMatrix
{
	float at[16]{};
};

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	float* operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float* operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float* Base() { return &m_flMatVal[0][0]; }
	const float* Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

class QAngle
{
public:
	QAngle(void)
	{
		Init();
	}
	QAngle(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}
	QAngle(const float* clr)
	{
		Init(clr[0], clr[1], clr[2]);
	}

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		pitch = ix;
		yaw = iy;
		roll = iz;
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}
	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	QAngle& operator+=(const QAngle& v)
	{
		pitch += v.pitch; yaw += v.yaw; roll += v.roll;
		return *this;
	}
	QAngle& operator-=(const QAngle& v)
	{
		pitch -= v.pitch; yaw -= v.yaw; roll -= v.roll;
		return *this;
	}
	QAngle& operator*=(float fl)
	{
		pitch *= fl;
		yaw *= fl;
		roll *= fl;
		return *this;
	}
	QAngle& operator*=(const QAngle& v)
	{
		pitch *= v.pitch;
		yaw *= v.yaw;
		roll *= v.roll;
		return *this;
	}
	QAngle& operator/=(const QAngle& v)
	{
		pitch /= v.pitch;
		yaw /= v.yaw;
		roll /= v.roll;
		return *this;
	}
	QAngle& operator+=(float fl)
	{
		pitch += fl;
		yaw += fl;
		roll += fl;
		return *this;
	}
	QAngle& operator/=(float fl)
	{
		pitch /= fl;
		yaw /= fl;
		roll /= fl;
		return *this;
	}
	QAngle& operator-=(float fl)
	{
		pitch -= fl;
		yaw -= fl;
		roll -= fl;
		return *this;
	}

	QAngle& operator=(const QAngle& vOther)
	{
		pitch = vOther.pitch; yaw = vOther.yaw; roll = vOther.roll;
		return *this;
	}

	QAngle operator-(void) const
	{
		return QAngle(-pitch, -yaw, -roll);
	}
	QAngle operator+(const QAngle& v) const
	{
		return QAngle(pitch + v.pitch, yaw + v.yaw, roll + v.roll);
	}
	QAngle operator-(const QAngle& v) const
	{
		return QAngle(pitch - v.pitch, yaw - v.yaw, roll - v.roll);
	}
	QAngle operator*(float fl) const
	{
		return QAngle(pitch * fl, yaw * fl, roll * fl);
	}
	QAngle operator*(const QAngle& v) const
	{
		return QAngle(pitch * v.pitch, yaw * v.yaw, roll * v.roll);
	}
	QAngle operator/(float fl) const
	{
		return QAngle(pitch / fl, yaw / fl, roll / fl);
	}
	QAngle operator/(const QAngle& v) const
	{
		return QAngle(pitch / v.pitch, yaw / v.yaw, roll / v.roll);
	}

	float Length() const
	{
		return sqrt(pitch * pitch + yaw * yaw + roll * roll);
	}
	float LengthSqr(void) const
	{
		return (pitch * pitch + yaw * yaw + roll * roll);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (pitch > -tolerance && pitch < tolerance &&
			yaw > -tolerance && yaw < tolerance &&
			roll > -tolerance && roll < tolerance);
	}
	float pitch;
	float yaw;
	float roll;
};


class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}
	inline double Length() {
		return sqrt(x * x + y * y + z * z);
	}
	inline bool Empty()
	{
		if (!x && !y && !z)
			return true;
		else
			return false;
	}
	inline void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}
	inline float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}
	float Magnitude2D()  {
		return std::sqrt(x * x + y * y);
	}
	inline float distance(Vector3 vec)
	{
		return sqrt(
			pow(vec.x - x, 2) +
			pow(vec.y - y, 2)
		);
	}
	float Magnitude() {
		return std::sqrt(x * x + y * y + z * z);
	}
	inline Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	inline Vector3 add(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	inline Vector3 sub(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline Vector3 mul(float v)
	{
		return Vector3(x * v, y * v, z * v);
	}
	inline Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator*(float flNum) { return Vector3(x * flNum, y * flNum, z * flNum); }
	inline double Size() {
		return Length();
	}
	bool equals(Vector3 src)
	{
		if (x == src.x && y == src.y && z == src.z)
			return true;
		else
			return false;
	}
};
class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	float x;
	float y;
	bool IsEmpty()
	{
		if (x == 0 && y == 0)
			return true;
		else
			return false;
	}
	inline Vector2 operator+(int i) {
		return { x + i, y + i };
	}
	inline Vector2 operator-(Vector2 v) {
		return { x - v.x, y - v.y };
	}
	inline Vector2 flip() {
		return { y, x };
	}

};
struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

inline float GetCrossDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
inline inline float calcDist(const Vector3 p1, const Vector3 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	float z = p1.z - p2.z;
	return sqrt(x * x + y * y + z * z);
}

inline float RandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

inline float SmoothStep(float t) {
	return t * t * (3 - 2 * t);
}

inline Vector3 CalcAngle(const Vector3& src, const Vector3& dst)
{
	Vector3 angle;
	Vector3 delta = Vector3((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	angle.x = atan(delta.z / hyp) * (180.0f / M_PI);
	angle.y = atan(delta.y / delta.x) * (180.0f / M_PI);
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}

inline Vector3 ApplyCurvature(const Vector3& delta, float progress) {
	Vector3 curvedDelta;
	float smoothProgress = SmoothStep(progress);

	// Introduce a random factor to make the curvature dynamic
	curvedDelta.x = delta.x * smoothProgress + RandomFloat(-0.2f, 0.2f);
	curvedDelta.y = delta.y * smoothProgress + RandomFloat(-0.2f, 0.2f);

	return curvedDelta;
}
struct bone_t
{
	BYTE pad[0xCC];
	float x;
	BYTE pad2[0xC];
	float y;
	BYTE pad3[0xC];
	float z;
};

inline Vector3 VAR_Adds(Vector3 src, Vector3 dst)
{
	Vector3 diff;
	diff.x = src.x + dst.x;
	diff.y = src.y + dst.y;
	diff.z = src.z + dst.z;
	return diff;
}

inline Vector3 VAR_toAngless(Vector3 const& v)
{
	double R2D = 57.2957795130823;
	Vector3 angles;
	angles.z = 0.0;
	angles.x = R2D * asin(v.z);
	angles.y = R2D * atan2(v.y, v.x);
	return angles;
}

inline Vector3 VAR_Subtracts(Vector3 src, Vector3 dst)
{
	Vector3 diff;
	diff.x = src.x - dst.x;
	diff.y = src.y - dst.y;
	diff.z = src.z - dst.z;
	return diff;
}
enum BoneList : int
{
	Head = 8,
	Neck = 5,
	RightPek = 35,
	RightForArm = 37,
	RightHand = 39,
	LeftPek = 11,
	LeftArm = 13,
	LeftHand = 15,
	LowerChest = 3,
	Pelivs = 2,
	RightHip = 62,
	RightKne = 63,
	RightFoot = 65,
	LeftHip = 57,
	LeftKne = 58,
	LeftFoot = 60,
};
inline void NormalizeAngles(Vector2& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

inline void normalY(float& f) {
	while (f > 180.f)
		f -= 360.f;

	while (f < -180.f)
		f += 360.f;
}

inline float VAR_Magnitudes(Vector3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
inline float VAR_deltaDistances(Vector3 src, Vector3 dst)
{
	Vector3 diff = VAR_Subtracts(src, dst);
	return VAR_Magnitudes(diff);
}
inline void VAR_VectorAngless(const float* forward, float* angles)
{
	float	tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 57.295779513082f);
		if (yaw < 0)
			yaw += 360;
		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 57.295779513082f);
		if (pitch < 0)
			pitch += 360;
	}
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

inline Vector3 Var_CalcAngless(Vector3& src, Vector3& dst)
{
	float output[3];
	float input[3] = { dst.x - src.x , dst.y - src.y, dst.z - src.z };
	VAR_VectorAngless(input, output);
	if (output[1] > 180) output[1] -= 360;
	if (output[1] < -180) output[1] += 360;
	if (output[0] > 180) output[0] -= 360;
	if (output[0] < -180) output[0] += 360;
	return { output[0], output[1], 0.f };
}
struct Vector4 {
	float x, y, z, w;
};
//void ProjW2s(Vector3 Position, Vector3& Screen)
//{
//	uintptr_t render = *reinterpret_cast<std::uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::ViewRender);
//	if (!render)return;
//	uintptr_t Matrixa = *reinterpret_cast<std::uintptr_t*>(OffsetsT1::ViewMatrix + render);
//	if (!Matrixa)return;
//	BaseMatrix Matrix = *reinterpret_cast<BaseMatrix*>(Matrixa);
//
//	Vector3 out;
//	float _x = Matrix.at[0] * Position.x + Matrix.at[1] * Position.y + Matrix.at[2] * Position.z + Matrix.at[3];
//	float _y = Matrix.at[4] * Position.x + Matrix.at[5] * Position.y + Matrix.at[6] * Position.z + Matrix.at[7];
//	out.z = Matrix.at[12] * Position.x + Matrix.at[13] * Position.y + Matrix.at[14] * Position.z + Matrix.at[15];
//
//	if (out.z < 0.1f) return;
//
//	_x *= 1.f / out.z;
//	_y *= 1.f / out.z;
//
//	out.x = ImGui::GetIO().DisplaySize.x * .5f;
//	out.y = ImGui::GetIO().DisplaySize.y * .5f;
//
//	out.x += 0.5f * _x * ImGui::GetIO().DisplaySize.x + 0.5f;
//	out.y -= 0.5f * _y * ImGui::GetIO().DisplaySize.y + 0.5f;
//	Screen = out;
//}

inline Vector2 RevolveCoordinatesSystem(float RevolveAngle, Vector2 OriginPos, Vector2 DestPos)
{
	Vector2 ResultPos;
	if (RevolveAngle == 0)
		return DestPos;
	ResultPos.x = OriginPos.x + (DestPos.x - OriginPos.x) * cos(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * sin(RevolveAngle * M_PI / 180);
	ResultPos.y = OriginPos.y - (DestPos.x - OriginPos.x) * sin(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * cos(RevolveAngle * M_PI / 180);
	return ResultPos;
}

inline double pi = 3.141592;
inline double Rad2Deg(double radianes) {
	return 360 / (2 * pi) * radianes;
}

inline void RotatePoint(float* pointToRotate, float* centerPoint, float angle, float* ReturnTo)
{
	angle = (float)(angle * (M_PI / (float)180));

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	ReturnTo[0] = cosTheta * (pointToRotate[0] - centerPoint[0]) - sinTheta * (pointToRotate[1] - centerPoint[1]);
	ReturnTo[1] = sinTheta * (pointToRotate[0] - centerPoint[0]) + cosTheta * (pointToRotate[1] - centerPoint[1]);

	ReturnTo[0] += centerPoint[0];
	ReturnTo[1] += centerPoint[1];
}

inline void WorldToScreen2D(float* worldPos, float* centerPos, float scale, float* screenPos) {
	screenPos[0] = (worldPos[0] - centerPos[0]) * scale;
	screenPos[1] = (worldPos[1] - centerPos[1]) * scale;
	screenPos[0] = -screenPos[0];
}
inline Vector3 WorldToRadar(float Yaw, Vector3 Origin, Vector3 LocalOrigin, float PosX, float PosY, Vector3 Size, bool& outbuff)
{
	bool flag = false;
	double num = static_cast<double>(Yaw);
	double num2 = num * 0.017453292519943295;
	float num3 = static_cast<float>(std::cos(num2));
	float num4 = static_cast<float>(std::sin(num2));
	float num5 = Origin.x - LocalOrigin.x;
	float num6 = Origin.y - LocalOrigin.y;

	// Calculate the transformed coordinates
	Vector3 vector;
	vector.x = (num6 * num3 - num5 * num4) / 150.0f;
	vector.y = (num5 * num3 + num6 * num4) / 150.0f;

	// Adjusted vector to center around PosX and PosY
	Vector3 vector2;
	vector2.x = vector.x + PosX;
	vector2.y = -vector.y + PosY;

	// Clamping within radar boundaries
	if (vector2.x > PosX + Size.x)
	{
		vector2.x = PosX + Size.x;
		flag = true;
	}
	else if (vector2.x < PosX)
	{
		vector2.x = PosX;
		flag = true;
	}

	if (vector2.y > PosY + Size.y)
	{
		vector2.y = PosY + Size.y;
		flag = true;
	}
	else if (vector2.y < PosY)
	{
		vector2.y = PosY;
		flag = true;
	}

	outbuff = flag;
	return vector2;
}
inline void VectorAnglesRadar(Vector3& forward, Vector3& angles)
{
	if (forward.x == 0.f && forward.y == 0.f)
	{
		angles.x = forward.z > 0.f ? -90.f : 90.f;
		angles.y = 0.f;
	}
	else
	{
		angles.x = RAD2DEG(atan2(-forward.z, forward.Size()));
		angles.y = RAD2DEG(atan2(forward.y, forward.z));
	}
	angles.z = 0.f;
}
inline void RotateTriangle(std::array<Vector3, 3>& points, float rotation)
{
	const auto points_center = (points.at(0) + points.at(1) + points.at(2));
	points_center.x / 3;
	points_center.y / 3;
	points_center.z / 3;
	for (auto& point : points)
	{
		// Translate point to the origin (relative to the center)
		point = point - points_center;

		// Store the current x and y values
		const auto temp_x = point.x;
		const auto temp_y = point.y;

		// Convert rotation from degrees to radians
		const auto theta = DEG2RAD(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		// Perform the rotation using 2D rotation matrix
		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		// Translate the point back
		point = point + points_center;
	}
}


//example
// Velocity = 2500;
// Gravity = 1.2;
// Distance = 101;

// a1 = 2.5
// a2 2.5 + 1.2
// 1
// v3 = 3.2
inline Vector2 CalPrediction(Vector2 Angle, float Gravity, float Velocity, float Distance, float LocalPlayerHeight, float Entityheight)
{
	double Height = 0;
	float AngledHeight = 0;
	float normalizedVelocity = Velocity / 10000.f;
	float distanceFactor = 0;

	if (normalizedVelocity < 1.f) {
		AngledHeight = LocalPlayerHeight / Entityheight / 2;

		if (Distance > 150) {
			distanceFactor = Distance / 10 / 2.8;
		}
		else if (Distance > 125) {
			distanceFactor = Distance / 10 / 3.9f;
		}
		else if (Distance > 75) {
			distanceFactor = Distance / 10 / 4.8f;
		}
		else if (Distance > 50) {
			distanceFactor = Distance / 10 / 6.f;
		}
		else {
			distanceFactor = Distance / 10 / 200.f;
		}

		Height = (normalizedVelocity / Gravity) + distanceFactor;

	}
	else {
		AngledHeight = LocalPlayerHeight / Entityheight / 10;
		Height = (normalizedVelocity / Gravity) + Distance / 100 / 10000.f;
		Height /= 10.f;
	}

	if (AngledHeight > 0.0f) {
		Height -= AngledHeight;
	}
	else {
		AngledHeight /= 5;
		Height += AngledHeight;
	}

	printf("Prediction Height : %f\n", Height);

	return Vector2(Angle.x - Height, Angle.y);
}