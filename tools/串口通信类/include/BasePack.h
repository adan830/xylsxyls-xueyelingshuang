#ifndef __BASE_PACK_H__
#define __BASE_PACK_H__

typedef struct BASE_MSG		//�����İ�ͷ�����а��������˰�ͷ
{
	UINT 	uSize;
	UINT	uType;
	BASE_MSG()
	{
		memset(this,0x00,sizeof(BASE_MSG));
	}
	BASE_MSG(UINT Size,UINT Type)
	{
		uSize = Size;
		uType = Type;
	}
}*LPBASE_MSG;

typedef struct BASE_MSG_PACK
{
	int		nSize;
	char*	pszData;
	BASE_MSG_PACK()
	{
		nSize=0;
		pszData=NULL;
	}
	int GetHeaderSize()	//��ð�ͷ��С��������д�˺���
	{
		return sizeof(BASE_MSG);
	}
	UINT GetPackSize(char* szHeaderPack)	//��ð��Ĵ�С��������ͷ���ȡ�������д�˺���
	{
		LPBASE_MSG pMsg = (LPBASE_MSG)szHeaderPack;
		return pMsg->uSize;
	}
}*LPBASE_MSG_PACK;

#endif
