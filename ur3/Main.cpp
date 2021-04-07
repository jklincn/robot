#include<iostream>
#include<math.h>
#include<string>
#include<windows.h>
extern "C" {
#include"extApi.h"
#include"extApiPlatform.h"
}
#include"IK.h"
#include"base.h"
using namespace std;
pose test(63.78 / 1000, 201.25 / 1000, 287.28 / 1000, 0.192, 3.109, 0.036);
int client_id;
int main()
{
	//---------------------����V-rep-------------------
	client_id = vrep_connect();
	//client_id = 0;
	//----------------------��ȡ����-------------------
	int control_handle;
	int target;
	simxGetObjectHandle(client_id, "UR3", &control_handle, simx_opmode_blocking);
	simxGetObjectHandle(client_id, "target", &target, simx_opmode_blocking);
	int jointHandles[6];
	for (int i = 0; i < 6; i++)
	{
		string temp_name = "UR3_joint" + to_string(i + 1);
		simxGetObjectHandle(client_id, temp_name.c_str(), &jointHandles[i], simx_opmode_blocking);
	}
	//-------------------------------------------------
	vector<vector<double>> IKSolveResult;
	IKSolveResult = Inverse_kinematics(test);
	vector<double> thebest = ChooseTheBest(IKSolveResult);
	for (int i = 0; i < 6; i++)
		simxSetJointTargetPosition(client_id, jointHandles[i], thebest[i + 1], simx_opmode_oneshot);
	//simxSetJointTargetPosition(client_id, jointHandles[i], IKSolveResult[4][i + 1], simx_opmode_oneshot);
	//float position[3];
	//simxGetObjectPosition(client_id, target, -1, position, simx_opmode_blocking);
	//printf("(%f,%f,%f)\n", position[0], position[1], position[2]);
	//----------------------�������--------------------
	/*
	//--------------------��ȡλ����Ϣ
	float position[4];
	simxGetObjectPosition(client_id, control_handle, -1, position, simx_opmode_blocking);
	printf("(%f,%f,%f)\n", position[0], position[1], position[2]);
	for (int i = 1; i <= 6; i++)
	{
		simxGetObjectPosition(client_id, jointHandles[i], -1, position, simx_opmode_blocking);
		printf("(%f,%f,%f)\n", position[0], position[1], position[2]);
	}
	*/

	system("pause");
	simxFinish(client_id);
}