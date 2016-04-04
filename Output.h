#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <windows.h>
#include "Global.h"
#include "List.h"

#define NEXT_LINE fwrite("\n", 1, strlen("\n"), file)
#define TAB_SPACE fwrite("\t", 1, strlen("\t"), file)
#define ONE_SPACE fwrite(" ", 1, strlen(" "), file)
#define BEGIN_BRACKET fwrite("{", 1, strlen("{"), file)
#define CLOSE_BRACKET fwrite("}", 1, strlen("}"), file)
#define OFFSET fwrite("OFFSET", 1, strlen("OFFSET"), file)
#define JOINT fwrite("JOINT", 1, strlen("JOINT"), file)
#define CHANNELS fwrite("CHANNELS", 1, strlen("CHANNELS"), file)
#define END_SITE fwrite("End Site", 1, strlen("END Site"), file)

//-----------------------------
//	Hierarchy
//-----------------------------
enum Hierarchy
{
	root = 0,
	joint,
	childJoint
};

//-----------------------------
//	BVH class
//-----------------------------
class Output{
public:
	Output();

	~Output();

	bool createBVHFile(std::string rootName, bool hasRotChannel, bool hasPosChannel, float *offsetValues);

	bool closeBVHFile();

	void setFileName(std::string fileName);

	void exportToBvh(double frameTime);

	void addMotion();
protected:

	//-- HIERARCHY

	bool addHierarchy();

	bool closeHierarchy();

	bool addJoint(std::string, bool hasRotChannel, bool hasPosChannel, float* offsetValues);

	bool addChildJoint(std::string childName, bool hasRotChannel, bool hasPosChannel, float* offsetValues);

	void addJointEndSite(float *offsetValues);

	void addChildJointEndSite(float *offsetValues);

	bool closeJoint();

	bool closeChildJoint();

	//-- MOTION

	void addMotionHeader(float frameTime);

	void addMotionFrameData();

private:

	bool addBody(std::string name, bool hasRotChannel, bool hasPosChannel, float* offsetValues, Hierarchy hierarchy);

	void addEndSite(float* offsetValues, Hierarchy hierarchy);

	FILE* file;

	std::string motion_data[4096];

	std::string m_rootName;

	std::string fileName;

	bool m_hasRotChannel;

	bool m_hasPosChannel;

	float* m_offsetValues;

	ListOrganizer organizer;

	List *list;
};

#endif //_OUTPUT_H_