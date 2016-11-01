#include <SDKDDKVer.h>
#include "Cxml.h"
#include "CStringManager/CStringManagerAPI.h"
#include "CCharset/CCharsetAPI.h"

Cxml::Cxml(){
	version = 0;
}

void Cxml::init(double version,CString charset,CString standalone){
	this->version = version;
	this->charset = charset;
	this->standalone = standalone;
}

void Cxml::LoadHead(CString* strXml){
	//������ļ�ͷ�ȼ����ļ�ͷ
	int nHeadLeft = strXml->Find("<?xml");
	//�ļ�ͷ�����ؼ��ֿ�����CDATA�д���
	int nHeadLeftSame = strXml->Find("<");
	//���û���ļ�ͷ���Ҳ����ؼ��ֻ����ҵ��ˣ����ؼ��ֺ�<����ͬһλ��
	if(nHeadLeft == -1 || (nHeadLeft != -1 && nHeadLeftSame != nHeadLeft)) return;
	//�����
	int nHeadRight = strXml->Find(">");
	if(nHeadRight == -1){
		mapError[*strXml] = "�޶�Ӧ>";
		return;
	}
	CString strHead = strXml->Mid(nHeadLeft,nHeadRight - nHeadLeft + 1);
	int nBegin = 0;
	if((nBegin = strHead.Find("version")) != -1 || (nBegin = strHead.Find("VERSION")) != -1){
		int nLeft = strHead.Find("\"",nBegin);
		if(nLeft == -1){
			mapError[strHead] = "version�����ų���";
			return;
		}
		int nRight = strHead.Find("\"",nLeft + 1);
		if(nRight == -1){
			mapError[strHead] = "version�����ų���";
			return;
		}
		CString strVersion = strHead.Mid(nLeft + 1,nRight - nLeft - 1);
		version = atof(strVersion);
	}
	if((nBegin = strHead.Find("encoding")) != -1 || (nBegin = strHead.Find("ENCODING")) != -1){
		int nLeft = strHead.Find("\"",nBegin);
		if(nLeft == -1){
			mapError[strHead] = "encoding�����ų���";
			return;
		}
		int nRight = strHead.Find("\"",nLeft + 1);
		if(nRight == -1){
			mapError[strHead] = "encoding�����ų���";
			return;
		}
		charset = strHead.Mid(nLeft + 1,nRight - nLeft - 1);
	}
	if((nBegin = strHead.Find("standalone")) != -1 || (nBegin = strHead.Find("STANDALONE")) != -1){
		int nLeft = strHead.Find("\"",nBegin);
		if(nLeft == -1){
			mapError[strHead] = "standalone�����ų���";
			return;
		}
		int nRight = strHead.Find("\"",nLeft + 1);
		if(nRight == -1){
			mapError[strHead] = "standalone�����ų���";
			return;
		}
		standalone = strHead.Mid(nLeft + 1,nRight - nLeft - 1);
	}
	strXml->Delete(nHeadLeft,nHeadRight - nHeadLeft + 1);
	return;
}

bool Cxml::GetOneModule(CString* pstrXml,int* flag,CString* strXmlName,CString* strXmlAttri,CString* strXmlText){
	int nLeft = pstrXml->Find("<");
	if(nLeft == -1){
		CString strTemp = *pstrXml;
		//���ȫ������Ч�ַ����˳�ѭ��
		pstrXml->Replace(" ","");
		pstrXml->Replace("\t","");
		pstrXml->Replace("\n","");
		pstrXml->Replace("\r","");
		if(*pstrXml == "") return 0;
		//������ַ�������жϽ���
		else{
			mapError[strTemp] = "���ڶ����ַ��������ж�";
			return 0;
		}
	}
	CStringManager strManager = *pstrXml;
	int nRight = strManager.FindOther('<','>',nLeft);
	if(nRight == -1){
		mapError[*pstrXml] = "�Ҳ�����Ӧ�Ҳ�����\">\"�������ж�";
		return 0;
	}
	//ȡ����Ӧ�����ڵ����ݣ��ж�ʱ����ע�ͻ���CDATA�����򰴽ڵ㴦��
	CString strOne = pstrXml->Mid(nLeft + 1,nRight - nLeft - 1);
	//�����ע��
	if(strOne.Mid(0,3) == "!--" && strOne.Mid(strOne.GetLength() - 2,2) == "--" && strOne.GetLength() >= 5){
		*strXmlText = strOne.Mid(3,strOne.GetLength() - 5);
		*flag = NOTE;
		//ɾ���������
		pstrXml->Delete(nLeft,nRight - nLeft + 1);
		return 1;
	}
	//�����CDATA <![CDATA[�ı�����]]>
	else if(strOne.Mid(0,8) == "![CDATA[" && strOne.Mid(strOne.GetLength() - 2,2) == "]]" && strOne.GetLength() >= 10){
		*strXmlText = strOne.Mid(8,strOne.GetLength() - 10);
		*flag = CDATA;
		//ɾ��������֣�Ȼ�����ѭ��
		pstrXml->Delete(nLeft,nRight - nLeft + 1);
		return 1;
	}
	//�ȵ��ɽڵ㴦��
	else{
		//����ǿսڵ�
		if(strOne[strOne.GetLength() - 1] == '/'){
			*flag = NULLVALUE;
			int nAttriLeft = strOne.Find(" ") + 1;
			//˵��û������ֵ
			if(nAttriLeft == 0){
				*strXmlName = strOne.Mid(0,strOne.GetLength() - 1);
				*strXmlAttri = "";
			}
			else{
				*strXmlName = strOne.Mid(0,nAttriLeft - 1);
				*strXmlAttri = strOne.Mid(nAttriLeft,strOne.GetLength() - nAttriLeft - 1);
			}
			*strXmlText = "null";
			pstrXml->Delete(nLeft,nRight - nLeft + 1);
			return 1;
		}
		else{
			*flag = XML;
			int nAttriLeft = strOne.Find(" ") + 1;
			//˵��û������ֵ
			if(nAttriLeft == 0){
				*strXmlName = strOne.Mid(0,strOne.GetLength());
				*strXmlAttri = "";
			}
			else{
				*strXmlName = strOne.Mid(0,nAttriLeft - 1);
				*strXmlAttri = strOne.Mid(nAttriLeft,strOne.GetLength() - nAttriLeft);
			}
			//���ҵ�β�ڵ�
			int nTailLeft = pstrXml->Find("</" + *strXmlName + ">",nRight + 1);
			if(nTailLeft == -1){
				mapError["<" + *strXmlName + ">"] = "�޷��ҵ���ǰ�ڵ��Ӧ��β�ڵ�";
				pstrXml->Delete(nLeft,nRight - nLeft + 1);
				return 0;
			}
			else{
				int nTailRight = nTailLeft + strXmlName->GetLength() + 2;
				*strXmlText = pstrXml->Mid(nRight + 1,nTailLeft - nRight - 1);;
				pstrXml->Delete(nLeft,nTailRight - nLeft + 1);
				return 1;
			}
		}
	}
}

void Cxml::LoadOneModule(int flag,CString strXmlName,CString strXmlAttri,CString strXmlText){
	if(flag == NOTE){
		listNote.push_back(CNoteData(listXml.size(),strXmlText));
	}
	else if(flag == CDATA){
		listCDATA.push_back(CNoteData(listXml.size(),strXmlText));
	}
	else if(flag == NULLVALUE){
		Cxml nullXml;
		nullXml.strOneXmlName = strXmlName;
		nullXml.strOneXmlValue = strXmlText;
		if(strXmlAttri != "") nullXml.mapAttri = nullXml.LoadAttri(strXmlAttri);
		listXml.push_back(nullXml);
	}
	else if(flag == XML){
		//���������û��<˵���ǵ����ڵ�
		if(strXmlText.Find('<') == -1){
			Cxml xmlTempOne;
			xmlTempOne.strOneXmlName = strXmlName;
			xmlTempOne.strOneXmlValue = strXmlText;
			if(strXmlAttri != "") xmlTempOne.mapAttri = xmlTempOne.LoadAttri(strXmlAttri);
			listXml.push_back(xmlTempOne);
		}
		//��<��ݹ�
		else{
			Cxml xmlTemp;
			xmlTemp.strOneXmlName = strXmlName;
			if(strXmlAttri != "") xmlTemp.mapAttri = xmlTemp.LoadAttri(strXmlAttri);
			map<CString,CString> mapChildError = xmlTemp.Load(strXmlText);
			//�ϲ�����map
			AddErrorMap(mapChildError);
			listXml.push_back(xmlTemp);
		}
	}
	return;
}

map<CString,CString> Cxml::LoadAttri(CString strXmlAttri){
	map<CString,CString> mapAttri;
	CStringManager strManager = strXmlAttri;
	vector<CString> vecHead = strManager.split(" ");
	int i = -1;
	while(i++ != vecHead.size() - 1){
		CStringManager strOneManager = vecHead.at(i);
		vector<CString> vecOneAttri = strOneManager.split("=");
		if(vecOneAttri.size() == 1){
			mapError[strXmlAttri] = "����֮���ж���ո������޵Ⱥ�����";
		}
		else if(vecOneAttri.size() > 2){
			mapError[strXmlAttri] = "����֮���ж���Ⱥ�";
		}
		else{
			CString strAttriValue = vecOneAttri.at(1);
			if((strAttriValue[0] == '\"' && strAttriValue[strAttriValue.GetLength() - 1] == '\"') || (strAttriValue[0] == '\'' && strAttriValue[strAttriValue.GetLength() - 1] == '\'')){
				mapAttri[vecOneAttri.at(0)] = strAttriValue.Mid(1,strAttriValue.GetLength() - 2);
			}
			else{
				mapError[strXmlAttri] = "����ֵ��Χ�����ţ����пո�";
			}
		}
	}
	return mapAttri;
}

map<CString,CString> Cxml::Load(CString strXml){
	//�����ļ�ͷ
	LoadHead(&strXml);
	while(1){
		CString strXmlName,strXmlAttri,strXmlText;
		int flag = 0;
		bool x = GetOneModule(&strXml,&flag,&strXmlName,&strXmlAttri,&strXmlText);
		if(x == 0) break;
		LoadOneModule(flag,strXmlName,strXmlAttri,strXmlText);
	}
	return mapError;
}

void Cxml::AddErrorMap(map<CString,CString> mapChildError){
	auto it = mapChildError.begin();
	for(;it != mapChildError.end();it++){
		mapError[it->first] = it->second;
	}
	return;
}

CString Cxml::toCString(CString NewLineSign,CString FormatSign,int FormatLength){
	//�ļ�ͷ
	CString strHead;
	if(version != 0 || charset != "" || standalone != ""){
		strHead = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
		if(version != 0){
			CString strTemp;
			strTemp.Format("%1.1lf",version);
			strHead.Replace("1.0",strTemp);
		}
		else strHead.Replace("version=\"1.0\" ","");
		if(charset != "") strHead.Replace("UTF-8",charset);
		else strHead.Replace("encoding=\"UTF-8\" ","");
		if(standalone != "") strHead.Replace("yes",standalone);
		else strHead.Replace("standalone=\"yes\" ","");
	}

	//�õ�strFormatSignTemp������ʽ�����ĸ�ʽ��ʶλ
	int nFormatLengthTemp = FormatLength;
	CString strFormatSignTemp;
	while(nFormatLengthTemp-- != 0) strFormatSignTemp = strFormatSignTemp + FormatSign;
	
	CString strXmlResult;
	int nInsert = 0;
	//�Ȱ����ֺ�ֵת�����ַ���������������ʾ�������
	//����
	if(strOneXmlName != ""){
		//��ֵ
		if(strOneXmlValue == "null"){
			strXmlResult = NewLineSign + strFormatSignTemp + "<" + strOneXmlName + AttriToCString(mapAttri) + "/>";
			nInsert = nInsert + strXmlResult.GetLength();
		}
		//ʵֵ
		else if(strOneXmlValue != ""){
			strXmlResult = NewLineSign + strFormatSignTemp + "<" + strOneXmlName + AttriToCString(mapAttri) + ">" + strOneXmlValue + "</" + strOneXmlName + ">";
			nInsert = nInsert + strXmlResult.GetLength();
		}
		//��ֵ����listXml�������һ��
		else{
			strXmlResult = NewLineSign + strFormatSignTemp + "<" + strOneXmlName + AttriToCString(mapAttri) + ">" + strFormatSignTemp + "</" + strOneXmlName + ">";
			nInsert = strXmlResult.Find(strFormatSignTemp + "</" + strOneXmlName + ">");
			//��Ϊ���뵽��һ�㣬������Ҫ��ʽ + 1
			AddXml(&strXmlResult,&nInsert,NewLineSign,FormatSign,FormatLength + 1);
		}
	}
	//����
	else{
		//������ʾ����㣬���Ը�ʽ����
		AddXml(&strXmlResult,&nInsert,NewLineSign,FormatSign,FormatLength);
	}
	//������ļ�ͷȥ���ͷ�Ļس���
	if(strHead == ""){
		return strXmlResult.Mid(NewLineSign.GetLength(),strXmlResult.GetLength() - NewLineSign.GetLength());
	}
	return strHead + strXmlResult;
}

CString Cxml::AttriToCString(map<CString,CString> mapAttri){
	CString strResult;
	for(auto it = mapAttri.begin();it != mapAttri.end();it++){
		strResult = strResult + " " + it->first + "=";
		int nFind = it->second.Find("\"");
		//˵��ֵ���м�û��˫���ţ��������Ҽ���˫����
		if(nFind == -1) strResult = strResult + "\"" + it->second + "\"";
		else strResult = strResult + "\'" + it->second + "\'";
	}
	return strResult;
}

void Cxml::AddXml(CString* strXmlResult,int* pInsert,CString NewLineSign,CString FormatSign,int FormatLength){
	auto itNote = listNote.begin();
	auto itData = listCDATA.begin();
	auto itXml = listXml.begin();
	int i = -1;
	//ѭ����������listXml����
	while(itXml != listXml.end()){
		//�ڼ���ѭ���ı�ʶλ
		i++;
		//�õ�strFormatSignTemp������ʽ�����ĸ�ʽ��ʶλ
		int nFormatLengthTemp = FormatLength;
		CString strFormatSignTemp;
		while(nFormatLengthTemp-- != 0) strFormatSignTemp = strFormatSignTemp + FormatSign;
		//������˶�Ӧ��ע�ͻ�CDATA����ӽ�ȥ
		if(itNote != listNote.end() && itNote->nPosition == i){
			CString strNote = NewLineSign + strFormatSignTemp + "<!--" + itNote->strNoteData + "-->";
			strXmlResult->Insert(*pInsert,strNote);
			*pInsert = *pInsert + strNote.GetLength();
			itNote++;
		}
		if(itData != listCDATA.end() && itData->nPosition == i){
			CString strData = NewLineSign + strFormatSignTemp + "<![CDATA[" + itData->strNoteData + "]]>";
			strXmlResult->Insert(*pInsert,strData);
			*pInsert = *pInsert + strData.GetLength();
			itData++;
		}
		CString strXmlTemp = NewLineSign + itXml->toCString(NewLineSign,FormatSign,FormatLength);
		strXmlResult->Insert(*pInsert,strXmlTemp);
		*pInsert = *pInsert + strXmlTemp.GetLength();
		itXml++;
	}
	strXmlResult->Insert(*pInsert,NewLineSign);
	*pInsert = *pInsert + NewLineSign.GetLength();
	return;
}

int main(){
	double a = 0;
	if(a != 0) AfxMessageBox("1");
	CString str = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><!--by months--> <class_list a=\'1\' b=\"2\">  		<student a=\"3\" b=\'\"6\"\'>  		<!--Shdds--><name/>  <!--Shs--><![CDATA[123456<<<>>>789]]><grade>A</grade>  		</student>  		</class_list>";
	Cxml xml;
	xml.Load(str);
	CString strXml = xml.toCString();
	AfxMessageBox(strXml);
	int x = 3;
	return 0;
}