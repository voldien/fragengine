#include<Scene/SubGraph/Camera.h>
#include<Core/Math.h>
#include<gtest/gtest.h>

using namespace fragcore;
using namespace fragengine;

TEST(Camera, Frustum_Create_No_Throw) { 
	ASSERT_NO_THROW(Camera());
}

TEST(Camera, Frustum_Set_Fov_Calucated_Correctly) {

	Camera frustum;
	frustum.setFov(Math::PI / 2.0f);
	ASSERT_EQ(Math::PI / 2.0f, frustum.getFov());
}

TEST(Camera, Frustum_Calculate_Frustum_Intersection) {
	Camera frustum0;
	Camera frustum1;
	ASSERT_NO_THROW(frustum0.intersectionFrustum(frustum1));
}

TEST(Camera, Frustum_Calculate_Point_Frustum_Intersection_No_Throw) {
	Camera camera;
	ASSERT_NO_THROW(camera.checkPoint(PVVector3::zero()));
}

TEST(Camera, Frustum_Calculate_Point_Frustum_Intersection_Intersection) {
	Camera camera;
	ASSERT_NO_THROW(camera.checkPoint(PVVector3::zero()));
}

TEST(Camera, Frustum_Calculate_Point_Frustum_Intersection_Outside) {
	Camera camera;
	ASSERT_NO_THROW(camera.checkPoint(PVVector3::zero()));
}

TEST(Camera, Frustum_Calculate_AABB_Frustum_Intersection_Inside){
	Camera camera;
	PVAABB aabb;
	ASSERT_EQ(camera.intersectionAABB(aabb), Frustum::In);
}

TEST(Camera, Frustum_Calculate_Sphere_Frustum_Intersection_Outside) {
    Camera camera;
    PVBoundingSphere spb;
    ASSERT_EQ(camera.intersectionSphere(spb), Frustum::Out);
}
TEST(Camera, Frustum_Calculate_Sphere_Frustum_Intersection_Intersect) {
    Camera camera;
    PVBoundingSphere spb;
    ASSERT_EQ(camera.intersectionSphere(spb), Frustum::Intersect);
}

TEST(Camera, Frustum_Calculate_Sphere_Frustum_Intersection_Inside) {
	Camera camera;
	PVBoundingSphere spb;
	ASSERT_EQ(camera.intersectionSphere(spb), Frustum::In);
}