#ifndef COOKIE_H
#define COOKIE_H
#include <iostream>
#include <cmath>
#include <vector>
namespace cookie {

class Vector
{
public:
	double X, Y;
	Vector();
	Vector(const double _X, const double _Y);
	void Set(const double _X, const double _Y);
};

class Bone;
class Joint
{
	Vector Position;
public:
	Joint(const Vector& _Position);
	void SetPosition(const Vector& _Position);
	Vector GetPosition() const;
};

class Chain
{
	std::vector<Bone*> BonesInChain;
	
public:
	friend class Bone;
	void AddBone(Bone* BoneToAdd);
	void AddBone(std::vector<Bone*> Bones);
};

class Bone 
{	
	double Angle;
	Chain* BonesChain;  
	Joint* MainJoint;
	std::vector<Joint*> KnownJoints;
	std::vector<Bone*> KnownBones; 
	std::vector<Joint*> PrepareJoints();
protected:
	std::vector<Bone*> GetKnownBones() const;
	std::vector<Joint*> GetKnownJoints() const;
	void ConnectBone(Bone* BoneToConnect);
	Chain* GetChain() const;
public:
	friend class Chain;
	
	Bone(const double X1, const double Y1, const double Width, const double Height, Chain* _BonesChain);
	Bone(Bone* TargetBone, const double Width, const double Height);
	void Rotate(const double AnglePlus);
	void RotateToAngle(const double _Angle);
	Joint* GetMainJoint() const;
	Joint* GetFreeJoint() const;
	double GetAngle() const;
	void Delete(); //Oh, shit
};

};

#endif 
