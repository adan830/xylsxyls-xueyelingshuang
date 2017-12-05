#include "stdafx.h"
#include "DataNeuron.h"
#include "FundHelper.h"
#include "CStringManager/CStringManagerAPI.h"

DataNeuron::DataNeuron()
{

}

double DataNeuron::ForecastData(int32_t days)
{
	if (m_preData == nullptr)
	{
		return 0;
	}
	std::vector<DataNeuron> vecDataNeuron;
	int32_t dayBk = days;
	DataNeuron* thisNeuron = this;
	while (dayBk-- != 0)
	{
		vecDataNeuron.push_back(*thisNeuron);
		if (thisNeuron->m_preData == nullptr)
		{
			return 0;
		}
		thisNeuron = thisNeuron->m_preData;
	}

	double updata = 0;
	//��õ��ǵ�ʱԤ�������
	std::map<double, std::vector<DataNeuron*>> mapUpData;
	m_preData->AnalyzeData(vecDataNeuron, 0, updata, mapUpData);
	double all = 0;
	//ȡ��1���µķ���
	for (auto itUpdata = mapUpData.begin(); itUpdata != mapUpData.end(); ++itUpdata)
	{
        std::vector<DataNeuron*>& vecNeuron = itUpdata->second;
        int32_t index = -1;
        while (index++ != vecNeuron.size() - 1)
        {
            if (Condition(itUpdata->first, vecNeuron[index]))
            {
                all += (1 / itUpdata->first) * itUpdata->second.size();
            }
        }
	}

	double forecast = 0;
	for (auto itUpdata = mapUpData.begin(); itUpdata != mapUpData.end(); ++itUpdata)
	{
        std::vector<DataNeuron*>& vecNeuron = itUpdata->second;
        int32_t index = -1;
        while (index++ != vecNeuron.size() - 1)
        {
            if (Condition(itUpdata->first, vecNeuron[index]))
            {
                forecast += vecNeuron[index]->m_dayChg * ((1 / itUpdata->first) / all);
            }
        }
	}

	/**/

    
    //AfxMessageBox(CStringManager::Format("%.2lf%%", forecast * 100).c_str());
	int x = 3;
    return forecast;
}

bool DataNeuron::Condition(double variance, DataNeuron* forecastNeuron)
{
    return variance < 1 && (forecastNeuron->m_time > IntDateTime("2013-01-01 00:00:00"));
}

void DataNeuron::AnalyzeData(const std::vector<DataNeuron>& vecDataNeuron,
							 int32_t index,
							 double& updata,
							 std::map<double, std::vector<DataNeuron*>>& mapUpData)
{
	updata += FundHelper::Square(vecDataNeuron[index].m_dayChg * 100 - m_dayChg * 100);
	++index;
	//�����ĩβ�˾�����
	if (index == (int32_t)vecDataNeuron.size())
	{
		DataNeuron* upNeuron = GetNextNeuron((int32_t)vecDataNeuron.size());
		if (upNeuron != nullptr)
		{
			mapUpData[updata].push_back(upNeuron);
		}
	}
	//���û��ĩβ������һ����Ԫ������
	else
	{
		if (m_preData == nullptr)
		{
			return;
		}
		m_preData->AnalyzeData(vecDataNeuron, index, updata, mapUpData);
		//���index��1����ô�Ŵ��ݵ���һ����Ԫ������Ԫ��ͷ��
		if (index == 1)
		{
			double newUpdata = 0;
			m_preData->AnalyzeData(vecDataNeuron, 0, newUpdata, mapUpData);
		}
	}
}

DataNeuron* DataNeuron::GetPreNeuron(int32_t days)
{
	DataNeuron* thisNeuron = this;
	while (days-- != 0)
	{
		if (thisNeuron->m_preData == nullptr)
		{
			return nullptr;
		}
		thisNeuron = thisNeuron->m_preData;
	}
	return thisNeuron;
}

DataNeuron* DataNeuron::GetNextNeuron(int32_t days)
{
	DataNeuron* thisNeuron = this;
	while (days-- != 0)
	{
		if (thisNeuron->m_nextData == nullptr)
		{
			return nullptr;
		}
		thisNeuron = thisNeuron->m_nextData;
	}
	return thisNeuron;
}