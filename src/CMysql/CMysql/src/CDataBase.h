�}�6  �  �gF'�������R1���S�����y[=y�٣z�A�d�����g�n�S�nKN��Ԭ��VC�3��C�j7��A�����ˁ�I[vH)o�����@�T�10�4���|@�@s�0v�zY$���nYF�����5j�a���R�շ� ��v�."*��~�ԗ������Yʺ8Xg��4#l��؄��u#%&>^�<	�O	}�툮|���77ވ�E���\4G2P��]5��Ś���!lt<ҷ�p�K���7��8L�)m��vw�v��'�*G�!n�T�h iK�q׋)2)\����D���L�(PV��am}pU:`�l9=m�g�}I��Q���$/}�/q�\*�@L䑟 
)P3g+ú8�0�ƃ ��^*?<0=�"���2� �	 :�zp̖� !e��5�b+��z���|5�,J3�x �3{�����F��k�\��xI�M f`�r�Ga��[����A,ttring User,CString PassWord,CString dbName);

public:
	//����
	CTable* CreateTable(CString TableName,CString FieldName,BOOL type,int length,bool ifExists = 1,bool AutoCommit = 1);
	//ɾ��
	int DropTable(CString TableName,bool ifExists = 1);
	//�򿪱��ӿ�
	CTable* OpenTableInterface(CString TableName,bool AutoCommit = 1);
	//�رձ��ӿ�
	void CloseTableInterface(CTable* pTable);
};