#include "Output.h"

Output::Output()
{
	m_rootName = "";

	fileName = "";

	m_hasRotChannel = false;

	m_hasPosChannel = false;

	m_offsetValues = NULL;

	file = NULL;

	list = organizer.newList();
}

Output::~Output()
{
	if (file)
		fclose(file);

	file = NULL;
}

void Output::exportToBvh(double frameTime)
{
	float rootOffsetValues[3] = { 0.0f, 0.0f, 0.0f };

	createBVHFile("Head", true, true, rootOffsetValues);

	addHierarchy();
	addJoint("Face", true, false, rootOffsetValues);
	addJointEndSite(rootOffsetValues);
	{
		for (int i = 0; i < MAX_MARKERS; ++i)
		{
			if (marker[i].isSelected)
			{
				addChildJoint(marker[i].name(i), false, true, rootOffsetValues);

				addChildJointEndSite(rootOffsetValues);

				closeChildJoint();
			}
		}
	}

	closeJoint();

	closeHierarchy();
	addMotionHeader(frameTime);
	addMotionFrameData();

	closeBVHFile();
}

bool Output::createBVHFile(std::string rootName, bool hasRotChannel, bool hasPosChannel, float* offsetValues)
{
	m_rootName = rootName;

	m_hasRotChannel = hasRotChannel;

	m_hasPosChannel = hasPosChannel;

	m_offsetValues = offsetValues;

	file = fopen(fileName.c_str(), "w+");

	if (file)
		return true;

	return false;
}

bool Output::closeBVHFile()
{
	if (file)
		fclose(file);

	file = NULL;
	return true;
}

bool Output::addHierarchy()
{
	if (!file)
		return false;

	fwrite("HIERARCHY", 1, strlen("HIERARCHY"), file);

	NEXT_LINE;

	fwrite("ROOT", 1, strlen("ROOT"), file);

	return addBody(m_rootName, m_hasRotChannel, m_hasPosChannel, m_offsetValues, root);
}

bool Output::closeHierarchy()
{
	if (!file)
		return false;

	NEXT_LINE;
	CLOSE_BRACKET;
	NEXT_LINE;

	return true;
}

bool Output::addJoint(std::string jointName, bool hasRotChannel, bool hasPosChannel, float* offsetValues)
{
	if (!file)
		return false;

	TAB_SPACE;

	fwrite("JOINT", 1, strlen("JOINT"), file);

	return addBody(jointName, hasRotChannel, hasPosChannel, offsetValues, joint);
}

bool Output::closeJoint()
{
	if (!file)
		return false;

	TAB_SPACE;
	CLOSE_BRACKET;

	return true;
}

bool Output::addChildJoint(std::string childName, bool hasRotChannel, bool hasPosChannel, float* offsetValues)
{
	if (!file)
		return false;

	TAB_SPACE;
	TAB_SPACE;

	fwrite("JOINT", 1, strlen("JOINT"), file);

	return addBody(childName, hasRotChannel, hasPosChannel, offsetValues, childJoint);
}

bool Output::closeChildJoint()
{
	if (!file)
		return false;

	TAB_SPACE;
	TAB_SPACE;
	CLOSE_BRACKET;
	NEXT_LINE;

	return true;
}

void Output::addJointEndSite(float* offsetValues)
{
	TAB_SPACE;
	TAB_SPACE;
	addEndSite(offsetValues, joint);
}

void Output::addChildJointEndSite(float* offsetValues)
{
	TAB_SPACE;
	TAB_SPACE;
	TAB_SPACE;
	addEndSite(offsetValues, childJoint);
}

void Output::addEndSite(float* offsetValues, Hierarchy hierarchy)
{
	char floatVal[32] = { 0 };

	END_SITE;
	NEXT_LINE;

	if (hierarchy == joint)
	{
		TAB_SPACE;
		TAB_SPACE;
	}
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}

	BEGIN_BRACKET;
	NEXT_LINE;

	if (hierarchy == joint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}

	OFFSET;
	TAB_SPACE;

	sprintf(floatVal, "%f", offsetValues[0]);
	fwrite(floatVal, 1, strlen(floatVal), file);

	ONE_SPACE;

	sprintf(floatVal, "%f", offsetValues[0]);
	fwrite(floatVal, 1, strlen(floatVal), file);

	ONE_SPACE;

	sprintf(floatVal, "%f", offsetValues[0]);
	fwrite(floatVal, 1, strlen(floatVal), file);

	NEXT_LINE;

	if (hierarchy == joint)
	{
		TAB_SPACE;
		TAB_SPACE;
	}
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}

	CLOSE_BRACKET;
	NEXT_LINE;
}

bool Output::addBody(std::string name, bool hasRotChannel, bool hasPosChannel, float* offsetValues, Hierarchy hierarchy)
{
	char floatVal[32] = { 0 };
	if (!file)
		return false;

	ONE_SPACE;
	fwrite(name.c_str() , 1, name.length(), file);
	NEXT_LINE;
	if (hierarchy == joint)
		TAB_SPACE;
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
	}

	BEGIN_BRACKET;
	NEXT_LINE;

	if (hierarchy == root)
		TAB_SPACE;
	else if (hierarchy == joint)
	{
		TAB_SPACE;
		TAB_SPACE;
	}
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}

	OFFSET;
	TAB_SPACE;

	sprintf(floatVal, "%f", offsetValues[0]);
	fwrite(floatVal, 1, strlen(floatVal), file);
	sprintf(floatVal, " %f", offsetValues[1]);
	fwrite(floatVal, 1, strlen(floatVal), file);
	sprintf(floatVal, " %f", offsetValues[2]);
	fwrite(floatVal, 1, strlen(floatVal), file);

	NEXT_LINE;

	if (hierarchy == root)
		TAB_SPACE;
	else if (hierarchy == joint)
	{
		TAB_SPACE;
		TAB_SPACE;
	}
	else if (hierarchy == childJoint)
	{
		TAB_SPACE;
		TAB_SPACE;
		TAB_SPACE;
	}

	CHANNELS;
	ONE_SPACE;

	if (hasRotChannel & hasPosChannel)
		fwrite("6 Xposition Yposition Zposition Zrotation Xrotation Yrotation",	1, strlen("6 Xposition Yposition Zposition Zrotation Xrotation Yrotation"), file);
	else if (hasRotChannel)
		fwrite("3 Zrotation Xrotation Yrotation", 1, strlen("3 Zrotation Xrotation Yrotation"),	file);
	else if (hasPosChannel)
		fwrite("3 Xposition Yposition Zposition", 1, strlen("3 Xposition Yposition Zposition"),	file);

	NEXT_LINE;

	return true;
}

void Output::setFileName(std::string _fileName)
{
	fileName = _fileName + ".bvh";
}

void Output::addMotionHeader(float frameTime)
{
	char frameStr[32] = { 0 };
	fwrite("MOTION", 1, strlen("MOTION"), file);

	NEXT_LINE;

	fwrite("Frames:", 1, strlen("Frames:"), file);

	TAB_SPACE;

	sprintf(frameStr, "%d", currentFrame);
	fwrite(frameStr, 1, strlen(frameStr), file);

	NEXT_LINE;

	fwrite("Frame Time:", 1, strlen("Frame Time:"), file);

	ONE_SPACE;

	sprintf(frameStr, "%f", frameTime);
	fwrite(frameStr, 1, strlen(frameStr), file);

	NEXT_LINE;
}

void Output::addMotionFrameData()
{
	Node *node = list->front;
	do {
		std::string temp = node->data;
		fwrite(temp.c_str(), 1, temp.length(), file);
		NEXT_LINE;
		node = node->next;
	} while (node->next != NULL);
	BLOCK = false;
}

void Output::addMotion()
{
	std::string temp = "0 0 0 0 0 0 0 0 0";
	for (int i = 0; i < MAX_MARKERS; i++)
	{
		if (marker[i].isSelected)
			temp += marker[i].toString();
	}
	if (list->front == NULL)
		organizer.insertAtFront(list, temp);
	else
		organizer.insertAtRear(list, temp);
}