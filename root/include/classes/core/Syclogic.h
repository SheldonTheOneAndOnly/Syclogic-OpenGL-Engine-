#ifndef SYCLOGIC_H
#define SYCLOGIC_H

#include<iostream>
#include<string>
#include<set>

#include<classes/misc/shortcuts.h>

using namespace std;

class Syclogic {
public:
	static GLFWwindow* w;
	static void Setup(GLFWwindow* window);
	static void Update(GLFWwindow* window);
};

#endif