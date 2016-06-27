#include "StdAfx.h"
#include "wav.h"

wav::wav(void)
{
/*	strcpy(fact_block_buffer,"0123456789ABCDEF000");
	fact_block_buffer[0]=0x20;
	fact_block_buffer[1]=0x8a;
	fact_block_buffer[2]=0x00;
	fact_block_buffer[3]=0x00;
	pcmFACT.dwFactSize = 4;
	pcmFACT.szFactID[0] = 'f';
	pcmFACT.szFactID[1] = 'a';
	pcmFACT.szFactID[2] = 'c';
	pcmFACT.szFactID[3] = 't';
	*/
}

wav::~wav(void)
{
}
int wav::makeHead(unsigned short wFormatTag ,unsigned long dwSamplesPerSec ,
		unsigned short uiBitsPerSample ,unsigned short wChannels , 
		unsigned short wBlockAlign )
{
	strcpy(pcmHEADER.fccID, "RIFF");                   
	strcpy(pcmHEADER.fccType, "WAVE"); 
	strcpy(pcmFMT.fccID, "fmt "); 
	strcpy(pcmDATA.fccID, "data"); 

	pcmFMT.dwSamplesPerSec	=	dwSamplesPerSec;
	pcmFMT.uiBitsPerSample	=	uiBitsPerSample;
	pcmFMT.wChannels		=	wChannels;
	pcmFMT.wFormatTag		=	wFormatTag;
	pcmFMT.wBlockAlign		=	wBlockAlign; 
	if(wFormatTag == WAVE_FORMAT_PCM)
	{
		pcmFMT.dwAvgBytesPerSec	=	pcmFMT.dwSamplesPerSec*sizeof(unsigned short);
		pcmFMT.dwSize			=	0x10; 
	}
	else if(wFormatTag == WAVE_FORMAT_A_LAW)
	{
		pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec;//*sizeof(unsigned char);
		pcmFMT.dwSize			=	0x12; 
	}
	else if(wFormatTag == WAVE_FORMAT_U_LAW)
	{
		pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec;//*sizeof(unsigned char);
		pcmFMT.dwSize			=	0x12; 
	}
	else
	{
		return WAV_FORMAT_ERROR;
	}
	//pcmDATA.dwSize			=	0;
	return 0;
}
/*int wav::getHead(FILE *fp )
{
	long file_pos = ftell(fp);
	//Read RIFF_HEADER
	fread(&pcmHEADER, sizeof(HEADER), 1, fp);
	if(	memcmp(pcmHEADER.fccID, "RIFF", 4) != 0 ||
		memcmp(pcmHEADER.fccType, "WAVE", 4) != 0 )
	{
		return(WAV_FLAG_HEADER_ERROR);
	}

	file_pos = ftell(fp);
	//Read pcmFMT
	fread(&pcmFMT, sizeof(FMT), 1, fp);
	if(	memcmp(pcmFMT.fccID, "fmt ", 4) !=0 
		//|| pcmFMT.dwSize != 16
		//|| pcmFMT.wFormatTag != 0x1 
		//|| pcmFMT.wChannels != 0x1 
		//|| pcmFMT.dwSamplesPerSec != 16000 
		//|| pcmFMT.uiBitsPerSample != 16
		)
	{
		return(WAV_FLAG_FMT_ERROR);
	}

	file_pos = ftell(fp);
	if(pcmFMT.wFormatTag == WAVE_FORMAT_MU_LAW
		|| pcmFMT.wFormatTag == WAVE_FORMAT_A_LAW)
	{
	//read FACTdata
		file_pos+=2;
		fseek(fp, file_pos, SEEK_SET);
		fread(&pcmFACT, sizeof(FACT), 1, fp);
		if( memcmp(pcmFACT.szFactID, "fact", 4) != 0 )
		{	
			return(WAV_FLAG_FACT_ERROR);
		}
		//has_fact_block =1;
		fread(&fact_block_buffer,pcmFACT.dwFactSize, 1, fp);
	}
	file_pos = ftell(fp);
	//read PCMdata
	fread(&pcmDATA, sizeof(DATA), 1, fp);
	if (memcmp(pcmDATA.fccID, "data", 4) != 0)
	{
		return(WAV_FLAG_DATA_ERROR);
	}
	return 0;
}

int wav::getHead(const char * in ,unsigned short &wFormatTag,unsigned long &dwSamplesPerSec,
		unsigned short &uiBitsPerSample,unsigned short &wChannels, 
		unsigned short &wBlockAlign)
{
	int nRet = 0 ;
	FILE *fp = fopen(in,"rb");
	if(fp==NULL)
	{
		return WAV_IN_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet != 0)
	{
		fclose(fp);
		return nRet;
	}
	dwSamplesPerSec	=	pcmFMT.dwSamplesPerSec;
	uiBitsPerSample	=	pcmFMT.uiBitsPerSample;
	wChannels		=	pcmFMT.wChannels;
	wFormatTag		=	pcmFMT.wFormatTag;
	wBlockAlign		=	pcmFMT.wBlockAlign; 
	fclose(fp);
	return 0;
}
*/
int wav::pcm2wav(const char * in , const char * out)
{
	unsigned   short   m_pcmData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	FILE   *fp,*fpCpy; 
	int nRet = 0;
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		fclose(fp);
		return WAV_OUT_FILE_ERROR;
	}
	
//�����Ǵ���wavͷ��HEADER;��.dwsizeδ������Ϊ��֪��Data�ĳ��ȡ� 
//	strcpy(pcmHEADER.fccID, "RIFF");                   
//	strcpy(pcmHEADER.fccType, "WAVE"); 
//�����Ǵ���wavͷ��HEADER; 

//�����Ǵ���wavͷ��FMT; 
//	pcmFMT.dwSamplesPerSec=16000; 
//	pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec*sizeof(m_pcmData); 
//	pcmFMT.uiBitsPerSample=16; 

//	strcpy(pcmFMT.fccID, "fmt "); 
//	pcmFMT.dwSize=16; 
//	pcmFMT.wBlockAlign=2; 
//	pcmFMT.wChannels=1; 
//	pcmFMT.wFormatTag=WAVE_FORMAT_PCM; 
//�����Ǵ���wavͷ��FMT;  

//	strcpy(pcmDATA.fccID, "data"); 
//�����Ǵ���wavͷ��DATA; 

//	pcmDATA.dwSize=0;	 //��pcmDATA.dwsize   0�Ա������������ֵ 

	nRet = makeHead(WAVE_FORMAT_PCM,16000,16,1,2);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT,��ΪFMT�Ѿ�д�� 
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	pcmDATA.dwSize=0;
	while(!feof(fp))	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		fread(&m_pcmData,sizeof(unsigned   short),1,fp);	 //��.pcm�ж������� 
		pcmDATA.dwSize+=2;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		fwrite(&m_pcmData,sizeof(unsigned   short),1,fpCpy);	//������д��.wav�ļ�; 
	} 

	pcmHEADER.dwSize=44+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fp);	 //�ر��ļ� 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}
/*
int wav::wav2pcm(const char * in , const char * out)
{
	unsigned short m_pcmData;                               //����.wav��д���ļ�.pcm���ݱ��� 

	int nRet = 0;
	FILE   *fp,*fpCpy;
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return WAV_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		fclose(fp);
		return PCM_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_PCM)
	{
		return WAV_FORMAT_ERROR;
	}

	while(pcmDATA.dwSize>0)//!feof(fp))	 //��.wav�ļ�����ǰ����������ת��������.pcm;
	{ 
		fread(&m_pcmData,sizeof(unsigned short),1,fp);	 //��.wav�ж������� 
		pcmDATA.dwSize-=2;	 //�������ݵ�ʣ�೤�ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		fwrite(&m_pcmData,sizeof(unsigned short),1,fpCpy);	//������д��.pcm�ļ�; 
	} 
	fclose(fp);	 //�ر��ļ� 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}


int wav::wav2a(const char * in , const char * out)
{
	unsigned short m_pcmData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_aData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_PCM)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_A_LAW,16000,8,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fseek(fpCpy,sizeof(FACT),1);	 //����FACT
	fseek(fpCpy,pcmFACT.dwFactSize,1);	 //����FACT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_pcmData,sizeof(unsigned   short),1,fp);	 //��.pcm�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=2;
		pcmDATA.dwSize+=1;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_aData = G711.linear2alaw(m_pcmData);
		//m_aData = G711.ALawEncode(m_pcmData);
		fwrite(&m_aData,sizeof(unsigned char),1,fpCpy);	//������д��.wav�ļ�; 
		fread(&m_pcmData,sizeof(unsigned short),1,fp);	 //��.pcm�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=58+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fwrite(&pcmFACT,sizeof(FACT),1,fpCpy);	   //д��FACT; 
	fwrite(fact_block_buffer,pcmFACT.dwFactSize,1,fpCpy);	   //д��FACT; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}

int wav::a2wav(const char * in , const char * out)
{
	unsigned short m_pcmData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_aData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_A_LAW)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_PCM,16000,16,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_aData,sizeof(unsigned char),1,fp);	 //��a-law�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=1;
		pcmDATA.dwSize+=2;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_pcmData = G711.alaw2linear(m_aData);
		//m_aData = G711.ALawEncode(m_pcmData);
		fwrite(&m_pcmData,sizeof(unsigned short),1,fpCpy);	//������д��wav�ļ�; 
		fread(&m_aData,sizeof(unsigned char),1,fp);	 //��a-low�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=44+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}


int wav::wav2u(const char * in , const char * out)
{
	unsigned short m_pcmData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_uData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_PCM)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_U_LAW,16000,8,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fseek(fpCpy,sizeof(FACT),1);	 //����FACT
	fseek(fpCpy,pcmFACT.dwFactSize,1);	 //����FACT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_pcmData,sizeof(unsigned   short),1,fp);	 //��.pcm�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=2;
		pcmDATA.dwSize+=1;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_uData = G711.linear2ulaw(m_pcmData);
		//m_uData = G711.ALawEncode(m_pcmData);
		fwrite(&m_uData,sizeof(unsigned char),1,fpCpy);	//������д��.wav�ļ�; 
		fread(&m_pcmData,sizeof(unsigned short),1,fp);	 //��.pcm�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=58+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fwrite(&pcmFACT,sizeof(FACT),1,fpCpy);	   //д��FACT; 
	fwrite(fact_block_buffer,pcmFACT.dwFactSize,1,fpCpy);	   //д��FACT; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}

int wav::u2wav(const char * in , const char * out)
{
	unsigned short m_pcmData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_uData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_U_LAW)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_PCM,16000,16,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_uData,sizeof(unsigned char),1,fp);	 //��a-law�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=1;
		pcmDATA.dwSize+=2;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_pcmData = G711.ulaw2linear(m_uData);
		//m_uData = G711.ALawEncode(m_pcmData);
		fwrite(&m_pcmData,sizeof(unsigned short),1,fpCpy);	//������д��wav�ļ�; 
		fread(&m_uData,sizeof(unsigned char),1,fp);	 //��a-low�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=44+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}

int wav::u2a(const char * in , const char * out)
{
	unsigned char m_uData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_aData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_U_LAW)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_A_LAW,16000,8,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fseek(fpCpy,sizeof(FACT),1);	 //����FACT
	fseek(fpCpy,pcmFACT.dwFactSize,1);	 //����FACT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_uData,sizeof(unsigned char),1,fp);	 //��a-law�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=1;
		pcmDATA.dwSize+=1;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_aData = G711.ulaw2alaw(m_uData);
		//m_aData = G711.ALawEncode(m_pcmData);
		fwrite(&m_aData,sizeof(unsigned char),1,fpCpy);	//������д��wav�ļ�; 
		fread(&m_uData,sizeof(unsigned char),1,fp);	 //��a-low�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=58+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fwrite(&pcmFACT,sizeof(FACT),1,fpCpy);	   //д��FACT; 
	fwrite(fact_block_buffer,pcmFACT.dwFactSize,1,fpCpy);	   //д��FACT; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}

int wav::a2u(const char * in , const char * out)
{
	unsigned char m_uData;                               //����.pcm��д���ļ�.wav���ݱ��� 
	unsigned char m_aData;
	int nRet = 0;
	FILE   *fp,*fpCpy; 
	if((fp=fopen( in , "rb"))   ==   NULL)	 //��ȡ�ļ� 
	{ 
		return PCM_IN_FILE_ERROR;
	}   

	if((fpCpy=fopen( out , "wb"))   ==   NULL)	 //Ϊת������һ�����ļ� 
	{ 
		return WAV_OUT_FILE_ERROR;
	}
	nRet = getHead(fp);
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	if(pcmFMT.wFormatTag!=WAVE_FORMAT_A_LAW)
	{
		return WAV_FORMAT_ERROR;
	}
	unsigned long pcmSize = pcmDATA.dwSize;
	pcmDATA.dwSize = 0;
	nRet = makeHead(WAVE_FORMAT_U_LAW,16000,8,1,2);//makeֻ�Բ������Խ��в�����ԭ����pcmDATA.dwSizeû���ܵ�Ӱ��
	if(nRet!=0)
	{
		fclose(fp);
		fclose(fpCpy);
		return nRet;
	}
	
	
	fseek(fpCpy,sizeof(HEADER),1);	 //����HEADER�ĳ��ȣ��Ա��������д��wav�ļ�������; 
	fseek(fpCpy,sizeof(FMT),1);	 //����FMT
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fseek(fpCpy,sizeof(FACT),1);	 //����FACT
	fseek(fpCpy,pcmFACT.dwFactSize,1);	 //����FACT
	fseek(fpCpy,sizeof(DATA),1);	 //����DATA�ĳ��ȣ��Ա��Ժ���д��wavͷ��DATA; 
	fread(&m_aData,sizeof(unsigned char),1,fp);	 //��a-law�ж�������
	
	while(pcmSize>0)	 //��.pcm�ļ�����ǰ����������ת��������.wav; 
	{ 
		pcmSize-=1;
		pcmDATA.dwSize+=1;	 //�������ݵĳ��ȣ�ÿ����һ�����ݣ����Ⱦͼ�һ�� 
		m_uData = G711.alaw2ulaw(m_aData);
		//m_aData = G711.ALawEncode(m_pcmData);
		fwrite(&m_uData,sizeof(unsigned char),1,fpCpy);	//������д��wav�ļ�; 
		fread(&m_aData,sizeof(unsigned char),1,fp);	 //��a-low�ж������� 
	}
	fclose(fp);	 //�ر��ļ� 

	pcmHEADER.dwSize=58+pcmDATA.dwSize;	   //����pcmDATA.dwsize�ó�pcmHEADER.dwsize��ֵ 
	rewind(fpCpy);	 //��fpCpy��Ϊ.wav��ͷ���Ա���д��HEADER��DATA; 
	fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy);	 //д��HEADER 
	fwrite(&pcmFMT,sizeof(FMT),1,fpCpy);	 //��FMTд��.wav�ļ�; 
	fseek(fpCpy,2,1);	 //fmt��������ֽ�
	fwrite(&pcmFACT,sizeof(FACT),1,fpCpy);	   //д��FACT; 
	fwrite(fact_block_buffer,pcmFACT.dwFactSize,1,fpCpy);	   //д��FACT; 
	fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);	   //д��DATA; 
	fclose(fpCpy);	   //�ر��ļ�
	return WAV_SUCCESS;
}
*/