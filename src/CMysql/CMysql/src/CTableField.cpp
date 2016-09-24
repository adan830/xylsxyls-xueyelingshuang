#include <SDKDDKVer.h>
#include "CTableField.h"
#include "CValue.h"
#include "CCondition.h"

CTableField CTableField::operator()(CString Table){
	this->Table = Table;
	return *this;
}

CTableField CTableField::operator[](CString Field){
	this->Field = Field;
	return *this;
}

CTableField::CTableField(){

}

CTableField::CTableField(const CTableField& tf){
	this->Table = tf.Table;
	this->Field = tf.Field;
}

CTableField CTableField::operator=(const CTableField& tf){
	this->Table = tf.Table;
	this->Field = tf.Field;
	return *this;
}

CTableField::CTableField(CString Table,CString Field){
	this->Table = Table;
	this->Field = Field;
}

CCondition CTableField::operator==(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s=%s)",Table,Field,value.strValue);
	return con;
}

CCondition CTableField::operator!=(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s!=%s)",Table,Field,value.strValue);
	return con;
}

CCondition CTableField::operator<(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s<%s)",Table,Field,value.strValue);
	return con;
}

CCondition CTableField::operator>(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s>%s)",Table,Field,value.strValue);
	return con;
}

CCondition CTableField::operator<=(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s<=%s)",Table,Field,value.strValue);
	return con;
}

CCondition CTableField::operator>=(const CValue& value){
	CCondition con;
	con.strSQL.Format("(%s.%s>=%s)",Table,Field,value.strValue);
	return con;
}

//�������
CCondition CTableField::operator&&(const CTableField& tf){
	CCondition con;
	con.strSQL.Format("(%s inner join %s on %s.%s=%s.%s)",Table,tf.Table,Table,Field,tf.Table,tf.Field);
	return con;
}

//�����ϣ���ߵ�������С�ڵ����ұߵ�������
CCondition CTableField::operator<=(const CTableField& tf){
	CCondition con;
	con.strSQL.Format("(%s left outer join %s on %s.%s=%s.%s)",Table,tf.Table,Table,Field,tf.Table,tf.Field);
	return con;
}

//�����ϣ���ߵ����������ڵ����ұߵ�������
CCondition CTableField::operator>=(const CTableField& tf){
	CCondition con;
	con.strSQL.Format("(%s right outer join %s on %s.%s=%s.%s)",Table,tf.Table,Table,Field,tf.Table,tf.Field);
	return con;
}

CCondition CTableField::operator||(const CTableField& tf){
	CCondition con;
	con.strSQL.Format("(%s full outer join %s on %s.%s=%s.%s)",Table,tf.Table,Table,Field,tf.Table,tf.Field);
	return con;
}