#include "cookie.h"

/** Vector **/
cookie::Vector::Vector()
{
	X = 0;
	Y = 0;
}

cookie::Vector::Vector(const double _X, const double _Y)
{
	X = _X;
	Y = _Y;
}

void cookie::Vector::Set(const double _X, const double _Y)
{
	X = _X;
	Y = _Y;
}

/** Joint **/
cookie::Joint::Joint(const Vector& _Position)
{
	Position = _Position;
}

void cookie::Joint::SetPosition(const Vector& _Position)
{
        Position = _Position;
}

cookie::Vector cookie::Joint::GetPosition() const
{
	return Position; 
}

/** Chain **/

void cookie::Chain::AddBone(Bone* BoneToAdd)
{
	auto BonesToShare = BoneToAdd->GetKnownBones();

	for (auto BoneIndex = 0; BoneIndex < BonesInChain.size(); BoneIndex++)
	{
		for (auto ShareBoneIndex = 0; ShareBoneIndex < BonesToShare.size(); ShareBoneIndex++)
		{
			BonesInChain.at(BoneIndex)->ConnectBone(BonesToShare.at(ShareBoneIndex));
		}
	}
}

/** Bone **/ 
cookie::Bone::Bone(const double X1, const double Y1, const double Width, const double Height, Chain* _BonesChain)
{
	BonesChain = _BonesChain;
	Angle = 0.0f;
	MainJoint = new Joint(cookie::Vector(X1, Y1));
	auto temp = new Joint(cookie::Vector(X1 + Width, Y1 + Height));
	KnownJoints.push_back(temp);
}

cookie::Bone::Bone(Bone* TargetBone, const double Width, const double Height)
{
	BonesChain = TargetBone->GetChain();
	Angle = 0.0f;
	MainJoint = TargetBone->GetFreeJoint();
	auto temp = new Joint(cookie::Vector(MainJoint->GetPosition().X + Width, MainJoint->GetPosition().Y + Height));
	KnownJoints.push_back(temp);
	TargetBone->ConnectBone(this);
}

cookie::Chain* cookie::Bone::GetChain() const
{
	return BonesChain;
} 

std::vector<cookie::Joint*> cookie::Bone::PrepareJoints()
{
	auto temp = GetKnownJoints();
	
	for (auto BoneIndex = 0; BoneIndex < KnownBones.size(); BoneIndex++)
	{
		Bone* TempBone = KnownBones.at(BoneIndex);
		
		for (auto JointIndex = 0; JointIndex < TempBone->GetKnownJoints().size(); JointIndex++)
		{
			temp.push_back(TempBone->GetKnownJoints().at(JointIndex));
		}
	}
	return temp;
}

std::vector<cookie::Bone*> cookie::Bone::GetKnownBones() const
{
	return KnownBones;
}

std::vector<cookie::Joint*> cookie::Bone::GetKnownJoints() const
{
	return KnownJoints;
}

void cookie::Bone::ConnectBone(Bone* BoneToConnect)
{
	KnownBones.push_back(BoneToConnect);
}

void cookie::Bone::Rotate(const double AnglePlus)
{
	
	std::vector<Joint*> JointsToRotate = PrepareJoints();

	Angle += AnglePlus;

	if (Angle >= 360.0f)
	{
		Angle = Angle - 360.0f;
	}

	std::cout << Angle << std::endl;

	const double XOrigin = MainJoint->GetPosition().X;
	const double YOrigin = MainJoint->GetPosition().Y;
        
	for (auto JointIndex = 0; JointIndex < JointsToRotate.size(); JointIndex++)
	{		
		const double XStart = JointsToRotate.at(JointIndex)->GetPosition().X;
		const double YStart = JointsToRotate.at(JointIndex)->GetPosition().Y;

		const double XDelta = XStart - XOrigin;
		const double YDelta = YStart - YOrigin;
		
		const double XTransf = XOrigin + 50.0 * sin(Angle * M_PI / 180); //FIXPLACE
		const double YTransf = YOrigin + 50.0 * cos(Angle * M_PI / 180); //FIXPLACE
		
		/*
		const double XTransf = XOrigin + XDelta * cos(Angle * M_PI / 180) - YDelta * sin(Angle *M_PI / 180);
		const double YTransf = YOrigin + XDelta * sin(Angle * M_PI / 180) - YDelta * cos(Angle * M_PI / 180);
		*/
		JointsToRotate.at(JointIndex)->SetPosition(cookie::Vector(round(XTransf), round(YTransf)));
	}
}
/*
void cookie::Bone::RotateToAngle(const double _Angle)
{
	Angle = _Angle;
}
*/
cookie::Joint* cookie::Bone::GetMainJoint() const
{
	return MainJoint;
} 

cookie::Joint* cookie::Bone::GetFreeJoint() const
{
	return KnownJoints.at(0);
}

double cookie::Bone::GetAngle() const
{
	return Angle;
}

void cookie::Bone::Delete()
{

}
