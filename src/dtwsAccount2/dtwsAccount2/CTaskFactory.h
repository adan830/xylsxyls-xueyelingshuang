#pragma once
#include "CTaskThreadManager/CTaskThreadManagerAPI.h"
#include "Rect/RectAPI.h"

//�����Ϊ�����֣�׼�����ݺ�ִ������
//׼���������Ⱦ��������ƶ���ĳ��������ƶ���ĳ����Ϊ׼�����������Ϊ����ִ������
//һ������ϣ�׼�����ݱ���Ҳ��������
//׼�����ݺ�ִ�������ǲ��ɷֵ�

/** ��¼����
*/
class CLoginTask : public CTask
{
public:
	virtual void DoTask();
};

/** Ѱ��ĳ��ͼ���ƶ�����ͼƬ���Ĳ�����
*/
class CClickPicTask : public CTask
{
public:
	CClickPicTask(const std::string& picPath,const xyls::Rect& rect);
	virtual void DoTask();

private:
	std::string m_picPath;
	xyls::Rect m_picRect;

private:
	/** ����Ⱥ
	*/
	std::list<std::shared_ptr<CTask>> m_taskList;
};

class CFindPicTask : public CTask
{
public:
	virtual void DoTask();
	xyls::Point& GetPoint();
private:
	xyls::Point m_pointResult;
};

class CMoveMouseTask : public CTask
{
public:
	CMoveMouseTask(const xyls::Point& point);
	virtual void DoTask();

private:
	xyls::Point m_point;
};

class CClickTask : public CTask
{
public:
	virtual void DoTask();
};