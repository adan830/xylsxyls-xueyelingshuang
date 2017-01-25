#include <SDKDDKVer.h>
#include "Cxml.h"
#include "CStringManager/CStringManagerAPI.h"
#include "CCharset/CCharsetAPI.h"

Cxml::Cxml(){
	version = 0;
	bVisit = 1;
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
	CStringManager strManager = (LPSTR)(LPCTSTR)(*pstrXml);
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
		//nullXml.pPreXml = this;
		if(strXmlAttri != "") nullXml.mapAttri = nullXml.LoadAttri(strXmlAttri);
		listXml.push_back(nullXml);
		//listXml.back().pPreXml = &(listXml.back());
	}
	else if(flag == XML){
		//���������û��<˵���ǵ����ڵ�
		if(strXmlText.Find('<') == -1){
			Cxml xmlTempOne;
			xmlTempOne.strOneXmlName = strXmlName;
			xmlTempOne.strOneXmlValue = strXmlText;
			//xmlTempOne.pPreXml = this;
			if(strXmlAttri != "") xmlTempOne.mapAttri = xmlTempOne.LoadAttri(strXmlAttri);
			listXml.push_back(xmlTempOne);
			//listXml.back().pPreXml = &(listXml.back());
		}
		//��<��ݹ�
		else{
			Cxml xmlTemp;
			xmlTemp.strOneXmlName = strXmlName;
			//xmlTemp.pPreXml = this;
			if(strXmlAttri != "") xmlTemp.mapAttri = xmlTemp.LoadAttri(strXmlAttri);
			map<CString,CString> mapChildError = xmlTemp.Load(strXmlText);
			//�ϲ�����map
			AddErrorMap(mapChildError);
			listXml.push_back(xmlTemp);
			//listXml.back().pPreXml = &(listXml.back());
		}
	}
	return;
}

map<CString,CString> Cxml::LoadAttri(CString strXmlAttri){
	map<CString,CString> mapAttri;
	CStringManager strManager = (LPSTR)(LPCTSTR)strXmlAttri;
	vector<string> vecHead = strManager.split(" ");
	int i = -1;
	while(i++ != vecHead.size() - 1){
		CStringManager strOneManager = vecHead.at(i);
		vector<string> vecOneAttri = strOneManager.split("=");
		if(vecOneAttri.size() == 1){
			mapError[strXmlAttri] = "����֮���ж���ո������޵Ⱥ�����";
		}
		else if(vecOneAttri.size() > 2){
			mapError[strXmlAttri] = "����֮���ж���Ⱥ�";
		}
		else{
			CString strAttriValue = vecOneAttri.at(1).c_str();
			if((strAttriValue[0] == '\"' && strAttriValue[strAttriValue.GetLength() - 1] == '\"') || (strAttriValue[0] == '\'' && strAttriValue[strAttriValue.GetLength() - 1] == '\'')){
				mapAttri[vecOneAttri.at(0).c_str()] = strAttriValue.Mid(1,strAttriValue.GetLength() - 2);
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
	while(itNote != listNote.end() || itData != listCDATA.end() || itXml != listXml.end()){
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
		if(itXml != listXml.end()){
			CString strXmlTemp = NewLineSign + itXml->toCString(NewLineSign,FormatSign,FormatLength);
			strXmlResult->Insert(*pInsert,strXmlTemp);
			*pInsert = *pInsert + strXmlTemp.GetLength();
			itXml++;
		}
	}
	strXmlResult->Insert(*pInsert,NewLineSign);
	*pInsert = *pInsert + NewLineSign.GetLength();
	return;
}

Cxml& Cxml::operator[](CString strNode){
	//������һ��Ԫ�س���
	if(listVisit.size() > 0){
		int nLast = listVisit.back();
		if(nLast == 3 || nLast == 5){
			bVisit = 0;
			return *this;
		}
	}
	listVisit.push_back(1);
	listCStringStorage.push_back(strNode);
	return *this;
}

Cxml& Cxml::operator()(int n){
	if(n < 0){
		bVisit = 0;
		return *this;
	}
	//�������·��Ϊ�������
	if(listVisit.size() == 0){
		bVisit = 0;
		return *this;
	}
	//������һ��Ԫ�س���
	int nLast = listVisit.back();
	if(nLast == 2 || nLast == 3 || nLast == 5){
		bVisit = 0;
		return *this;
	}
	listVisit.push_back(2);
	listintStorage.push_back(n);
	return *this;
}

Cxml& Cxml::operator()(CString strAttriName){
	//�������·��Ϊ�������
	if(listVisit.size() == 0){
		bVisit = 0;
		return *this;
	}
	//������һ��Ԫ�س���
	int nLast = listVisit.back();
	if(nLast == 3 || nLast == 5){
		bVisit = 0;
		return *this;
	}
	listVisit.push_back(3);
	listCStringStorage.push_back(strAttriName);
	return *this;
}

Cxml& Cxml::operator()(CString strAttriName,CString strAttriValue){
	//�������·��Ϊ�������
	if(listVisit.size() == 0){
		bVisit = 0;
		return *this;
	}
	//������һ��Ԫ�س���
	int nLast = listVisit.back();
	if(nLast == 2 || nLast == 3 || nLast == 5){
		bVisit = 0;
		return *this;
	}
	listVisit.push_back(4);
	listCStringStorage.push_back(strAttriName);
	listCStringStorage.push_back(strAttriValue);
	return *this;
}

Cxml& Cxml::operator()(CString strNOTECDATA,int nFlag){
	//�������·��Ϊ�������
	if(listVisit.size() == 0){
		bVisit = 0;
		return *this;
	}
	//������һ��Ԫ�س���
	int nLast = listVisit.back();
	if(nLast == 3 || nLast == 5){
		bVisit = 0;
		return *this;
	}
	listVisit.push_back(5);
	listCStringStorage.push_back(strNOTECDATA);
	listintStorage.push_back(nFlag);
	return *this;
}



Cxml Cxml::operator=(CString strValue){
	//�������·��������ֱ�ӷ���
	if(bVisit == 0){
		bVisit = 1;
		return *this;
	}
	//����һ��ָ��أ���ŷ��Ͽ��ܵ�����ָ�룬�ȴ����һ����listXml��ָ��
	list<list<Cxml>*> listplistXml;
	//�ϲ�ָ��
	Cxml* pPreXmlTemp = this;
	//�ϲ�ָ���
	list<Cxml*> listpPrelistXml;
	listplistXml.push_back(&listXml);
	listpPrelistXml.push_back(this);
	//����������ʱ������һ���洢��һ���ڵ�·����һ���洢CString
	list<int> listVisitTemp;
	list<CString> listCStringStorageTemp;
	list<Cxml> listXmlTemp;
	listXmlTemp.push_back(*this);
	//����ָ��
	list<Cxml>* plistXmlTemp = &listXmlTemp;
	//ȡ��listVisit�����һ�����������ֵ�ж�
	int nLast = listVisit.back();
	//ѭ����·��û��Ϊֹ
	while(listVisit.size() != 0){
		//����ǽڵ�
		if(listVisit.front() == 1){
			//ȡ���ڵ���������ʱ�����������ڵ���
			CString strNode = *listCStringStorage.begin();
			listCStringStorage.pop_front();
			listVisitTemp.clear();
			listVisitTemp.push_back(1);
			listCStringStorageTemp.clear();
			listCStringStorageTemp.push_back(strNode);

			//������д�뻹���޸ĸò��ֵ���������
			list<Cxml>* plistXmlFirst = (*listplistXml.begin());
			for(auto itplistXmlTemp = plistXmlTemp->begin();itplistXmlTemp != plistXmlTemp->end();itplistXmlTemp++){
				if(&(itplistXmlTemp->listXml) == plistXmlFirst){
					itplistXmlTemp->strOneXmlValue = "";
					break;
				}
			}

			//ȡ��ָ��list�е�һ��ָ�룬ѭ���ӵ�һ��ָ��ָ��list�в���
			plistXmlTemp = *listplistXml.begin();
			//ȡ����һ��֮�����գ������������²�Ķ��ָ��
			listplistXml.clear();
			listpPrelistXml.clear();
			for(auto itXml = plistXmlTemp->begin();itXml != plistXmlTemp->end();itXml++){
				//������ҵ��ýڵ�
				if(itXml->strOneXmlName == strNode){
					//����һ��Cxmlָ�븳ֵ����ʱ����
					listplistXml.push_back(&(itXml->listXml));
					listpPrelistXml.push_back(&(*itXml));
					pPreXmlTemp = &(*(plistXmlTemp->begin()));
				}
			}
			//���Ϊ��˵����д��
			if(listplistXml.size() == 0){
				Cxml xmlTemp;
				xmlTemp.strOneXmlName = strNode;
				xmlTemp.strOneXmlValue = "AddNewTemp";
				//xmlTemp.pPreXml = pPreXmlTemp;
				plistXmlTemp->push_back(xmlTemp);
				//�������list���ܸ���������ָ�룬���¿��Ŀ�listָ�봫��ָ���
				listplistXml.push_back(&(plistXmlTemp->back().listXml));
				listpPrelistXml.push_back(&(plistXmlTemp->back()));
				pPreXmlTemp = &(plistXmlTemp->back());
			}
		}
		else if(listVisit.front() == 2){
			//ȡ���������洢����
			int n = *listintStorage.begin();
			listintStorage.pop_front();

			//���ֻ��һ�����������ϲ���ӽ�ȥ��
			if(listplistXml.size() == 1){
				list<Cxml>* plistXmlFirst = (*listplistXml.begin());
				for(auto itplistXmlTemp = plistXmlTemp->begin();itplistXmlTemp != plistXmlTemp->end();itplistXmlTemp++){
					if(itplistXmlTemp->strOneXmlValue == "AddNewTemp"){
						if(++listVisit.begin() != listVisit.end() && *(++listVisit.begin()) == 5) itplistXmlTemp->strOneXmlValue = "AddNewTemp";
						else itplistXmlTemp->strOneXmlValue = "";
						goto rem;
					}
				}
			}
			
			//���ָ�����û�и�λ�õ�ָ��
			if(listplistXml.size() <= (unsigned int)n){
				//���һ���µ�Cxml����������listXml��ָ��
				Cxml xmlTemp;
				xmlTemp.strOneXmlName = *listCStringStorageTemp.begin();
				xmlTemp.strOneXmlValue = "AddNewTemp";
				//xmlTemp.pPreXml = pPreXmlTemp;
				listCStringStorageTemp.pop_front();
				while(listCStringStorageTemp.size() != 0){
					xmlTemp.mapAttri[*listCStringStorageTemp.begin()] = *(++listCStringStorageTemp.begin());
					listCStringStorageTemp.pop_front();
					listCStringStorageTemp.pop_front();
				}
				//������ʱCxml�����ָ��أ�����list�е�ָ�����ָ�����
				plistXmlTemp->push_back(xmlTemp);
				pPreXmlTemp = &(plistXmlTemp->back());
				listplistXml.clear();
				listpPrelistXml.clear();
				listplistXml.push_back(&(plistXmlTemp->back().listXml));
				listpPrelistXml.push_back(&(plistXmlTemp->back()));	
			}
			else{
				int nTemp = n;
				auto itlistplistXml = listplistXml.begin();
				auto itlistpPrelistXml = listpPrelistXml.begin();
				while(nTemp-- != 0){
					itlistplistXml++;
					itlistpPrelistXml++;
				}
				//ȡ��ָ�����ָ�����Ǹ�ָ�룬�����ָ��أ��ٷ���ָ�����Ǹ�
				list<Cxml>* plistXmlTemp = *itlistplistXml;
				listplistXml.clear();
				listpPrelistXml.clear();
				listplistXml.push_back(plistXmlTemp);
				listpPrelistXml.push_back(&(plistXmlTemp->back()));
			}
		}
		else if(listVisit.front() == 3){
			//ȡ����������������
			CString strAttriName = *listCStringStorage.begin();
			listCStringStorage.pop_front();
			//Ĭ�ϰ��յ�һ����
			(*listplistXml.begin())->begin()->mapAttri[strAttriName] = strValue;
		}
		else if(listVisit.front() == 4){
			//ȡ��������������ֵ
			CString strAttriName = *listCStringStorage.begin();
			CString strAttriValue = *(++listCStringStorage.begin());
			listCStringStorage.pop_front();
			listCStringStorage.pop_front();
			//��ָ�����Ѱ���Ƿ��з�����������Ľڵ㣬���û����ȫ�����½���
			//�Ȱ�������������ֵ������ʱlist��
			listCStringStorageTemp.push_back(strAttriName);
			listCStringStorageTemp.push_back(strAttriValue);
			//���ָ�����ֻ��һ��ָ�룬���ж��ǲ�������ӵģ�����ǣ���ôֱ�����һ�����Լ���
			if(listplistXml.size() == 1){
				auto itlistplistXml = (*listplistXml.begin())->begin();
				for(;itlistplistXml != (*listplistXml.begin())->end();itlistplistXml++){
					if(itlistplistXml->strOneXmlValue == "AddNewTemp"){
						itlistplistXml->mapAttri[strAttriName] = strAttriValue;
						goto rem;
					}
				}
			}
			//����һ����ʱָ���
			list<list<Cxml>*> listplistXmlTemp;
			//����һ����ʱ�ϲ�ָ���
			list<Cxml*> listpPrelistTemp;
			//auto itlistpPrelistXml = listpPrelistXml.begin();
			for(auto itlistplistXml = listplistXml.begin();itlistplistXml != listplistXml.end();itlistplistXml++){
				//���ϲ�ָ���map�н��бȽ�
				map<CString,CString>* pmapAttriTemp = &((*listpPrelistXml.begin())->mapAttri);
				//����ҵ�����������ѵ�ǰ��ָ��ŵ���ʱָ�����
				if(pmapAttriTemp->find(strAttriName) != pmapAttriTemp->end() && (*pmapAttriTemp)[strAttriName] == strAttriValue){
					listplistXmlTemp.push_back(*itlistplistXml);
					//��������ȵľͰ��ϲ�ָ���еĵ�һ���Ž���ʱ�ϲ�ָ�����
					listpPrelistTemp.push_back(listpPrelistXml.front());
				}
				//�����ϵ��ϲ�ָ�뵯��
				listpPrelistXml.pop_front();
			}
			//����ʱָ��ظ�ֵ��ָ���
			listplistXml = listplistXmlTemp;
			listpPrelistXml = listpPrelistTemp;
			//�����ʱָ�����ȻΪ�գ����Һ��治������4��˵��û��ָ����ָ����Ҫ����
			if(listplistXml.size() == 0 && (*(++listVisit.begin()) != 4)){
				Cxml xmlTemp;
				xmlTemp.strOneXmlName = *listCStringStorageTemp.begin();
				xmlTemp.strOneXmlValue = "AddNewTemp";
				//xmlTemp.pPreXml = pPreXmlTemp;
				listCStringStorageTemp.pop_front();
				while(listCStringStorageTemp.size() != 0){
					xmlTemp.mapAttri[*listCStringStorageTemp.begin()] = *(++listCStringStorageTemp.begin());
					listCStringStorageTemp.pop_front();
					listCStringStorageTemp.pop_front();
				}
				//������ʱCxml�����ָ��أ�����list�е�ָ�����ָ�����
				plistXmlTemp->push_back(xmlTemp);
				pPreXmlTemp = &(plistXmlTemp->back());
				listplistXml.clear();
				listpPrelistXml.clear();
				listplistXml.push_back(&(plistXmlTemp->back().listXml));
				listpPrelistXml.push_back(&(plistXmlTemp->back()));	
			}
		}
		else if(listVisit.front() == 5){
			CString strNOTECDATA = *listCStringStorage.begin();
			int nFlag = *listintStorage.begin();
			if(strNOTECDATA == "NOTE"){
				if(nFlag == -1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlNOTE->listXml.begin();itlistXml != pxmlNOTE->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							if(itlistXml->strOneXmlValue == "AddNewTemp") itlistXml->strOneXmlValue = "null";
							CNoteData NoteDataTemp;
							NoteDataTemp.nPosition = nPositionTemp;//����1������һ��
							NoteDataTemp.strNoteData = strValue;
							pxmlNOTE->listNote.push_back(NoteDataTemp);
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlNOTE->listXml.begin();itlistXml != pxmlNOTE->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							if(itlistXml->strOneXmlValue == "AddNewTemp") itlistXml->strOneXmlValue = "null";
							CNoteData NoteDataTemp;
							NoteDataTemp.nPosition = nPositionTemp + 1;//��1
							NoteDataTemp.strNoteData = strValue;
							pxmlNOTE->listNote.push_back(NoteDataTemp);//�����CDATA�Ͱ����ﻻ��listCDATA������һ��
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 0){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(plistXmlFirst);
					if(pxmlNOTE->strOneXmlValue == "AddNewTemp") pxmlNOTE->strOneXmlValue = "";
					CNoteData NoteDataTemp;
					NoteDataTemp.nPosition = 0;//0
					NoteDataTemp.strNoteData = strValue;
					pxmlNOTE->listNote.push_back(NoteDataTemp);//�����CDATA�Ͱ����ﻻ��listCDATA������һ��
					goto rem;
				}
				else AfxMessageBox("��ʶ�����ֱ�Ϊ-1��0��1");
			}
			else if(strNOTECDATA == "CDATA"){
				if(nFlag == -1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlCDATA->listXml.begin();itlistXml != pxmlCDATA->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							if(itlistXml->strOneXmlValue == "AddNewTemp") itlistXml->strOneXmlValue = "null";
							CNoteData NoteDataTemp;
							NoteDataTemp.nPosition = nPositionTemp;//����1������һ��
							NoteDataTemp.strNoteData = strValue;
							pxmlCDATA->listCDATA.push_back(NoteDataTemp);
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlCDATA->listXml.begin();itlistXml != pxmlCDATA->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							if(itlistXml->strOneXmlValue == "AddNewTemp") itlistXml->strOneXmlValue = "null";
							CNoteData NoteDataTemp;
							NoteDataTemp.nPosition = nPositionTemp + 1;
							NoteDataTemp.strNoteData = strValue;
							pxmlCDATA->listCDATA.push_back(NoteDataTemp);
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 0){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(plistXmlFirst);
					if(pxmlCDATA->strOneXmlValue == "AddNewTemp") pxmlCDATA->strOneXmlValue = "";
					CNoteData NoteDataTemp;
					NoteDataTemp.nPosition = 0;//0
					NoteDataTemp.strNoteData = strValue;
					pxmlCDATA->listCDATA.push_back(NoteDataTemp);//�����CDATA�Ͱ����ﻻ��listCDATA������һ��
					goto rem;
				}
				else AfxMessageBox("��ʶ�����ֱ�Ϊ-1��0��1");
			}
			else AfxMessageBox("ע�ͻ�CDATA�����ʶ�����ֱ�ΪNOTE��CDATA");
		}
		else AfxMessageBox("����·�����۸�");
		rem:
		//ȡ��һ��·������һ��·��
		listVisit.pop_front();
	}
	//ȡ��ָ����еĵ�һ�����и�ֵ
	if(nLast == 1 || nLast == 2 || nLast == 4){
		//��ָ����е�һ��ָ����ָlist��գ�Ȼ����ϲ�ָ����ѭ��Ѱ�ҵ�һ��ָ�����ڵ�Cxml��Ȼ���޸ĸ�ֵ
		list<Cxml>* plistXmlFirst = (*listplistXml.begin());
		plistXmlFirst->clear();
		for(auto itplistXmlTemp = plistXmlTemp->begin();itplistXmlTemp != plistXmlTemp->end();itplistXmlTemp++){
			if(&(itplistXmlTemp->listXml) == plistXmlFirst){
				itplistXmlTemp->strOneXmlValue = strValue;
				break;
			}
		}
	}
	else if(nLast == 3 || nLast == 5);
	else AfxMessageBox("����·�����۸�");

	listVisit.clear();
	listintStorage.clear();
	listCStringStorage.clear();
	return *this;
}

Cxml Cxml::operator=(int nValue){
	CString strTemp;
	strTemp.Format("%d",nValue);
	*this = strTemp;
	return *this;
}

Cxml Cxml::operator=(double dValue){
	CString strTemp;
	strTemp.Format("%lf",dValue);
	*this = strTemp;
	return *this;
}

CString Cxml::toValue(){
	//�������·��������ֱ�ӷ���
	if(bVisit == 0){
		bVisit = 1;
		return "-1";
	}
	//��Ž��
	CString strResult = "-1";
	//����һ��ָ��أ���ŷ��Ͽ��ܵ�����ָ�룬�ȴ����һ����listXml��ָ��
	list<list<Cxml>*> listplistXml;
	//�ϲ�ָ��
	Cxml* pPreXmlTemp = this;
	//�ϲ�ָ���
	list<Cxml*> listpPrelistXml;
	listplistXml.push_back(&listXml);
	listpPrelistXml.push_back(this);
	//����������ʱ������һ���洢��һ���ڵ�·����һ���洢CString
	list<int> listVisitTemp;
	list<CString> listCStringStorageTemp;
	list<Cxml> listXmlTemp;
	listXmlTemp.push_back(*this);
	//����ָ��
	list<Cxml>* plistXmlTemp = &listXmlTemp;
	//ȡ��listVisit�����һ�����������ֵ�ж�
	int nLast = listVisit.back();
	//ѭ����·��û��Ϊֹ
	while(listVisit.size() != 0){
		//����ǽڵ�
		if(listVisit.front() == 1){
			//ȡ���ڵ���������ʱ�����������ڵ���
			CString strNode = *listCStringStorage.begin();
			listCStringStorage.pop_front();
			listVisitTemp.clear();
			listVisitTemp.push_back(1);
			listCStringStorageTemp.clear();
			listCStringStorageTemp.push_back(strNode);

			//ȡ��ָ��list�е�һ��ָ�룬ѭ���ӵ�һ��ָ��ָ��list�в���
			plistXmlTemp = *listplistXml.begin();
			//ȡ����һ��֮�����գ������������²�Ķ��ָ��
			listplistXml.clear();
			listpPrelistXml.clear();
			for(auto itXml = plistXmlTemp->begin();itXml != plistXmlTemp->end();itXml++){
				//������ҵ��ýڵ�
				if(itXml->strOneXmlName == strNode){
					//����һ��Cxmlָ�븳ֵ����ʱ����
					listplistXml.push_back(&(itXml->listXml));
					listpPrelistXml.push_back(&(*itXml));
					pPreXmlTemp = &(*(plistXmlTemp->begin()));
				}
			}
			//���Ϊ��˵��û�ҵ��ýڵ㣬���ش���
			if(listplistXml.size() == 0) goto Exit;
		}
		else if(listVisit.front() == 2){
			//ȡ���������洢����
			int n = *listintStorage.begin();
			listintStorage.pop_front();

			//���ָ�����û�и�λ�õ�ָ��
			if(listplistXml.size() <= (unsigned int)n) goto Exit;
			else{
				int nTemp = n;
				auto itlistplistXml = listplistXml.begin();
				auto itlistpPrelistXml = listpPrelistXml.begin();
				while(nTemp-- != 0){
					itlistplistXml++;
					itlistpPrelistXml++;
				}
				//ȡ��ָ�����ָ�����Ǹ�ָ�룬�����ָ��أ��ٷ���ָ�����Ǹ�
				list<Cxml>* plistXmlTemp = *itlistplistXml;
				listplistXml.clear();
				listpPrelistXml.clear();
				listplistXml.push_back(plistXmlTemp);
				listpPrelistXml.push_back(&(plistXmlTemp->back()));
			}
		}
		else if(listVisit.front() == 3){
			//ȡ����������������
			CString strAttriName = *listCStringStorage.begin();
			listCStringStorage.pop_front();
			//Ĭ�ϰ��յ�һ����
			auto itAttriName = (*listplistXml.begin())->begin()->mapAttri.find(strAttriName);
			if(itAttriName != (*listplistXml.begin())->begin()->mapAttri.end()){
				strResult = itAttriName->second;
				goto Exit;
			}
		}
		else if(listVisit.front() == 4){
			//ȡ��������������ֵ
			CString strAttriName = *listCStringStorage.begin();
			CString strAttriValue = *(++listCStringStorage.begin());
			listCStringStorage.pop_front();
			listCStringStorage.pop_front();
			//��ָ�����Ѱ���Ƿ��з�����������Ľڵ㣬���û����ȫ�����½���
			//�Ȱ�������������ֵ������ʱlist��
			listCStringStorageTemp.push_back(strAttriName);
			listCStringStorageTemp.push_back(strAttriValue);
			//����һ����ʱָ���
			list<list<Cxml>*> listplistXmlTemp;
			//����һ����ʱ�ϲ�ָ���
			list<Cxml*> listpPrelistTemp;
			//auto itlistpPrelistXml = listpPrelistXml.begin();
			for(auto itlistplistXml = listplistXml.begin();itlistplistXml != listplistXml.end();itlistplistXml++){
				//���ϲ�ָ���map�н��бȽ�
				map<CString,CString>* pmapAttriTemp = &((*listpPrelistXml.begin())->mapAttri);
				//����ҵ�����������ѵ�ǰ��ָ��ŵ���ʱָ�����
				if(pmapAttriTemp->find(strAttriName) != pmapAttriTemp->end() && (*pmapAttriTemp)[strAttriName] == strAttriValue){
					listplistXmlTemp.push_back(*itlistplistXml);
					//��������ȵľͰ��ϲ�ָ���еĵ�һ���Ž���ʱ�ϲ�ָ�����
					listpPrelistTemp.push_back(listpPrelistXml.front());
				}
				//�����ϵ��ϲ�ָ�뵯��
				listpPrelistXml.pop_front();
			}
			//����ʱָ��ظ�ֵ��ָ���
			listplistXml = listplistXmlTemp;
			listpPrelistXml = listpPrelistTemp;
			//�����ʱָ�����ȻΪ�գ�˵�����ʴ���
			if(listplistXml.size() == 0) goto Exit;
		}
		else if(listVisit.front() == 5){
			CString strNOTECDATA = *listCStringStorage.begin();
			int nFlag = *listintStorage.begin();
			if(strNOTECDATA == "NOTE"){
				if(nFlag == -1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlNOTE->listXml.begin();itlistXml != pxmlNOTE->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							for(auto itlistNote = pxmlNOTE->listNote.begin();itlistNote != pxmlNOTE->listNote.end();itlistNote++){
								if(itlistNote->nPosition == nPositionTemp){
									strResult = itlistNote->strNoteData;
									goto Exit;
								}
							}
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlNOTE->listXml.begin();itlistXml != pxmlNOTE->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							for(auto itlistNote = pxmlNOTE->listNote.begin();itlistNote != pxmlNOTE->listNote.end();itlistNote++){
								if(itlistNote->nPosition == nPositionTemp + 1){
									strResult = itlistNote->strNoteData;
									itlistNote->strNoteData;
								}
							}
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 0){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlNOTE = FindPrepXml(plistXmlFirst);

					for(auto itlistNote = pxmlNOTE->listNote.begin();itlistNote != pxmlNOTE->listNote.end();itlistNote++){
						if(itlistNote->nPosition == 0){
							strResult = itlistNote->strNoteData;
							goto Exit;
						}
					}

					goto rem;
				}
				else AfxMessageBox("��ʶ�����ֱ�Ϊ-1��0��1");
			}
			else if(strNOTECDATA == "CDATA"){
				if(nFlag == -1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlCDATA->listXml.begin();itlistXml != pxmlCDATA->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							for(auto itlistNote = pxmlCDATA->listCDATA.begin();itlistNote != pxmlCDATA->listCDATA.end();itlistNote++){
								if(itlistNote->nPosition == nPositionTemp){
									strResult = itlistNote->strNoteData;
									goto Exit;
								}
							}
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 1){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(FindPrepXml(plistXmlFirst));
					int nPositionTemp = 0;
					for(auto itlistXml = pxmlCDATA->listXml.begin();itlistXml != pxmlCDATA->listXml.end();itlistXml++){
						if(FindPrepXml(plistXmlFirst) == &(*itlistXml)){
							for(auto itlistNote = pxmlCDATA->listCDATA.begin();itlistNote != pxmlCDATA->listCDATA.end();itlistNote++){
								if(itlistNote->nPosition == nPositionTemp + 1){
									strResult = itlistNote->strNoteData;
									goto Exit;
								}
							}
							goto rem;
						}
						nPositionTemp++;
					}
				}
				else if(nFlag == 0){
					//��ע�ͻ�CDATA��ָ������ָ�붼���²�ָ��
					list<Cxml>* plistXmlFirst = *listplistXml.begin();
					Cxml* pxmlCDATA = FindPrepXml(plistXmlFirst);
					for(auto itlistNote = pxmlCDATA->listCDATA.begin();itlistNote != pxmlCDATA->listCDATA.end();itlistNote++){
						if(itlistNote->nPosition == 0){
							strResult = itlistNote->strNoteData;
							goto Exit;
						}
					}
					goto rem;
				}
				else AfxMessageBox("��ʶ�����ֱ�Ϊ-1��0��1");
			}
			else AfxMessageBox("ע�ͻ�CDATA�����ʶ�����ֱ�ΪNOTE��CDATA");
		}
		else AfxMessageBox("����·�����۸�");
rem:
		//ȡ��һ��·������һ��·��
		listVisit.pop_front();
	}
	//ȡ��ָ����еĵ�һ�����и�ֵ
	if(nLast == 1 || nLast == 2 || nLast == 4){
		//��ָ����е�һ��ָ����ָlist��գ�Ȼ����ϲ�ָ����ѭ��Ѱ�ҵ�һ��ָ�����ڵ�Cxml��Ȼ���޸ĸ�ֵ
		list<Cxml>* plistXmlFirst = (*listplistXml.begin());
		plistXmlFirst->clear();
		for(auto itplistXmlTemp = plistXmlTemp->begin();itplistXmlTemp != plistXmlTemp->end();itplistXmlTemp++){
			if(&(itplistXmlTemp->listXml) == plistXmlFirst){
				strResult = itplistXmlTemp->strOneXmlValue;
				goto Exit;
			}
		}
	}
	else if(nLast == 3 || nLast == 5);
	else AfxMessageBox("����·�����۸�");

Exit:
	listVisit.clear();
	listintStorage.clear();
	listCStringStorage.clear();
	return strResult;
}

Cxml* Cxml::FindPrepXmlFromXml(Cxml* pxml,list<Cxml>* plistXml){
	Cxml* xmlResult = pxml;
	if(&(xmlResult->listXml) == plistXml) return xmlResult;
	else{
		if(xmlResult->listXml.size() == 0) return NULL;
		for(auto itlistXml = xmlResult->listXml.begin();itlistXml != xmlResult->listXml.end();itlistXml++){
			Cxml* xmlTemp = FindPrepXmlFromXml(&(*itlistXml),plistXml);
			if(xmlTemp != NULL) return xmlTemp;
		}
	}
	return NULL;
}

Cxml* Cxml::FindPrepXml(list<Cxml>* plistXml){
	return FindPrepXmlFromXml(this,plistXml);
}

Cxml* Cxml::FindPrepXmlFromXml(Cxml* pxml,Cxml* pFindXml){
	Cxml* xmlResult = pxml;
	if(xmlResult->listXml.size() == 0) return NULL;
	for(auto itlistXml = xmlResult->listXml.begin();itlistXml != xmlResult->listXml.end();itlistXml++){
		if(&(*itlistXml) == pFindXml) return xmlResult;
		else{
			Cxml* xmlTemp = FindPrepXmlFromXml(&(*itlistXml),pFindXml);
			if(xmlTemp != NULL) return xmlTemp;
		}
	}
	return NULL;
}

Cxml* Cxml::FindPrepXml(Cxml* pFindXml){
	if(this == pFindXml) return NULL;
	return FindPrepXmlFromXml(this,pFindXml);
}


int main(){
	//double a = 0;
	//if(a != 0) AfxMessageBox("1");
	//
	Cxml xml;
	xml["aaa"]["bbb"] = 1;
	xml["aaa"]("a","1")["ccc"](2)["ddd"]["eee"] = 1;
	xml["aaa"]("a","1")("b","2")["ccc"](2)["ddd"]["eee"] = 1;
	xml["aaa"]("a","1")("b","2")["ccc"](2)["ddd"]["eee"] = 1;
	xml["aaa"]("a","1")("b","2")["ccc"](2)["ddd"]["eee"] = 1;
	xml["aaa"]("a","1")("b","2")["ccc"](2)["ddd"]("n","3.4")["eee"] = 2;
	xml["aaa"]("a","1")("b","2")("c","3")(2)("CDATA",0) = "1";

	CString str = xml["aaa"]["bbb"].toValue();

	//CString str = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><!--by months--> <class_list a=\'1\' b=\"2\">  		<student a=\"3\" b=\'\"6\"\'>  		<!--Shdds--><name/>  <!--Shs--><![CDATA[123456<<<>>>789]]><grade>A</grade>  		</student>  		</class_list>";
	//xml["aaa"] = 1;
	//xml.Load(str);
	CString strXml = xml.toCString();
	AfxMessageBox(strXml);
	int x = 3;
	return 0;
}